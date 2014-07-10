using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GameGen
{
    class FunctionParameter : VariableDefinition
    {
        public FunctionParameter(String name, String type, String value = "") : base(name, type, value)
        {

        }

        public override string ToString()
        {
            return Type + " " + VariableName;
        }
    }
}
