namespace _3DTest
{
    partial class SceneEditor
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.fileDialog = new System.Windows.Forms.OpenFileDialog();
            this.loadModelButton = new System.Windows.Forms.Button();
            this.modelList = new System.Windows.Forms.ComboBox();
            this.exportButton = new System.Windows.Forms.Button();
            this.importButton = new System.Windows.Forms.Button();
            this.pctSurface = new System.Windows.Forms.PictureBox();
            this.showGrid = new System.Windows.Forms.CheckBox();
            this.frontButton = new System.Windows.Forms.Button();
            this.rightButton = new System.Windows.Forms.Button();
            this.bottomButton = new System.Windows.Forms.Button();
            this.leftButton = new System.Windows.Forms.Button();
            this.topButton = new System.Windows.Forms.Button();
            this.backButton = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.pctSurface)).BeginInit();
            this.SuspendLayout();
            // 
            // fileDialog
            // 
            this.fileDialog.FileName = "fileDialog";
            this.fileDialog.Filter = ".FBX|*.fbx";
            this.fileDialog.InitialDirectory = "Visual Studio 2010/";
            // 
            // loadModelButton
            // 
            this.loadModelButton.Location = new System.Drawing.Point(26, 75);
            this.loadModelButton.Name = "loadModelButton";
            this.loadModelButton.Size = new System.Drawing.Size(75, 23);
            this.loadModelButton.TabIndex = 2;
            this.loadModelButton.Text = "Load Model";
            this.loadModelButton.UseVisualStyleBackColor = true;
            this.loadModelButton.Click += new System.EventHandler(this.button1_Click);
            // 
            // modelList
            // 
            this.modelList.CausesValidation = false;
            this.modelList.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.modelList.FormattingEnabled = true;
            this.modelList.ImeMode = System.Windows.Forms.ImeMode.Off;
            this.modelList.Location = new System.Drawing.Point(26, 36);
            this.modelList.Name = "modelList";
            this.modelList.Size = new System.Drawing.Size(80, 21);
            this.modelList.TabIndex = 3;
            this.modelList.TabStop = false;
            this.modelList.SelectedIndexChanged += new System.EventHandler(this.modelList_SelectedIndexChanged);
            // 
            // exportButton
            // 
            this.exportButton.Location = new System.Drawing.Point(26, 104);
            this.exportButton.Name = "exportButton";
            this.exportButton.Size = new System.Drawing.Size(75, 23);
            this.exportButton.TabIndex = 28;
            this.exportButton.Text = "Export";
            this.exportButton.UseVisualStyleBackColor = true;
            this.exportButton.Click += new System.EventHandler(this.exportButton_Click);
            // 
            // importButton
            // 
            this.importButton.Location = new System.Drawing.Point(107, 104);
            this.importButton.Name = "importButton";
            this.importButton.Size = new System.Drawing.Size(75, 23);
            this.importButton.TabIndex = 29;
            this.importButton.Text = "Import";
            this.importButton.UseVisualStyleBackColor = true;
            this.importButton.Click += new System.EventHandler(this.importButton_Click);
            // 
            // pctSurface
            // 
            this.pctSurface.Location = new System.Drawing.Point(227, 36);
            this.pctSurface.Name = "pctSurface";
            this.pctSurface.Size = new System.Drawing.Size(600, 600);
            this.pctSurface.TabIndex = 0;
            this.pctSurface.TabStop = false;
            // 
            // showGrid
            // 
            this.showGrid.AutoSize = true;
            this.showGrid.Checked = true;
            this.showGrid.CheckState = System.Windows.Forms.CheckState.Checked;
            this.showGrid.Location = new System.Drawing.Point(109, 79);
            this.showGrid.Name = "showGrid";
            this.showGrid.Size = new System.Drawing.Size(73, 17);
            this.showGrid.TabIndex = 30;
            this.showGrid.Text = "Show grid";
            this.showGrid.UseVisualStyleBackColor = true;
            // 
            // frontButton
            // 
            this.frontButton.Location = new System.Drawing.Point(26, 151);
            this.frontButton.Name = "frontButton";
            this.frontButton.Size = new System.Drawing.Size(48, 26);
            this.frontButton.TabIndex = 31;
            this.frontButton.Text = "Front";
            this.frontButton.UseVisualStyleBackColor = true;
            this.frontButton.Click += new System.EventHandler(this.frontButton_Click);
            // 
            // rightButton
            // 
            this.rightButton.Location = new System.Drawing.Point(80, 183);
            this.rightButton.Name = "rightButton";
            this.rightButton.Size = new System.Drawing.Size(48, 26);
            this.rightButton.TabIndex = 32;
            this.rightButton.Text = "Right";
            this.rightButton.UseVisualStyleBackColor = true;
            this.rightButton.Click += new System.EventHandler(this.rightButton_Click);
            // 
            // bottomButton
            // 
            this.bottomButton.Location = new System.Drawing.Point(80, 215);
            this.bottomButton.Name = "bottomButton";
            this.bottomButton.Size = new System.Drawing.Size(48, 26);
            this.bottomButton.TabIndex = 33;
            this.bottomButton.Text = "Bottom";
            this.bottomButton.UseVisualStyleBackColor = true;
            this.bottomButton.Click += new System.EventHandler(this.bottomButton_Click);
            // 
            // leftButton
            // 
            this.leftButton.Location = new System.Drawing.Point(26, 183);
            this.leftButton.Name = "leftButton";
            this.leftButton.Size = new System.Drawing.Size(48, 26);
            this.leftButton.TabIndex = 34;
            this.leftButton.Text = "Left";
            this.leftButton.UseVisualStyleBackColor = true;
            this.leftButton.Click += new System.EventHandler(this.leftButton_Click);
            // 
            // topButton
            // 
            this.topButton.Location = new System.Drawing.Point(26, 215);
            this.topButton.Name = "topButton";
            this.topButton.Size = new System.Drawing.Size(48, 26);
            this.topButton.TabIndex = 35;
            this.topButton.Text = "Top";
            this.topButton.UseVisualStyleBackColor = true;
            this.topButton.Click += new System.EventHandler(this.topButton_Click);
            // 
            // backButton
            // 
            this.backButton.Location = new System.Drawing.Point(80, 151);
            this.backButton.Name = "backButton";
            this.backButton.Size = new System.Drawing.Size(48, 26);
            this.backButton.TabIndex = 36;
            this.backButton.Text = "Back";
            this.backButton.UseVisualStyleBackColor = true;
            this.backButton.Click += new System.EventHandler(this.backButton_Click);
            // 
            // SceneEditor
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(904, 675);
            this.Controls.Add(this.backButton);
            this.Controls.Add(this.topButton);
            this.Controls.Add(this.leftButton);
            this.Controls.Add(this.bottomButton);
            this.Controls.Add(this.rightButton);
            this.Controls.Add(this.frontButton);
            this.Controls.Add(this.showGrid);
            this.Controls.Add(this.pctSurface);
            this.Controls.Add(this.importButton);
            this.Controls.Add(this.exportButton);
            this.Controls.Add(this.modelList);
            this.Controls.Add(this.loadModelButton);
            this.Name = "SceneEditor";
            this.Text = "SceneEditor";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.SceneEditor_FormClosed);
            ((System.ComponentModel.ISupportInitialize)(this.pctSurface)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        public System.Windows.Forms.OpenFileDialog fileDialog;
        private System.Windows.Forms.Button loadModelButton;
        public System.Windows.Forms.ComboBox modelList;
        private System.Windows.Forms.Button exportButton;
        private System.Windows.Forms.Button importButton;
        public System.Windows.Forms.PictureBox pctSurface;
        public System.Windows.Forms.CheckBox showGrid;
        private System.Windows.Forms.Button frontButton;
        private System.Windows.Forms.Button backButton;
        private System.Windows.Forms.Button leftButton;
        private System.Windows.Forms.Button rightButton;
        private System.Windows.Forms.Button topButton;
        private System.Windows.Forms.Button bottomButton;
    }
}