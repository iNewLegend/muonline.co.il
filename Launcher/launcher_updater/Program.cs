// Decompiled with JetBrains decompiler
// Type: launcher_updater.exe.Program
// Assembly: launcher_updater.exe, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: FC9D1C0C-25CF-47A2-8F11-C02283AFBE35
// Assembly location: C:\Users\Roye\Desktop\launcher_updater.exe

using Ionic.Zip;
using System;
using System.Collections;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Threading;

namespace launcher_updater.exe
{
  internal class Program
  {
    private static bool isLauncherAlive()
    {
      foreach (Process process in Process.GetProcesses())
      {
          if (process.ProcessName == "Launcher v2")
          return true;
      }
      return false;
    }

    private static void Main(string[] args)
    {
      string baseDirectory = AppDomain.CurrentDomain.BaseDirectory;
      while (true)
      {
        do
        {
          Thread.Sleep(1);
        }
        while (Program.isLauncherAlive());
        using (ZipFile zipFile = ZipFile.Read("launcher.zip"))
        {
          using (IEnumerator<ZipEntry> enumerator = zipFile.GetEnumerator())
          {
            while (((IEnumerator) enumerator).MoveNext())
            {
              ZipEntry current = enumerator.Current;
              try
              {
                current.Extract(baseDirectory, true);
              }
              catch (Exception ex)
              {
                return;
              }
            }
          }
        }
        Program.deleteFile("launcher.zip");
        Thread.Sleep(1500);
        try
        {
          Process.Start("Launcher.exe", "");
        }
        catch (Exception ex)
        {
            return;
        }
        Environment.Exit(0);
      }
    }

    private static bool deleteFile(string f)
    {
      try
      {
        File.Delete(f);
        return true;
      }
      catch (IOException ex)
      {
        return false;
      }
    }
  }
}
