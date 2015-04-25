using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;

namespace MapEditor
{
    public partial class Form1 : Form
    {
        int selected;
        int previousHover;

        Map map;
        TileSet tileSet;

        Pen mapTileBorderColor = Pens.Gray;
        Pen tileBorderColor = Pens.Gray;
        Pen tileSelectedBorderColor = Pens.Yellow;
        Pen tileHoverBorderColor = Pens.Black;

        public Form1()
        {
            InitializeComponent();
            map = new Map(MaxMapWidth, MaxMapHeight, MapPanel);
        }

        public void DrawMap()
        {
            PanelDrawingHelper.Clear(MapPanel, Brushes.White);
            if (tileSet != null)
            {
                Grid grid = new Grid(MapWidth / SnapWidth, MapHeight / SnapHeight, SnapPixelWidth, SnapPixelHeight, mapTileBorderColor);
                map.Draw(ShowGrid ? grid : null, tileSet);
            }
        }

        public void DrawMapBorder(int x, int y, Pen color)
        {
            Graphics g = MapPanel.CreateGraphics();
            g.DrawRectangle(color, GetMapTileRectangle(x, y));
            g.Dispose();
        }

        public void DrawTileSet()
        {
            if (tileSet != null)
            {
                Grid grid = new Grid(tileSet.Width / TilePixelWidth, tileSet.Height / TilePixelHeight, TilePixelWidth, TilePixelHeight, tileBorderColor);
                tileSet.Draw(ShowGrid ? grid : null);
            }
        }

        public void DrawTileSetBorder(int tileIndex, Pen color)
        {
            Graphics g = TilePanel.CreateGraphics();
            g.DrawRectangle(color, tileSet.GetTileRectangle(tileIndex, TileWidth, TileHeight));
            g.Dispose();
        }

        private void SelectTileSet()
        {
            OpenFileDialog dialog = new OpenFileDialog();
            dialog.RestoreDirectory = true;

            if (dialog.ShowDialog() == DialogResult.OK)
            {
                tileSet = new TileSet(dialog.FileName, TilePanel);
                NoTileSetLabel.Visible = false;
                DrawTileSet();
                DrawMap();
            }
        }

        public int GetMouseOverTile()
        {
            Point pos = TilePanel.PointToClient(Cursor.Position);
            
            int x = MathHelper.Clamp(0, pos.X / 8, tileSet.HorTileCount - 1);
            int y = MathHelper.Clamp(0, pos.Y / 8, tileSet.VertTileCount - 1);
            int tileIndex = tileSet.GetTileIndex(x / TileWidth * TileWidth, y / TileHeight * TileHeight);

            return tileIndex;
        }

        public Rectangle GetMapTileRectangle(int x, int y)
        {
            return new Rectangle(x * 8, y * 8, SnapPixelWidth, SnapPixelHeight);
        }

        private void MapPanel_MouseMove(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                MapPanel_Click(null, null);
            }
        }

        private void MapPanel_Click(object sender, EventArgs e)
        {
            if (tileSet != null)
            {
                Point pos = MapPanel.PointToClient(Cursor.Position);

                int x = MathHelper.Clamp(0, pos.X / 8, MapWidth - 1) / SnapWidth * SnapWidth;
                int y = MathHelper.Clamp(0, pos.Y / 8, MapHeight - 1) / SnapHeight * SnapHeight;

                for (int i = 0; i < TileWidth; i++)
                for (int j = 0; j < TileHeight; j++)
                {
                    int tileX = tileSet.GetTileX(selected) + i;
                    int tileY = tileSet.GetTileY(selected) + j;

                    map.SetScreenBlockEntry(x + i, y + j, tileSet.GetTileIndex(tileX, tileY));
                    map.DrawTile(x + i, y + j, tileSet);
                }

                if (ShowGrid)
                {
                    DrawMapBorder(x, y, mapTileBorderColor);
                }
            }
        }

        private void TilePanel_Click(object sender, EventArgs e)
        {
            if (tileSet == null)
            {
                SelectTileSet();
                return;
            }
            
            if (ShowGrid)
                DrawTileSetBorder(selected, tileBorderColor);
            else
                tileSet.DrawTile(selected); // Ook voor andere sizes! Zie hoveren over tileset met grid uit

            selected = GetMouseOverTile();

            DrawTileSetBorder(selected, tileSelectedBorderColor);
        }

        private void TilePanel_MouseMove(object sender, MouseEventArgs e)
        {
            if (tileSet == null)
                return;

            int hover = GetMouseOverTile();
            StatusLabel.Text = "Tile under mouse: " + hover;

            if (hover != previousHover)
            {
                Graphics g = TilePanel.CreateGraphics();

                if (ShowGrid)
                    DrawTileSetBorder(previousHover, tileBorderColor);
                else
                    tileSet.DrawTile(previousHover);

                DrawTileSetBorder(hover, tileHoverBorderColor);
                DrawTileSetBorder(selected, tileSelectedBorderColor);

                previousHover = hover;

                g.Dispose();
            }
        }

