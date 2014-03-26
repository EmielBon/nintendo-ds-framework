using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Content;

namespace GameEditor
{
    class EffectCatalog
    {
        public static void Initialize(ContentManager content)
        {
            PostProcessEffect = content.Load<Effect>("Effects/PostProcessing");
            BlurEffect = content.Load<Effect>("Effects/GaussianBlur");
            MaskEffect = content.Load<Effect>("Effects/Mask");
            ColorEffect = content.Load<Effect>("Effects/Color");
            ScreenSpaceEffect = content.Load<Effect>("Effects/ScreenSpaceEffect");
        }

        public static Effect PostProcessEffect
        {
            get;
            private set;
        }

        public static Effect BlurEffect
        {
            get;
            private set;
        }

        public static Effect MaskEffect
        {
            get;
            private set;
        }

        public static Effect ColorEffect
        {
            get;
            private set;
        }

        public static Effect ScreenSpaceEffect
        {
            get;
            private set;
        }
    }
}
