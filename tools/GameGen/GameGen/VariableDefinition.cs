using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GameGen
{
    class VariableDefinition : Statement
    {
        String Type;
        String VariableName;
        String Value; // optional
    }
}
