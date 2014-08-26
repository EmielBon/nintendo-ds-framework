using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GameGen
{
    class Expression : Statement
    {
        public List<VariableReference> VariableReferences = new List<VariableReference>();

        public Expression(String expr)
        {
            Content = expr;
        }

        public static Expression Parse(String content, Dictionary<string, string> SubExpressions = null)
        {
            String operators = "=+-*/.";

            content = content.Replace(" ", "");
            
            var dollars = new Dictionary<string, string>();

            while (content.Contains("("))
            {
                var key = "$" + dollars.Count;
                var subExpr = FindDeepestHaakjesExpression(content);
                dollars.Add(key, subExpr);
                content = content.Replace("(" + subExpr + ")", key);
                SubExpressions = dollars;
            }

            if (IsSubExpressionReference(content))
                content = SubExpressions[content];

            foreach (char c in operators)
            {
                var split = content.Split(c);
                if (split.Length >= 2)
                {
                    if (split[0].Trim() == String.Empty)
                    {
                        Expression operand = Expression.Parse(content.Substring(split[0].Length + 1), SubExpressions);
                        return new UnaryOperation(c.ToString(), operand);
                    }
                    else
                    {
                        string left  = split[0];
                        string right = content.Substring(split[0].Length + 1);

                        Expression leftOperand  = Expression.Parse(left, SubExpressions);
                        Expression rightOperand = Expression.Parse(right, SubExpressions);

                        if (c == '.')
                        {
                            return new VariableReference(leftOperand, rightOperand);
                        }
                        else
                        {
                            return new BinaryOperation(c.ToString(), leftOperand, rightOperand);
                            //Console.WriteLine(expression.ToString(0));
                        }
                    }
                }
            }
            
            if (content.Contains('$') && content.IndexOf("$") == content.Length - 2)
                return FunctionCall.Parse(content, SubExpressions);

            return new Expression(content);
        }

        public static bool IsSubExpressionReference(string expr)
        {
            return (expr.Length == 2 && expr.StartsWith("$"));
        }

        public static string FindDeepestHaakjesExpression(string input)
        {
            int closeIndex = input.IndexOf(")");
            int i = closeIndex;
            while (input[i] != '(')
                i--;
            return input.Substring(i + 1, closeIndex - i - 1);
        }

        public override string ToString(int depth)
        {
            return GetTabs(depth) + Content.Trim();
        }
    }
}
