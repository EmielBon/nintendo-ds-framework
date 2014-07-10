using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GameGen
{
    class UnaryOperation : Expression
    {
        public Expression Operand;
        public String Operator;

        public UnaryOperation(String op, Expression operand) : base("")
        {
            Operator = op;
            Operand  = operand;
        }

        public override string ToString(int depth)
        {
            string operand = Operand.ToString(depth);
            string op = String.Format("{0}{1} {2}", GetTabs(depth), GetType().Name, Operator);
            return op + '\n' + operand;
        }
    }
}
