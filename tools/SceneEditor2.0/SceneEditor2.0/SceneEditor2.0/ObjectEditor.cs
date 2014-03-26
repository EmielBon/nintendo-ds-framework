using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using System.IO;

/*namespace GameEditor
{
    class ObjectEditor : Editor
    {
       void HandleSelecting()
        {
            int width = MeshIdRender.Width;
            int height = MeshIdRender.Height;

            Color[] pixels = new Color[width * height];
            MeshIdRender.GetData(pixels);

            if (!InputState.MouseInClientArea())
                return;
            MouseState mouse = InputState.MouseState;
            Color colorId = pixels[mouse.X + mouse.Y * width];

            if (SelectedModel.Id != colorId.R)
                return;

            if (colorId.G == 255)
                return;
            SelectedMesh = SelectedModel.Meshes[colorId.G];
        }

        void SelectTexture()
        {
            if (SelectedMesh == null)
                return;

            var dialog = new System.Windows.Forms.OpenFileDialog();
            dialog.Filter = "Portable Network Graphics (*.png)|*.png|All files (*.*)|*.*";
            dialog.InitialDirectory = NDSFrameworkHelper.TexturesDirectory;

            if (dialog.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                int modelId = Models.Count;
                for (int i = 0; i < Models.Count; ++i)
                {
                    if (Models[i].MarkedForDeletion)
                    {
                        modelId = i;
                        break;
                    }
                }

                SelectedMesh.Texture = Texture2D.FromStream(SelectedMesh.Texture.GraphicsDevice, File.OpenRead(dialog.FileName));
            }
        }
    }
}
*/