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
            this.buttonAction = new System.Windows.Forms.Button();
            this.listStatus = new System.Windows.Forms.ListView();
            this.SuspendLayout();
            // 
            // buttonAction
            // 
            this.buttonAction.BackColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.buttonAction.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.buttonAction.Location = new System.Drawing.Point(0, 310);
            this.buttonAction.Name = "buttonAction";
            this.buttonAction.Size = new System.Drawing.Size(394, 32);
            this.buttonAction.TabIndex = 0;
            this.buttonAction.Text = "Action";
            this.buttonAction.UseVisualStyleBackColor = false;
            this.buttonAction.Click += new System.EventHandler(this.buttonAction_Click);
            // 
            // listStatus
            // 
            this.listStatus.BackColor = System.Drawing.SystemColors.InactiveCaptionText;
            this.listStatus.Dock = System.Windows.Forms.DockStyle.Right;
            this.listStatus.ForeColor = System.Drawing.Color.Lime;
            this.listStatus.Location = new System.Drawing.Point(238, 0);
            this.listStatus.Name = "listStatus";
            this.listStatus.Size = new System.Drawing.Size(156, 310);
            this.listStatus.TabIndex = 1;
            this.listStatus.UseCompatibleStateImageBehavior = false;
            // 
            // Sever
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.ClientSize = new System.Drawing.Size(394, 342);
            this.Controls.Add(this.listStatus);
            this.Controls.Add(this.buttonAction);
            this.ForeColor = System.Drawing.SystemColors.ControlLightLight;
            this.Name = "Sever";
            this.Text = "ServerUI";
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button buttonAction;
        private System.Windows.Forms.ListView listStatus;
    }
}