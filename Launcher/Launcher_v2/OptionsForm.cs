using Ionic.Zip;
using Launcher_v2.Properties;
using Microsoft.Win32;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.IO;
using System.Runtime.InteropServices;
using System.Windows.Forms;

namespace Launcher_v2
{
  public class OptionsForm : Form
  {
    public static Dictionary<string, string> langLaun = new Dictionary<string, string>();
    public string configPath = "Software\\Webzen\\Mu\\Config";
    public string Root = AppDomain.CurrentDomain.BaseDirectory;
    public string Server = "http://update.muonline.co.il/update/";
    public const int WM_NCLBUTTONDOWN = 161;
    public const int HT_CAPTION = 2;
    private IContainer components;
    private Button closeBtn;
    private Panel panel1;
    private Label usernameLabel;
    private TextBox userNameTextbox;
    private Button optSaveBtn;
    private Button optCloseBtn;
    private ComboBox comboBox1;
    private Label resoluLb;
    private GroupBox grahpicsGrop;
    private RadioButton highRadio;
    private RadioButton lowRadio;
    private CheckBox MusicCheckBox;
    private CheckBox soundsCheckBox;
    private Label soundLb;
    private GroupBox PlayerBmdGroup;
    private RadioButton radioPlayerBmd2;
    private GroupBox autoGroupBox;
    private RadioButton blueRadioBtn;
    private RadioButton redRadioBtn;
    private RadioButton radioPlayerBmd1;

    public OptionsForm()
    {
      OptionsForm.buildDictionary();
      this.InitializeComponent();
      if (!MainWindow.langFlag)
        return;
      this.changeBtnLang();
    }

    [DllImport("user32.dll")]
    public static extern int SendMessage(IntPtr hWnd, int Msg, int wParam, int lParam);

    [DllImport("user32.dll")]
    public static extern bool ReleaseCapture();

    private static void buildDictionary()
    {
      if (OptionsForm.langLaun.Count != 0)
        return;
      OptionsForm.langLaun.Add("&Save", "&שמור");
      OptionsForm.langLaun.Add("&Close", "&סגור");
      OptionsForm.langLaun.Add("Grahpics :", "גרפיקה :");
      OptionsForm.langLaun.Add("&High", "&גבוה");
      OptionsForm.langLaun.Add("&Low", "&נמוך");
      OptionsForm.langLaun.Add("Sound :", "צליל :");
      OptionsForm.langLaun.Add("Sounds", "צלילים");
      OptionsForm.langLaun.Add("Music", "מוסיקה");
      OptionsForm.langLaun.Add("Resolution :", "רזולוציה :");
      OptionsForm.langLaun.Add("Username :", "שם משתמש :");
      OptionsForm.langLaun.Add("PlayerBMD :", "פלייר ביאמדי :");
      OptionsForm.langLaun.Add("AutoClicker :", "אוטוקליקר :");
      OptionsForm.langLaun.Add("&Original", "&מקורי");
      OptionsForm.langLaun.Add("&SM/MG Bug", "&קוסם/אמגי באג");
      OptionsForm.langLaun.Add("", "");
      OptionsForm.langLaun.Add("&שמור", "&Save");
      OptionsForm.langLaun.Add("&סגור", "&Close");
      OptionsForm.langLaun.Add("גרפיקה :", "Grahpics :");
      OptionsForm.langLaun.Add("&גבוה", "&High");
      OptionsForm.langLaun.Add("&נמוך", "&Low");
      OptionsForm.langLaun.Add("צליל :", "Sound :");
      OptionsForm.langLaun.Add("צלילים", "Sounds");
      OptionsForm.langLaun.Add("מוסיקה", "Music");
      OptionsForm.langLaun.Add("רזולוציה :", "Resolution :");
      OptionsForm.langLaun.Add("שם משתמש :", "Username :");
      OptionsForm.langLaun.Add("פלייר ביאמדי :", "PlayerBMD :");
      OptionsForm.langLaun.Add("אוטוקליקר :", "AutoClicker :");
      OptionsForm.langLaun.Add("&מקורי", "&Original");
      OptionsForm.langLaun.Add("&קוסם/אמגי באג", "&SM/MG Bug");
    }

