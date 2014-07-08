namespace MotorControlClient
{
    partial class MotorControlMainForm
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.labelX1 = new DevComponents.DotNetBar.LabelX();
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.panel1 = new System.Windows.Forms.Panel();
            this.rBtn_Disable = new System.Windows.Forms.RadioButton();
            this.labelX7 = new DevComponents.DotNetBar.LabelX();
            this.rBtn_Enable = new System.Windows.Forms.RadioButton();
            this.labelX6 = new DevComponents.DotNetBar.LabelX();
            this.nmUD_frequency = new System.Windows.Forms.NumericUpDown();
            this.btn_cancel = new DevComponents.DotNetBar.ButtonX();
            this.btn_changeMotorState = new DevComponents.DotNetBar.ButtonX();
            this.cmbx_DIR = new DevComponents.DotNetBar.Controls.ComboBoxEx();
            this.comboItem_F = new DevComponents.Editors.ComboItem();
            this.comboItem_R = new DevComponents.Editors.ComboItem();
            this.labelX5 = new DevComponents.DotNetBar.LabelX();
            this.labelX4 = new DevComponents.DotNetBar.LabelX();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.ipAIpt_Ipaddr = new DevComponents.Editors.IpAddressInput();
            this.btn_disConnect = new DevComponents.DotNetBar.ButtonX();
            this.btn_Connect = new DevComponents.DotNetBar.ButtonX();
            this.txtBx_port = new DevComponents.DotNetBar.Controls.TextBoxX();
            this.labelX3 = new DevComponents.DotNetBar.LabelX();
            this.labelX2 = new DevComponents.DotNetBar.LabelX();
            this.tabControl1.SuspendLayout();
            this.tabPage1.SuspendLayout();
            this.panel1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.nmUD_frequency)).BeginInit();
            this.tabPage2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.ipAIpt_Ipaddr)).BeginInit();
            this.SuspendLayout();
            // 
            // labelX1
            // 
            // 
            // 
            // 
            this.labelX1.BackgroundStyle.Class = "";
            this.labelX1.Font = new System.Drawing.Font("宋体", 18F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.labelX1.Location = new System.Drawing.Point(62, 3);
            this.labelX1.Name = "labelX1";
            this.labelX1.Size = new System.Drawing.Size(153, 30);
            this.labelX1.TabIndex = 0;
            this.labelX1.Text = "电机控制器";
            this.labelX1.TextAlignment = System.Drawing.StringAlignment.Center;
            // 
            // tabControl1
            // 
            this.tabControl1.Controls.Add(this.tabPage1);
            this.tabControl1.Controls.Add(this.tabPage2);
            this.tabControl1.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.tabControl1.Location = new System.Drawing.Point(0, 26);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(284, 236);
            this.tabControl1.TabIndex = 1;
            // 
            // tabPage1
            // 
            this.tabPage1.Controls.Add(this.panel1);
            this.tabPage1.Controls.Add(this.labelX6);
            this.tabPage1.Controls.Add(this.nmUD_frequency);
            this.tabPage1.Controls.Add(this.btn_cancel);
            this.tabPage1.Controls.Add(this.btn_changeMotorState);
            this.tabPage1.Controls.Add(this.cmbx_DIR);
            this.tabPage1.Controls.Add(this.labelX5);
            this.tabPage1.Controls.Add(this.labelX4);
            this.tabPage1.Location = new System.Drawing.Point(4, 22);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage1.Size = new System.Drawing.Size(276, 210);
            this.tabPage1.TabIndex = 0;
            this.tabPage1.Text = "控制面板";
            this.tabPage1.UseVisualStyleBackColor = true;
            // 
            // panel1
            // 
            this.panel1.Controls.Add(this.rBtn_Disable);
            this.panel1.Controls.Add(this.labelX7);
            this.panel1.Controls.Add(this.rBtn_Enable);
            this.panel1.Location = new System.Drawing.Point(44, 29);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(200, 29);
            this.panel1.TabIndex = 11;
            // 
            // rBtn_Disable
            // 
            this.rBtn_Disable.AutoSize = true;
            this.rBtn_Disable.Location = new System.Drawing.Point(121, 6);
            this.rBtn_Disable.Name = "rBtn_Disable";
            this.rBtn_Disable.Size = new System.Drawing.Size(35, 16);
            this.rBtn_Disable.TabIndex = 10;
            this.rBtn_Disable.Text = "关";
            this.rBtn_Disable.UseVisualStyleBackColor = true;
            // 
            // labelX7
            // 
            // 
            // 
            // 
            this.labelX7.BackgroundStyle.Class = "";
            this.labelX7.Location = new System.Drawing.Point(0, 3);
            this.labelX7.Name = "labelX7";
            this.labelX7.Size = new System.Drawing.Size(45, 23);
            this.labelX7.TabIndex = 8;
            this.labelX7.Text = "使能：";
            // 
            // rBtn_Enable
            // 
            this.rBtn_Enable.AutoSize = true;
            this.rBtn_Enable.Checked = true;
            this.rBtn_Enable.Location = new System.Drawing.Point(64, 6);
            this.rBtn_Enable.Name = "rBtn_Enable";
            this.rBtn_Enable.Size = new System.Drawing.Size(35, 16);
            this.rBtn_Enable.TabIndex = 9;
            this.rBtn_Enable.TabStop = true;
            this.rBtn_Enable.Text = "开";
            this.rBtn_Enable.UseVisualStyleBackColor = true;
            this.rBtn_Enable.CheckedChanged += new System.EventHandler(this.rBtn_Enable_CheckedChanged);
            // 
            // labelX6
            // 
            // 
            // 
            // 
            this.labelX6.BackgroundStyle.Class = "";
            this.labelX6.Location = new System.Drawing.Point(223, 113);
            this.labelX6.Name = "labelX6";
            this.labelX6.Size = new System.Drawing.Size(21, 23);
            this.labelX6.TabIndex = 7;
            this.labelX6.Text = "HZ";
            // 
            // nmUD_frequency
            // 
            this.nmUD_frequency.Location = new System.Drawing.Point(81, 114);
            this.nmUD_frequency.Maximum = new decimal(new int[] {
            1000,
            0,
            0,
            0});
            this.nmUD_frequency.Minimum = new decimal(new int[] {
            10,
            0,
            0,
            0});
            this.nmUD_frequency.Name = "nmUD_frequency";
            this.nmUD_frequency.Size = new System.Drawing.Size(141, 21);
            this.nmUD_frequency.TabIndex = 6;
            this.nmUD_frequency.Value = new decimal(new int[] {
            10,
            0,
            0,
            0});
            // 
            // btn_cancel
            // 
            this.btn_cancel.AccessibleRole = System.Windows.Forms.AccessibleRole.PushButton;
            this.btn_cancel.ColorTable = DevComponents.DotNetBar.eButtonColor.OrangeWithBackground;
            this.btn_cancel.Location = new System.Drawing.Point(147, 154);
            this.btn_cancel.Name = "btn_cancel";
            this.btn_cancel.Size = new System.Drawing.Size(75, 23);
            this.btn_cancel.Style = DevComponents.DotNetBar.eDotNetBarStyle.StyleManagerControlled;
            this.btn_cancel.TabIndex = 5;
            this.btn_cancel.Text = "取消";
            this.btn_cancel.Click += new System.EventHandler(this.btn_cancel_Click);
            // 
            // btn_changeMotorState
            // 
            this.btn_changeMotorState.AccessibleRole = System.Windows.Forms.AccessibleRole.PushButton;
            this.btn_changeMotorState.ColorTable = DevComponents.DotNetBar.eButtonColor.OrangeWithBackground;
            this.btn_changeMotorState.Location = new System.Drawing.Point(44, 154);
            this.btn_changeMotorState.Name = "btn_changeMotorState";
            this.btn_changeMotorState.Size = new System.Drawing.Size(75, 23);
            this.btn_changeMotorState.Style = DevComponents.DotNetBar.eDotNetBarStyle.StyleManagerControlled;
            this.btn_changeMotorState.TabIndex = 4;
            this.btn_changeMotorState.Text = "确定";
            this.btn_changeMotorState.Click += new System.EventHandler(this.btn_changeMotorState_Click);
            // 
            // cmbx_DIR
            // 
            this.cmbx_DIR.DisplayMember = "Text";
            this.cmbx_DIR.DrawMode = System.Windows.Forms.DrawMode.OwnerDrawFixed;
            this.cmbx_DIR.FormattingEnabled = true;
            this.cmbx_DIR.ItemHeight = 15;
            this.cmbx_DIR.Items.AddRange(new object[] {
            this.comboItem_F,
            this.comboItem_R});
            this.cmbx_DIR.Location = new System.Drawing.Point(81, 74);
            this.cmbx_DIR.Name = "cmbx_DIR";
            this.cmbx_DIR.Size = new System.Drawing.Size(141, 21);
            this.cmbx_DIR.Style = DevComponents.DotNetBar.eDotNetBarStyle.StyleManagerControlled;
            this.cmbx_DIR.TabIndex = 2;
            // 
            // comboItem_F
            // 
            this.comboItem_F.Text = "顺时针";
            // 
            // comboItem_R
            // 
            this.comboItem_R.Text = "逆时针";
            // 
            // labelX5
            // 
            // 
            // 
            // 
            this.labelX5.BackgroundStyle.Class = "";
            this.labelX5.Location = new System.Drawing.Point(44, 114);
            this.labelX5.Name = "labelX5";
            this.labelX5.Size = new System.Drawing.Size(45, 23);
            this.labelX5.TabIndex = 1;
            this.labelX5.Text = "频率：";
            // 
            // labelX4
            // 
            // 
            // 
            // 
            this.labelX4.BackgroundStyle.Class = "";
            this.labelX4.Location = new System.Drawing.Point(44, 74);
            this.labelX4.Name = "labelX4";
            this.labelX4.Size = new System.Drawing.Size(45, 23);
            this.labelX4.TabIndex = 0;
            this.labelX4.Text = "方向：";
            // 
            // tabPage2
            // 
            this.tabPage2.Controls.Add(this.ipAIpt_Ipaddr);
            this.tabPage2.Controls.Add(this.btn_disConnect);
            this.tabPage2.Controls.Add(this.btn_Connect);
            this.tabPage2.Controls.Add(this.txtBx_port);
            this.tabPage2.Controls.Add(this.labelX3);
            this.tabPage2.Controls.Add(this.labelX2);
            this.tabPage2.Location = new System.Drawing.Point(4, 22);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage2.Size = new System.Drawing.Size(276, 210);
            this.tabPage2.TabIndex = 1;
            this.tabPage2.Text = "基本配置";
            this.tabPage2.UseVisualStyleBackColor = true;
            // 
            // ipAIpt_Ipaddr
            // 
            this.ipAIpt_Ipaddr.AutoOverwrite = true;
            // 
            // 
            // 
            this.ipAIpt_Ipaddr.BackgroundStyle.Class = "DateTimeInputBackground";
            this.ipAIpt_Ipaddr.ButtonFreeText.Shortcut = DevComponents.DotNetBar.eShortcut.F2;
            this.ipAIpt_Ipaddr.ButtonFreeText.Visible = true;
            this.ipAIpt_Ipaddr.Location = new System.Drawing.Point(96, 51);
            this.ipAIpt_Ipaddr.Name = "ipAIpt_Ipaddr";
            this.ipAIpt_Ipaddr.Size = new System.Drawing.Size(137, 21);
            this.ipAIpt_Ipaddr.Style = DevComponents.DotNetBar.eDotNetBarStyle.StyleManagerControlled;
            this.ipAIpt_Ipaddr.TabIndex = 6;
            // 
            // btn_disConnect
            // 
            this.btn_disConnect.AccessibleRole = System.Windows.Forms.AccessibleRole.PushButton;
            this.btn_disConnect.ColorTable = DevComponents.DotNetBar.eButtonColor.OrangeWithBackground;
            this.btn_disConnect.Location = new System.Drawing.Point(163, 143);
            this.btn_disConnect.Name = "btn_disConnect";
            this.btn_disConnect.Size = new System.Drawing.Size(70, 24);
            this.btn_disConnect.Style = DevComponents.DotNetBar.eDotNetBarStyle.StyleManagerControlled;
            this.btn_disConnect.TabIndex = 5;
            this.btn_disConnect.Text = "断开";
            this.btn_disConnect.Click += new System.EventHandler(this.btn_disConnect_Click);
            // 
            // btn_Connect
            // 
            this.btn_Connect.AccessibleRole = System.Windows.Forms.AccessibleRole.PushButton;
            this.btn_Connect.ColorTable = DevComponents.DotNetBar.eButtonColor.OrangeWithBackground;
            this.btn_Connect.Location = new System.Drawing.Point(30, 143);
            this.btn_Connect.Name = "btn_Connect";
            this.btn_Connect.Size = new System.Drawing.Size(75, 24);
            this.btn_Connect.Style = DevComponents.DotNetBar.eDotNetBarStyle.StyleManagerControlled;
            this.btn_Connect.TabIndex = 4;
            this.btn_Connect.Text = "连接";
            this.btn_Connect.Click += new System.EventHandler(this.btn_Connect_Click);
            // 
            // txtBx_port
            // 
            // 
            // 
            // 
            this.txtBx_port.Border.Class = "TextBoxBorder";
            this.txtBx_port.Location = new System.Drawing.Point(96, 89);
            this.txtBx_port.Name = "txtBx_port";
            this.txtBx_port.Size = new System.Drawing.Size(137, 21);
            this.txtBx_port.TabIndex = 3;
            // 
            // labelX3
            // 
            // 
            // 
            // 
            this.labelX3.BackgroundStyle.Class = "";
            this.labelX3.Location = new System.Drawing.Point(30, 89);
            this.labelX3.Name = "labelX3";
            this.labelX3.Size = new System.Drawing.Size(75, 23);
            this.labelX3.TabIndex = 1;
            this.labelX3.Text = "主机端口:";
            // 
            // labelX2
            // 
            // 
            // 
            // 
            this.labelX2.BackgroundStyle.Class = "";
            this.labelX2.Location = new System.Drawing.Point(30, 50);
            this.labelX2.Name = "labelX2";
            this.labelX2.Size = new System.Drawing.Size(75, 23);
            this.labelX2.TabIndex = 0;
            this.labelX2.Text = "主机地址:";
            // 
            // MotorControlMainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.White;
            this.ClientSize = new System.Drawing.Size(284, 262);
            this.Controls.Add(this.tabControl1);
            this.Controls.Add(this.labelX1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Name = "MotorControlMainForm";
            this.Text = "电机控制器";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.MotorControlMainForm_FormClosing);
            this.Load += new System.EventHandler(this.MotorControlMainForm_Load);
            this.tabControl1.ResumeLayout(false);
            this.tabPage1.ResumeLayout(false);
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.nmUD_frequency)).EndInit();
            this.tabPage2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.ipAIpt_Ipaddr)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private DevComponents.DotNetBar.LabelX labelX1;
        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tabPage1;
        private System.Windows.Forms.TabPage tabPage2;
        private DevComponents.DotNetBar.Controls.TextBoxX txtBx_port;
        private DevComponents.DotNetBar.LabelX labelX3;
        private DevComponents.DotNetBar.LabelX labelX2;
        private DevComponents.DotNetBar.ButtonX btn_disConnect;
        private DevComponents.DotNetBar.ButtonX btn_Connect;
        private DevComponents.DotNetBar.Controls.ComboBoxEx cmbx_DIR;
        private DevComponents.Editors.ComboItem comboItem_F;
        private DevComponents.Editors.ComboItem comboItem_R;
        private DevComponents.DotNetBar.LabelX labelX5;
        private DevComponents.DotNetBar.LabelX labelX4;
        private DevComponents.Editors.IpAddressInput ipAIpt_Ipaddr;
        private DevComponents.DotNetBar.ButtonX btn_cancel;
        private DevComponents.DotNetBar.ButtonX btn_changeMotorState;
        private DevComponents.DotNetBar.LabelX labelX6;
        private System.Windows.Forms.NumericUpDown nmUD_frequency;
        private DevComponents.DotNetBar.LabelX labelX7;
        private System.Windows.Forms.RadioButton rBtn_Disable;
        private System.Windows.Forms.RadioButton rBtn_Enable;
        private System.Windows.Forms.Panel panel1;
    }
}

