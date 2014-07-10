using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GameGen
{
    enum DeclarationType
    {
        Local,
        Extern,
    }

    class Type : IEquatable<Type>
    {
        public DeclarationType DeclarationType;
        public String   Name;
        public String   DefaultValue;

        public Type(String name, String defaultValue, DeclarationType declarationType = DeclarationType.Local)
        {
            Name = name;
            DefaultValue = defaultValue;
            DeclarationType = declarationType;
        }

        public bool Equals(Type other)
        {
            return Name == other.Name;
        }
    }
}
