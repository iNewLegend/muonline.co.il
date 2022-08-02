// Decompiled with JetBrains decompiler
// Type: Launcher_v2.MainWindow
// Assembly: Launcher_v2, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: 62AD7470-6E7C-4CD6-AD3C-47F3F5D3DB0B
// Assembly location: C:\Program Files (x86)\Mu Israel\Launcher_v2.exe

using Ionic.Zip;
using Launcher_v2.Properties;
using Microsoft.Win32;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Net;
using System.Net.Sockets;
using System.Runtime.InteropServices;
using System.Threading;
using System.Windows.Forms;
using System.Xml.Linq;

namespace Launcher_v2
{
  public class MainWindow : Form
  {
    public static Dictionary<string, string> langLaun = new Dictionary<string, string>();
    public static bool langFlag = true;
    public string configPath = "Software\\Webzen\\Mu\\Config";
    public string Server = "http://update.muonline.co.il/update/";
    public string Root = AppDomain.CurrentDomain.BaseDirectory;
    public const int WM_NCLBUTTONDOWN = 161;
    public const int HT_CAPTION = 2;
    private bool isError;
    private IContainer components;
    private BackgroundWorker backgroundWorker1;
    private Button closeBtn;
    private Button minimizeBtn;
    private Label proccessLb;
    private ProgressBar progressBar1;
    private Button strtGameBtn;
    private Button optionsBtn;
    private Button checkforupdatesBtn;
    private Label downloadLbl;
    private Label title;
    public WebBrowser patchNotes;
    private Panel panelImg;
    private Panel panel1;
    private CheckBox windowModeCheck;
    private CheckBox checkBox3D;
    private RadioButton engRadio;
    private RadioButton hebRadio;
    private Label versionLb;

    public MainWindow()
    {
      MainWindow.buildDictionary();
      this.InitializeComponent();
      this.backgroundWorker1.RunWorkerAsync();
    }

    [DllImport("user32.dll")]
    public static extern int SendMessage(IntPtr hWnd, int Msg, int wParam, int lParam);

    [DllImport("user32.dll")]
    public static extern bool ReleaseCapture();

    private static void buildDictionary()
    {
      if (MainWindow.langLaun.Count != 0)
        return;
      MainWindow.langLaun.Add("Mu Israel Launcher", "לאנצר אמיו ישראל");
      MainWindow.langLaun.Add("No new updates", "אין עידכונים חדשים");
      MainWindow.langLaun.Add("Downloading Updates", "מוריד עידכונים");
      MainWindow.langLaun.Add("&OPTIONS", "&אפשרויות");
      MainWindow.langLaun.Add("&START GAME", "&שחק");
      MainWindow.langLaun.Add("&CHECK FOR UPDATES", "&בדוק האם קיימים עידכונים");
      MainWindow.langLaun.Add("&Hebrew", "&עברית");
      MainWindow.langLaun.Add("&English", "&אנגלית");
      MainWindow.langLaun.Add("Window Mode", "הפעל כחלון");
      MainWindow.langLaun.Add("Starting to Extract", "מתחיל לחלץ");
      MainWindow.langLaun.Add("Finished to Extract", "סיים לחלץ");
      MainWindow.langLaun.Add("Finished", "סיים");
      MainWindow.langLaun.Add("Checking ...", "בודק ...");
      MainWindow.langLaun.Add("Starting updating language", "מתחיל לעדכן שפה");
      MainWindow.langLaun.Add("File not found. Starting to download language from server.", "קובץ לא נמצא. מוריד את השפה מהשרת");
      MainWindow.langLaun.Add("Couldn't extract the lang", "לא מהצליח לחלץ את השפה");
      MainWindow.langLaun.Add("Finished updating language to English", "סיים לעדכן לעברית");
      MainWindow.langLaun.Add("Didn't update", "לא עודכן");
      MainWindow.langLaun.Add("", "");
      MainWindow.langLaun.Add("לאנצר אמיו ישראל", "Mu Israel Launcher");
      MainWindow.langLaun.Add("אין עידכונים חדשים", "No new updates");
      MainWindow.langLaun.Add("מוריד עידכונים", "Downloading Updates");
      MainWindow.langLaun.Add("&אפשרויות", "&OPTIONS");
      MainWindow.langLaun.Add("&שחק", "&START GAME");
      MainWindow.langLaun.Add("&בדוק האם קיימים עידכונים", "&CHECK FOR UPDATES");
      MainWindow.langLaun.Add("&עברית", "&Hebrew");
      MainWindow.langLaun.Add("&אנגלית", "&English");
      MainWindow.langLaun.Add("הפעל כחלון", "Window Mode");
      MainWindow.langLaun.Add("מתחיל לחלץ", "Starting to Extract");
      MainWindow.langLaun.Add("סיים לחלץ", "Finished to Extract");
      MainWindow.langLaun.Add("סיים", "Finished");
      MainWindow.langLaun.Add("בודק ...", "Checking ...");
      MainWindow.langLaun.Add("מתחיל לעדכן שפה", "Starting updating language");
      MainWindow.langLaun.Add("קובץ לא נמצא. מוריד את השפה מהשרת", "File not found. Starting to download language from server.");
      MainWindow.langLaun.Add("לא מהצליח לחלץ את השפה", "Couldn't extract the lang");
      MainWindow.langLaun.Add("סיים לעדכן לעברית", "Finished updating language to English");
      MainWindow.langLaun.Add("לא עודכן", "Didn't update");
    }