    private void OptionsForm_MouseDown(object sender, MouseEventArgs e)
    {
      if (e.Button != MouseButtons.Left)
        return;
      OptionsForm.ReleaseCapture();
      OptionsForm.SendMessage(this.Handle, 161, 2, 0);
    }

    private void closeBtn_Click(object sender, EventArgs e)
    {
      this.Close();
    }

    private void closeBtn_MouseEnter(object sender, EventArgs e)
    {
      this.closeBtn.BackgroundImage = (Image) Resources.close2;
    }

    private void closeBtn_MouseLeave(object sender, EventArgs e)
    {
      this.closeBtn.BackgroundImage = (Image) Resources.close1;
    }

    private void OptionsForm_Load(object sender, EventArgs e)
    {
      RegistryKey registryKey = Registry.CurrentUser.OpenSubKey(this.configPath);
      this.userNameTextbox.Text = (string) registryKey.GetValue("ID");
      switch ((int) registryKey.GetValue("Resolution", (object) 0))
      {
        case 0:
          this.comboBox1.SelectedItem = (object) "600x400";
          break;
        case 1:
          this.comboBox1.SelectedItem = (object) "800x600";
          break;
        case 2:
          this.comboBox1.SelectedItem = (object) "1024x768";
          break;
        case 3:
          this.comboBox1.SelectedItem = (object) "1280x960";
          break;
        case 4:
          this.comboBox1.SelectedItem = (object) "1600x1200";
          break;
      }
      switch ((int) registryKey.GetValue("ColorDepth", (object) 0))
      {
        case 0:
          this.lowRadio.Checked = true;
          break;
        case 1:
          this.highRadio.Checked = true;
          break;
      }
      if ((int) registryKey.GetValue("SoundOnOff", (object) 0) == 1)
        this.soundsCheckBox.Checked = true;
      if ((int) registryKey.GetValue("MusicOnOff", (object) 0) == 1)
        this.MusicCheckBox.Checked = true;
      switch ((int) registryKey.GetValue("AutoClickerMuIsrael", (object) 0))
      {
        case 1:
          this.blueRadioBtn.Checked = true;
          break;
        default:
          this.redRadioBtn.Checked = true;
          break;
      }
      switch ((int) registryKey.GetValue("PlayerBmdMuIsrael", (object) 0))
      {
        case 1:
          this.radioPlayerBmd2.Checked = true;
          break;
        default:
          this.radioPlayerBmd1.Checked = true;
          break;
      }
    }

    private void optSaveBtn_Click(object sender, EventArgs e)
    {
      RegistryKey registryKey = Registry.CurrentUser.OpenSubKey(this.configPath, true);
      uint num1 = 0U;
      uint num2 = 0U;
      uint num3 = 0U;
      uint num4 = 0U;
      uint num5 = 0U;
      uint num6 = 0U;
      switch (this.comboBox1.Text)
      {
        case "600x400":
          num1 = 0U;
          break;
        case "800x600":
          num1 = 1U;
          break;
        case "1024x768":
          num1 = 2U;
          break;
        case "1280x960":
          num1 = 3U;
          break;
        case "1600x1200":
          num1 = 4U;
          break;
      }
      if (this.highRadio.Checked)
        num2 = 1U;
      if (this.soundsCheckBox.Checked)
        num3 = 1U;
      if (this.MusicCheckBox.Checked)
        num4 = 1U;
      if (this.blueRadioBtn.Checked)
        num5 = 1U;
      if (this.radioPlayerBmd2.Checked)
        num6 = 1U;
      registryKey.SetValue("ID", (object) this.userNameTextbox.Text);
      registryKey.SetValue("Resolution", (object) num1, RegistryValueKind.DWord);
      registryKey.SetValue("ColorDepth", (object) num2, RegistryValueKind.DWord);
      registryKey.SetValue("SoundOnOff", (object) num3, RegistryValueKind.DWord);
      registryKey.SetValue("MusicOnOff", (object) num4, RegistryValueKind.DWord);
      registryKey.SetValue("AutoClickerMuIsrael", (object) num5, RegistryValueKind.DWord);
      registryKey.SetValue("PlayerBmdMuIsrael", (object) num6, RegistryValueKind.DWord);
      this.Close();
    }

