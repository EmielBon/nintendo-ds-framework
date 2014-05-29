using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

namespace GameGen
{
    class DSLSourceFile
    {
        public DSLProject Project;

        public String ClassName;
        public String BaseClassName;
        public SortedSet<Include> HeaderIncludes = new SortedSet<Include>();
        public SortedSet<Include> SourceIncludes = new SortedSet<Include>();
        public List<Member> Members = new List<Member>();
        public List<ContainerMember> ContainerMembers = new List<ContainerMember>();
        public List<Function> Functions = new List<Function>();

        public static DSLSourceFile Parse(string sourceFile, DSLProject project)
        {
            String source = File.ReadAllText(sourceFile);
            Lexer lexer = new Lexer(source);
            DSLSourceFile obj = new DSLSourceFile(project);
            obj.HeaderIncludes.Add(new Include(project.Name + "Types"));

            obj.ClassName = lexer.ReadToken();
            lexer.SkipToken(); // :
            obj.BaseClassName = lexer.ReadToken();

            string classContents = lexer.ReadBlock("{", "}");
            DSLSourceFile.ParseClassBody(classContents, obj);

            return obj;
        }

        public DSLSourceFile(DSLProject project)
        {
            Project = project;
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
            String output = CompactWhitespace(source);
            output = output.Replace("#pragma once", "#pragma once\n\n"); 
            output = output.Replace(".h\"", ".h\"\n");
            output = output.Replace("namespace", "\nnamespace");
            output = output.Replace("public:", "public:\n"); 
            output = output.Replace(";", ";\n");
            output = output.Replace(" ( ", "(").Replace(" ) ", ")");
            output = output.Replace(" [ ", "[").Replace(" ] ", "]");
            output = output.Replace(" < ", "<").Replace(" >", ">");
            output = output.Replace(" ;", ";");
            output = output.Replace("{", "\n{\n");
            output = output.Replace("}", "}\n");
            output = output.Replace("\n ", "\n");

            String[] lines = output.Split('\n');
            output = "";
            int depth = 0;
            foreach(String line in lines)
            {
                if (line == "}") depth--;
                output += new String('\t', (line == "public:") ? depth-1 : depth);
                output +=  line + "\n";
                if (line == "{") depth++;
            }
            //output = output.Replace("[", "{");          // Correct the formatting for lists
            //output = output.Replace("]", "}");
            
            // Replace all enums . with ::
            foreach (var enumConstant in Project.Enums)
            {
                String name = enumConstant.Name;
                output = output.Replace(name + ".", name + "::");
            }

            return output;
        }

        public static void ParseClassBody(string source, DSLSourceFile obj)
        {
            Lexer lexer = new Lexer(source);

            while (lexer.HasNext())
            {
                if (lexer.PeekToken(2) == ";") // Member definition without initial value
                {
                    var member = CreateMember(lexer.ReadToken(), lexer.ReadToken(), obj);
                    lexer.SkipToken(); // ;
                    obj.Members.Add(member);
                }
                if (lexer.PeekToken(2) == "=") // Member definition with initial value
                {
                    var member = CreateMember(lexer.ReadToken(), lexer.ReadToken(), obj, lexer.ReadBlock("=", ";"));
                    obj.Members.Add(member);
                }
                /*if (lexer.PeekToken(1) == "<") // Container definition with initial value
                {
                    ContainerMember member = new ContainerMember();
                    member.ContainerType = lexer.ReadToken();
                    lexer.SkipToken();          // "<"
                    member.Type = new Type(lexer.ReadToken());
                    lexer.SkipToken();          // ">"
                    member.Name = lexer.ReadToken();
                    lexer.SkipToken();          // "="
                    member.InitialValue = new Value(member.Type, lexer.ReadBlock("[", "]"));
                    lexer.SkipToken(); // ";"
                    obj.ContainerMembers.Add(member);
                }*/
                if (lexer.PeekToken(2) == "(") // Function definition
                {
                    Function function = new Function();
                    function.ReturnType = lexer.ReadToken();
                    function.Name = lexer.ReadToken();
                    function.Arguments = lexer.ReadBlock("(", ")");
                    function.Body = lexer.ReadBlock("{", "}");
                    obj.Functions.Add(function);
                }
                if (lexer.PeekToken(3) == "(" && lexer.PeekToken(0) == "inline") // Function definition
                {
                    Function function = new Function();
                    lexer.SkipToken(); // inline
                    function.ReturnType = lexer.ReadToken();
                    function.Name = lexer.ReadToken();
                    function.Arguments = lexer.ReadBlock("(", ")");
                    function.Body = lexer.ReadBlock("{", "}");
                    function.Inline = true;
                    obj.Functions.Add(function);
                }
            }
            obj.AddFunctionIfNotDefined("Initialize", "void");

            foreach (Function function in obj.Functions)
            {
                if (function.Name == "Update" || function.Name == "Draw")
                {
                    function.Arguments += "const GameTime &gameTime";
                }
            }
        }

