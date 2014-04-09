using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GameGen
{
    class Program
    {
        static void Main(string[] args)
        {
            GameObject obj = GameObject.Parse(File.ReadAllText("ClassGenerationSource.txt"));

            Console.Write(obj.ExportCpp());
            Console.ReadKey();
        }
    }
}
