using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace GameEditor
{
    partial class Editor
    {
        public KeyFrameControl KeyFrameControl;
        
        public void Animate()
        {
            foreach (var model in Models)
            {
                if (KeyFrameControl.HasTransformation(model, KeyFrameControl.CurrentFrameIndex) && KeyFrameControl.Playing)
                    model.Transformation = KeyFrameControl.GetTransformation(model, KeyFrameControl.CurrentFrameIndex);
            }
        }
    }
}
