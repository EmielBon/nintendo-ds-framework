using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GameGen
{
    class SimpleMember : Member
    {
        public override Value InitialValue
        {
            get 
            { 
                if (Type.IsPrimitive())
                {
                    if (initialValue == null)
                        return Type.DefaultValue;
                    else
                        return initialValue;
                }
                else
                {
                    if (initialValue == null)
                        return new Value(Type, String.Format("New<{0}>()", Type.Name));
                    else
                        return new Value(new Type(initialValue.Val), String.Format("New<{0}>()", initialValue.Val));
                }
                
            }
            set { initialValue = value; }
        }
    }
}
