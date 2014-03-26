using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace GameEditor
{
    static class NDSFrameworkHelper
    {
        public static string RootDirectory
        {
            get { return Environment.GetEnvironmentVariable("ARPIGI"); }
        }

        public static string CodeDirectory
        {
            get { return RootDirectory + @"\code"; }
        }

        public static string GraphicsDirectory
        {
            get { return RootDirectory + @"\graphics"; }
        }

        public static string ScenesDirectory
        {
            get { return GraphicsDirectory + @"\scenes"; }
        }

        public static string ModelsDirectory
        {
            get { return GraphicsDirectory + @"\models"; }
        }

        public static string TexturesDirectory
        {
            get { return GraphicsDirectory + @"\textures"; }
        }

        public static string TileSetsDirectory
        {
            get { return GraphicsDirectory + @"\tilesets"; }
        }

        public static string SpritesDirectory
        {
            get { return GraphicsDirectory + @"\sprites"; }
        }

        public static string FontsDirectory
        {
            get { return GraphicsDirectory + @"\fonts"; }
        }
    }
}
