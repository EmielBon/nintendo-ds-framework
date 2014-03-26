using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using System.Windows.Forms;
using System.IO;

namespace MapEditor
{
    public class TileSet
    {
        public Image Image;
        public Panel Panel;
        public string FileName;

        public TileSet(string imagePath, Panel panel)
        {
            Image = Image.FromFile(imagePath);
            Panel = panel;
            FileName = Path.GetFileNameWithoutExtension(imagePath);
        }

        public void Draw(Grid grid)
        {
            Graphics g = Panel.CreateGraphics();
            g.DrawImage(Image, 0, 0, Width, Height);
            g.Dispose();

            if (grid != null)
            {
                grid.Draw(Panel);
            }
        }

        public void DrawTile(int tileIndex)
        {
            Graphics g = Panel.CreateGraphics();

            Rectangle tileRect = GetTileRectangle(tileIndex);

            g.DrawImage(Image, tileRect, tileRect, GraphicsUnit.Pixel);

            g.Dispose();
        }

        public int GetMouseOverTile(int tileWidth, int tileHeight)
        {
            Point pos = Panel.PointToClient(Cursor.Position);

            int x = MathHelper.Clamp(0, pos.X / 8, HorTileCount - 1);
            int y = MathHelper.Clamp(0, pos.Y / 8, VertTileCount - 1);
            int tileIndex = GetTileIndex(x / tileWidth * tileWidth, y / tileHeight * tileHeight);

            return tileIndex;
        }

        public Rectangle GetTileRectangle(int tileIndex)
        {
            return GetTileRectangle(tileIndex, 1, 1);
        }

        public Rectangle GetTileRectangle(int tileIndex, int width, int height)
        {
            return new Rectangle(GetTileX(tileIndex) * 8, GetTileY(tileIndex) * 8, width * 8, height * 8);
        }

        public int GetTileX(int tileIndex)
        {
            return tileIndex % HorTileCount;
        }

        public int GetTileY(int tileIndex)
        {
            return tileIndex / HorTileCount;
        }

        public int GetTileIndex(int x, int y)
        {
            return x + y * HorTileCount;
        }

        public int Width
        {
            get { return Image.Width; }
        }

        public int Height
        {
            get { return Image.Height; }
        }

        public int HorTileCount
        {
            get { return Width / 8; }
        }

        public int VertTileCount
        {
            get { return Height / 8; }
        }
    }
}
