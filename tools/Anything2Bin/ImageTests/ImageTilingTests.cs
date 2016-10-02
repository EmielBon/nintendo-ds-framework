using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System.Drawing;

[TestClass()]
public class ImageTilingTests
{
    [TestMethod()]
    public void ImageTilingTest()
    {
        string filename = "TestImages/tilingTest16x16.png";
        var bitmap = new Bitmap(filename);
        var tiles = bitmap.Tiled();

        Assert.AreEqual(4, tiles.Count, "Incorrect number of tiles");

        Assert.IsTrue(TileHasUniformColor(tiles[0], Color.FromArgb(255, 255, 0, 0)));
        Assert.IsTrue(TileHasUniformColor(tiles[1], Color.FromArgb(255, 0, 255, 0)));
        Assert.IsTrue(TileHasUniformColor(tiles[2], Color.FromArgb(255, 0, 0, 255)));
        Assert.IsTrue(TileHasUniformColor(tiles[3], Color.FromArgb(255, 255, 255, 0)));
    }

    [TestMethod()]
    public void Image16x16TilingTest()
    {
        string filename = "TestImages/tilingTestB16x16.png";
        var bitmap = new Bitmap(filename);
        var tiles = bitmap.Tiled();
        Assert.AreEqual(8, tiles.Count, "Incorrect number of tiles");
        Assert.AreEqual(8, tiles[0].Width, "Incorrect width");
        Assert.AreEqual(8, tiles[0].Height, "Incorrect height");


        Assert.IsTrue(TileHasUniformColor(tiles[0], Color.FromArgb(255, 255, 0, 0)));
        Assert.IsTrue(TileHasUniformColor(tiles[1], Color.FromArgb(255, 0, 255, 0)));
        Assert.IsTrue(TileHasUniformColor(tiles[2], Color.FromArgb(255, 0, 0, 255)));
        Assert.IsTrue(TileHasUniformColor(tiles[3], Color.FromArgb(255, 255, 255, 0)));

        Assert.IsTrue(TileHasUniformColor(tiles[4], Color.FromArgb(255, 255, 0, 0)));
        Assert.IsTrue(TileHasUniformColor(tiles[5], Color.FromArgb(255, 0, 255, 0)));
        Assert.IsTrue(TileHasUniformColor(tiles[6], Color.FromArgb(255, 0, 0, 255)));
        Assert.IsTrue(TileHasUniformColor(tiles[7], Color.FromArgb(255, 255, 255, 0)));

    }

    private bool TileHasUniformColor(Bitmap tile, Color c)
    {
        for (var y = 0; y < tile.Height; y++)
            for (var x = 0; x < tile.Width; x++)
            {
                var tileColor = tile.GetPixel(x, y);
                if (!c.Equals(tileColor))
                    return false;
            }
        return true;
    }

    [TestMethod()]
    public void ColorConversionTest()
    {
        var red = Color.Red;
        var green = Color.Green;
        var blue = Color.Blue;

        Assert.AreEqual(red.ToRGB16(),   0x801F, "Red not equal to 0x801F");
        Assert.AreEqual(green.ToRGB16(), 0x81E0, "Green not equal to 0x81E0");
        Assert.AreEqual(blue.ToRGB16(), 0xFC00, "Blue not equal to 0x801F");
    }

}
