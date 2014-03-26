using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework.Graphics;

namespace GameEditor
{
    static class RenderTargetFactory
    {
        public static RenderTarget2D CreateRenderTarget(GraphicsDevice device, int downSample, bool multiSample)
        {
            PresentationParameters pp = device.PresentationParameters;
            return new RenderTarget2D(
                device,
                pp.BackBufferWidth / downSample,
                pp.BackBufferHeight / downSample,
                true,
                device.DisplayMode.Format,
                DepthFormat.Depth24,
                (multiSample) ? pp.MultiSampleCount : 0,
                pp.RenderTargetUsage
            );
        }
    }
}
