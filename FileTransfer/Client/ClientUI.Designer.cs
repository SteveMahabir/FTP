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
            this.panel1 = new System.Windows.Forms.Panel();
            this.labelIp = new System.Windows.Forms.Label();
            this.textIp = new System.Windows.Forms.TextBox();
            this.labelPort = new System.Windows.Forms.Label();
            this.textPort = new System.Windows.Forms.TextBox();
            this.panel2 = new System.Windows.Forms.Panel();
            this.buttonSendFile = new System.Windows.Forms.Button();
            this.textBoxMessage = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.panel1.SuspendLayout();
            this.panel2.SuspendLayout();
            this.SuspendLayout();
            // 
            // buttonSend
            // 
            this.buttonSend.BackColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.buttonSend.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.buttonSend.ForeColor = System.Drawing.Color.Lime;
            this.buttonSend.Location = new System.Drawing.Point(0, 336);
            this.buttonSend.Margin = new System.Windows.Forms.Padding(5);
            this.buttonSend.Name = "buttonSend";
            this.buttonSend.Padding = new System.Windows.Forms.Padding(5);
            this.buttonSend.Size = new System.Drawing.Size(571, 35);
            this.buttonSend.TabIndex = 0;
            this.buttonSend.Text = "Send File";
            this.buttonSend.UseVisualStyleBackColor = false;
            this.buttonSend.Click += new System.EventHandler(this.buttonSendFile_Click);
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
            this.listExplorer.SelectedIndexChanged += new System.EventHandler(this.listExplorer_SelectedIndexChanged);
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
            this.panel1.Size = new System.Drawing.Size(435, 34);
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
            // panel2
            // 
            this.panel2.Controls.Add(this.label1);
            this.panel2.Controls.Add(this.textBoxMessage);
            this.panel2.Controls.Add(this.buttonSendFile);
            this.panel2.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.panel2.Location = new System.Drawing.Point(136, 268);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(435, 34);
            this.panel2.TabIndex = 5;
            // 
            // buttonSendFile
            // 
            this.buttonSendFile.BackColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.buttonSendFile.ForeColor = System.Drawing.Color.Lime;
            this.buttonSendFile.Location = new System.Drawing.Point(0, -1);
            this.buttonSendFile.Margin = new System.Windows.Forms.Padding(5);
            this.buttonSendFile.Name = "buttonSendFile";
            this.buttonSendFile.Padding = new System.Windows.Forms.Padding(5);
            this.buttonSendFile.Size = new System.Drawing.Size(175, 33);
            this.buttonSendFile.TabIndex = 6;
            this.buttonSendFile.Text = "Send Message";
            this.buttonSendFile.UseVisualStyleBackColor = false;
            this.buttonSendFile.Click += new System.EventHandler(this.buttonSend_Click);
            // 
            // textBoxMessage
            // 
            this.textBoxMessage.BackColor = System.Drawing.Color.Black;
            this.textBoxMessage.ForeColor = System.Drawing.Color.Lime;
            this.textBoxMessage.Location = new System.Drawing.Point(266, 8);
            this.textBoxMessage.Name = "textBoxMessage";
            this.textBoxMessage.Size = new System.Drawing.Size(166, 20);
            this.textBoxMessage.TabIndex = 12;
            this.textBoxMessage.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.ForeColor = System.Drawing.Color.Lime;
            this.label1.Location = new System.Drawing.Point(183, 11);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(77, 13);
            this.label1.TabIndex = 12;
            this.label1.Text = "Message Text:";
            // 
            // ClientUI
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.ClientSize = new System.Drawing.Size(571, 371);
            this.Controls.Add(this.panel2);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.listExplorer);
            this.Controls.Add(this.treeExplorer);
            this.Controls.Add(this.buttonSend);
            this.ForeColor = System.Drawing.SystemColors.ControlLightLight;
            this.Name = "ClientUI";
            this.Text = "ClientUI";
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.panel2.ResumeLayout(false);
            this.panel2.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button buttonSend;
        private System.Windows.Forms.TreeView treeExplorer;
        private System.Windows.Forms.ListView listExplorer;
        private System.Windows.Forms.ImageList imageList1;
        private System.Windows.Forms.ColumnHeader columnHeader1;
        private System.Windows.Forms.ColumnHeader columnHeader2;
        private System.Windows.Forms.ColumnHeader columnHeader3;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Label labelIp;
        private System.Windows.Forms.TextBox textIp;
        private System.Windows.Forms.Label labelPort;
        private System.Windows.Forms.TextBox textPort;
        private System.Windows.Forms.Panel panel2;
        private System.Windows.Forms.TextBox textBoxMessage;
        private System.Windows.Forms.Button buttonSendFile;
        private System.Windows.Forms.Label label1;
    }
}