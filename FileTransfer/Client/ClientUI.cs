using System;
using System.IO;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using ClientInterface;
using System.Net;

namespace Client
{
    // Main Client UI
    public partial class ClientUI : Form
    {
        // Data Members
        String _ipaddress;
        uint _portnumber;
        String _file;
        String _directory;

        // Constructor
        public ClientUI()
        {
            InitializeComponent();

            // Populate the Explorer
            PopulateTreeView();
            this.treeExplorer.NodeMouseClick +=
                new TreeNodeMouseClickEventHandler(this.treeExplorer_NodeMouseClick);
            _file = "";
        }
   
        // Send a Message to the Server!
        private void buttonSend_Click(object sender, EventArgs e)
        {

            try {

                IPAddress ipadd;

                if (IPAddress.TryParse(textIp.Text, out ipadd)) {
                    _ipaddress = textIp.Text;
                    _portnumber = uint.Parse(textPort.Text);
                    ClientSocket c = new ClientSocket(_ipaddress, _portnumber);
                    if(textBoxMessage.Text.Length != 0) { 
                        String returnMessage = c.SendMessage(textBoxMessage.Text);
                        MessageBox.Show("Attempting to Send Message\nServer Response: " + returnMessage, "Send Message To Server", MessageBoxButtons.OK);
                    }
                    else
                        MessageBox.Show("Please enter some text to send", "Warning", MessageBoxButtons.OK);
                }

                else
                    MessageBox.Show("Not a valid IP Address");

            }
            catch(System.FormatException ex)
            {
                MessageBox.Show("Not a valid Port Number", ex.Message, MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            catch(Exception ex){
                MessageBox.Show(ex.Message, "Send Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }          
            
        }

        // This region is used to handle the File Directory section
        #region File Directory Browsing
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
            try { 
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
                _directory = file.Directory.ToString();
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
        #endregion


        // Send a File to the Server!
        private void buttonSendFile_Click(object sender, EventArgs e)
        {
            try
            {
                IPAddress ipadd;
                if (IPAddress.TryParse(textIp.Text, out ipadd))
                {
                    _ipaddress = textIp.Text;
                    _portnumber = uint.Parse(textPort.Text);
                    ClientSocket c = new ClientSocket(_ipaddress, _portnumber);
                    
                    if(_file.Length == 0)
                    {
                        MessageBox.Show("Please select a file to send first");
                        return;
                    }

                    c.SendFile(_directory + "\\" + _file, _file);

                }
                else
                    MessageBox.Show("Not a valid IP Address");

                MessageBox.Show("File has been sent to the server", "Success", MessageBoxButtons.OK);
            }
            catch (System.FormatException ex)
            {
                MessageBox.Show("Not a valid Port Number", ex.Message, MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Send Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        // List Explorer Handle, used to get the Filename and Path to send to the Library
        private void listExplorer_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (listExplorer.SelectedIndices.Count <= 0)
            {
                return;
            }
            int intselectedindex = listExplorer.SelectedIndices[0];
            if (intselectedindex >= 0)
            {
                String text = listExplorer.Items[intselectedindex].Text;
                _file = text;
            }
        }
    }
}
