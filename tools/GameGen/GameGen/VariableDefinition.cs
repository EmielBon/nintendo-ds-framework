using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GameGen
{
    class VariableDefinition : Statement
    {
        public String Type;
        public String VariableName;
        public Expression Value; // optional

        public VariableDefinition(String name, String type, String value = "")
        {
            VariableName = name;
            Type = type;
            Value = Expression.Parse(value);
        }

        public override string ToString(int depth)
        {
            var str = "";
            var tabs = GetTabs(depth);

            str += tabs + GetType().Name + "\n";
            str += tabs + GetTabs(1) + Type + " " + VariableName + "\n";
            str += Value.ToString(depth + 1);

            return str;
        }
    }
}
