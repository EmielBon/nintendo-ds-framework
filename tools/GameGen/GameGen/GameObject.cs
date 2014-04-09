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
        public List<Member> Members = new List<Member>();
        public List<Assignment> Assignments = new List<Assignment>();
        public List<Function> Functions = new List<Function>();

        public static GameObject Parse(string source)
        {
            Lexer lexer = new Lexer(source);
            GameObject obj = new GameObject();

            obj.ClassName = lexer.ReadToken();
            lexer.SkipToken(); // :
            obj.BaseClassName = lexer.ReadToken();

            string classContents = lexer.ReadBlock("{", "}");
            GameObject.ParseClassBody(classContents, obj);

            return obj;
        }

        public static void ParseClassBody(string source, GameObject obj)
        {
            Lexer lexer = new Lexer(source);

            while (lexer.HasNext())
            {
                if (lexer.PeekToken(1) == "=") // Variable assignment
                {
                    Assignment assignment = new Assignment();
                    assignment.VariableName = lexer.ReadToken();
                    lexer.SkipToken(); // "="
                    assignment.Value = lexer.ReadToken();
                    lexer.SkipToken(); // ";"
                    obj.Assignments.Add(assignment);
                }
                if (lexer.PeekToken(2) == "=") // Member definition
                {
                    Member member = new Member();
                    member.Type = lexer.ReadToken();
                    member.Name = lexer.ReadToken();
                    lexer.SkipToken(); // "="
                    member.InitialValue = lexer.ReadToken();
                    lexer.SkipToken(); // ";"
                    obj.Members.Add(member);
                }
                if (lexer.PeekToken(2) == "(") // Function definition
                {
                    Function function = new Function();
                    function.ReturnType = lexer.ReadToken();
                    function.Name = lexer.ReadToken();
                    function.Arguments = lexer.ReadBlock("(", ")");
                    function.Body = lexer.ReadBlock("{", "}").Replace(" ( ", "(").Replace(" ) ", ")").Replace(" ;", ";");
                    obj.Functions.Add(function);
                }
            }
        }

        public string ExportHeader()
        {
            string template = File.ReadAllText("Templates/HeaderTemplate.txt");

            string members = "";
            foreach (Member member in Members)
                members += String.Format("{0} {1};\n", member.Type, member.Name);

            string functions = "";
            foreach (Function function in Functions)
                functions += String.Format("\t\t{0} {1}({2});\n\n", function.ReturnType, function.Name, function.Arguments);

            return String.Format(template, ClassName, BaseClassName, members, functions);
        }

        public string ExportCpp()
        {
            string template = File.ReadAllText("Templates/CppTemplate.txt");

            string functions = "";
            foreach (Function function in Functions)
            {
                if (function.Name == "Initialize")
                {
                    string assignments = "";
                    foreach (Assignment assignment in Assignments)
                        assignments += assignment.VariableName + " = New<" + assignment.Value + ">();\n\t\t";
                    function.Body = assignments + function.Body;
                }
                function.Body = function.Body.Replace("; ", ";\n\t\t");
                function.Body = function.Body.Replace("{ ", "\n\t\t{\n\t\t");
                function.Body = function.Body.Replace(" }", "\n\t\t}\n");
                functions += String.Format("\t{0} {1}::{2}({3})\n\t{{\n\t\t{4}\n\t}}\n\n", function.ReturnType, ClassName, function.Name, function.Arguments, function.Body);
            }

            return String.Format(template, ClassName, functions);
        }
    }
}
