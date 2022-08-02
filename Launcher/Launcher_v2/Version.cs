// Decompiled with JetBrains decompiler
// Type: Launcher_v2.Version
// Assembly: Launcher_v2, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: 62AD7470-6E7C-4CD6-AD3C-47F3F5D3DB0B
// Assembly location: C:\Program Files (x86)\Mu Israel\Launcher_v2.exe

namespace Launcher_v2
{
  internal class Version
  {
    public const string SEPERATOR = ".";
    public const int MAX = 50;

    public static bool isUpdate(string server, string client)
    {
      int[] numArray1 = Version.get(server);
      int[] numArray2 = Version.get(client);
      if (numArray1[0] < numArray2[0])
          return false;
      if (numArray1[1] < numArray2[1])
          return false;
      return true;
    }

    public static string getNext(string version)
    {
      int[] numArray = Version.get(version);
      if (numArray[1] + 1 == MAX)
      {
        ++numArray[0];
        numArray[1] = 0;
      }
      else
        ++numArray[1];
      return Version.set(numArray[0], numArray[1]);
    }

    public static int[] get(string version)
    {
      int length = version.IndexOf(".");
      int[] numArray = new int[2]
      {
        -1,
        -1
      };
      if (length != -1)
      {
        numArray[0] = int.Parse(version.Substring(0, length));
        numArray[1] = int.Parse(version.Substring(length + 1));
      }
      return numArray;
    }

    public static string set(int first, int last)
    {
      return first.ToString() + "." + last.ToString();
    }
  }
}
