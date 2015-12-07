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
using System.IO;

namespace Server
{
    public partial class Sever : Form
    {

        bool continueListening = false;

        public Sever()
        {
            InitializeComponent();
            PopulateTreeView();
            this.treeExplorer.NodeMouseClick +=
                new TreeNodeMouseClickEventHandler(this.treeExplorer_NodeMouseClick);

        }

        private void PopulateTreeView()
        {
            TreeNode rootNode;

            DirectoryInfo info = new DirectoryInfo(@"../..");
            if (info.Exists)
            {
                rootNode = new TreeNode(info.Name);
                rootNode.Tag = info;
                GetDirectories(info.GetDirectories(), rootNode);
                treeExplorer.Nodes.Add(rootNode);
            }
        }

        private void GetDirectories(DirectoryInfo[] subDirs, TreeNode nodeToAddTo)
        {
            try
            { 
                TreeNode aNode;
                DirectoryInfo[] subSubDirs;
                foreach (DirectoryInfo subDir in subDirs)
                {
                    aNode = new TreeNode(subDir.Name, 0, 0);
                    aNode.Tag = subDir;
                    aNode.ImageKey = "folder";
                    subSubDirs = subDir.GetDirectories();
                    if (subSubDirs.Length != 0)
                    {
                        GetDirectories(subSubDirs, aNode);
                    }
                    nodeToAddTo.Nodes.Add(aNode);
                }
            }
            catch (System.UnauthorizedAccessException)
            {
                return;
            }
        }

        private void ResizeColumnHeaders()
        {
            for (int i = 0; i < this.listStatus.Columns.Count - 1; i++) this.listStatus.AutoResizeColumn(i, ColumnHeaderAutoResizeStyle.ColumnContent);
            this.listStatus.Columns[this.listStatus.Columns.Count - 1].Width = -2;
        }

        private async void buttonAction_Click(object sender, EventArgs e)
        {

            Button b = buttonAction;
            b.Text = "Listening for Messages...";

            ListViewItem starting_line = new ListViewItem("Server started at " + DateTime.Now.ToShortDateString());
            listStatus.Items.Add(starting_line);

            continueListening = true;

            try { 
            String returnLine = await ListenForMessages();
                returnLine += " at " + DateTime.Now.ToShortDateString();
            listStatus.Items.Add( new ListViewItem(returnLine.ToString()));
            //ResizeColumnHeaders();
            }
            catch(Exception ex) { MessageBox.Show(ex.Message, "Error"); }
            //ListenForMessages();

            b.Text = "Start Listening!";
        }

        public async Task<String> ListenForMessages()
        {
            return ServerSocket.task_runner();

            //try
            //{
            //    string returnLine = await Task.FromResult<string>(ServerSocket.task_runner());
            //    MessageBox.Show(returnLine);
            //    //Task.FromResult<string>(ServerSocket.task_runner());
            //    //listStatus.Items.Add(returnLine.ToString());
            //    //ResizeColumnHeaders();
            //}
            //catch (Exception ex)
            //{
            //    MessageBox.Show(ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            //}

            //// Recursive Call - Will ensure always listening until stopped
            //if (continueListening)
                
            //    //ListenForMessages();

            //return null;
        }

        private void Sever_Load(object sender, EventArgs e)
        {

        }

        private void treeExplorer_NodeMouseClick(object sender, TreeNodeMouseClickEventArgs e)
        {

            TreeNode newSelected = e.Node;
            listExplorer.Items.Clear();
            DirectoryInfo nodeDirInfo = (DirectoryInfo)newSelected.Tag;
            ListViewItem.ListViewSubItem[] subItems;
            ListViewItem item = null;

            foreach (DirectoryInfo dir in nodeDirInfo.GetDirectories())
            {
                item = new ListViewItem(dir.Name, 0);
                subItems = new ListViewItem.ListViewSubItem[]
                          {new ListViewItem.ListViewSubItem(item, "Directory"),
                   new ListViewItem.ListViewSubItem(item,
                dir.LastAccessTime.ToShortDateString())};
                item.SubItems.AddRange(subItems);
                listExplorer.Items.Add(item);
            }
            foreach (FileInfo file in nodeDirInfo.GetFiles())
            {
                item = new ListViewItem(file.Name, 1);
                subItems = new ListViewItem.ListViewSubItem[]
                          { new ListViewItem.ListViewSubItem(item, "File"),
                   new ListViewItem.ListViewSubItem(item,
                file.LastAccessTime.ToShortDateString())};

                item.SubItems.AddRange(subItems);
                listExplorer.Items.Add(item);
            }

            listExplorer.AutoResizeColumns(ColumnHeaderAutoResizeStyle.HeaderSize);
        }
    }
}
