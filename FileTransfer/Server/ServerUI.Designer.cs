namespace Server
{
    partial class Sever
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Sever));
            this.buttonAction = new System.Windows.Forms.Button();
            this.treeExplorer = new System.Windows.Forms.TreeView();
            this.imageList1 = new System.Windows.Forms.ImageList(this.components);
            this.listExplorer = new System.Windows.Forms.ListView();
            this.columnHeader1 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnHeader2 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnHeader3 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.listStatus = new System.Windows.Forms.ListBox();
            this.panelInfo = new System.Windows.Forms.Panel();
            this.labelIp = new System.Windows.Forms.Label();
            this.textIp = new System.Windows.Forms.TextBox();
            this.labelPort = new System.Windows.Forms.Label();
            this.textPort = new System.Windows.Forms.TextBox();
            this.panelInfo.SuspendLayout();
            this.SuspendLayout();
            // 
            // buttonAction
            // 
            this.buttonAction.BackColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.buttonAction.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.buttonAction.ForeColor = System.Drawing.Color.Lime;
            this.buttonAction.Location = new System.Drawing.Point(0, 383);
            this.buttonAction.Name = "buttonAction";
            this.buttonAction.Size = new System.Drawing.Size(797, 32);
            this.buttonAction.TabIndex = 0;
            this.buttonAction.Text = "Start Listening";
            this.buttonAction.UseVisualStyleBackColor = false;
            this.buttonAction.Click += new System.EventHandler(this.buttonAction_Click);
            // 
            // treeExplorer
            // 
            this.treeExplorer.BackColor = System.Drawing.SystemColors.MenuText;
            this.treeExplorer.Dock = System.Windows.Forms.DockStyle.Left;
            this.treeExplorer.ForeColor = System.Drawing.Color.Lime;
            this.treeExplorer.ImageIndex = 0;
            this.treeExplorer.ImageList = this.imageList1;
            this.treeExplorer.Location = new System.Drawing.Point(0, 0);
            this.treeExplorer.Name = "treeExplorer";
            this.treeExplorer.SelectedImageIndex = 0;
            this.treeExplorer.Size = new System.Drawing.Size(185, 383);
            this.treeExplorer.TabIndex = 2;
            this.treeExplorer.NodeMouseClick += new System.Windows.Forms.TreeNodeMouseClickEventHandler(this.treeExplorer_NodeMouseClick);
            // 
            // imageList1
            // 
            this.imageList1.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("imageList1.ImageStream")));
            this.imageList1.TransparentColor = System.Drawing.Color.Transparent;
            this.imageList1.Images.SetKeyName(0, "icon-dir.gif");
            this.imageList1.Images.SetKeyName(1, "File_icon.png");
            this.imageList1.Images.SetKeyName(2, "text.png");
            // 
            // listExplorer
            // 
            this.listExplorer.BackColor = System.Drawing.SystemColors.InfoText;
            this.listExplorer.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnHeader1,
            this.columnHeader2,
            this.columnHeader3});
            this.listExplorer.Dock = System.Windows.Forms.DockStyle.Fill;
            this.listExplorer.ForeColor = System.Drawing.Color.Lime;
            this.listExplorer.Location = new System.Drawing.Point(185, 0);
            this.listExplorer.MultiSelect = false;
            this.listExplorer.Name = "listExplorer";
            this.listExplorer.Size = new System.Drawing.Size(612, 383);
            this.listExplorer.SmallImageList = this.imageList1;
            this.listExplorer.TabIndex = 3;
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
            // listStatus
            // 
            this.listStatus.BackColor = System.Drawing.Color.Black;
            this.listStatus.Dock = System.Windows.Forms.DockStyle.Right;
            this.listStatus.ForeColor = System.Drawing.Color.Lime;
            this.listStatus.FormattingEnabled = true;
            this.listStatus.Location = new System.Drawing.Point(520, 0);
            this.listStatus.Name = "listStatus";
            this.listStatus.Size = new System.Drawing.Size(277, 383);
            this.listStatus.TabIndex = 4;
            // 
            // panelInfo
            // 
            this.panelInfo.BackColor = System.Drawing.Color.Black;
            this.panelInfo.Controls.Add(this.labelIp);
            this.panelInfo.Controls.Add(this.textIp);
            this.panelInfo.Controls.Add(this.labelPort);
            this.panelInfo.Controls.Add(this.textPort);
            this.panelInfo.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.panelInfo.ForeColor = System.Drawing.Color.Lime;
            this.panelInfo.Location = new System.Drawing.Point(185, 346);
            this.panelInfo.Name = "panelInfo";
            this.panelInfo.Size = new System.Drawing.Size(335, 37);
            this.panelInfo.TabIndex = 5;
            // 
            // labelIp
            // 
            this.labelIp.AutoSize = true;
            this.labelIp.Location = new System.Drawing.Point(114, 11);
            this.labelIp.Name = "labelIp";
            this.labelIp.Size = new System.Drawing.Size(64, 13);
            this.labelIp.TabIndex = 3;
            this.labelIp.Text = ": IP Address";
            // 
            // textIp
            // 
            this.textIp.BackColor = System.Drawing.Color.Black;
            this.textIp.ForeColor = System.Drawing.Color.Lime;
            this.textIp.Location = new System.Drawing.Point(6, 8);
            this.textIp.Name = "textIp";
            this.textIp.Size = new System.Drawing.Size(108, 20);
            this.textIp.TabIndex = 2;
            this.textIp.Text = "127.0.0.1";
            this.textIp.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // labelPort
            // 
            this.labelPort.AutoSize = true;
            this.labelPort.Location = new System.Drawing.Point(231, 11);
            this.labelPort.Name = "labelPort";
            this.labelPort.Size = new System.Drawing.Size(29, 13);
            this.labelPort.TabIndex = 1;
            this.labelPort.Text = "Port:";
            // 
            // textPort
            // 
            this.textPort.BackColor = System.Drawing.Color.Black;
            this.textPort.ForeColor = System.Drawing.Color.Lime;
            this.textPort.Location = new System.Drawing.Point(266, 8);
            this.textPort.Name = "textPort";
            this.textPort.Size = new System.Drawing.Size(49, 20);
            this.textPort.TabIndex = 0;
            this.textPort.Text = "70007";
            this.textPort.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // Sever
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.ClientSize = new System.Drawing.Size(797, 415);
            this.Controls.Add(this.panelInfo);
            this.Controls.Add(this.listStatus);
            this.Controls.Add(this.listExplorer);
            this.Controls.Add(this.treeExplorer);
            this.Controls.Add(this.buttonAction);
            this.ForeColor = System.Drawing.SystemColors.ControlLightLight;
            this.Name = "Sever";
            this.Text = "ServerUI";
            this.panelInfo.ResumeLayout(false);
            this.panelInfo.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button buttonAction;
        private System.Windows.Forms.TreeView treeExplorer;
        private System.Windows.Forms.ImageList imageList1;
        private System.Windows.Forms.ListView listExplorer;
        private System.Windows.Forms.ColumnHeader columnHeader1;
        private System.Windows.Forms.ColumnHeader columnHeader2;
        private System.Windows.Forms.ColumnHeader columnHeader3;
        private System.Windows.Forms.ListBox listStatus;
        private System.Windows.Forms.Panel panelInfo;
        private System.Windows.Forms.TextBox textPort;
        private System.Windows.Forms.TextBox textIp;
        private System.Windows.Forms.Label labelPort;
        private System.Windows.Forms.Label labelIp;
    }
}