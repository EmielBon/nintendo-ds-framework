using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GameGen
{
    class Include : IComparable<Include>
    {
        public String FileName;

        public Include(String fileName)
        {
            FileName = fileName;
        }

        public int CompareTo(Include other)
        {
            return FileName.CompareTo(other.FileName);
        }
    }
}
