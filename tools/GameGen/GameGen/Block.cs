using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GameGen
{
    class Block : Statement
    {
        public List<Statement> Statements;

        public Block(String body)
        {
            // todo: parse
        }
    }
}