    private void optCloseBtn_Click(object sender, EventArgs e)
    {
      this.Close();
    }

    private void common_mouseenter(object sender, EventArgs e)
    {
      Button button = sender as Button;
      button.BackColor = System.Drawing.Color.Orange;
      button.Cursor = Cursors.Hand;
    }

    private void common_mouseleave(object sender, EventArgs e)
    {
      Button button = sender as Button;
      button.BackColor = System.Drawing.Color.FromArgb(17, 17, 17);
      button.Cursor = Cursors.Default;
    }

    private void changeBtnLang()
    {
      this.usernameLabel.Text = OptionsForm.langLaun[this.usernameLabel.Text];
      this.resoluLb.Text = OptionsForm.langLaun[this.resoluLb.Text];
      this.soundLb.Text = OptionsForm.langLaun[this.soundLb.Text];
      this.soundsCheckBox.Text = OptionsForm.langLaun[this.soundsCheckBox.Text];
      this.MusicCheckBox.Text = OptionsForm.langLaun[this.MusicCheckBox.Text];
      this.grahpicsGrop.Text = OptionsForm.langLaun[this.grahpicsGrop.Text];
      this.lowRadio.Text = OptionsForm.langLaun[this.lowRadio.Text];
      this.highRadio.Text = OptionsForm.langLaun[this.highRadio.Text];
      this.optSaveBtn.Text = OptionsForm.langLaun[this.optSaveBtn.Text];
      this.optCloseBtn.Text = OptionsForm.langLaun[this.optCloseBtn.Text];
      this.autoGroupBox.Text = OptionsForm.langLaun[this.autoGroupBox.Text];
      this.PlayerBmdGroup.Text = OptionsForm.langLaun[this.PlayerBmdGroup.Text];
      this.radioPlayerBmd1.Text = OptionsForm.langLaun[this.radioPlayerBmd1.Text];
      this.radioPlayerBmd2.Text = OptionsForm.langLaun[this.radioPlayerBmd2.Text];
    }

    private void radioPlayerBmd1_Click(object sender, EventArgs e)
    {
      RegistryKey registryKey = Registry.CurrentUser.OpenSubKey(this.configPath, true);
      if ((int) registryKey.GetValue("PlayerBmdMuIsrael", (object) 0) == 0 || !this.radioPlayerBmd1.Checked)
        return;
      this.updatePlayer("player1");
      registryKey.SetValue("PlayerBmdMuIsrael", (object) 1, RegistryValueKind.DWord);
    }

    private void radioPlayerBmd2_Click(object sender, EventArgs e)
    {
      RegistryKey registryKey = Registry.CurrentUser.OpenSubKey(this.configPath, true);
      if ((int) registryKey.GetValue("PlayerBmdMuIsrael", (object) 0) == 1 || !this.radioPlayerBmd2.Checked)
        return;
      this.updatePlayer("player2");
      registryKey.SetValue("PlayerBmdMuIsrael", (object) 1, RegistryValueKind.DWord);
    }

    private bool updatePlayer(string nameFile)
    {
      string str = this.Root + "Data\\Player\\" + nameFile + ".zip";
      if (!File.Exists(str))
        return false;
      using (ZipFile zipFile = ZipFile.Read(str))
      {
        foreach (ZipEntry zipEntry in zipFile)
        {
          try
          {
            zipEntry.Extract(this.Root + "Data\\Player", true);
          }
          catch (Exception ex)
          {
            int num = (int) MessageBox.Show(ex.Message);
            return false;
          }
        }
      }
      return true;
    }

