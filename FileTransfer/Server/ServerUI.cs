﻿using System;
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
using System.Net;

namespace Server
{
    // Server UI
    public partial class Sever : Form
    {
        // Data Members
        static bool continueListening = false;

        // Controls
        ListView _lvExplorer;
        Button _buttonAction;

        // Socket Information
        String _ipaddress;
        uint _portnumber;

        // Current Directory
        String _directory;

        // Default Constructor
        public Sever()
        {
            InitializeComponent();

            // Initialize the File Explorer
            PopulateTreeView();
            this.treeExplorer.NodeMouseClick +=
                new TreeNodeMouseClickEventHandler(this.treeExplorer_NodeMouseClick);
            listStatus.Items.Add(" - Server Status Log -");
            _lvExplorer = listExplorer;
            _buttonAction = buttonAction;
        }

        // This region is used for File Exploring
        #region File Directory Browsing
        private void PopulateTreeView()
        {
            TreeNode rootNode;

            DirectoryInfo info = new DirectoryInfo(@"../..");
            _directory = info.FullName;
            
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

        private void treeExplorer_NodeMouseClick(object sender, TreeNodeMouseClickEventArgs e)
        {

            TreeNode newSelected = e.Node;
            listExplorer.Items.Clear();
            DirectoryInfo nodeDirInfo = (DirectoryInfo)newSelected.Tag;
            ListViewItem.ListViewSubItem[] subItems;
            ListViewItem item = null;
            
            // Store Current Directory
            _directory = nodeDirInfo.FullName;

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

        #endregion
        

        // This is used for starting the Main Listener on the Server
        private async void buttonAction_Click(object sender, EventArgs e)
        {
            if (continueListening)
            {
                continueListening = false;
                listStatus.Items.Add("Server stopped at " + DateTime.Now.ToShortDateString());
                _buttonAction.Text = "Shutting down Server";
                MessageBox.Show("Thank you for using our program!", "Shutting Down");
                this.Close();
                return;
            }

            if (!FieldsValidated())
                return;

            // Start to Listen Flag
            continueListening = true;

            
            _buttonAction.Text = "Currently Listening... (Click here to stop and close program)";

            TextBox textIpAddress = textIp;
            textIp.Enabled = false;
            textPort.Enabled = false;

            listStatus.Items.Add("Server started at " + DateTime.Now.ToShortDateString());

            do
            {
                try
                {
                    //String returnLine = await ListenForMessages(_ipaddress, _portnumber);
                    String returnLine = await Listen(_ipaddress, _portnumber);
                    returnLine += " (from a client @ " + DateTime.Now.ToShortDateString() + ")";
                    listStatus.Items.Add(returnLine.ToString());
                }
                catch (Exception ex) { MessageBox.Show(ex.Message, "Error"); }
                //ListenForMessages();
            } while (continueListening);

            _buttonAction.Text = "Start Listening!";

        }


        // Threaded task, this ensures we can still use this application ASYNC meaning it wont block any input
        public Task<String> Listen(String ip, uint port)
        {
            
            Task<String> threaded_listener = new Task<String>
            (() =>
            {
                ServerSocket s = new ServerSocket(ip, port, _directory);
                return s.Recieve();
            }
            );
            threaded_listener.Start();
            return threaded_listener;
        }

        // Ensures all the Fields are validated before hitting the library
        private bool FieldsValidated()
        {
            try
            {
                IPAddress ipadd;
                if (IPAddress.TryParse(textIp.Text, out ipadd))
                {
                    _ipaddress = textIp.Text;
                    _portnumber = uint.Parse(textPort.Text);
                    return true;
                }
                else
                {
                    MessageBox.Show("Not a valid IP Address");
                    return false;
                }
            }
            catch (System.FormatException ex)
            {
                MessageBox.Show("Not a valid Port Number", ex.Message, MessageBoxButtons.OK, MessageBoxIcon.Error);
                return false;
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Validation Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return false;
            }
        }

    }
}
