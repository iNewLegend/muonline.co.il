// Decompiled with JetBrains decompiler
// Type: Launcher_v2.Program
// Assembly: Launcher_v2, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: 62AD7470-6E7C-4CD6-AD3C-47F3F5D3DB0B
// Assembly location: C:\Program Files (x86)\Mu Israel\Launcher_v2.exe

using System;
using System.Windows.Forms;

namespace Launcher_v2
{
  internal static class Program
  {
    [STAThread]
    private static void Main()
    {
      Application.EnableVisualStyles();
      Application.SetCompatibleTextRenderingDefault(false);
      Application.Run((Form) new MainWindow());
    }
  }
}
