using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System.Drawing;

[TestClass()]
public class ImageTilingTests
{
    [TestMethod()]
    public void ImageTilingTest()
    {
        string filename = "TestImages/tilingTest.png";
        var bitmap = new Bitmap(filename);
        var tiles = bitmap.Tiled(8, 8);

        Assert.AreEqual(tiles.Count, 4, "Incorrect number of tiles");

        Assert.IsTrue(TileHasUniformColor(tiles[0], Color.Red));
        Assert.IsTrue(TileHasUniformColor(tiles[1], Color.Green));
        Assert.IsTrue(TileHasUniformColor(tiles[2], Color.Blue));
        Assert.IsTrue(TileHasUniformColor(tiles[3], Color.Yellow));
    }

    private bool TileHasUniformColor(Bitmap tile, Color c)
    {
        for (var y = 0; y < tile.Height; y++)
            for (var x = 0; x < tile.Width; x++)
            {
                var tileColor = tile.GetPixel(x, y);
                if (c.Equals(tileColor))
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
