using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

namespace GameGen
{
    class GameObject
    {
        public String ClassName;
        public String BaseClassName;
        public SortedSet<Include> HeaderIncludes = new SortedSet<Include>();
        public SortedSet<Include> SourceIncludes = new SortedSet<Include>();
        public List<SimpleMember> SimpleMembers = new List<SimpleMember>();
        public List<ContainerMember> ContainerMembers = new List<ContainerMember>();
        public List<Function> Functions = new List<Function>();
        
        public static GameObject Parse(string source)
        {
            Lexer lexer = new Lexer(source);
            GameObject obj = new GameObject();
            obj.HeaderIncludes.Add(new Include("types"));

            obj.ClassName = lexer.ReadToken();
            lexer.SkipToken(); // :
            obj.BaseClassName = lexer.ReadToken();

            string classContents = lexer.ReadBlock("{", "}");
            GameObject.ParseClassBody(classContents, obj);

            return obj;
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

        public static String Postprocess(String source)
        {
            String output = CompactWhitespace(source);
            output = output.Replace("#pragma once", "#pragma once\n\n"); 
            output = output.Replace(".h\"", ".h\"\n");
            output = output.Replace("namespace", "\nnamespace");
            output = output.Replace("public:", "public:\n"); 
            output = output.Replace(";", ";\n");
            output = output.Replace(" ( ", "(").Replace(" ) ", ")").Replace(" ;", ";");
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
            return output;
        }

        public static void ParseClassBody(string source, GameObject obj)
        {
            Lexer lexer = new Lexer(source);

            while (lexer.HasNext())
            {
                if (lexer.PeekToken(2) == ";") // Member definition without initial value
                {
                    SimpleMember member = new SimpleMember();
                    member.Type = new Type(lexer.ReadToken());
                    member.Name = lexer.ReadToken();
                    member.InitialValue = null;
                    lexer.SkipToken(); // ";"
                    obj.SimpleMembers.Add(member);
                }
                if (lexer.PeekToken(2) == "=") // Member definition with initial value
                {
                    SimpleMember member = new SimpleMember();
                    member.Type = new Type(lexer.ReadToken());
                    member.Name = lexer.ReadToken();
                    member.InitialValue = new Value(member.Type, lexer.ReadBlock("=", ";"));
                    obj.SimpleMembers.Add(member);
                }
                if (lexer.PeekToken(1) == "<") // Container definition with initial value
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
                }
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
        }

        public string ExportHeader()
        {
            string simpleMembers = "";
            foreach (SimpleMember member in SimpleMembers)
            {
                string type = member.Type.IsPrimitive() ? member.Type.Name : String.Format("Ptr<{0}>", member.Type.Name);
                simpleMembers += String.Format("{0} {1};", type, member.Name);
            }

            string containerMembers = "";
            foreach (ContainerMember member in ContainerMembers)
            {
                string type = member.Type.IsPrimitive() ? member.Type.Name : String.Format("Ptr<{0}>", member.Type.Name);
                containerMembers += String.Format("{0}<{1}> {2};", member.ContainerType, type, member.Name);
            }

            string functions = "";
            foreach (Function function in Functions)
                functions += String.Format("{0} {1}({2}){3}", function.ReturnType, function.Name, function.Arguments, function.Inline ? ("{" + function.Body + "}") : ";");

            String output = Preprocess(File.ReadAllText("Templates/HeaderTemplate.txt"));
            string includes = "";
            foreach (Include include in HeaderIncludes)
                includes += String.Format("#include \"{0}.h\"", include.FileName);
            output = output.Replace("[HeaderIncludes]", includes);
            output = output.Replace("[Namespace]", "Test");
            output = output.Replace("[ClassName]", ClassName);
            output = output.Replace("[BaseClass]", BaseClassName);
            output = output.Replace("[FunctionDefinitions]", functions);
            output = output.Replace("[Members]", simpleMembers + containerMembers);

            return Postprocess(output);
        }

        public string ExportCpp()
        {
            string functions = "";

            AddFunctionIfNotDefined("Initialize", "void");

            var allMembers = new List<Member>();
            allMembers.AddRange(SimpleMembers);
            allMembers.AddRange(ContainerMembers);

            foreach(Member member in allMembers)
            {
                if (!member.Type.IsPrimitive())
                    SourceIncludes.Add(new Include(member.InitialValue.Type.Name));
            }

            foreach (Function function in Functions)
            {
                if (function.Inline)
                    continue;

                if (function.Name == "Initialize")
                {
                    string members = "";
                    foreach (SimpleMember member in SimpleMembers)
                    {
                        if (member.InitialValue != null)
                            members += member.Name + " = " + member.InitialValue.Val + ";";
                    }
                    foreach (ContainerMember member in ContainerMembers)
                    {
                        members += member.Name + " = [" + member.InitialValue.Val + "];";     
                    }
                    function.Body = members + function.Body;
                }
                functions += String.Format("{0} {1}::{2}({3}){{{4}}}", function.ReturnType, ClassName, function.Name, function.Arguments, function.Body);
            }

            string output = Preprocess(File.ReadAllText("Templates/CppTemplate.txt"));
            
            string includes = "";
            foreach (Include include in SourceIncludes)
                includes += String.Format("#include \"{0}.h\"", include.FileName);
            output = output.Replace("[SourceIncludes]", includes);
            output = output.Replace("[Namespace]", "Test");
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
                Functions.Add(new Function() { Name = name, ReturnType = returnType });
        }
    }
}
