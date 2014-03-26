namespace MapEditor
{
    partial class Form1
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
            this.MenuBar = new System.Windows.Forms.MenuStrip();
            this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.openToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.saveToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.importToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.exportToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.exitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.tilesetToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.selectToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.TilePanel = new System.Windows.Forms.Panel();
            this.NoTileSetLabel = new System.Windows.Forms.Label();
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.StatusLabel = new System.Windows.Forms.ToolStripStatusLabel();
            this.MapPanel = new System.Windows.Forms.Panel();
            this.panel1 = new System.Windows.Forms.Panel();
            this.collisionBox = new System.Windows.Forms.CheckBox();
            this.SnapHeightChanger = new System.Windows.Forms.NumericUpDown();
            this.label5 = new System.Windows.Forms.Label();
            this.SnapWidthChanger = new System.Windows.Forms.NumericUpDown();
            this.label6 = new System.Windows.Forms.Label();
            this.MapHeightChanger = new System.Windows.Forms.NumericUpDown();
            this.label4 = new System.Windows.Forms.Label();
            this.MapWidthChanger = new System.Windows.Forms.NumericUpDown();
            this.label3 = new System.Windows.Forms.Label();
            this.ShowGridCheckBox = new System.Windows.Forms.CheckBox();
            this.TileHeightChanger = new System.Windows.Forms.NumericUpDown();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.TileWidthChanger = new System.Windows.Forms.NumericUpDown();
            this.MenuBar.SuspendLayout();
            this.TilePanel.SuspendLayout();
            this.statusStrip1.SuspendLayout();
            this.panel1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.SnapHeightChanger)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.SnapWidthChanger)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.MapHeightChanger)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.MapWidthChanger)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.TileHeightChanger)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.TileWidthChanger)).BeginInit();
            this.SuspendLayout();
            // 
            // MenuBar
            // 
            this.MenuBar.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem,
            this.tilesetToolStripMenuItem});
            this.MenuBar.Location = new System.Drawing.Point(0, 0);
            this.MenuBar.Name = "MenuBar";
            this.MenuBar.Size = new System.Drawing.Size(804, 24);
            this.MenuBar.TabIndex = 0;
            this.MenuBar.Text = "menuStrip1";
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.openToolStripMenuItem,
            this.saveToolStripMenuItem,
            this.importToolStripMenuItem,
            this.exportToolStripMenuItem,
            this.exitToolStripMenuItem});
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(37, 20);
            this.fileToolStripMenuItem.Text = "File";
            // 
            // openToolStripMenuItem
            // 
            this.openToolStripMenuItem.Name = "openToolStripMenuItem";
            this.openToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.openToolStripMenuItem.Text = "Open...";
            // 
            // saveToolStripMenuItem
            // 
            this.saveToolStripMenuItem.Name = "saveToolStripMenuItem";
            this.saveToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.saveToolStripMenuItem.Text = "Save...";
            this.saveToolStripMenuItem.Click += new System.EventHandler(this.saveToolStripMenuItem_Click);
            // 
            // importToolStripMenuItem
            // 
            this.importToolStripMenuItem.Name = "importToolStripMenuItem";
            this.importToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.importToolStripMenuItem.Text = "Import...";
            this.importToolStripMenuItem.Click += new System.EventHandler(this.importToolStripMenuItem_Click);
            // 
            // exportToolStripMenuItem
            // 
            this.exportToolStripMenuItem.Name = "exportToolStripMenuItem";
            this.exportToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.exportToolStripMenuItem.Text = "Export...";
            // 
            // exitToolStripMenuItem
            // 
            this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
            this.exitToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.exitToolStripMenuItem.Text = "Exit";
            // 
            // tilesetToolStripMenuItem
            // 
            this.tilesetToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.selectToolStripMenuItem});
            this.tilesetToolStripMenuItem.Name = "tilesetToolStripMenuItem";
            this.tilesetToolStripMenuItem.Size = new System.Drawing.Size(53, 20);
            this.tilesetToolStripMenuItem.Text = "Tileset";
            // 
            // selectToolStripMenuItem
            // 
            this.selectToolStripMenuItem.Name = "selectToolStripMenuItem";
            this.selectToolStripMenuItem.Size = new System.Drawing.Size(114, 22);
            this.selectToolStripMenuItem.Text = "Select...";
            this.selectToolStripMenuItem.Click += new System.EventHandler(this.selectToolStripMenuItem_Click);
            // 
            // TilePanel
            // 
            this.TilePanel.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.TilePanel.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.TilePanel.Controls.Add(this.NoTileSetLabel);
            this.TilePanel.Location = new System.Drawing.Point(548, 57);
            this.TilePanel.Name = "TilePanel";
            this.TilePanel.Size = new System.Drawing.Size(256, 352);
            this.TilePanel.TabIndex = 1;
            this.TilePanel.Click += new System.EventHandler(this.TilePanel_Click);
            this.TilePanel.Paint += new System.Windows.Forms.PaintEventHandler(this.TilePanel_Paint);
            this.TilePanel.MouseMove += new System.Windows.Forms.MouseEventHandler(this.TilePanel_MouseMove);
            // 
            // NoTileSetLabel
            // 
            this.NoTileSetLabel.AutoSize = true;
            this.NoTileSetLabel.Enabled = false;
            this.NoTileSetLabel.ForeColor = System.Drawing.SystemColors.ButtonShadow;
            this.NoTileSetLabel.Location = new System.Drawing.Point(56, 254);
            this.NoTileSetLabel.Name = "NoTileSetLabel";
            this.NoTileSetLabel.Size = new System.Drawing.Size(139, 13);
            this.NoTileSetLabel.TabIndex = 1;
            this.NoTileSetLabel.Text = "Click here to select a tile set";
            this.NoTileSetLabel.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // statusStrip1
            // 
            this.statusStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.StatusLabel});
            this.statusStrip1.Location = new System.Drawing.Point(0, 418);
            this.statusStrip1.Name = "statusStrip1";
            this.statusStrip1.Size = new System.Drawing.Size(804, 22);
            this.statusStrip1.TabIndex = 2;
            this.statusStrip1.Text = "statusStrip1";
            // 
            // StatusLabel
            // 
            this.StatusLabel.Name = "StatusLabel";
            this.StatusLabel.Size = new System.Drawing.Size(102, 17);
            this.StatusLabel.Text = "Tile under mouse:";
            // 
            // MapPanel
            // 
            this.MapPanel.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.MapPanel.BackColor = System.Drawing.SystemColors.Window;
            this.MapPanel.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.MapPanel.Location = new System.Drawing.Point(0, 57);
            this.MapPanel.Name = "MapPanel";
            this.MapPanel.Size = new System.Drawing.Size(542, 352);
            this.MapPanel.TabIndex = 3;
            this.MapPanel.Click += new System.EventHandler(this.MapPanel_Click);
            this.MapPanel.Paint += new System.Windows.Forms.PaintEventHandler(this.MapPanel_Paint);
            this.MapPanel.MouseMove += new System.Windows.Forms.MouseEventHandler(this.MapPanel_MouseMove);
            // 
            // panel1
            // 
            this.panel1.Controls.Add(this.collisionBox);
            this.panel1.Controls.Add(this.SnapHeightChanger);
            this.panel1.Controls.Add(this.label5);
            this.panel1.Controls.Add(this.SnapWidthChanger);
            this.panel1.Controls.Add(this.label6);
            this.panel1.Controls.Add(this.MapHeightChanger);
            this.panel1.Controls.Add(this.label4);
            this.panel1.Controls.Add(this.MapWidthChanger);
            this.panel1.Controls.Add(this.label3);
            this.panel1.Controls.Add(this.ShowGridCheckBox);
            this.panel1.Controls.Add(this.TileHeightChanger);
            this.panel1.Controls.Add(this.label2);
            this.panel1.Controls.Add(this.label1);
            this.panel1.Controls.Add(this.TileWidthChanger);
            this.panel1.Location = new System.Drawing.Point(1, 27);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(795, 24);
            this.panel1.TabIndex = 4;
            // 
            // collisionBox
            // 
            this.collisionBox.AutoSize = true;
            this.collisionBox.Location = new System.Drawing.Point(673, 4);
            this.collisionBox.Name = "collisionBox";
            this.collisionBox.Size = new System.Drawing.Size(107, 17);
            this.collisionBox.TabIndex = 14;
            this.collisionBox.Text = "Edit collision map";
            this.collisionBox.UseVisualStyleBackColor = true;
            // 
            // SnapHeightChanger
            // 
            this.SnapHeightChanger.Location = new System.Drawing.Point(258, 2);
            this.SnapHeightChanger.Maximum = new decimal(new int[] {
            8,
            0,
            0,
            0});
            this.SnapHeightChanger.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.SnapHeightChanger.Name = "SnapHeightChanger";
            this.SnapHeightChanger.Size = new System.Drawing.Size(28, 20);
            this.SnapHeightChanger.TabIndex = 13;
            this.SnapHeightChanger.Value = new decimal(new int[] {
            2,
            0,
            0,
            0});
            this.SnapHeightChanger.ValueChanged += new System.EventHandler(this.SnapHeightChanger_ValueChanged);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(240, 5);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(12, 13);
            this.label5.TabIndex = 12;
            this.label5.Text = "x";
            // 
            // SnapWidthChanger
            // 
            this.SnapWidthChanger.Location = new System.Drawing.Point(206, 2);
            this.SnapWidthChanger.Maximum = new decimal(new int[] {
            8,
            0,
            0,
            0});
            this.SnapWidthChanger.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.SnapWidthChanger.Name = "SnapWidthChanger";
            this.SnapWidthChanger.Size = new System.Drawing.Size(28, 20);
            this.SnapWidthChanger.TabIndex = 11;
            this.SnapWidthChanger.Value = new decimal(new int[] {
            2,
            0,
            0,
            0});
            this.SnapWidthChanger.ValueChanged += new System.EventHandler(this.SnapWidthChanger_ValueChanged);
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(165, 5);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(35, 13);
            this.label6.TabIndex = 10;
            this.label6.Text = "Snap:";
            // 
            // MapHeightChanger
            // 
            this.MapHeightChanger.Location = new System.Drawing.Point(122, 2);
            this.MapHeightChanger.Maximum = new decimal(new int[] {
            64,
            0,
            0,
            0});
            this.MapHeightChanger.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.MapHeightChanger.Name = "MapHeightChanger";
            this.MapHeightChanger.Size = new System.Drawing.Size(37, 20);
            this.MapHeightChanger.TabIndex = 9;
            this.MapHeightChanger.Value = new decimal(new int[] {
            24,
            0,
            0,
            0});
            this.MapHeightChanger.ValueChanged += new System.EventHandler(this.MapHeightChanger_ValueChanged);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(104, 5);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(12, 13);
            this.label4.TabIndex = 8;
            this.label4.Text = "x";
            // 
            // MapWidthChanger
            // 
            this.MapWidthChanger.Location = new System.Drawing.Point(61, 2);
            this.MapWidthChanger.Maximum = new decimal(new int[] {
            64,
            0,
            0,
            0});
            this.MapWidthChanger.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.MapWidthChanger.Name = "MapWidthChanger";
            this.MapWidthChanger.Size = new System.Drawing.Size(37, 20);
            this.MapWidthChanger.TabIndex = 7;
            this.MapWidthChanger.Value = new decimal(new int[] {
            32,
            0,
            0,
            0});
            this.MapWidthChanger.ValueChanged += new System.EventHandler(this.MapWidthChanger_ValueChanged);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(3, 5);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(52, 13);
            this.label3.TabIndex = 6;
            this.label3.Text = "Map size:";
            // 
            // ShowGridCheckBox
            // 
            this.ShowGridCheckBox.AutoSize = true;
            this.ShowGridCheckBox.Checked = true;
            this.ShowGridCheckBox.CheckState = System.Windows.Forms.CheckState.Checked;
            this.ShowGridCheckBox.Location = new System.Drawing.Point(292, 4);
            this.ShowGridCheckBox.Name = "ShowGridCheckBox";
            this.ShowGridCheckBox.Size = new System.Drawing.Size(73, 17);
            this.ShowGridCheckBox.TabIndex = 5;
            this.ShowGridCheckBox.Text = "Show grid";
            this.ShowGridCheckBox.UseVisualStyleBackColor = true;
            this.ShowGridCheckBox.CheckedChanged += new System.EventHandler(this.ShowGridCheckBox_CheckedChanged);
            // 
            // TileHeightChanger
            // 
            this.TileHeightChanger.Location = new System.Drawing.Point(639, 2);
            this.TileHeightChanger.Maximum = new decimal(new int[] {
            8,
            0,
            0,
            0});
            this.TileHeightChanger.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.TileHeightChanger.Name = "TileHeightChanger";
            this.TileHeightChanger.Size = new System.Drawing.Size(27, 20);
            this.TileHeightChanger.TabIndex = 3;
            this.TileHeightChanger.Value = new decimal(new int[] {
            2,
            0,
            0,
            0});
            this.TileHeightChanger.ValueChanged += new System.EventHandler(this.TileHeightChanger_ValueChanged);
            // 
            // label2
            // 
            this.label2.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(621, 4);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(12, 13);
            this.label2.TabIndex = 2;
            this.label2.Text = "x";
            // 
            // label1
            // 
            this.label1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(535, 5);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(48, 13);
            this.label1.TabIndex = 1;
            this.label1.Text = "Tile size:";
            // 
            // TileWidthChanger
            // 
            this.TileWidthChanger.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.TileWidthChanger.Location = new System.Drawing.Point(589, 2);
            this.TileWidthChanger.Maximum = new decimal(new int[] {
            8,
            0,
            0,
            0});
            this.TileWidthChanger.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.TileWidthChanger.Name = "TileWidthChanger";
            this.TileWidthChanger.Size = new System.Drawing.Size(26, 20);
            this.TileWidthChanger.TabIndex = 0;
            this.TileWidthChanger.Value = new decimal(new int[] {
            2,
            0,
            0,
            0});
            this.TileWidthChanger.ValueChanged += new System.EventHandler(this.TileWidthChanger_ValueChanged);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(804, 440);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.MapPanel);
            this.Controls.Add(this.statusStrip1);
            this.Controls.Add(this.TilePanel);
            this.Controls.Add(this.MenuBar);
            this.MainMenuStrip = this.MenuBar;
            this.MinimumSize = new System.Drawing.Size(639, 478);
            this.Name = "Form1";
            this.Text = "Nintendo DS Map Editor by Emiel";
            this.ResizeEnd += new System.EventHandler(this.Form1_ResizeEnd);
            this.MenuBar.ResumeLayout(false);
            this.MenuBar.PerformLayout();
            this.TilePanel.ResumeLayout(false);
            this.TilePanel.PerformLayout();
            this.statusStrip1.ResumeLayout(false);
            this.statusStrip1.PerformLayout();
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.SnapHeightChanger)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.SnapWidthChanger)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.MapHeightChanger)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.MapWidthChanger)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.TileHeightChanger)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.TileWidthChanger)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip MenuBar;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem openToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem saveToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem importToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem exportToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem exitToolStripMenuItem;
        private System.Windows.Forms.Panel TilePanel;
        private System.Windows.Forms.StatusStrip statusStrip1;
        private System.Windows.Forms.Panel MapPanel;
        private System.Windows.Forms.Label NoTileSetLabel;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.NumericUpDown TileWidthChanger;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.NumericUpDown TileHeightChanger;
        private System.Windows.Forms.CheckBox ShowGridCheckBox;
        private System.Windows.Forms.ToolStripMenuItem tilesetToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem selectToolStripMenuItem;
        private System.Windows.Forms.NumericUpDown MapHeightChanger;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.NumericUpDown MapWidthChanger;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.NumericUpDown SnapHeightChanger;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.NumericUpDown SnapWidthChanger;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.ToolStripStatusLabel StatusLabel;
        private System.Windows.Forms.CheckBox collisionBox;
    }
}