        public static Member CreateMember(String type, String name, DSLSourceFile obj, String initialValue = null)
        {
            Member member = new Member();
            member.Type = new Type(type, "nullptr");
            int i = obj.Project.ExternTypes.IndexOf(member.Type);
            if (i != -1)
            {
                member.Type = obj.Project.ExternTypes[i];
                member.InitialValue = member.Type.DefaultValue;
            }
            if (initialValue != null)
            {
                member.InitialValue = initialValue;
            }
                
            else if (member.Type.MetaType == MetaType.ReferenceType)
                member.InitialValue = String.Format("New<{0}>()", member.Type.Name);
            member.Name = name;
            return member;
        }

        public string GenerateHeader()
        {
            string members = "";
            foreach (Member member in Members)
            {
                string type = member.Type.MetaType == MetaType.ReferenceType ? String.Format("Ptr<{0}>", member.Type.Name) : member.Type.Name;
                members += String.Format("{0} {1};", type, member.Name);
            }
            /*
            string containerMembers = "";
            foreach (ContainerMember member in ContainerMembers)
            {
                string type = member.Type.IsPrimitive() ? member.Type.Name : String.Format("Ptr<{0}>", member.Type.Name);
                containerMembers += String.Format("{0}<{1}> {2};", member.ContainerType, type, member.Name);
            }*/

            string functions = "";
            foreach (Function function in Functions)
                functions += String.Format("{0} {1}({2}){3}", function.ReturnType, function.Name, function.Arguments, function.Inline ? ("{" + function.Body + "}") : ";");

            String output = Preprocess(File.ReadAllText("Templates/HeaderTemplate.txt"));
            string includes = "";
            foreach (Include include in HeaderIncludes)
                includes += String.Format("#include \"{0}.h\"", include.FileName);
            output = output.Replace("[HeaderIncludes]", includes);
            output = output.Replace("[ClassName]", ClassName);
            output = output.Replace("[BaseClass]", BaseClassName);
            output = output.Replace("[FunctionDefinitions]", functions);
            output = output.Replace("[Members]", members /*+ containerMembers*/);

            return Postprocess(output);
        }

        public string GenerateCpp()
        {
            string functions = "";

            var allMembers = new List<Member>();
            allMembers.AddRange(Members);
            allMembers.AddRange(ContainerMembers);

            foreach (Member member in allMembers)
            {
                // Add relevant includes for members of locally defined types
                if (member.Type.DeclarationType == DeclarationType.Local)
                    SourceIncludes.Add(new Include(member.Type.Name));
            }

            foreach (Function function in Functions)
            {
                if (function.Inline)
                    continue;

                if (function.Name == "Initialize")
                {
                    string members = "";
                    foreach (Member member in Members)
                    {
                        if (member.InitialValue != null)
                            members += member.Name + " = " + member.InitialValue + ";";
                    }
                    foreach (ContainerMember member in ContainerMembers)
                    {
                        members += member.Name + " = [" + member.InitialValue + "];";     
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

                functions += String.Format("{0} {1}::{2}({3}){{{4}}}", function.ReturnType, ClassName, function.Name, function.Arguments, function.Body);
            }

            string output = Preprocess(File.ReadAllText("Templates/CppTemplate.txt"));
            
            string includes = "";
            foreach (Include include in SourceIncludes)
                includes += String.Format("#include \"{0}.h\"", include.FileName);
            output = output.Replace("[SourceIncludes]", includes);
            output = output.Replace("[ClassName]", ClassName);
            output = output.Replace("[BaseClass]", BaseClassName);
            output = output.Replace("[Functions]", functions);

            return Postprocess(output);
        }

        public void AddFunctionIfNotDefined(String name, String returnType)
        {
            bool found = false;
            foreach (Function function in Functions)
                found |= (function.Name == name);

            if (!found)
                Functions.Insert(0, new Function() { Name = name, ReturnType = returnType });

        }
    }
}
