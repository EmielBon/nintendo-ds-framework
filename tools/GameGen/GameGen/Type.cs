using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GameGen
{
    enum MetaType
    {
        ReferenceType,
        ValueType,
    }

    enum DeclarationType
    {
        Local,
        Extern,
    }

    class Type : IEquatable<Type>
    {
        public MetaType MetaType;
        public DeclarationType DeclarationType;
        public String   Name;
        public String   DefaultValue;

        public Type(String name, String defaultValue, MetaType type = MetaType.ReferenceType, DeclarationType declarationType = DeclarationType.Local)
        {
            MetaType = type;
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
