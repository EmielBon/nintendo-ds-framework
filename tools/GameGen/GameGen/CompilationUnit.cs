using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

namespace GameGen
{
    class CompilationUnit
    {
        public DSLProject Project;
        public ClassDefinition ClassDefinition;
        public SortedSet<Include> HeaderIncludes = new SortedSet<Include>();
        public SortedSet<Include> SourceIncludes = new SortedSet<Include>();
        
        public static CompilationUnit Parse(string sourceFile, DSLProject project)
        {
            String sourceText = File.ReadAllText(sourceFile);
            return new CompilationUnit(project, sourceText);
        }

        public CompilationUnit(DSLProject project, String sourceText)
        {
            Project = project;

            Lexer lexer = new Lexer(sourceText);
            HeaderIncludes.Add(new Include(project.Name + "Types"));

            ClassDefinition = ClassDefinition.Parse(lexer);
        }

        public static String CompactWhitespace(String source)
        {
            return Regex.Replace(source, @"\s+", " ");
        }

        public static String Preprocess(String source)
        {
            String output = CompactWhitespace(source);
            return output;
        }

        public String Postprocess(String source)
        {
            String output = source;
            output = output.Replace(" ( ", "(").Replace(" ) ", ")");
            output = output.Replace(" [ ", "[").Replace(" ] ", "]");
            output = output.Replace(" < ", "<").Replace(" >", ">");
            output = output.Replace(" ;", ";");
            
            return output;
        }

        public string GenerateHeader()
        {
            string members = "";
            foreach (Member member in ClassDefinition.Members)
            {
                string type = member.Type.MetaType == MetaType.ReferenceType ? String.Format("Ptr<{0}>", member.Type.Name) : member.Type.Name;
                members += String.Format("{0} {1};", type, member.Name);
            }
            
            string functions = "";
            foreach (Function function in ClassDefinition.Functions)
                functions += String.Format("{0} {1}({2}){3}", function.ReturnType, function.Name, function.Arguments, function.Inline ? ("{" + function.Body + "}") : ";");

            String output = Preprocess(File.ReadAllText("Templates/HeaderTemplate.txt"));
            string includes = "#pragma once\n\n";
            foreach (Include include in HeaderIncludes)
                includes += String.Format("#include \"{0}.h\"\n", include.FileName);
            output = output.Replace("[HeaderIncludes]", includes + "\n");
            output = output.Replace("[ClassName]", ClassDefinition.ClassName);
            output = output.Replace("[BaseClass]", ClassDefinition.BaseClassName);
            output = output.Replace("[FunctionDefinitions]", functions);
            output = output.Replace("[Members]", members /*+ containerMembers*/);

            return Postprocess(output);
        }

        public string GenerateCpp()
        {
            string functions = "";

            var allMembers = new List<Member>();
            allMembers.AddRange(ClassDefinition.Members);

            foreach (Member member in allMembers)
            {
                // Add relevant includes for members of locally defined types
                if (member.Type.DeclarationType == DeclarationType.Local)
                    SourceIncludes.Add(new Include(member.Type.Name));
            }

            foreach (Function function in ClassDefinition.Functions)
            {
                if (function.Inline)
                    continue;

                if (function.Name == "Initialize")
                {
                    string members = "";
                    foreach (Member member in ClassDefinition.Members)
                    {
                        if (member.InitialValue != null)
                            members += member.Name + " = " + member.InitialValue + ";";
                    }
                    function.Body = members + function.Body;
                }
                if (function.Name == "LoadContent")
                {
                    function.Body = function.Body.Replace("Load <", "ContentManager::Load <");
                }
                if (function.Name == "Initialize" || function.Name == "LoadContent")
                    function.Body += String.Format("base::{0}();", function.Name);

                if (function.Name == "Update" || function.Name == "Draw")
                {
                    function.Body = function.Body.Replace("ElapsedTime.", "gameTime.ElapsedGameTime.Total");
                    function.Body = function.Body.Replace("IsKey", "KeyPad::GetState().IsKey");
                    function.Body += String.Format("base::{0}(gameTime);", function.Name);
                }

                functions += String.Format("{0} {1}::{2}({3}){{{4}}}\n\n", function.ReturnType, ClassDefinition.ClassName, function.Name, function.Arguments, function.Body);
            }

            string output = Preprocess(File.ReadAllText("Templates/CppTemplate.txt"));

            string includes = String.Format("#include \"{0}.h\"\n", ClassDefinition.ClassName);
            foreach (Include include in SourceIncludes)
                includes += String.Format("#include \"{0}.h\"\n", include.FileName);
            output = output.Replace("[SourceIncludes]", includes + "\n");
            output = output.Replace("[Functions]", functions);

            return Postprocess(output);
        }
    }
}
