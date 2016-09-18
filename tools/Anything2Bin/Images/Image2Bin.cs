using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using System.IO;
using System.Text.RegularExpressions;
using System.Diagnostics;

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
            int bpp        = 8; // 16bpp true color does not seem to work properly, so we just generate a palette and substitute the colors from there

            string fileName = Path.GetFileNameWithoutExtension(inputFile);
            //string gritOutputImageFile = Path.ChangeExtension(outputFile, ".img.bin");
            //string gritOutputPaletteFile = Path.ChangeExtension(outputFile, ".pal.bin");
            string projectRoot = Environment.GetEnvironmentVariable("ARPIGI");

            //string gritPath = projectRoot + "/tools/grit/grit.exe";

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

            /*
            Process grit = new Process();
            int p = (int) Environment.OSVersion.Platform;
            String arguments = String.Format("{0} -gt -gB{1} -MRp -Mw{2} -Mh{3} -fh! -ftb -W1 -o{4}", inputFile, bpp, tileWidth / 8, tileHeight / 8, outputFile);

            if (p == 4 || p == 128) { // Unix
                grit.StartInfo.FileName = @"wine";
                grit.StartInfo.Arguments = gritPath + " " + arguments;
            } else { // Probably Windows
                grit.StartInfo.FileName = gritPath;
                grit.StartInfo.Arguments = arguments;
            }
            grit.StartInfo.UseShellExecute = false;
            grit.StartInfo.RedirectStandardOutput = true;
            grit.Start();
            Console.SetIn(grit.StandardOutput);
            grit.WaitForExit();
            
            if (!File.Exists(gritOutputImageFile))
            {
                Console.WriteLine("Error: Grit did not output graphics");
                return;
            }

            if (!File.Exists(gritOutputPaletteFile))
            {
                Console.WriteLine("Error: Grit did not output palette");
                return;
            }

            Console.Write("Converting grit output...");
            byte[] tilesBytes = File.ReadAllBytes(gritOutputImageFile);
            byte[] paletteBytes = File.ReadAllBytes(gritOutputPaletteFile);
            
            UInt16[] colors = new UInt16[paletteBytes.Length / 2];
            Buffer.BlockCopy(paletteBytes, 0, colors, 0, paletteBytes.Length);

            FileStream stream = new FileStream(outputFile, FileMode.Create);
            BinaryWriter output = new BinaryWriter(stream);
            output.Write(tileWidth);
            output.Write(tileHeight);

            foreach (var palettedColor in tilesBytes)
            {
                output.Write(colors[palettedColor]);
            }
            
            stream.Close();
            */

            var bitmap = new Bitmap(inputFile);
            var tiles = bitmap.Tiled(tileWidth, tileHeight);

            FileStream stream = new FileStream(outputFile, FileMode.Create);
            BinaryWriter output = new BinaryWriter(stream, Encoding.BigEndianUnicode);
            output.Write(tileWidth);
            output.Write(tileHeight);

            foreach (var tile in tiles)
            {
                for (var y = 0; y < tileHeight; y++)
                for (var x = 0; x < tileWidth; x++)
                {
                    var pixel = tile.GetPixel(x, y);
                    var value = pixel.ToRGB16();
                    var bytes = BitConverter.GetBytes(value);
                    output.Write(bytes[1]);
                    output.Write(bytes[0]);
                }
            }

            stream.Close();

            //File.Delete(gritOutputImageFile);
            //File.Delete(gritOutputPaletteFile);

            Console.WriteLine(" done");
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

    public static class Extensions
    {
        public static List<Bitmap> Tiled(this Bitmap bitmap, int tileWidth, int tileHeight)
        {
            var width = bitmap.Width;
            var height = bitmap.Height;

            var tiledBitmap = new Bitmap(width, height);

            var length = width * height;

            List<Bitmap> tiles = new List<Bitmap>();

            for (var y = 0; y < height; y+= tileHeight)
            for (var x = 0; x < width;  x+= tileWidth)
            {
                var tile = new Bitmap(tileWidth, tileHeight);

                for (int tileX = 0; tileX < tileWidth; tileX++)
                for (int tileY = 0; tileY < tileHeight; tileY++)
                {
                    var pixel = bitmap.GetPixel(x + tileX, y + tileY);
                    tile.SetPixel(tileX, tileY, pixel);
                }
                tiles.Add(tile);
            }

            return tiles;
        }

        public static ushort ToRGB16(this Color c)
        {
            int r = ((int)c.R * 31) / 255;
            int g = ((int)c.G * 31) / 255;
            int b = ((int)c.B * 31) / 255;
            int a = (c.A == 0) ? 0 : 1;

            return (ushort)((a << 15) | r | (g << 5) | (b << 10));
        }

    }
