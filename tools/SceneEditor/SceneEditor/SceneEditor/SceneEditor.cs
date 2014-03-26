using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using Microsoft.Xna.Framework;
using System.IO;
using System.Text.RegularExpressions;

namespace _3DTest
{
   
    public partial class SceneEditor : Form
    {
        
        public Game1 game;
        public List<String> models;
        public SceneEditor()
        {
            InitializeComponent();
            models = new List<String>();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            LoadModel();
        }

        public void LoadModel()
        {
            DialogResult result = fileDialog.ShowDialog();
            if (result == DialogResult.OK)
            {
                String fileName = Path.GetFileNameWithoutExtension(fileDialog.FileName);
                models.Add(fileName);
                game.addModel(fileName);

                // Add the model to the drop down list.
                modelList.Items.Add(fileName);
                modelList.SelectedIndex = modelList.Items.Count - 1;
                game.selectedModel = game.models[modelList.SelectedIndex];
            }
        }

        private void modelList_SelectedIndexChanged(object sender, EventArgs e)
        {
            game.selectedModel = game.models[modelList.SelectedIndex];
        }

        private void exportButton_Click(object sender, EventArgs e)
        {
            Export();
        }

        public String Vector3ToString(Vector3 v)
        {
            return v.X + " " + v.Y + " " + v.Z;
        }

        private void importButton_Click(object sender, EventArgs e)
        {
            Import();
        }

        public void Export()
        {
            FileStream stream = new FileStream("scene.bin", FileMode.Create);
            StreamWriter output = new StreamWriter(stream);
            for (int i = 0; i < models.Count; ++i)
            {
                Model3D m = game.models[i];
                output.Write(m.name + " ");
                output.Write(Vector3ToString(m.translate) + " ");
                output.Write(Vector3ToString(m.scale) + " ");
                output.Write(Vector3ToString(m.rotate));
                if (i < models.Count - 1)
                    output.Write("\r\n");
            }
            output.Close();
        }

        public void Import()
        {
            String file = new StreamReader("scene.bin").ReadToEnd();
            String[] lines = Regex.Split(file, "\r\n");
            foreach (String line in lines)
            {
                String[] model = line.Split(' ');
                models.Add(model[0]);
                game.addModel(model[0]);
                modelList.Items.Add(model[0]);
                modelList.SelectedIndex = modelList.Items.Count - 1;
                game.selectedModel = game.models[modelList.SelectedIndex];
                game.selectedModel.Translate(new Vector3(float.Parse(model[1]), float.Parse(model[2]), float.Parse(model[3])));
                game.selectedModel.Scale(new Vector3(float.Parse(model[4]), float.Parse(model[5]), float.Parse(model[6])));
                game.selectedModel.RotateX(int.Parse(model[7]));
                game.selectedModel.RotateY(int.Parse(model[8]));
                game.selectedModel.RotateZ(int.Parse(model[9]));
            }
        }

        private void SceneEditor_FormClosed(object sender, FormClosedEventArgs e)
        {
            game.Exit();
            Application.Exit();
        }

        private void frontButton_Click(object sender, EventArgs e)
        {
            game.camera.Eye = game.camera.Eye.Length() * View.Front;
        }

        private void backButton_Click(object sender, EventArgs e)
        {
            game.camera.Eye = game.camera.Eye.Length() * View.Back;
        }

        private void leftButton_Click(object sender, EventArgs e)
        {
            game.camera.Eye = game.camera.Eye.Length() * View.Left;
        }

        private void rightButton_Click(object sender, EventArgs e)
        {
            game.camera.Eye = game.camera.Eye.Length() * View.Right;
        }

        private void topButton_Click(object sender, EventArgs e)
        {
            game.camera.Eye = game.camera.Eye.Length() * View.Top;
        }

        private void bottomButton_Click(object sender, EventArgs e)
        {
            game.camera.Eye = game.camera.Eye.Length() * View.Bottom;
        }
    }
}
