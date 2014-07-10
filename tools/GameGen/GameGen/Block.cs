using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GameGen
{
    class Block : Statement
    {
        public List<Statement> Statements = new List<Statement>();
        
        public static Block Parse(String body)
        {
            var block = new Block();
            var lexer = new Lexer(body);

            while (lexer.HasNext())
            {
                // Conditional
                if (lexer.PeekToken() == "if")
                {
                    lexer.SkipToken();      // Absorb if
                    Expression condition = new Expression(lexer.ReadBlock("(", ")"));
                    Block b = Block.Parse(lexer.ReadBlock("{", "}"));
                    IfStatement statement = new IfStatement(condition, b);
                    block.Statements.Add(statement);
                }
                else if(lexer.PeekToken(2) == "=")
                {
                    var type = lexer.ReadToken();
                    var name = lexer.ReadToken();
                    lexer.SkipToken();
                    var value = lexer.ReadUntil(";");
                    var variableDefinition = new VariableDefinition(name, type, value);
                    block.Statements.Add(variableDefinition);
                }
                else
                {
                    string str = lexer.ReadUntil(";");
                    block.Statements.Add( Expression.Parse(str) );
                    lexer.SkipToken();  // Skip ;
                }
            }

            return block;
        }

        public override string ToString(int depth)
        {
            String str = "";

            for (int i = 0; i < Statements.Count; ++i)
            {
                str += Statements[i].ToString(depth) + "\n";
            }

            return str;
        }
    }
}