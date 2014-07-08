using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Net;
using System.Net.Sockets;
using System.Windows.Forms;

namespace MotorControlClient
{
    public partial class MotorControlMainForm : Form
    {
        private String ipAddr = "192.168.1.104";
        private int port = 8989;
        private int frequency = 10;
        private String direction = "F";
        private bool enable = true;

        private Socket s = null;

        public MotorControlMainForm()
        {
            InitializeComponent();
        }

        private void MotorControlMainForm_Load(object sender, EventArgs e)
        {
            // set up the default values
            this.ipAIpt_Ipaddr.Value = ipAddr;
            this.txtBx_port.Text = port.ToString();
            this.cmbx_DIR.SelectedItem = this.comboItem_F;
            this.nmUD_frequency.Value = frequency;
            this.rBtn_Enable.Checked = true;

            setSettingsButtonState(true);
        }


        private void btn_changeMotorState_Click(object sender, EventArgs e)
        {
            if (this.s == null)
            {
                MessageBox.Show(null, "错误, 尚未连接电机!", MessageBoxButtons.OK);
                return;
            }

            string cmd = "";
            if(this.rBtn_Enable.Checked){
                // record the values first
                this.frequency = (int)this.nmUD_frequency.Value;
                this.direction = (this.cmbx_DIR.SelectedIndex == 0) ? "F" : "R";
                this.enable = true;

                int f = (int)((double)this.frequency / (10.0));
                cmd = "START " + f.ToString() + " " + this.direction;
                //send command
            }else{
                this.enable = false;
                cmd = "STOP";
            }
            string response = SocketSendReceive(this.s, cmd);
            if(response.Contains("SUCCESS"))
                MessageBox.Show(null, "设置成功!", "返回消息", MessageBoxButtons.OK, MessageBoxIcon.Information);
            else
                MessageBox.Show(null, "设置失败!", "返回消息", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }

        private void btn_cancel_Click(object sender, EventArgs e)
        {
            // restore the values to previous
            this.nmUD_frequency.Value = frequency;
            cmbx_DIR.SelectedIndex = (direction == "F") ? 0 : 1;
            this.rBtn_Enable.Checked = enable;
            rBtn_Disable.Checked = !enable;
        }

        private void setSettingsButtonState(bool connect)
        {
            btn_Connect.Enabled = connect;
            btn_disConnect.Enabled = !connect;
        }

        private void btn_Connect_Click(object sender, EventArgs e)
        {
            if(String.IsNullOrEmpty(ipAIpt_Ipaddr.Text) ||
                String.IsNullOrEmpty(txtBx_port.Text)){
                    MessageBox.Show(null, "请填好相关的配置信息!", "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return;
            }

            try
            {
                this.ipAddr = this.ipAIpt_Ipaddr.Text;
                this.port = int.Parse(this.txtBx_port.Text);

                this.s = ConnectSocket(this.ipAddr, this.port);

                setSettingsButtonState(false);
                MessageBox.Show(null, "连接成功!", "成功", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
            catch (ArgumentException ex)
            {
                MessageBox.Show(null, "请正确填写端口信息!", "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }
        }

        private void btn_disConnect_Click(object sender, EventArgs e)
        {
            this.s.Close();
            this.s = null;
            setSettingsButtonState(true);
        }


        private static Socket ConnectSocket(string server, int port)
        {
            Socket s = null;
            IPHostEntry hostEntry = null;

            // Get host related information.
            hostEntry = Dns.GetHostEntry(server);

            // Loop through the AddressList to obtain the supported AddressFamily. This is to avoid 
            // an exception that occurs when the host IP Address is not compatible with the address family 
            // (typical in the IPv6 case). 
            foreach (IPAddress address in hostEntry.AddressList)
            {
                IPEndPoint ipe = new IPEndPoint(address, port);
                Socket tempSocket =
                    new Socket(ipe.AddressFamily, SocketType.Stream, ProtocolType.Tcp);

                tempSocket.Connect(ipe);

                if (tempSocket.Connected)
                {
                    s = tempSocket;
                    break;
                }
                else
                {
                    continue;
                }
            }

            Byte[] bytesReceived = new Byte[1024];
            int bytes = 0;
            string response = "";

            // The following will block until te page is transmitted. 
            bytes = s.Receive(bytesReceived, bytesReceived.Length, 0);
            response = response + Encoding.ASCII.GetString(bytesReceived, 0, bytes);

            return s;
        }

 
        private static string SocketSendReceive(Socket s, String cmd)
        {
            Byte[] bytesSent = Encoding.ASCII.GetBytes(cmd);
            Byte[] bytesReceived = new Byte[1024];

            if (s == null)
                return ("error socket");

            // Send request to the server.
            s.Send(bytesSent, bytesSent.Length, 0);

            // Receive the server home page content. 
            int bytes = 0;
            //bytes = s.Receive(bytesReceived, bytesReceived.Length, 0);
            string response = "";

            // The following will block until te page is transmitted. 
            bytes = s.Receive(bytesReceived, bytesReceived.Length, 0);
            response = response + Encoding.ASCII.GetString(bytesReceived, 0, bytes);

            return response;
        }

        private void rBtn_Enable_CheckedChanged(object sender, EventArgs e)
        {
            this.nmUD_frequency.Enabled = this.rBtn_Enable.Checked;
            this.cmbx_DIR.Enabled = this.rBtn_Enable.Checked;
        }

        private void MotorControlMainForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (s != null)
            {
                s.Close();
            }
        }
    }
}
