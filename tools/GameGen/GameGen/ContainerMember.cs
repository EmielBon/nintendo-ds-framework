using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GameGen
{
    class ContainerMember : Member
    {
        public String[] ContainerTypes = { "List", "Set" };
        public String ContainerType;

        public String GetContainerType()
        {
            foreach (String containerType in ContainerTypes)
            {
                if (ContainerType.StartsWith(containerType))
                    return containerType;
            }
            throw new Exception("Parse error: Unknown container type in type \"" + Type + "\"");
        }

    }
}