    private void Form1_MouseDown(object sender, MouseEventArgs e)
    {
      if (e.Button != MouseButtons.Left)
        return;
      MainWindow.ReleaseCapture();
      MainWindow.SendMessage(this.Handle, 161, 2, 0);
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

    private void minimizeBtn_Click(object sender, EventArgs e)
    {
      this.WindowState = FormWindowState.Minimized;
    }

    private void minimizeBtn_MouseEnter(object sender, EventArgs e)
    {
      this.minimizeBtn.BackgroundImage = (Image) Resources.minimize2;
    }

    private void minimizeBtn_MouseLeave(object sender, EventArgs e)
    {
      this.minimizeBtn.BackgroundImage = (Image) Resources.minimize1;
    }

    private static bool deleteFile(string f)
    {
      try
      {
        System.IO.File.Delete(f);
        return true;
      }
      catch (IOException ex)
      {
        return false;
      }
    }

    public bool downloadUpdate(string Url, string File, string PathTtoWrite)
    {
      Uri requestUri = new Uri(Url);
      HttpWebResponse httpWebResponse;
      try
      {
        httpWebResponse = (HttpWebResponse) WebRequest.Create(requestUri).GetResponse();
      }
      catch (Exception ex)
      {
        this.Invoke((Action) (() =>
        {
          this.downloadLbl.Text = File + " " + ex.Message;
          this.isError = true;
        }));
        Thread.Sleep(500);
        return false;
      }
      httpWebResponse.Close();
      long contentLength = httpWebResponse.ContentLength;
      long num = 0L;
      using (WebClient webClient = new WebClient())
      {
        using (Stream stream1 = webClient.OpenRead(new Uri(Url)))
        {
          using (Stream stream2 = (Stream) new FileStream(PathTtoWrite, FileMode.Create, FileAccess.Write, FileShare.None))
          {
            byte[] buffer = new byte[contentLength];
            int count;
            while ((count = stream1.Read(buffer, 0, buffer.Length)) > 0)
            {
              stream2.Write(buffer, 0, count);
              num += (long) count;
              int iProgressPercentage = (int) ((double) num / (double) buffer.Length * 100.0);
              this.Invoke((Action) (() => this.proccessLb.Text = string.Concat(new object[4]
              {
                (object) File,
                (object) ": ",
                (object) iProgressPercentage,
                (object) "% / 100%"
              })));
              try
              {
                this.backgroundWorker1.ReportProgress(iProgressPercentage);
              }
              catch
              {
              }
            }
            stream2.Close();
          }
          stream1.Close();
        }
      }
      this.Invoke((Action) (() =>
      {
        string index = "Starting to Extract";
        if (MainWindow.langFlag)
          index = MainWindow.langLaun[index];
        this.proccessLb.Text = File + ": " + index;
      }));
      using (ZipFile zipFile = ZipFile.Read(File))
      {
        foreach (ZipEntry zipEntry in zipFile)
        {
          try
          {
            zipEntry.Extract(this.Root, true);
          }
          catch (Exception ex)
          {
            this.Invoke((Action) (() =>
            {
              this.downloadLbl.Text = File + " extract " + ex.Message;
              this.isError = true;
            }));
            return false;
          }
        }
      }
      this.Invoke((Action) (() =>
      {
        string index = "Finished to Extract";
        if (MainWindow.langFlag)
          index = MainWindow.langLaun[index];
        this.proccessLb.Text = File + ": " + index;
      }));
      return true;
    }

    private void backgroundWorker1_DoWork(object sender, DoWorkEventArgs e)
    {
      this.isError = false;
      if (System.IO.File.Exists("launcher_updater.exe"))
        MainWindow.deleteFile("launcher_updater.exe");
      this.Invoke((Action) (() => this.setBtnOff()));
      this.backgroundWorker1.ReportProgress(0);
      Thread.Sleep(500);
      if (!System.IO.File.Exists("version"))
      {
        using (System.IO.File.Create("version"));
        using (StreamWriter streamWriter = new StreamWriter("version"))
        {
          string str = StringCipher.Encrypt("1.0", "ImProVersion123");
          streamWriter.Write(str);
          streamWriter.Close();
        }
      }
      string lclVersion;
      using (StreamReader streamReader = new StreamReader("version"))
      {
        lclVersion = streamReader.ReadLine();
        lclVersion = StringCipher.Decrypt(lclVersion, "ImProVersion123");
        streamReader.Close();
      }
      this.Invoke((Action) (() => this.versionLb.Text = "Version: " + lclVersion));
      XDocument xdocument;
      try
      {
        xdocument = XDocument.Load(this.Server + "Updates.xml");
      }
      catch (Exception ex)
      {
        this.Invoke((Action) (() =>
        {
          this.downloadLbl.Text = "XML File: " + ex.Message;
          this.isError = true;
        }));
        return;
      }
      foreach (XElement xelement in xdocument.Descendants((XName) "update"))
      {
        string server = xelement.Element((XName) "version").Value;
        string file = xelement.Element((XName) "file").Value;
        string Url = this.Server + "files/" + file;
        string PathTtoWrite = this.Root + file;
        if (Version.isUpdate(server, lclVersion))
        {
          if (this.downloadUpdate(Url, file, PathTtoWrite))
          {
            if (!System.IO.File.Exists("version"))
            {
              using (System.IO.File.Create("version"));
              using (StreamWriter streamWriter = new StreamWriter("version"))
              {
                  string str = StringCipher.Encrypt("1.0", "ImProVersion123");
                  streamWriter.Write(str);
                  streamWriter.Close();
              }
            }
            using (StreamReader streamReader = new StreamReader("version"))
            {
                lclVersion = streamReader.ReadLine();
                lclVersion = StringCipher.Decrypt(lclVersion, "ImProVersion123");
                streamReader.Close();
            }
            string nextVersion = Version.getNext(lclVersion);
            using (StreamWriter streamWriter = new StreamWriter("version"))
            {
              string str = StringCipher.Encrypt(nextVersion, "ImProVersion123");
              streamWriter.Write(str);
            }
            this.Invoke((Action) (() => this.versionLb.Text = "Version: " + nextVersion));
          }
          MainWindow.deleteFile(file);
          Thread.Sleep(500);
          this.Invoke((Action) (() =>
          {
            string index = "Finished";
            if (MainWindow.langFlag)
              index = MainWindow.langLaun[index];
            this.proccessLb.Text = file + ": " + index;
          }));
          Thread.Sleep(750);
          this.Invoke((Action) (() => this.proccessLb.Text = ""));
        }
        this.backgroundWorker1.ReportProgress(100);
        if (System.IO.File.Exists("launcher.zip"))
        {
          this.downloadLauncherUpdater();
          try
          {
            Process.Start("launcher_updater.exe");
          }
          catch (Exception ex)
          {
            int num = (int) MessageBox.Show(ex.Message);
            return;
          }
          Environment.Exit(0);
        }
      }
      this.Invoke((Action) (() => this.setBtnOn()));
    }

    private void backgroundWorker1_ProgressChanged(object sender, ProgressChangedEventArgs e)
    {
      this.progressBar1.Value = e.ProgressPercentage;
      this.downloadLbl.ForeColor = System.Drawing.Color.Silver;
      string index = "Downloading Updates";
      if (MainWindow.langFlag)
        index = MainWindow.langLaun[index];
      this.downloadLbl.Text = index;
    }

    private void backgroundWorker1_RunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e)
    {
      if (e.Error != null)
      {
        int num = (int) MessageBox.Show(e.Error.Message + "\nSRC: " + e.Error.Source);
      }
      else
      {
        this.downloadLbl.ForeColor = System.Drawing.Color.FromArgb((int) byte.MaxValue, 99, 7);
        if (this.isError)
        {
          string index = "Didn't update";
          if (MainWindow.langFlag)
            index = MainWindow.langLaun[index];
          this.downloadLbl.Text = index;
          this.Invoke((Action) (() => this.setBtnOn()));
        }
        else
        {
          string index = "No new updates";
          if (MainWindow.langFlag)
            index = MainWindow.langLaun[index];
          this.downloadLbl.Text = index;
          this.Invoke((Action) (() => this.setBtnOn()));
        }
      }
    }

