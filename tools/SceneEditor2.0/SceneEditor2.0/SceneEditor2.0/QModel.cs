using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework.Graphics;
using System.IO;
using Microsoft.Xna.Framework;

namespace GameEditor
{
    class QModel : Model3D
    {
        public QModel(int id = -1, String name = "")
            : base(id, name)
        {

        }

        public static QModel FromSimpleModel(SimpleModel simpleModel)
        {
            QModel model = new QModel(simpleModel.Id, simpleModel.Name);
            model.Meshes = simpleModel.Meshes;
            return model;
        }

        public override Matrix TransformationMatrix
        {
            get
            {
                return Matrix.CreateScale(Transformation.Scaling) *
                       Matrix.CreateFromYawPitchRoll(Transformation.Rotation.X, Transformation.Rotation.Y, Transformation.Rotation.Z) *
                       Matrix.CreateTranslation(Transformation.Translation);
            }
        }
    }
}
