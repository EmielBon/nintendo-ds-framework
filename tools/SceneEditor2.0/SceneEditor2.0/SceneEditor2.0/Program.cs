using System;
using System.Threading;
using System.Globalization;

namespace GameEditor
{
#if WINDOWS || XBOX
    static class Program
    {
        [STAThreadAttribute]
        static void Main(string[] args)
        {
            Thread.CurrentThread.CurrentCulture = new CultureInfo("", false);

            using (Game1 game = new Game1())
            {
                game.Run();
            }
        }
    }
#endif
}

