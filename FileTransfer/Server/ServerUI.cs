using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using ServerInterface;

namespace Server
{
    public partial class Sever : Form
    {
        public Sever()
        {
            InitializeComponent();
        }

        private void ResizeColumnHeaders()
        {
            for (int i = 0; i < this.listStatus.Columns.Count - 1; i++) this.listStatus.AutoResizeColumn(i, ColumnHeaderAutoResizeStyle.ColumnContent);
            this.listStatus.Columns[this.listStatus.Columns.Count - 1].Width = -2;
        }

        private async void buttonAction_Click(object sender, EventArgs e)
        {
            ListViewItem starting_line = new ListViewItem("Server started at " + DateTime.Now.ToShortDateString());
            listStatus.Items.Add(starting_line);
            do
            {
                try
                {
                    String returnline = await ExampleMethodAsync();
                    listStatus.Items.Add(returnline);
                    ResizeColumnHeaders();
                }
                catch (Exception)
                {
                }
            } while (true);
        }

        public async Task<String> ExampleMethodAsync()
        {
            try
            {
                
                string server_status = await Task.FromResult<string>(ServerSocket.task_runner());

                return "Message Received!";
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return "Error...";
            }
        }

    }
}
