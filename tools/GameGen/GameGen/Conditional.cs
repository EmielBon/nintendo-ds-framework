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
    }
}