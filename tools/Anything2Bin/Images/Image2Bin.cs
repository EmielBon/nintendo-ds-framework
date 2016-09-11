using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using System.IO;
using System.Text.RegularExpressions;
using System.Diagnostics;

namespace Anything2Bin.Images
{
    class Image2Bin
    {
        public static void Bitmap2Bin(String inputFile, string outputFile)
        {
            Console.WriteLine(inputFile);
            Bitmap bitmap = new Bitmap(inputFile);
    
            Console.Write("Bitmap size: " + bitmap.Width + "x" + bitmap.Height + " pixels...");

            FileStream stream = new FileStream(outputFile, FileMode.Create);
            BinaryWriter output = new BinaryWriter(stream);

            output.Write(bitmap.Width);
            output.Write(bitmap.Height);

            Color transparent = bitmap.GetPixel(0, 0);

            for (int y = 0; y < bitmap.Height; ++y)
            for (int x = 0; x < bitmap.Width;  ++x)
            {
                Color c = bitmap.GetPixel(x, y);
                short color = ColorToRGB16(c);
                output.Write(color);
            }

            output.Close();

            Console.WriteLine(" done");
        }

        public static void TileSet2Bin(String inputFile, String outputFile)
        {
            int tileWidth  = 8;
            int tileHeight = 8;
            int bpp        = 16;

            string fileName = Path.GetFileNameWithoutExtension(inputFile);

            Match match = Regex.Match(fileName, @"[0-9]+x[0-9]+(@[0-9]+)?$");
            
            if (match.Success)
            {
                string[] parameters = match.Groups[0].Value.Split('@');
  
                string[] dimensionStr = parameters[0].Split('x');
                tileWidth = int.Parse(dimensionStr[0]);
                tileHeight = int.Parse(dimensionStr[1]);

                if (parameters.Length > 1)
                {
                    string bppStr = parameters[1];
                    bpp = int.Parse(bppStr);
                }
            }

            Process grit = new Process();

            int p = (int) Environment.OSVersion.Platform;
            if (p == 4 || p == 128) { // Unix
                grit.StartInfo.FileName = @"wine";
                grit.StartInfo.Arguments = String.Format(Environment.GetEnvironmentVariable("ARPIGI") + "/tools/grit/grit.exe {0} -gt -gB{1} -W1 -fh! -ftb -MRp -Mw{2} -Mh{3} -o{4}", inputFile, bpp, tileWidth / 8, tileHeight / 8, outputFile);
            } else { // Probably Windows
                grit.StartInfo.FileName = Environment.GetEnvironmentVariable("ARPIGI") + "/tools/grit/grit.exe";
                grit.StartInfo.Arguments = String.Format("{0} -gt -p! -gu16 -gB{1} -W1 -fh! -ftb -MRp -Mw{2} -Mh{3} -o{4}", inputFile, bpp, tileWidth / 8, tileHeight / 8, outputFile);
            }
            grit.StartInfo.UseShellExecute = false;
            grit.StartInfo.RedirectStandardOutput = true;
            grit.Start();
            Console.SetIn(grit.StandardOutput);
            grit.WaitForExit();

            string gritOutputImageFile = Path.ChangeExtension(outputFile, ".img.bin");
            string gritOutputPaletteFile = Path.ChangeExtension(outputFile, ".pal.bin");

            if (File.Exists(gritOutputImageFile))
            {
                FileStream stream = new FileStream(outputFile, FileMode.Create);
                BinaryWriter output = new BinaryWriter(stream);
                output.Write((byte)tileWidth);
                output.Write((byte)tileHeight);
                output.Write((byte)0xFF); // Todo: change to actual tile count

                FileStream file = new FileStream(gritOutputImageFile, FileMode.Open, FileAccess.Read);
                file.CopyTo(stream);
                
                file.Close();
                stream.Close();
            }

            
            if (File.Exists(gritOutputPaletteFile))
            {
                string path = Path.GetDirectoryName(outputFile) + @"/" + Path.GetFileNameWithoutExtension(outputFile) + "_pal.bin";
                FileStream stream = new FileStream(path, FileMode.Create);
                BinaryWriter output = new BinaryWriter(stream);
                
                FileStream file = new FileStream(gritOutputPaletteFile, FileMode.Open, FileAccess.Read);
                BinaryReader reader = new BinaryReader(file);
                List<ushort> colors = new List<ushort>();

                while(true)
                {
                    try
                    {
                        colors.Add(reader.ReadUInt16());
                    }
                    catch (EndOfStreamException ex)
                    {
                    	break;
                    }
                }

                for (int i = 0; i < colors.Count - 1; ++i)
                {
                    if (colors[i] == 0 && colors[i + 1] == 0)
                        break;
                    output.Write(colors[i]);
                }

                file.Close();
                stream.Close();
            }

            File.Delete(gritOutputImageFile);
            File.Delete(gritOutputPaletteFile);
        }

        static short ColorToRGB16(Color c)
        {
            int r = ((int)c.R * 31) / 255;
            int g = ((int)c.G * 31) / 255;
            int b = ((int)c.B * 31) / 255;
            int a = (c.A == 0) ? 0 : 1;

            return (short)((a << 15) | r | (g << 5) | (b << 10));
        }
    }
}
