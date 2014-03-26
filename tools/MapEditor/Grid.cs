using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Drawing;

namespace MapEditor
{
    public class Grid
    {
        public int HorCellCount;
        public int VertCellCount;
        public int CellWidth;
        public int CellHeight;
        public Pen Color;

        public Grid(int horCellCount, int vertCellCount, int cellWidth, int cellHeight, Pen color)
        {
            HorCellCount = horCellCount;
            VertCellCount = vertCellCount;
            CellWidth = cellWidth;
            CellHeight = cellHeight;
            Color = color;
        }

        public void Draw(Panel panel)
        {
            Graphics g = panel.CreateGraphics();

            for (int x = 0; x <= HorCellCount; x++)
            for (int y = 0; y <= VertCellCount; y++)
            {
                g.DrawLine(Color, x * CellWidth, 0, x * CellWidth, FullHeight);
                g.DrawLine(Color, 0, y * CellHeight, FullWidth, y * CellHeight);
            }

            g.Dispose();
        }

        public int FullWidth
        {
            get { return HorCellCount * CellWidth; }
        }

        public int FullHeight
        {
            get { return VertCellCount * CellHeight; }
        }
    }
}
