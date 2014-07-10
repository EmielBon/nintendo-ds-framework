using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GameGen
{
    class ClassDefinition
    {
        public String ClassName;
        public String BaseClassName;
        public List<Member> Members = new List<Member>();
        public List<Function> Functions = new List<Function>();

        public static ClassDefinition Parse(Lexer lexer)
        {

            var className = lexer.ReadToken();
            lexer.SkipToken(); // :
            var baseClassName = lexer.ReadToken();
            var body = lexer.ReadBlock("{", "}");
            return new ClassDefinition(className, baseClassName, body);
        }

        public ClassDefinition(String className, String baseClassName, String body)
        {
            ClassName     = className;
            BaseClassName = baseClassName;
            ParseClassBody(body);
            AddFunctionIfNotDefined("void Initialize");
            Console.WriteLine(ToString(0));
        }

        private void ParseClassBody(String body)
        {
            Lexer lexer = new Lexer(body);

            while (lexer.HasNext())
            {
                if (lexer.PeekToken(2) == ";") // Member definition without initial value
                {
                    var member = CreateMember(lexer.ReadToken(), lexer.ReadToken());
                    lexer.SkipToken(); // ;
                    Members.Add(member);
                }
                if (lexer.PeekToken(2) == "=") // Member definition with initial value
                {
                    var member = CreateMember(lexer.ReadToken(), lexer.ReadToken(), lexer.ReadBlock("=", ";"));
                    Members.Add(member);
                }
                if (lexer.PeekToken(2) == "(") // Function definition
                {
                    Function function = Function.Parse(
                        lexer.ReadToken(), // return type
                        lexer.ReadToken(), // name
                        lexer.ReadBlock("(", ")"), // arguments 
                        lexer.ReadBlock("{", "}")); // body
                    Functions.Add(function);
                }
            }
        }

        public void AddFunctionIfNotDefined(String signature)
        {
            String type = signature.Split()[0];
            String name = signature.Split()[1];

            bool found = false;
            foreach (var function in Functions)
                found |= (function.Name == name);

            if (!found)
                Functions.Insert(0, new Function() { Name = name, ReturnType = type, Body = new Block()});
        }

        private static Member CreateMember(String type, String name, String initialValue = null)
        {
            Member member = new Member();
            member.Type = type;
            member.InitialValue = initialValue;
            member.Name = name;
            return member;
        }

        public string ToString(int depth)
        {
            var str = String.Format("{0} : {1}\n", ClassName, BaseClassName);

            foreach (var member in Members)
                str += member.ToString(depth + 1) + "\n";

            str += "\n";

            foreach (var function in Functions)
                str += function.ToString(depth + 1) + "\n";

            return str;
        }
    }
}
