using System;
using System.Windows.Forms;
using System.Threading;
using System.Globalization;
namespace _3DTest
{
    static class Program
    {
        [STAThread]
        static void Main(string[] args)
        {
            Thread.CurrentThread.CurrentCulture = new CultureInfo("", false);
            SceneEditor form = new SceneEditor();
            form.Show();
            form.game = new Game1(form.pctSurface.Handle,form,form.pctSurface);
            form.game.Run();
        }
    }
}

