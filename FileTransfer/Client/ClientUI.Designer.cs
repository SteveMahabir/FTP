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
            this.buttonSend = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // buttonSend
            // 
            this.buttonSend.BackColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.buttonSend.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.buttonSend.Location = new System.Drawing.Point(0, 255);
            this.buttonSend.Margin = new System.Windows.Forms.Padding(5);
            this.buttonSend.Name = "buttonSend";
            this.buttonSend.Padding = new System.Windows.Forms.Padding(5);
            this.buttonSend.Size = new System.Drawing.Size(300, 35);
            this.buttonSend.TabIndex = 0;
            this.buttonSend.Text = "Send";
            this.buttonSend.UseVisualStyleBackColor = false;
            this.buttonSend.Click += new System.EventHandler(this.buttonSend_Click);
            // 
            // ClientUI
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.ClientSize = new System.Drawing.Size(300, 290);
            this.Controls.Add(this.buttonSend);
            this.ForeColor = System.Drawing.SystemColors.ControlLightLight;
            this.Name = "ClientUI";
            this.Text = "ClientUI";
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button buttonSend;
    }
}