    private void strtGameBtn_Click(object sender, EventArgs e)
    {
      if (this.strtGameBtn.ForeColor == System.Drawing.Color.Gray)
        return;
      try
      {
        RegistryKey registryKey = Registry.CurrentUser.OpenSubKey(this.configPath);
        switch ((int) registryKey.GetValue("LangMuIsrael", (object) 0))
        {
          case 1:
            if ((int) registryKey.GetValue("3DActive", (object) 0) == 1)
            {
              Process.Start("main.exe", "connect /umuonline.linuxserv.co.il /p44405 1 EN");
              break;
            }
            Process.Start("main.exe", "connect /umuonline.linuxserv.co.il /p44405 0 EN");
            break;
          default:
            if ((int) registryKey.GetValue("3DActive", (object) 0) == 1)
            {
              Process.Start("main.exe", "connect /umuonline.linuxserv.co.il /p44405 1 HE");
              break;
            }
            Process.Start("main.exe", "connect /umuonline.linuxserv.co.il /p44405 0 HE");
            break;
        }
      }
      catch (Exception ex)
      {
        this.downloadLbl.Text = "main.exe " + ex.Message;
        return;
      }
      this.Close();
    }

    private void optionsBtn_Click(object sender, EventArgs e)
    {
      if (this.optionsBtn.ForeColor == System.Drawing.Color.Gray)
        return;
      OptionsForm optionsForm = new OptionsForm();
      this.Hide();
      int num = (int) optionsForm.ShowDialog();
      this.Show();
    }

