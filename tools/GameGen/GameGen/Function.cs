using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GameGen
{
    class Function
    {
        public String Name;
        public List<FunctionParameter> Arguments = new List<FunctionParameter>();
        public Block Body;
        public String ReturnType;

        public static Function Parse(String returnType, String name, String arguments, String body)
        {
            Function function = new Function();
            function.ReturnType = returnType;
            function.Name = name;
            function.ParseArguments(arguments);
            function.Body = Block.Parse(body);

            return function;
        }

        public void ParseArguments(String arguments)
        {
            if (arguments.Trim() == String.Empty) 
                return;

            Lexer lexer = new Lexer(arguments);
            
            while(lexer.HasNext(3))
            {
                Arguments.Add(new FunctionParameter( lexer.ReadToken(), lexer.ReadToken() ));
                lexer.SkipToken();
            }
            Arguments.Add(new FunctionParameter(lexer.ReadToken(), lexer.ReadToken()));
        }

        public string ToString(int depth)
        {
            var args = "";
            foreach (var arg in Arguments)
                args += arg + ",";

            if (args.Length > 0)
                args.Substring(0, args.Length - 1);

            return String.Format("{0}{1} {2} ({3}) \n{4}", Statement.GetTabs(depth), ReturnType, Name, args, Body.ToString(depth + 1));
        }
    }
}
