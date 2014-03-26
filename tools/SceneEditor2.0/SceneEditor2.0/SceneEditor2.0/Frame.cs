using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace GameEditor
{
    class Frame
    {
        public Dictionary<Model3D, Transformation> TransformationForModel = new Dictionary<Model3D, Transformation>();
        public int FrameIndex;

        public Frame(int frameIndex)
        {
            FrameIndex = frameIndex;
        }
    }
}