    private void Form1_Load(object sender, EventArgs e)
    {
      RegistryKey registryKey = Registry.CurrentUser.OpenSubKey(this.configPath, true);
      if (registryKey == null)
      {
        registryKey = Registry.CurrentUser.CreateSubKey(this.configPath);
        registryKey.SetValue("LangMuIsrael", (object) 0, RegistryValueKind.DWord);
        registryKey.SetValue("AutoClickerMuIsrael", (object) 0, RegistryValueKind.DWord);
        registryKey.SetValue("3DActive", (object) 0, RegistryValueKind.DWord);
        registryKey.SetValue("PlayerBmdMuIsrael", (object) 0, RegistryValueKind.DWord);
      }
      if ((int) registryKey.GetValue("WindowMode", (object) 0) == 1)
        this.windowModeCheck.Checked = true;
      if ((int) registryKey.GetValue("3DActive", (object) 0) == 1)
        this.checkBox3D.Checked = true;
      switch ((int) registryKey.GetValue("LangMuIsrael", (object) 0))
      {
        case 1:
          this.engRadio.Checked = true;
          MainWindow.langFlag = false;
          break;
        default:
          this.hebRadio.Checked = true;
          MainWindow.langFlag = true;
          this.changeBtnLang();
          break;
      }
      registryKey.SetValue("TextInput", (object) 2, RegistryValueKind.DWord);
    }

