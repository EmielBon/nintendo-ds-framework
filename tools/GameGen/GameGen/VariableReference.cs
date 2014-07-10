using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GameGen
{
    class VariableReference : BinaryOperation
    {
        public VariableReference(Expression left, Expression right) : base(".", left, right)
        {

        }
    }
}
