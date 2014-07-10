using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GameGen
{
    class FunctionCall : Expression 
    {
        public string Name;
        public List<Expression> Arguments = new List<Expression>();

        public FunctionCall() : base("")
        {

        }

        public static new FunctionCall Parse(string functionCall, Dictionary<string, string> SubExpressions = null)
        {
            var call = new FunctionCall();

            call.Name = functionCall.Split('$')[0];
            
            var arguments = SubExpressions[functionCall.Substring(functionCall.Length - 2)];
            var args = arguments.Split(',');
            foreach (var arg in args)
            {
                call.Arguments.Add( Expression.Parse(arg, SubExpressions) );
            }
            return call;
        }

        public override string ToString(int depth)
        {
            var tabs = GetTabs(depth);

            var str = tabs + GetType().Name + " " + Name + "\n" + tabs + "(\n";

            foreach (var arg in Arguments)
                str += arg.ToString(depth + 1) + "\n";

            return str + tabs + ")";
        }
    }
}