        private void saveToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SaveFileDialog dialog = new SaveFileDialog();
            dialog.RestoreDirectory = true;
            dialog.OverwritePrompt = true;

            if (dialog.ShowDialog() == DialogResult.OK)
            {
                string          fileName = dialog.FileName;
                string   mapDataFileName = fileName + "MapData";
                
                StreamWriter mapWriter = new StreamWriter(fileName + ".bin");
                mapWriter.WriteLine("s " + MapWidth + "x" + MapHeight);
                mapWriter.WriteLine("d " + Path.GetFileNameWithoutExtension(mapDataFileName));
                mapWriter.WriteLine("t " + tileSet.FileName);

                FileStream stream = new FileStream(mapDataFileName + ".bin", FileMode.Create);
                BinaryWriter writer = new BinaryWriter(stream);

                // Create the collision map
                for (int y = 0; y < MapHeight / 2; y++)
                for (int x = 0; x < MapWidth  / 2; x++)
                {
                    int tile = map.GetScreenBlockEntry(2 * x, 2 * y);//map[2 * x, 2 * y];
                    int tileX = tile % 8;
                    int tileY = tile / 8;
                    Console.WriteLine(tile + " x: " + tileX + " y: " + tileY);
                }

                // Write the map data and the collision map
                for (int y = 0; y < MapHeight; y++)
                for (int x = 0; x < MapWidth; x++)
                    writer.Write((short)map.GetScreenBlockEntry(x, y)/*map[x, y]*/);

                mapWriter.Close();
                writer.Close();
            }
        }

        private void importToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog dialog = new OpenFileDialog();
            dialog.RestoreDirectory = true;
            dialog.Multiselect = false;

            if (dialog.ShowDialog() == DialogResult.OK)
            {
                FileStream stream = new FileStream(dialog.FileName, FileMode.Open);
                BinaryReader reader = new BinaryReader(stream);

                MapWidthChanger.Value  = reader.ReadByte();
                MapHeightChanger.Value = reader.ReadByte();

                // Inverse of saving functionality
                for (int y = 0; y < MapHeight; y++)
                for (int x = 0; x < MapWidth; x++)
                {
                    map.SetScreenBlockEntry(x, y, reader.ReadInt16());
                }
            }

            DrawMap();
        }

        private void selectToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SelectTileSet();
        }

        private void MapWidthChanger_ValueChanged(object sender, EventArgs e)
        {
            DrawMap();
        }

        private void MapHeightChanger_ValueChanged(object sender, EventArgs e)
        {
            DrawMap();
        }

        private void SnapWidthChanger_ValueChanged(object sender, EventArgs e)
        {
            DrawMap();
        }

        private void SnapHeightChanger_ValueChanged(object sender, EventArgs e)
        {
            DrawMap();
        }

        private void TileWidthChanger_ValueChanged(object sender, EventArgs e)
        {
            DrawTileSet();
        }

        private void TileHeightChanger_ValueChanged(object sender, EventArgs e)
        {
            DrawTileSet();
        }

        private void ShowGridCheckBox_CheckedChanged(object sender, EventArgs e)
        {
            DrawMap();
            DrawTileSet();
        }

        private void Form1_ResizeEnd(object sender, EventArgs e)
        {
            DrawMap();
            DrawTileSet();
        }

        public int MapWidth
        {
            get { return (int)MapWidthChanger.Value; }
        }

        public int MapHeight
        {
            get { return (int)MapHeightChanger.Value; }
        }

        public int MapPixelWidth
        {
            get { return MapWidth * 8; }
        }

        public int MapPixelHeight
        {
            get { return MapHeight * 8; }
        }

        public int MaxMapWidth
        {
            get { return (int)MapWidthChanger.Maximum; }
        }

        public int MaxMapHeight
        {
            get { return (int)MapHeightChanger.Maximum; }
        }

        public int SnapWidth
        {
            get { return (int)SnapWidthChanger.Value; }
        }

        public int SnapHeight
        {
            get { return (int)SnapHeightChanger.Value; }
        }

        public int SnapPixelWidth
        {
            get { return 8 * SnapWidth; }
        }

        public int SnapPixelHeight
        {
            get { return 8 * SnapHeight; }
        }

        public int TileWidth
        {
            get { return (int)TileWidthChanger.Value; }
        }

        public int TileHeight
        {
            get { return (int)TileHeightChanger.Value; }
        }

        public int TilePixelWidth
        {
            get { return TileWidth * 8; }
        }

        public int TilePixelHeight
        {
            get { return TileHeight * 8; }
        }

        public bool ShowGrid
        {
            get { return ShowGridCheckBox.Checked; }
        }

        private void TilePanel_Paint(object sender, PaintEventArgs e)
        {

        }

        private void MapPanel_Paint(object sender, PaintEventArgs e)
        {

        }
    }
}
