using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;

namespace GameEditor
{
    abstract class Model3D
    {
        public String Name;
        public List<Mesh> Meshes;
        public bool Visible = true;
        public bool MarkedForDeletion = false;
        public bool SavedTransformation = false;
        public BoundingBox bbox;
        public Transformation Transformation;
        Transformation oldTransformation;
        
        public Model3D(int id = -1, String name = "")
        {
            Id = id;
            Name = name;
            Meshes = new List<Mesh>();
            Transformation = Transformation.Identity;
            oldTransformation = Transformation.Identity;
        }

        public void MarkForDeletion()
        {
            Visible = false;
            MarkedForDeletion = true;
        }

        public int Id
        {
            get; private set;
        }

        public void AddMesh(Mesh mesh)
        {
            Meshes.Add(mesh);
        }

        public void Translate(Vector3 trans)
        {
            Transformation.Translation += trans;
        }

        public void Rotate(Vector3 rot)
        {
            Transformation.Rotation += rot;
        }

        public void Scale(Vector3 scale)
        {
            Transformation.Scaling += scale;
        }

        public BoundingBox BoundingBox
        {
            // Todo: Include non-uniform scaling
            get { return new BoundingBox(bbox.Min, bbox.Max); }
            set { bbox = value; }
        }

        public Vector3 Center
        {
            get { return (bbox.Max - bbox.Min) / 2 + Transformation.Translation; }
        }

        public BoundingBox BoundingBoxFromMeshes()
        {
            Vector3 min = new Vector3(float.MaxValue);
            Vector3 max = new Vector3(float.MinValue);
            foreach (Mesh m in Meshes)
            {
                BoundingBox bbox = m.BoundingBox;
                if (bbox.Min.X < min.X) min.X = bbox.Min.X;
                if (bbox.Min.Y < min.Y) min.Y = bbox.Min.Y;
                if (bbox.Min.Z < min.Z) min.Z = bbox.Min.Z;
                if (bbox.Max.X > max.X) max.X = bbox.Max.X;
                if (bbox.Max.Y > max.Y) max.Y = bbox.Max.Y;
                if (bbox.Max.Z > max.Z) max.Z = bbox.Max.Z;
            }
            return new BoundingBox(min, max);
        }

        public void SaveTransformation()
        {
            oldTransformation = Transformation;
            SavedTransformation = true;
        }

        public void ResetTransformation()
        {
            Transformation = oldTransformation;
            SavedTransformation = false;
        }

        public abstract Matrix TransformationMatrix { get; }

        public static Model3D Parse(String[] input)
        {
            int keyFrameIndex = 0;
            var keyFrameControl = Editor.Instance.KeyFrameControl;
            Model3D model = null;

            for (int i = 0; i < input.Length; ++i)
            {
                var line = input[i];
                string[] tokens = line.Split('=');
                if (tokens[0].StartsWith("model"))
                {
                    model = Editor.Instance.LoadModel(tokens[1], false);
                    Editor.Instance.AddModel(model);
                }
                if (tokens[0].StartsWith("keyframe"))
                {
                    keyFrameIndex = int.Parse(tokens[0].Substring("keyframe".Length));
                    keyFrameControl.InsertKeyFrame(model, keyFrameIndex);

                    String str = input[++i] + "\n" + input[++i] + "\n" + input[++i] + "\n";
                    keyFrameControl.SetTransformation(model, keyFrameIndex, Transformation.Parse(str));
                }
            }

            return model;
        }
        
        public String ToExportFormat()
        {
            var keyFrameControl = Editor.Instance.KeyFrameControl;
            var keyFrames = keyFrameControl.KeyFrameIndicesForModel[this];

            String str = "GameObject{";
            str += String.Format("model = {0};", Name);
            foreach (var i in keyFrames)
            {
                var transformation = keyFrameControl.GetTransformation(this, i);
                str += String.Format("keyframe{0} {{ {1} }}", i, transformation.ToExportFormat());
            }
            str += "}";

            return str;
        }
    }
}
