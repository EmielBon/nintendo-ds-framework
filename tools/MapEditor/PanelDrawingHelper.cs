using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Drawing;

namespace MapEditor
{
    public static class PanelDrawingHelper
    {
        public static void Clear(Panel panel, Brush colorBrush)
        {
            Graphics g = panel.CreateGraphics();
            g.FillRectangle(colorBrush, new Rectangle(new Point(), panel.ClientSize));
            g.Dispose();
        }
    }
}
