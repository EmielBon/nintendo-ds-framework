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
            string path = args[0];// Environment.GetEnvironmentVariable("ARPIGI");
            DSLProject project = new DSLProject(path);
            project.Generate();
        }
    }
}