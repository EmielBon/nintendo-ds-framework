using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GameGen
{
    class Program
    {
        static void Main(string[] args)
        {
            //string path = args[0];// Environment.GetEnvironmentVariable("ARPIGI");
            //DSLProject project = new DSLProject(path);
            //File.WriteAllText(includePath + @"\GameGenProject.h", String.Format("#pragma once\n\n#include \"{0}.h\"\n\nusing GameGenProject = {0};", Name));
            //project.Generate();

            var lexer = new Lexer2("int i = 2 + 55.0 - \"abc\";");
			do
			{
				lexer.ReadToken();
			}
			while (lexer.Token != -1);

            /*var dollars = new Dictionary<string, string>();
*/
            //var expr = " ( a+ ( b /( e - fu n cution ( x  +  2.0 0 + y ,  ( b   -  c ) / 2 ) )) ) * ( c + d) " ;
            /*while(expr.Contains("("))
            {
                var key = "$" + dollars.Count;
                var subExpr = FindDeepestHaakjesExpression(expr);
                dollars.Add(key, subExpr);
                expr = expr.Replace("(" + subExpr + ")", key);
            }*/
            //var str = Expression.Parse(expr);
            //Console.WriteLine(str.ToString(0));
            //var y = "(a + b) * c".Replace(x, "$0");
            //Expression expr = Expression.Parse("x = (a + b) * (c - d)");
            //BinaryOperation operation = expr as BinaryOperation;
            //Console.WriteLine(operation.ToString(0));
            /*Expression expr = Expression.Parse("y = -1");
            Console.WriteLine(expr.ToString(0));*/
        }
    }
}