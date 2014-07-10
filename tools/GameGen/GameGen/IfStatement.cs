using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GameGen
{
    class IfStatement : Conditional
    {
        public IfStatement(Expression condition, Block block) : base(condition, block)
        {

        }
    }
}
