using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Drawing;

namespace MapEditor
{
    class Map
    {
        public int Width;
        public int Height;
        public Panel Panel;

        int[,] screenBlockEntries;
        
        public Map(int width, int height, Panel panel)
        {
            Width = width;
            Height = height;
            screenBlockEntries = new int[Width, Height];
            Panel = panel;
        }

        public int GetScreenBlockEntry(int x, int y)
        {
            return screenBlockEntries[x, y];
        }

        public void SetScreenBlockEntry(int x, int y, int value)
        {
            screenBlockEntries[x, y] = value;
        }

        public void Draw(Grid grid, TileSet tileSet)
        {
            // Screen block entries
            for (int x = 0; x < Width; x++)
            for (int y = 0; y < Height; y++)
            {
                DrawTile(x, y, tileSet);
            }

            if (grid != null)
            {
                grid.Draw(Panel);
            }
        }

        public void DrawTile(int x, int y, TileSet tileSet)
        {
            Graphics g = Panel.CreateGraphics();

            int tileIndex = screenBlockEntries[x, y];
            // Create rectangle for displaying image
            Rectangle destRect = new Rectangle(x * 8, y * 8, 8, 8);

            if (tileIndex == -1)
            {
                g.FillRectangle(Brushes.White, destRect);
                return;
            }

            // Create rectangle for source image
            Rectangle srcRect = tileSet.GetTileRectangle(tileIndex);
            // Draw image to screen
            g.DrawImage(tileSet.Image, destRect, srcRect, GraphicsUnit.Pixel);

            g.Dispose();
        }
    }
}