    protected override void Dispose(bool disposing)
    {
      if (disposing && this.components != null)
        this.components.Dispose();
      base.Dispose(disposing);
    }

    private void InitializeComponent()
    {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(OptionsForm));
            this.closeBtn = new System.Windows.Forms.Button();
            this.panel1 = new System.Windows.Forms.Panel();
            this.PlayerBmdGroup = new System.Windows.Forms.GroupBox();
            this.radioPlayerBmd2 = new System.Windows.Forms.RadioButton();
            this.radioPlayerBmd1 = new System.Windows.Forms.RadioButton();
            this.grahpicsGrop = new System.Windows.Forms.GroupBox();
            this.highRadio = new System.Windows.Forms.RadioButton();
            this.lowRadio = new System.Windows.Forms.RadioButton();
            this.MusicCheckBox = new System.Windows.Forms.CheckBox();
            this.soundsCheckBox = new System.Windows.Forms.CheckBox();
            this.soundLb = new System.Windows.Forms.Label();
            this.comboBox1 = new System.Windows.Forms.ComboBox();
            this.resoluLb = new System.Windows.Forms.Label();
            this.optSaveBtn = new System.Windows.Forms.Button();
            this.optCloseBtn = new System.Windows.Forms.Button();
            this.usernameLabel = new System.Windows.Forms.Label();
            this.userNameTextbox = new System.Windows.Forms.TextBox();
            this.redRadioBtn = new System.Windows.Forms.RadioButton();
            this.blueRadioBtn = new System.Windows.Forms.RadioButton();
            this.autoGroupBox = new System.Windows.Forms.GroupBox();
            this.panel1.SuspendLayout();
            this.PlayerBmdGroup.SuspendLayout();
            this.grahpicsGrop.SuspendLayout();
            this.autoGroupBox.SuspendLayout();
            this.SuspendLayout();
            // 
            // closeBtn
            // 
            this.closeBtn.AllowDrop = true;
            this.closeBtn.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.closeBtn.AutoEllipsis = true;
            this.closeBtn.BackColor = System.Drawing.Color.Transparent;
            this.closeBtn.BackgroundImage = global::Launcher_v2.Properties.Resources.close1;
            this.closeBtn.Cursor = System.Windows.Forms.Cursors.Hand;
            this.closeBtn.FlatAppearance.BorderSize = 0;
            this.closeBtn.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.closeBtn.Location = new System.Drawing.Point(296, -2);
            this.closeBtn.Name = "closeBtn";
            this.closeBtn.Size = new System.Drawing.Size(34, 26);
            this.closeBtn.TabIndex = 4;
            this.closeBtn.UseVisualStyleBackColor = false;
            this.closeBtn.Click += new System.EventHandler(this.closeBtn_Click);
            this.closeBtn.MouseEnter += new System.EventHandler(this.closeBtn_MouseEnter);
            this.closeBtn.MouseLeave += new System.EventHandler(this.closeBtn_MouseLeave);
            // 
            // panel1
            // 
            this.panel1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.panel1.BackColor = System.Drawing.Color.Black;
            this.panel1.Controls.Add(this.PlayerBmdGroup);
            this.panel1.Controls.Add(this.autoGroupBox);
            this.panel1.Controls.Add(this.grahpicsGrop);
            this.panel1.Controls.Add(this.MusicCheckBox);
            this.panel1.Controls.Add(this.soundsCheckBox);
            this.panel1.Controls.Add(this.soundLb);
            this.panel1.Controls.Add(this.comboBox1);
            this.panel1.Controls.Add(this.resoluLb);
            this.panel1.Controls.Add(this.optSaveBtn);
            this.panel1.Controls.Add(this.optCloseBtn);
            this.panel1.Controls.Add(this.usernameLabel);
            this.panel1.Controls.Add(this.userNameTextbox);
            this.panel1.Location = new System.Drawing.Point(2, 24);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(325, 323);
            this.panel1.TabIndex = 10;
            // 
            // PlayerBmdGroup
            // 
            this.PlayerBmdGroup.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.PlayerBmdGroup.Controls.Add(this.radioPlayerBmd2);
            this.PlayerBmdGroup.Controls.Add(this.radioPlayerBmd1);
            this.PlayerBmdGroup.Font = new System.Drawing.Font("Tahoma", 14.25F, System.Drawing.FontStyle.Bold);
            this.PlayerBmdGroup.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(99)))), ((int)(((byte)(7)))));
            this.PlayerBmdGroup.Location = new System.Drawing.Point(20, 198);
            this.PlayerBmdGroup.Name = "PlayerBmdGroup";
            this.PlayerBmdGroup.Size = new System.Drawing.Size(287, 60);
            this.PlayerBmdGroup.TabIndex = 36;
            this.PlayerBmdGroup.TabStop = false;
            this.PlayerBmdGroup.Text = "PlayerBMD :";
            // 
            // radioPlayerBmd2
            // 
            this.radioPlayerBmd2.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.radioPlayerBmd2.AutoSize = true;
            this.radioPlayerBmd2.Cursor = System.Windows.Forms.Cursors.Hand;
            this.radioPlayerBmd2.Font = new System.Drawing.Font("Tahoma", 14.25F);
            this.radioPlayerBmd2.ForeColor = System.Drawing.Color.White;
            this.radioPlayerBmd2.Location = new System.Drawing.Point(106, 28);
            this.radioPlayerBmd2.Name = "radioPlayerBmd2";
            this.radioPlayerBmd2.Size = new System.Drawing.Size(128, 27);
            this.radioPlayerBmd2.TabIndex = 33;
            this.radioPlayerBmd2.TabStop = true;
            this.radioPlayerBmd2.Text = "&SM/MG Bug";
            this.radioPlayerBmd2.UseVisualStyleBackColor = true;
            this.radioPlayerBmd2.Click += new System.EventHandler(this.radioPlayerBmd2_Click);
            // 
            // radioPlayerBmd1
            // 
            this.radioPlayerBmd1.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.radioPlayerBmd1.AutoSize = true;
            this.radioPlayerBmd1.Cursor = System.Windows.Forms.Cursors.Hand;
            this.radioPlayerBmd1.Font = new System.Drawing.Font("Tahoma", 14.25F);
            this.radioPlayerBmd1.ForeColor = System.Drawing.Color.White;
            this.radioPlayerBmd1.Location = new System.Drawing.Point(12, 27);
            this.radioPlayerBmd1.Name = "radioPlayerBmd1";
            this.radioPlayerBmd1.Size = new System.Drawing.Size(92, 27);
            this.radioPlayerBmd1.TabIndex = 32;
            this.radioPlayerBmd1.TabStop = true;
            this.radioPlayerBmd1.Text = "&Original";
            this.radioPlayerBmd1.UseVisualStyleBackColor = true;
            this.radioPlayerBmd1.Click += new System.EventHandler(this.radioPlayerBmd1_Click);
            // 
            // grahpicsGrop
            // 
            this.grahpicsGrop.Controls.Add(this.highRadio);
            this.grahpicsGrop.Controls.Add(this.lowRadio);
            this.grahpicsGrop.Font = new System.Drawing.Font("Tahoma", 14.25F, System.Drawing.FontStyle.Bold);
            this.grahpicsGrop.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(99)))), ((int)(((byte)(7)))));
            this.grahpicsGrop.Location = new System.Drawing.Point(20, 131);
            this.grahpicsGrop.Name = "grahpicsGrop";
            this.grahpicsGrop.Size = new System.Drawing.Size(287, 60);
            this.grahpicsGrop.TabIndex = 26;
            this.grahpicsGrop.TabStop = false;
            this.grahpicsGrop.Text = "Grahpics :";
            // 
            // highRadio
            // 
            this.highRadio.AutoSize = true;
            this.highRadio.Cursor = System.Windows.Forms.Cursors.Hand;
            this.highRadio.Font = new System.Drawing.Font("Tahoma", 14.25F);
            this.highRadio.ForeColor = System.Drawing.Color.White;
            this.highRadio.Location = new System.Drawing.Point(88, 28);
            this.highRadio.Name = "highRadio";
            this.highRadio.Size = new System.Drawing.Size(67, 27);
            this.highRadio.TabIndex = 33;
            this.highRadio.TabStop = true;
            this.highRadio.Text = "&High";
            this.highRadio.UseVisualStyleBackColor = true;
            // 
            // lowRadio
            // 
            this.lowRadio.AutoSize = true;
            this.lowRadio.Cursor = System.Windows.Forms.Cursors.Hand;
            this.lowRadio.Font = new System.Drawing.Font("Tahoma", 14.25F);
            this.lowRadio.ForeColor = System.Drawing.Color.White;
            this.lowRadio.Location = new System.Drawing.Point(12, 27);
            this.lowRadio.Name = "lowRadio";
            this.lowRadio.Size = new System.Drawing.Size(61, 27);
            this.lowRadio.TabIndex = 32;
            this.lowRadio.TabStop = true;
            this.lowRadio.Text = "&Low";
            this.lowRadio.UseVisualStyleBackColor = true;
            // 
            // MusicCheckBox
            // 
            this.MusicCheckBox.AutoSize = true;
            this.MusicCheckBox.Cursor = System.Windows.Forms.Cursors.Hand;
            this.MusicCheckBox.Font = new System.Drawing.Font("Tahoma", 14.25F);
            this.MusicCheckBox.ForeColor = System.Drawing.Color.White;
            this.MusicCheckBox.Location = new System.Drawing.Point(228, 98);
            this.MusicCheckBox.Name = "MusicCheckBox";
            this.MusicCheckBox.Size = new System.Drawing.Size(76, 27);
            this.MusicCheckBox.TabIndex = 31;
            this.MusicCheckBox.Text = "Music";
            this.MusicCheckBox.UseVisualStyleBackColor = false;
            // 
            // soundsCheckBox
            // 
            this.soundsCheckBox.AutoSize = true;
            this.soundsCheckBox.Cursor = System.Windows.Forms.Cursors.Hand;
            this.soundsCheckBox.Font = new System.Drawing.Font("Tahoma", 14.25F);
            this.soundsCheckBox.ForeColor = System.Drawing.Color.White;
            this.soundsCheckBox.Location = new System.Drawing.Point(125, 98);
            this.soundsCheckBox.Name = "soundsCheckBox";
            this.soundsCheckBox.Size = new System.Drawing.Size(91, 27);
            this.soundsCheckBox.TabIndex = 30;
            this.soundsCheckBox.Text = "Sounds";
            this.soundsCheckBox.UseVisualStyleBackColor = true;
            // 
            // soundLb
            // 
            this.soundLb.AutoSize = true;
            this.soundLb.Cursor = System.Windows.Forms.Cursors.Default;
            this.soundLb.Font = new System.Drawing.Font("Tahoma", 14.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(177)));
            this.soundLb.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(99)))), ((int)(((byte)(7)))));
            this.soundLb.Location = new System.Drawing.Point(21, 98);
            this.soundLb.Name = "soundLb";
            this.soundLb.Size = new System.Drawing.Size(83, 23);
            this.soundLb.TabIndex = 29;
            this.soundLb.Text = "Sound :";
            // 
            // comboBox1
            // 
            this.comboBox1.BackColor = System.Drawing.Color.DimGray;
            this.comboBox1.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBox1.Font = new System.Drawing.Font("Tahoma", 14.25F);
            this.comboBox1.ForeColor = System.Drawing.Color.White;
            this.comboBox1.FormattingEnabled = true;
            this.comboBox1.Items.AddRange(new object[] {
            "600x400",
            "800x600",
            "1024x768",
            "1280x960"});
            this.comboBox1.Location = new System.Drawing.Point(164, 61);
            this.comboBox1.Name = "comboBox1";
            this.comboBox1.Size = new System.Drawing.Size(137, 31);
            this.comboBox1.TabIndex = 15;
            // 
            // resoluLb
            // 
            this.resoluLb.AutoSize = true;
            this.resoluLb.Cursor = System.Windows.Forms.Cursors.Default;
            this.resoluLb.Font = new System.Drawing.Font("Tahoma", 14.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(177)));
            this.resoluLb.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(99)))), ((int)(((byte)(7)))));
            this.resoluLb.Location = new System.Drawing.Point(21, 61);
            this.resoluLb.Name = "resoluLb";
            this.resoluLb.Size = new System.Drawing.Size(126, 23);
            this.resoluLb.TabIndex = 14;
            this.resoluLb.Text = "Resolution :";
            // 
            // optSaveBtn
            // 
            this.optSaveBtn.Anchor = System.Windows.Forms.AnchorStyles.Bottom;
            this.optSaveBtn.AutoSize = true;
            this.optSaveBtn.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(17)))), ((int)(((byte)(17)))), ((int)(((byte)(17)))));
            this.optSaveBtn.FlatAppearance.BorderColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(99)))), ((int)(((byte)(7)))));
            this.optSaveBtn.FlatAppearance.BorderSize = 2;
            this.optSaveBtn.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.optSaveBtn.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.optSaveBtn.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(99)))), ((int)(((byte)(7)))));
            this.optSaveBtn.Location = new System.Drawing.Point(10, 278);
            this.optSaveBtn.Name = "optSaveBtn";
            this.optSaveBtn.Size = new System.Drawing.Size(100, 38);
            this.optSaveBtn.TabIndex = 13;
            this.optSaveBtn.Text = "&Save";
            this.optSaveBtn.UseVisualStyleBackColor = false;
            this.optSaveBtn.Click += new System.EventHandler(this.optSaveBtn_Click);
            this.optSaveBtn.MouseEnter += new System.EventHandler(this.common_mouseenter);
            this.optSaveBtn.MouseLeave += new System.EventHandler(this.common_mouseleave);
            // 
            // optCloseBtn
            // 
            this.optCloseBtn.Anchor = System.Windows.Forms.AnchorStyles.Bottom;
            this.optCloseBtn.AutoSize = true;
            this.optCloseBtn.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(17)))), ((int)(((byte)(17)))), ((int)(((byte)(17)))));
            this.optCloseBtn.FlatAppearance.BorderColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(99)))), ((int)(((byte)(7)))));
            this.optCloseBtn.FlatAppearance.BorderSize = 2;
            this.optCloseBtn.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.optCloseBtn.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.optCloseBtn.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(99)))), ((int)(((byte)(7)))));
            this.optCloseBtn.Location = new System.Drawing.Point(215, 278);
            this.optCloseBtn.Name = "optCloseBtn";
            this.optCloseBtn.Size = new System.Drawing.Size(100, 38);
            this.optCloseBtn.TabIndex = 11;
            this.optCloseBtn.Text = "&Close";
            this.optCloseBtn.UseVisualStyleBackColor = false;
            this.optCloseBtn.Click += new System.EventHandler(this.optCloseBtn_Click);
            this.optCloseBtn.MouseEnter += new System.EventHandler(this.common_mouseenter);
            this.optCloseBtn.MouseLeave += new System.EventHandler(this.common_mouseleave);
            // 
            // usernameLabel
            // 
            this.usernameLabel.AutoSize = true;
            this.usernameLabel.Cursor = System.Windows.Forms.Cursors.Default;
            this.usernameLabel.Font = new System.Drawing.Font("Tahoma", 14.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(177)));
            this.usernameLabel.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(99)))), ((int)(((byte)(7)))));
            this.usernameLabel.Location = new System.Drawing.Point(21, 17);
            this.usernameLabel.Name = "usernameLabel";
            this.usernameLabel.Size = new System.Drawing.Size(118, 23);
            this.usernameLabel.TabIndex = 11;
            this.usernameLabel.Text = "Username :";
            // 
            // userNameTextbox
            // 
            this.userNameTextbox.BackColor = System.Drawing.Color.DimGray;
            this.userNameTextbox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.userNameTextbox.Font = new System.Drawing.Font("Tahoma", 14.25F);
            this.userNameTextbox.ForeColor = System.Drawing.Color.White;
            this.userNameTextbox.Location = new System.Drawing.Point(164, 18);
            this.userNameTextbox.MaxLength = 10;
            this.userNameTextbox.Name = "userNameTextbox";
            this.userNameTextbox.Size = new System.Drawing.Size(137, 30);
            this.userNameTextbox.TabIndex = 12;
            this.userNameTextbox.Text = "Username";
            this.userNameTextbox.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // redRadioBtn
            // 
            this.redRadioBtn.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.redRadioBtn.AutoSize = true;
            this.redRadioBtn.Cursor = System.Windows.Forms.Cursors.Hand;
            this.redRadioBtn.Font = new System.Drawing.Font("Tahoma", 14.25F);
            this.redRadioBtn.ForeColor = System.Drawing.Color.White;
            this.redRadioBtn.Location = new System.Drawing.Point(12, 27);
            this.redRadioBtn.Name = "redRadioBtn";
            this.redRadioBtn.Size = new System.Drawing.Size(61, 27);
            this.redRadioBtn.TabIndex = 32;
            this.redRadioBtn.TabStop = true;
            this.redRadioBtn.Text = "&Red";
            this.redRadioBtn.UseVisualStyleBackColor = true;
            // 
            // blueRadioBtn
            // 
            this.blueRadioBtn.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.blueRadioBtn.AutoSize = true;
            this.blueRadioBtn.Cursor = System.Windows.Forms.Cursors.Hand;
            this.blueRadioBtn.Font = new System.Drawing.Font("Tahoma", 14.25F);
            this.blueRadioBtn.ForeColor = System.Drawing.Color.White;
            this.blueRadioBtn.Location = new System.Drawing.Point(88, 28);
            this.blueRadioBtn.Name = "blueRadioBtn";
            this.blueRadioBtn.Size = new System.Drawing.Size(64, 27);
            this.blueRadioBtn.TabIndex = 33;
            this.blueRadioBtn.TabStop = true;
            this.blueRadioBtn.Text = "&Blue";
            this.blueRadioBtn.UseVisualStyleBackColor = true;
            // 
            // autoGroupBox
            // 
            this.autoGroupBox.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.autoGroupBox.Controls.Add(this.blueRadioBtn);
            this.autoGroupBox.Controls.Add(this.redRadioBtn);
            this.autoGroupBox.Font = new System.Drawing.Font("Tahoma", 14.25F, System.Drawing.FontStyle.Bold);
            this.autoGroupBox.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(99)))), ((int)(((byte)(7)))));
            this.autoGroupBox.Location = new System.Drawing.Point(20, 197);
            this.autoGroupBox.Name = "autoGroupBox";
            this.autoGroupBox.Size = new System.Drawing.Size(287, 60);
            this.autoGroupBox.TabIndex = 34;
            this.autoGroupBox.TabStop = false;
            this.autoGroupBox.Text = "AutoClicker :";
            this.autoGroupBox.Visible = false;
            // 
            // OptionsForm
            // 
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(72)))), ((int)(((byte)(72)))), ((int)(((byte)(72)))));
            this.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None;
            this.ClientSize = new System.Drawing.Size(329, 349);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.closeBtn);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "OptionsForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "OptionsForm";
            this.Load += new System.EventHandler(this.OptionsForm_Load);
            this.MouseDown += new System.Windows.Forms.MouseEventHandler(this.OptionsForm_MouseDown);
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.PlayerBmdGroup.ResumeLayout(false);
            this.PlayerBmdGroup.PerformLayout();
            this.grahpicsGrop.ResumeLayout(false);
            this.grahpicsGrop.PerformLayout();
            this.autoGroupBox.ResumeLayout(false);
            this.autoGroupBox.PerformLayout();
            this.ResumeLayout(false);

    }

    public enum eLangs
    {
      HE,
      EN,
    }
  }
}
