using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GameGen
{
    class Type
    {
        public static String[] PrimitiveTypes = { "int", "bool", "float", "float12", "float16", "float24", "string", "Vector2", "Vector3" };
        public static String[] DefaultValues = { "0", "false", "0", "0", "0", "0", String.Empty, "Vector2(0, 0)", "Vector3(0, 0, 0)" };

        public String Name;

        public Type(String name)
        {
            Name = name;
        }

        public Value DefaultValue
        {
            get 
            { 
                return new Value(this, IsPrimitive() ? DefaultValues[PrimitiveTypes.ToList().IndexOf(Name)] : "nullptr");
            }
        }

        public bool IsPrimitive()
        {
            return (PrimitiveTypes.Contains(Name));
        }
    }
}
