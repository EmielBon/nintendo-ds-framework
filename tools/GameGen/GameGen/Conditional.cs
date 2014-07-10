using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GameGen
{
    class Conditional : Statement
    {
        public Expression Condition;
        public Block Body;

        public Conditional(Expression condition, Block block)
        {
            Condition = condition;
            Body = block;
        }

        public override string ToString(int depth)
        {
            var str = "";
            var tabs = GetTabs(depth);

            str += tabs + GetType().Name + "\n";
            str += Condition.ToString(depth + 1) + "\n";
            str += Body.ToString(depth + 1);

            return str;
        }
    }
}