    private void MusicCheckBox_CheckedChanged(object sender, EventArgs e)
    {
      RegistryKey registryKey = Registry.CurrentUser.OpenSubKey(this.configPath, true);
      uint num = 0U;
      if (this.windowModeCheck.Checked)
        num = 1U;
      registryKey.SetValue("WindowMode", (object) num, RegistryValueKind.DWord);
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

    private void button1_MouseClick(object sender, MouseEventArgs e)
    {
      if (this.checkforupdatesBtn.ForeColor == System.Drawing.Color.Gray || this.backgroundWorker1.IsBusy)
        return;
      string index = "Checking ...";
      if (MainWindow.langFlag)
        index = MainWindow.langLaun[index];
      this.downloadLbl.Text = index;
      this.backgroundWorker1.RunWorkerAsync();
    }

    private void downloadLauncherUpdater()
    {
      string str = "launcher_updater.zip";
      this.setBtnOff();
      this.downloadUpdate(this.Server + "files/" + str, str, this.Root + str);
      MainWindow.deleteFile(str);
      this.setBtnOn();
    }

    private void setBtnOff()
    {
      this.checkforupdatesBtn.ForeColor = System.Drawing.Color.Gray;
      this.optionsBtn.ForeColor = System.Drawing.Color.Gray;
      this.strtGameBtn.ForeColor = System.Drawing.Color.Gray;
      this.hebRadio.ForeColor = System.Drawing.Color.Gray;
      this.engRadio.ForeColor = System.Drawing.Color.Gray;
    }

    private void setBtnOn()
    {
      this.checkforupdatesBtn.ForeColor = System.Drawing.Color.FromArgb((int) byte.MaxValue, 99, 71);
      this.optionsBtn.ForeColor = System.Drawing.Color.FromArgb((int) byte.MaxValue, 99, 71);
      this.strtGameBtn.ForeColor = System.Drawing.Color.FromArgb((int) byte.MaxValue, 99, 71);
      this.hebRadio.ForeColor = System.Drawing.Color.FromArgb((int) byte.MaxValue, 99, 71);
      this.engRadio.ForeColor = System.Drawing.Color.FromArgb((int) byte.MaxValue, 99, 71);
    }

    private bool updateLang(MainWindow.eLangs lang)
    {
      string str1 = this.Root + "Data\\" + lang.ToString() + ".zip";
      if (!System.IO.File.Exists(str1))
      {
        this.Invoke((Action) (() =>
        {
          string index = "File not found. Starting to download language from server.";
          if (MainWindow.langFlag)
            index = MainWindow.langLaun[index];
          this.proccessLb.Text = index;
        }));
        string str2 = "Lang.zip";
        this.downloadUpdate(this.Server + "files/" + str2, str2, this.Root + str2);
        MainWindow.deleteFile(str2);
      }
      this.Invoke((Action) (() =>
      {
        string index = "Starting updating language";
        if (MainWindow.langFlag)
          index = MainWindow.langLaun[index];
        this.proccessLb.Text = index;
      }));
      using (ZipFile zipFile = ZipFile.Read(str1))
      {
        foreach (ZipEntry zipEntry in zipFile)
        {
          try
          {
            zipEntry.Extract(this.Root + "Data", true);
          }
          catch (Exception ex)
          {
            this.Invoke((Action) (() =>
            {
              string index = "Couldn't extract the lang";
              if (MainWindow.langFlag)
                index = MainWindow.langLaun[index];
              this.proccessLb.Text = index;
            }));
            return false;
          }
        }
      }
      this.Invoke((Action) (() =>
      {
        this.setBtnOn();
        string index = "Finished updating language to English";
        if (!MainWindow.langFlag)
          index = MainWindow.langLaun[index];
        this.proccessLb.Text = index;
      }));
      return true;
    }

    private void engRadio_Click(object sender, EventArgs e)
    {
      if (this.engRadio.ForeColor == System.Drawing.Color.Gray)
        return;
      RegistryKey registryKey = Registry.CurrentUser.OpenSubKey(this.configPath, true);
      if ((int) registryKey.GetValue("LangMuIsrael", (object) 0) == 1 || !this.engRadio.Checked)
        return;
      MainWindow.langFlag = false;
      this.updateLang(MainWindow.eLangs.EN);
      registryKey.SetValue("LangMuIsrael", (object) 1, RegistryValueKind.DWord);
      this.changeAllLang();
    }

    private void hebRadio_Click(object sender, EventArgs e)
    {
      if (this.hebRadio.ForeColor == System.Drawing.Color.Gray)
        return;
      RegistryKey registryKey = Registry.CurrentUser.OpenSubKey(this.configPath, true);
      if ((int) registryKey.GetValue("LangMuIsrael", (object) 0) == 0 || !this.hebRadio.Checked)
        return;
      MainWindow.langFlag = true;
      this.updateLang(MainWindow.eLangs.HE);
      registryKey.SetValue("LangMuIsrael", (object) 0, RegistryValueKind.DWord);
      this.changeAllLang();
    }

    private void changeAllLang()
    {
      this.title.Text = MainWindow.langLaun[this.title.Text];
      this.checkforupdatesBtn.Text = MainWindow.langLaun[this.checkforupdatesBtn.Text];
      this.optionsBtn.Text = MainWindow.langLaun[this.optionsBtn.Text];
      this.strtGameBtn.Text = MainWindow.langLaun[this.strtGameBtn.Text];
      this.windowModeCheck.Text = MainWindow.langLaun[this.windowModeCheck.Text];
      this.downloadLbl.Text = MainWindow.langLaun[this.downloadLbl.Text];
      this.proccessLb.Text = MainWindow.langLaun[this.proccessLb.Text];
    }

    private void changeBtnLang()
    {
      this.title.Text = MainWindow.langLaun[this.title.Text];
      this.checkforupdatesBtn.Text = MainWindow.langLaun[this.checkforupdatesBtn.Text];
      this.optionsBtn.Text = MainWindow.langLaun[this.optionsBtn.Text];
      this.strtGameBtn.Text = MainWindow.langLaun[this.strtGameBtn.Text];
      this.windowModeCheck.Text = MainWindow.langLaun[this.windowModeCheck.Text];
    }

    private void patchNotes_DocumentCompleted(object sender, WebBrowserDocumentCompletedEventArgs e)
    {
      if (this.patchNotes.ReadyState != WebBrowserReadyState.Complete)
        return;
      try
      {
        IPAddress[] hostAddresses = Dns.GetHostAddresses("update.muonline.co.il");
        Socket socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
        socket.Connect(hostAddresses[0], 80);
        this.patchNotes.Visible = true;
        this.panelImg.Visible = false;
        socket.Close();
      }
      catch
      {
      }
    }

    private void checkBox1_Click(object sender, EventArgs e)
    {
      uint num = 0U;
      RegistryKey registryKey = Registry.CurrentUser.OpenSubKey(this.configPath, true);
      if (this.checkBox3D.Checked)
        num = 1U;
      registryKey.SetValue("3DActive", (object) num, RegistryValueKind.DWord);
    }

    protected override void Dispose(bool disposing)
    {
      if (disposing && this.components != null)
        this.components.Dispose();
      base.Dispose(disposing);
    }

    private void InitializeComponent()
    {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainWindow));
            this.backgroundWorker1 = new System.ComponentModel.BackgroundWorker();
            this.proccessLb = new System.Windows.Forms.Label();
            this.progressBar1 = new System.Windows.Forms.ProgressBar();
            this.strtGameBtn = new System.Windows.Forms.Button();
            this.optionsBtn = new System.Windows.Forms.Button();
            this.checkforupdatesBtn = new System.Windows.Forms.Button();
            this.downloadLbl = new System.Windows.Forms.Label();
            this.title = new System.Windows.Forms.Label();
            this.minimizeBtn = new System.Windows.Forms.Button();
            this.closeBtn = new System.Windows.Forms.Button();
            this.patchNotes = new System.Windows.Forms.WebBrowser();
            this.panelImg = new System.Windows.Forms.Panel();
            this.hebRadio = new System.Windows.Forms.RadioButton();
            this.engRadio = new System.Windows.Forms.RadioButton();
            this.checkBox3D = new System.Windows.Forms.CheckBox();
            this.windowModeCheck = new System.Windows.Forms.CheckBox();
            this.panel1 = new System.Windows.Forms.Panel();
            this.versionLb = new System.Windows.Forms.Label();
            this.panel1.SuspendLayout();
            this.SuspendLayout();
            // 
            // backgroundWorker1
            // 
            this.backgroundWorker1.WorkerReportsProgress = true;
            this.backgroundWorker1.DoWork += new System.ComponentModel.DoWorkEventHandler(this.backgroundWorker1_DoWork);
            this.backgroundWorker1.ProgressChanged += new System.ComponentModel.ProgressChangedEventHandler(this.backgroundWorker1_ProgressChanged);
            this.backgroundWorker1.RunWorkerCompleted += new System.ComponentModel.RunWorkerCompletedEventHandler(this.backgroundWorker1_RunWorkerCompleted);
            // 
            // proccessLb
            // 
            this.proccessLb.AutoSize = true;
            this.proccessLb.BackColor = System.Drawing.Color.Black;
            this.proccessLb.Font = new System.Drawing.Font("Tahoma", 11.25F, System.Drawing.FontStyle.Bold);
            this.proccessLb.ForeColor = System.Drawing.Color.White;
            this.proccessLb.Location = new System.Drawing.Point(17, 552);
            this.proccessLb.Name = "proccessLb";
            this.proccessLb.Size = new System.Drawing.Size(0, 18);
            this.proccessLb.TabIndex = 502;
            // 
            // progressBar1
            // 
            this.progressBar1.Anchor = System.Windows.Forms.AnchorStyles.Bottom;
            this.progressBar1.BackColor = System.Drawing.SystemColors.AppWorkspace;
            this.progressBar1.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(192)))), ((int)(((byte)(0)))));
            this.progressBar1.Location = new System.Drawing.Point(12, 615);
            this.progressBar1.Name = "progressBar1";
            this.progressBar1.Size = new System.Drawing.Size(614, 34);
            this.progressBar1.Step = 0;
            this.progressBar1.Style = System.Windows.Forms.ProgressBarStyle.Continuous;
            this.progressBar1.TabIndex = 0;
            // 
            // strtGameBtn
            // 
            this.strtGameBtn.Anchor = System.Windows.Forms.AnchorStyles.Bottom;
            this.strtGameBtn.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(17)))), ((int)(((byte)(17)))), ((int)(((byte)(17)))));
            this.strtGameBtn.FlatAppearance.BorderColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(99)))), ((int)(((byte)(7)))));
            this.strtGameBtn.FlatAppearance.BorderSize = 2;
            this.strtGameBtn.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.strtGameBtn.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.strtGameBtn.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(99)))), ((int)(((byte)(7)))));
            this.strtGameBtn.Location = new System.Drawing.Point(739, 615);
            this.strtGameBtn.Name = "strtGameBtn";
            this.strtGameBtn.Size = new System.Drawing.Size(150, 34);
            this.strtGameBtn.TabIndex = 1;
            this.strtGameBtn.Text = "&START GAME";
            this.strtGameBtn.UseVisualStyleBackColor = false;
            this.strtGameBtn.Click += new System.EventHandler(this.strtGameBtn_Click);
            this.strtGameBtn.MouseEnter += new System.EventHandler(this.common_mouseenter);
            this.strtGameBtn.MouseLeave += new System.EventHandler(this.common_mouseleave);
            // 
            // optionsBtn
            // 
            this.optionsBtn.Anchor = System.Windows.Forms.AnchorStyles.Bottom;
            this.optionsBtn.AutoSize = true;
            this.optionsBtn.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(17)))), ((int)(((byte)(17)))), ((int)(((byte)(17)))));
            this.optionsBtn.FlatAppearance.BorderColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(99)))), ((int)(((byte)(7)))));
            this.optionsBtn.FlatAppearance.BorderSize = 2;
            this.optionsBtn.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.optionsBtn.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.optionsBtn.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(99)))), ((int)(((byte)(7)))));
            this.optionsBtn.Location = new System.Drawing.Point(632, 615);
            this.optionsBtn.Name = "optionsBtn";
            this.optionsBtn.Size = new System.Drawing.Size(100, 34);
            this.optionsBtn.TabIndex = 6;
            this.optionsBtn.Text = "&OPTIONS";
            this.optionsBtn.UseVisualStyleBackColor = false;
            this.optionsBtn.Click += new System.EventHandler(this.optionsBtn_Click);
            this.optionsBtn.MouseEnter += new System.EventHandler(this.common_mouseenter);
            this.optionsBtn.MouseLeave += new System.EventHandler(this.common_mouseleave);
            // 
            // checkforupdatesBtn
            // 
            this.checkforupdatesBtn.Anchor = System.Windows.Forms.AnchorStyles.Bottom;
            this.checkforupdatesBtn.AutoSize = true;
            this.checkforupdatesBtn.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(17)))), ((int)(((byte)(17)))), ((int)(((byte)(17)))));
            this.checkforupdatesBtn.FlatAppearance.BorderColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(99)))), ((int)(((byte)(7)))));
            this.checkforupdatesBtn.FlatAppearance.BorderSize = 2;
            this.checkforupdatesBtn.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.checkforupdatesBtn.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.checkforupdatesBtn.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(99)))), ((int)(((byte)(7)))));
            this.checkforupdatesBtn.Location = new System.Drawing.Point(631, 576);
            this.checkforupdatesBtn.Name = "checkforupdatesBtn";
            this.checkforupdatesBtn.Size = new System.Drawing.Size(258, 34);
            this.checkforupdatesBtn.TabIndex = 23;
            this.checkforupdatesBtn.Text = "&CHECK FOR UPDATES";
            this.checkforupdatesBtn.UseVisualStyleBackColor = false;
            this.checkforupdatesBtn.MouseClick += new System.Windows.Forms.MouseEventHandler(this.button1_MouseClick);
            this.checkforupdatesBtn.MouseEnter += new System.EventHandler(this.common_mouseenter);
            this.checkforupdatesBtn.MouseLeave += new System.EventHandler(this.common_mouseleave);
            // 
            // downloadLbl
            // 
            this.downloadLbl.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.downloadLbl.BackColor = System.Drawing.Color.Black;
            this.downloadLbl.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.downloadLbl.Font = new System.Drawing.Font("Tahoma", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.downloadLbl.ForeColor = System.Drawing.Color.Black;
            this.downloadLbl.ImageAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.downloadLbl.Location = new System.Drawing.Point(12, 576);
            this.downloadLbl.Name = "downloadLbl";
            this.downloadLbl.Size = new System.Drawing.Size(614, 36);
            this.downloadLbl.TabIndex = 501;
            this.downloadLbl.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // title
            // 
            this.title.AutoSize = true;
            this.title.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(72)))), ((int)(((byte)(72)))), ((int)(((byte)(72)))));
            this.title.Font = new System.Drawing.Font("Tahoma", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.title.ForeColor = System.Drawing.Color.White;
            this.title.ImageAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.title.Location = new System.Drawing.Point(1, 4);
            this.title.Name = "title";
            this.title.Size = new System.Drawing.Size(143, 19);
            this.title.TabIndex = 504;
            this.title.Text = "Mu Israel Launcher";
            this.title.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // minimizeBtn
            // 
            this.minimizeBtn.BackColor = System.Drawing.Color.Transparent;
            this.minimizeBtn.BackgroundImage = global::Launcher_v2.Properties.Resources.minimize1;
            this.minimizeBtn.Cursor = System.Windows.Forms.Cursors.Hand;
            this.minimizeBtn.FlatAppearance.BorderSize = 0;
            this.minimizeBtn.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.minimizeBtn.Location = new System.Drawing.Point(832, 0);
            this.minimizeBtn.Name = "minimizeBtn";
            this.minimizeBtn.Size = new System.Drawing.Size(34, 26);
            this.minimizeBtn.TabIndex = 4;
            this.minimizeBtn.UseVisualStyleBackColor = false;
            this.minimizeBtn.Click += new System.EventHandler(this.minimizeBtn_Click);
            this.minimizeBtn.MouseEnter += new System.EventHandler(this.minimizeBtn_MouseEnter);
            this.minimizeBtn.MouseLeave += new System.EventHandler(this.minimizeBtn_MouseLeave);
            // 
            // closeBtn
            // 
            this.closeBtn.BackColor = System.Drawing.Color.Transparent;
            this.closeBtn.BackgroundImage = global::Launcher_v2.Properties.Resources.close1;
            this.closeBtn.Cursor = System.Windows.Forms.Cursors.Hand;
            this.closeBtn.FlatAppearance.BorderSize = 0;
            this.closeBtn.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.closeBtn.Location = new System.Drawing.Point(866, 0);
            this.closeBtn.Name = "closeBtn";
            this.closeBtn.Size = new System.Drawing.Size(34, 26);
            this.closeBtn.TabIndex = 3;
            this.closeBtn.UseVisualStyleBackColor = false;
            this.closeBtn.Click += new System.EventHandler(this.closeBtn_Click);
            this.closeBtn.MouseEnter += new System.EventHandler(this.closeBtn_MouseEnter);
            this.closeBtn.MouseLeave += new System.EventHandler(this.closeBtn_MouseLeave);
            // 
            // patchNotes
            // 
            this.patchNotes.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)));
            this.patchNotes.Location = new System.Drawing.Point(0, 26);
            this.patchNotes.MinimumSize = new System.Drawing.Size(20, 20);
            this.patchNotes.Name = "patchNotes";
            this.patchNotes.ScrollBarsEnabled = false;
            this.patchNotes.Size = new System.Drawing.Size(900, 629);
            this.patchNotes.TabIndex = 500;
            this.patchNotes.Tag = "";
            this.patchNotes.Url = new System.Uri("http://update.muonline.co.il/update/html/", System.UriKind.Absolute);
            this.patchNotes.Visible = false;
            this.patchNotes.DocumentCompleted += new System.Windows.Forms.WebBrowserDocumentCompletedEventHandler(this.patchNotes_DocumentCompleted);
            // 
            // panelImg
            // 
            this.panelImg.BackgroundImage = global::Launcher_v2.Properties.Resources.background1;
            this.panelImg.Location = new System.Drawing.Point(0, 26);
            this.panelImg.Name = "panelImg";
            this.panelImg.Size = new System.Drawing.Size(900, 629);
            this.panelImg.TabIndex = 505;
            // 
            // hebRadio
            // 
            this.hebRadio.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.hebRadio.Cursor = System.Windows.Forms.Cursors.Hand;
            this.hebRadio.Font = new System.Drawing.Font("Tahoma", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.hebRadio.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(99)))), ((int)(((byte)(7)))));
            this.hebRadio.Location = new System.Drawing.Point(183, 2);
            this.hebRadio.Name = "hebRadio";
            this.hebRadio.Size = new System.Drawing.Size(72, 18);
            this.hebRadio.TabIndex = 24;
            this.hebRadio.TabStop = true;
            this.hebRadio.Text = "&עברית";
            this.hebRadio.UseVisualStyleBackColor = true;
            this.hebRadio.Click += new System.EventHandler(this.hebRadio_Click);
            // 
            // engRadio
            // 
            this.engRadio.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.engRadio.Cursor = System.Windows.Forms.Cursors.Hand;
            this.engRadio.Font = new System.Drawing.Font("Tahoma", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.engRadio.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(99)))), ((int)(((byte)(7)))));
            this.engRadio.Location = new System.Drawing.Point(183, 29);
            this.engRadio.Name = "engRadio";
            this.engRadio.Size = new System.Drawing.Size(73, 19);
            this.engRadio.TabIndex = 23;
            this.engRadio.TabStop = true;
            this.engRadio.Text = "&English";
            this.engRadio.UseVisualStyleBackColor = true;
            this.engRadio.Click += new System.EventHandler(this.engRadio_Click);
            // 
            // checkBox3D
            // 
            this.checkBox3D.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.checkBox3D.AutoSize = true;
            this.checkBox3D.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(72)))), ((int)(((byte)(72)))), ((int)(((byte)(72)))));
            this.checkBox3D.Cursor = System.Windows.Forms.Cursors.Hand;
            this.checkBox3D.Font = new System.Drawing.Font("Tahoma", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.checkBox3D.ForeColor = System.Drawing.Color.White;
            this.checkBox3D.Location = new System.Drawing.Point(4, 3);
            this.checkBox3D.Name = "checkBox3D";
            this.checkBox3D.Padding = new System.Windows.Forms.Padding(5, 0, 0, 0);
            this.checkBox3D.Size = new System.Drawing.Size(53, 23);
            this.checkBox3D.TabIndex = 506;
            this.checkBox3D.Text = "3D";
            this.checkBox3D.UseVisualStyleBackColor = false;
            this.checkBox3D.Click += new System.EventHandler(this.checkBox1_Click);
            // 
            // windowModeCheck
            // 
            this.windowModeCheck.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.windowModeCheck.AutoSize = true;
            this.windowModeCheck.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(72)))), ((int)(((byte)(72)))), ((int)(((byte)(72)))));
            this.windowModeCheck.Cursor = System.Windows.Forms.Cursors.Hand;
            this.windowModeCheck.Font = new System.Drawing.Font("Tahoma", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.windowModeCheck.ForeColor = System.Drawing.Color.White;
            this.windowModeCheck.Location = new System.Drawing.Point(4, 24);
            this.windowModeCheck.Name = "windowModeCheck";
            this.windowModeCheck.Padding = new System.Windows.Forms.Padding(5, 0, 0, 0);
            this.windowModeCheck.Size = new System.Drawing.Size(133, 23);
            this.windowModeCheck.TabIndex = 22;
            this.windowModeCheck.Text = "Window Mode";
            this.windowModeCheck.UseVisualStyleBackColor = false;
            this.windowModeCheck.CheckedChanged += new System.EventHandler(this.MusicCheckBox_CheckedChanged);
            // 
            // panel1
            // 
            this.panel1.Controls.Add(this.windowModeCheck);
            this.panel1.Controls.Add(this.checkBox3D);
            this.panel1.Controls.Add(this.engRadio);
            this.panel1.Controls.Add(this.hebRadio);
            this.panel1.Location = new System.Drawing.Point(632, 521);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(257, 49);
            this.panel1.TabIndex = 507;
            // 
            // versionLb
            // 
            this.versionLb.AutoSize = true;
            this.versionLb.Font = new System.Drawing.Font("Tahoma", 12F);
            this.versionLb.ForeColor = System.Drawing.Color.White;
            this.versionLb.Location = new System.Drawing.Point(734, 4);
            this.versionLb.Name = "versionLb";
            this.versionLb.Size = new System.Drawing.Size(0, 19);
            this.versionLb.TabIndex = 507;
            // 
            // MainWindow
            // 
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(72)))), ((int)(((byte)(72)))), ((int)(((byte)(72)))));
            this.ClientSize = new System.Drawing.Size(900, 655);
            this.Controls.Add(this.versionLb);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.title);
            this.Controls.Add(this.proccessLb);
            this.Controls.Add(this.downloadLbl);
            this.Controls.Add(this.checkforupdatesBtn);
            this.Controls.Add(this.optionsBtn);
            this.Controls.Add(this.minimizeBtn);
            this.Controls.Add(this.closeBtn);
            this.Controls.Add(this.strtGameBtn);
            this.Controls.Add(this.progressBar1);
            this.Controls.Add(this.panelImg);
            this.Controls.Add(this.patchNotes);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "MainWindow";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "LauncherWindow";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.MouseDown += new System.Windows.Forms.MouseEventHandler(this.Form1_MouseDown);
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

    }

    public enum eLangs
    {
      HE,
      EN,
    }
  }
}
