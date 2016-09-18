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

}
