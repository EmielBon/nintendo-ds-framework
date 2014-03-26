using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework.Graphics;
using System.IO;
using Microsoft.Xna.Framework;

namespace GameEditor
{
    class SimpleModel : Model3D
    {
        public SimpleModel(int id = -1, String name = "") : base(id, name)
        {

        }

        public override Matrix TransformationMatrix
        {
            get
            {
                return Matrix.CreateScale(Transformation.Scaling) *
                       Matrix.CreateRotationX(Transformation.Rotation.X) *
                       Matrix.CreateRotationY(Transformation.Rotation.Y) *
                       Matrix.CreateRotationZ(Transformation.Rotation.Z) *
                       Matrix.CreateTranslation(Transformation.Translation);
            }
        }
    }
}
