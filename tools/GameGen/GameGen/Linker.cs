using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GameGen
{
    class Linker
    {
        public List<EnumConstant> Enums = new List<EnumConstant>();
        public List<Type> ExternTypes = new List<Type>();

        void Resolve()
        {

        }

        void ResolveReferenceTypes()
        {
            /*int i = Project.ExternTypes.IndexOf(member.Type);
            if (i != -1)
            {
                member.Type = Project.ExternTypes[i];
                member.InitialValue = member.Type.DefaultValue;
            }
            if (initialValue != null)
            {
                member.InitialValue = initialValue;
            }

            else if (member.Type.MetaType == MetaType.ReferenceType)
                member.InitialValue = String.Format("New<{0}>()", member.Type.Name);*/
        }

        public void ScanEngineForStuff()
        {
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
        }

        public void FindAllTypes()
        {
            Lexer typeLexer = new Lexer(File.ReadAllText(ProjectRoot + @"\TypeDefinitions.dsl"));
            while (typeLexer.HasNext())
            {
                typeLexer.SkipToken(); // extern
                String metaType = typeLexer.ReadToken();
                String name = typeLexer.ReadToken();
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
        }

        public void AddAllIncludesToEverything()
        {
            foreach (String className in Classes)
            {
                if (className != source.ClassName)
                    source.SourceIncludes.Add(new Include(className));
            }
        }

        public void FixEnumReferences()
        {
            // Replace all enums . with ::
            foreach (var enumConstant in Project.Enums)
            {
                String name = enumConstant.Name;
                output = output.Replace(name + ".", name + "::");
            }
        }

        public void AddImplicitArguments()
        {
            foreach (Function function in Functions)
            {
                if (function.Name == "Update" || function.Name == "Draw")
                {
                    function.Arguments += "const GameTime &gameTime";
                }
            }
        }
    }
}
