namespace Client
{
    partial class ClientUI
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
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(ClientUI));
            this.buttonSend = new System.Windows.Forms.Button();
            this.treeExplorer = new System.Windows.Forms.TreeView();
            this.imageList1 = new System.Windows.Forms.ImageList(this.components);
            this.listExplorer = new System.Windows.Forms.ListView();
            this.columnHeader1 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnHeader2 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnHeader3 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.flowLayoutPanel1 = new System.Windows.Forms.FlowLayoutPanel();
            this.buttonSendFile = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.panel1 = new System.Windows.Forms.Panel();
            this.labelIp = new System.Windows.Forms.Label();
            this.textIp = new System.Windows.Forms.TextBox();
            this.labelPort = new System.Windows.Forms.Label();
            this.textPort = new System.Windows.Forms.TextBox();
            this.flowLayoutPanel1.SuspendLayout();
            this.panel1.SuspendLayout();
            this.SuspendLayout();
            // 
            // buttonSend
            // 
            this.buttonSend.BackColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.buttonSend.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.buttonSend.Location = new System.Drawing.Point(0, 336);
            this.buttonSend.Margin = new System.Windows.Forms.Padding(5);
            this.buttonSend.Name = "buttonSend";
            this.buttonSend.Padding = new System.Windows.Forms.Padding(5);
            this.buttonSend.Size = new System.Drawing.Size(571, 35);
            this.buttonSend.TabIndex = 0;
            this.buttonSend.Text = "Send Message";
            this.buttonSend.UseVisualStyleBackColor = false;
            this.buttonSend.Click += new System.EventHandler(this.buttonSend_Click);
            // 
            // treeExplorer
            // 
            this.treeExplorer.BackColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.treeExplorer.Dock = System.Windows.Forms.DockStyle.Left;
            this.treeExplorer.ForeColor = System.Drawing.Color.Lime;
            this.treeExplorer.ImageIndex = 0;
            this.treeExplorer.ImageList = this.imageList1;
            this.treeExplorer.Location = new System.Drawing.Point(0, 0);
            this.treeExplorer.Name = "treeExplorer";
            this.treeExplorer.SelectedImageIndex = 0;
            this.treeExplorer.Size = new System.Drawing.Size(136, 336);
            this.treeExplorer.TabIndex = 1;
            this.treeExplorer.NodeMouseClick += new System.Windows.Forms.TreeNodeMouseClickEventHandler(this.treeExplorer_NodeMouseClick);
            // 
            // imageList1
            // 
            this.imageList1.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("imageList1.ImageStream")));
            this.imageList1.TransparentColor = System.Drawing.Color.Transparent;
            this.imageList1.Images.SetKeyName(0, "icon-dir.gif");
            this.imageList1.Images.SetKeyName(1, "File_icon.png");
            // 
            // listExplorer
            // 
            this.listExplorer.BackColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.listExplorer.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnHeader1,
            this.columnHeader2,
            this.columnHeader3});
            this.listExplorer.Dock = System.Windows.Forms.DockStyle.Fill;
            this.listExplorer.ForeColor = System.Drawing.Color.Lime;
            this.listExplorer.Location = new System.Drawing.Point(136, 0);
            this.listExplorer.MultiSelect = false;
            this.listExplorer.Name = "listExplorer";
            this.listExplorer.Size = new System.Drawing.Size(435, 336);
            this.listExplorer.SmallImageList = this.imageList1;
            this.listExplorer.TabIndex = 2;
            this.listExplorer.UseCompatibleStateImageBehavior = false;
            this.listExplorer.View = System.Windows.Forms.View.Details;
            // 
            // columnHeader1
            // 
            this.columnHeader1.Text = "Name";
            // 
            // columnHeader2
            // 
            this.columnHeader2.Text = "Type";
            // 
            // columnHeader3
            // 
            this.columnHeader3.Text = "Last Modified";
            // 
            // flowLayoutPanel1
            // 
            this.flowLayoutPanel1.Controls.Add(this.buttonSendFile);
            this.flowLayoutPanel1.Controls.Add(this.button2);
            this.flowLayoutPanel1.Dock = System.Windows.Forms.DockStyle.Right;
            this.flowLayoutPanel1.Location = new System.Drawing.Point(457, 0);
            this.flowLayoutPanel1.Name = "flowLayoutPanel1";
            this.flowLayoutPanel1.Size = new System.Drawing.Size(114, 336);
            this.flowLayoutPanel1.TabIndex = 3;
            // 
            // buttonSendFile
            // 
            this.buttonSendFile.BackColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.buttonSendFile.ForeColor = System.Drawing.Color.Lime;
            this.buttonSendFile.Location = new System.Drawing.Point(3, 3);
            this.buttonSendFile.Name = "buttonSendFile";
            this.buttonSendFile.Size = new System.Drawing.Size(111, 23);
            this.buttonSendFile.TabIndex = 0;
            this.buttonSendFile.Text = "Send File";
            this.buttonSendFile.UseVisualStyleBackColor = false;
            this.buttonSendFile.Click += new System.EventHandler(this.buttonSendFile_Click);
            // 
            // button2
            // 
            this.button2.BackColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.button2.ForeColor = System.Drawing.Color.Lime;
            this.button2.Location = new System.Drawing.Point(3, 32);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(111, 23);
            this.button2.TabIndex = 1;
            this.button2.Text = "Get File";
            this.button2.UseVisualStyleBackColor = false;
            // 
            // panel1
            // 
            this.panel1.BackColor = System.Drawing.Color.Black;
            this.panel1.Controls.Add(this.labelIp);
            this.panel1.Controls.Add(this.textIp);
            this.panel1.Controls.Add(this.labelPort);
            this.panel1.Controls.Add(this.textPort);
            this.panel1.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.panel1.ForeColor = System.Drawing.Color.Lime;
            this.panel1.Location = new System.Drawing.Point(136, 302);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(321, 34);
            this.panel1.TabIndex = 4;
            // 
            // labelIp
            // 
            this.labelIp.AutoSize = true;
            this.labelIp.Location = new System.Drawing.Point(111, 9);
            this.labelIp.Name = "labelIp";
            this.labelIp.Size = new System.Drawing.Size(64, 13);
            this.labelIp.TabIndex = 11;
            this.labelIp.Text = ": IP Address";
            // 
            // textIp
            // 
            this.textIp.BackColor = System.Drawing.Color.Black;
            this.textIp.ForeColor = System.Drawing.Color.Lime;
            this.textIp.Location = new System.Drawing.Point(3, 6);
            this.textIp.Name = "textIp";
            this.textIp.Size = new System.Drawing.Size(108, 20);
            this.textIp.TabIndex = 10;
            this.textIp.Text = "127.0.0.1";
            this.textIp.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // labelPort
            // 
            this.labelPort.AutoSize = true;
            this.labelPort.Location = new System.Drawing.Point(228, 9);
            this.labelPort.Name = "labelPort";
            this.labelPort.Size = new System.Drawing.Size(29, 13);
            this.labelPort.TabIndex = 9;
            this.labelPort.Text = "Port:";
            // 
            // textPort
            // 
            this.textPort.BackColor = System.Drawing.Color.Black;
            this.textPort.ForeColor = System.Drawing.Color.Lime;
            this.textPort.Location = new System.Drawing.Point(263, 6);
            this.textPort.Name = "textPort";
            this.textPort.Size = new System.Drawing.Size(49, 20);
            this.textPort.TabIndex = 8;
            this.textPort.Text = "70007";
            this.textPort.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // ClientUI
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.ClientSize = new System.Drawing.Size(571, 371);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.flowLayoutPanel1);
            this.Controls.Add(this.listExplorer);
            this.Controls.Add(this.treeExplorer);
            this.Controls.Add(this.buttonSend);
            this.ForeColor = System.Drawing.SystemColors.ControlLightLight;
            this.Name = "ClientUI";
            this.Text = "ClientUI";
            this.flowLayoutPanel1.ResumeLayout(false);
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button buttonSend;
        private System.Windows.Forms.TreeView treeExplorer;
        private System.Windows.Forms.ListView listExplorer;
        private System.Windows.Forms.FlowLayoutPanel flowLayoutPanel1;
        private System.Windows.Forms.Button buttonSendFile;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.ImageList imageList1;
        private System.Windows.Forms.ColumnHeader columnHeader1;
        private System.Windows.Forms.ColumnHeader columnHeader2;
        private System.Windows.Forms.ColumnHeader columnHeader3;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Label labelIp;
        private System.Windows.Forms.TextBox textIp;
        private System.Windows.Forms.Label labelPort;
        private System.Windows.Forms.TextBox textPort;
    }
}