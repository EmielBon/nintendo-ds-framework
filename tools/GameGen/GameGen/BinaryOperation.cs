using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GameGen
{
    class BinaryOperation : Expression
    {
        public Expression LeftOperand;
        public Expression RightOperand;
        public String Operator;

        public BinaryOperation(String op, Expression leftOperand, Expression rightOperand) : base("")
        {
            Operator = op;
            LeftOperand  = leftOperand;
            RightOperand = rightOperand;
        }

        public override string ToString(int depth)
        {
            string left = LeftOperand.ToString(depth + 1);
            string right = RightOperand.ToString(depth + 1);
            string op = String.Format("{0}{1} {2}", GetTabs(depth), GetType().Name, Operator);
            return op + '\n' + left + "\n" + right;
        }
    }
}
