using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

namespace GameGen
{
    class DSLProject
    {
        public List<EnumConstant> Enums = new List<EnumConstant>();
        public List<String> Classes = new List<String>();
        public SortedSet<String> Namespaces = new SortedSet<String>();
        public String ProjectRoot;
        public List<Type> ExternTypes = new List<Type>();
        public List<DSLSourceFile> SourceFiles = new List<DSLSourceFile>();
        public List<Member> Members = new List<Member>();

        public void Generate()
        {
            String genPath     = NDSFrameworkHelper.CodeDirectory + @"\arm9";
            String includePath = genPath + @"\include";
            String sourcePath  = genPath + @"\source";

            Lexer typeLexer = new Lexer(File.ReadAllText(ProjectRoot + @"\TypeDefinitions.dsl"));
            while (typeLexer.HasNext())
            {
                typeLexer.SkipToken(); // extern
                String metaType = typeLexer.ReadToken();
                String name     = typeLexer.ReadToken();
                String defaultValue = "nullptr";
                if (metaType == "struct")
                {
                    typeLexer.SkipToken(); // =
                    defaultValue = typeLexer.ReadToken();
                    if (defaultValue == "default")
                        defaultValue = name + "()";
                }
                typeLexer.SkipToken(); // ;

                Type type = new Type(name, defaultValue, (metaType == "struct") ? MetaType.ValueType : MetaType.ReferenceType, DeclarationType.Extern); 
                ExternTypes.Add(type);
            }

            File.WriteAllText(includePath + @"\GameGenProject.h", String.Format("#pragma once\n\n#include \"{0}.h\"\n\nusing GameGenProject = {0};", Name));

            // Scan engine source for enums
            foreach (var fileName in Directory.EnumerateFiles(NDSFrameworkHelper.CodeDirectory + @"\arm9\include"))
            {
                String file = File.ReadAllText(fileName);
                if ((file.Contains("enum") && !file.Contains("class")) || file.Contains("enum class"))
                    Enums.Add(new EnumConstant(Path.GetFileNameWithoutExtension(fileName)));
            }

            String typesFile = File.ReadAllText(NDSFrameworkHelper.CodeDirectory + @"\arm9\include\types.h");
            MatchCollection results = Regex.Matches(typesFile, @"namespace ([A-Za-z0-9]+)\s*{");
            foreach (Match match in results)
                Namespaces.Add(match.Groups[1].ToString());
            Namespaces.Remove("Test");
            
            foreach (var fileName in Directory.EnumerateFiles(ProjectRoot, "*.dsl"))
            {
                if (Path.GetFileName(fileName) == "TypeDefinitions.dsl")
                    continue;
                var sourceFile = DSLSourceFile.Parse(fileName, this);
                Members.AddRange(sourceFile.Members);
                SourceFiles.Add(sourceFile);
                Classes.Add(sourceFile.ClassName);
            }

            foreach (DSLSourceFile source in SourceFiles)
            {
                foreach(String className in Classes)
                {
                    if (className != source.ClassName)
                        source.SourceIncludes.Add(new Include(className));
                }
                String header        = source.GenerateHeader();
                String cpp           = source.GenerateCpp();

                foreach (var className in Classes)
                {
                    header = header.Replace(className + "()", String.Format("New<{0}>()", className));
                    cpp    =    cpp.Replace(className + "()", String.Format("New<{0}>()", className));
                }

                foreach (Member member in Members)
                {
                    if (member.Type.MetaType == MetaType.ReferenceType)
                    {
                        header = header.Replace(member.Name + ".", member.Name + "->");
                        header = header.Replace(member.Name + "[", member.Name + "->at(");
                        header = header.Replace("]", ")"); 
                        cpp    =    cpp.Replace(member.Name + ".", member.Name + "->");
                        cpp    =    cpp.Replace(member.Name + "[", member.Name + "->at(");
                        cpp    =    cpp.Replace("]", ")");
                    }
                }

                File.WriteAllText(String.Format(@"{0}\{1}.h",   includePath, source.ClassName), header);
                File.WriteAllText(String.Format(@"{0}\{1}.cpp", sourcePath,  source.ClassName), cpp);
            }

            String typesSource = "#include \"types.h\"\n#include \"GlobalFunctions.h\"\n\n";

            foreach (var namespace_ in Namespaces)
            {
                typesSource += String.Format("#include \"{0}.h\"\n", namespace_);
            }

            typesSource += "\n";
            
            foreach (var className in Classes)
            {
                typesSource += String.Format("class {0};\n", className);
            }

            typesSource += "\n";

            foreach (var namespace_ in Namespaces)
            {
                typesSource += String.Format("using namespace {0};\n", namespace_);
            }

            File.WriteAllText(String.Format(@"{0}\{1}.h", includePath, Name + "Types"), typesSource);
        }

        public DSLProject(String projectRoot)
        {
            ProjectRoot = projectRoot;
        }

        public String Name
        {
            get { return Directory.GetParent(ProjectRoot).Name; }
        }
    }
}
