using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace _3DTest
{
    public class Model3D
    {
        public Vector3 translate;
        public Vector3 rotate;
        public Vector3 scale;
        public Model model;
        public Boolean visible;
        public String name;

        public Model3D()
        {
            scale = new Vector3(1.0f);
            translate = new Vector3(0.0f);
            rotate = new Vector3(0.0f);
            visible = true;
        }

        public void Draw(Camera camera)
        {
            if (!visible) return;
            foreach (ModelMesh mesh in model.Meshes)
            {
                foreach (BasicEffect e in mesh.Effects)
                {
                    e.EnableDefaultLighting();

                    e.World = GetWorld(mesh);
                    e.View = camera.ViewMatrix;
                    e.Projection = camera.ProjectionMatrix;
                }
                mesh.Draw();
            }
        }

        public Matrix GetWorld(ModelMesh mesh)
        {
            Matrix[] transforms = new Matrix[model.Bones.Count];
            model.CopyAbsoluteBoneTransformsTo(transforms);
            Matrix s = Matrix.CreateScale(scale);
            Matrix trans = Matrix.CreateTranslation(translate.X, translate.Y, translate.Z);

            Matrix rotX = Matrix.CreateRotationX((rotate.X * MathHelper.Pi * 2) / 360);
            Matrix rotY = Matrix.CreateRotationY((rotate.Y * MathHelper.Pi * 2) / 360);
            Matrix rotZ = Matrix.CreateRotationZ((rotate.Z * MathHelper.Pi * 2) / 360);

            return transforms[mesh.ParentBone.Index] * s * rotX * rotY * rotZ * trans;
        }

        public void RotateX(int r)
        {
            this.rotate.X = r;
        }

        public void RotateY(int r)
        {
            this.rotate.Y = r;
        }

        public void RotateZ(int r)
        {
            this.rotate.Z = r;
        }

        public void Scale(Vector3 scale)
        {
            this.scale = scale;
        }

        public void Scale(float scale)
        {
            this.scale = new Vector3(scale, scale, scale);
        }

        public void Translate(Vector3 translation)
        {
            this.translate = translation;
        }
    }
}
