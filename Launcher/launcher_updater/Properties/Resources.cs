// Decompiled with JetBrains decompiler
// Type: launcher_updater.exe.Properties.Resources
// Assembly: launcher_updater.exe, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: FC9D1C0C-25CF-47A2-8F11-C02283AFBE35
// Assembly location: C:\Users\Roye\Desktop\launcher_updater.exe

using System.CodeDom.Compiler;
using System.ComponentModel;
using System.Diagnostics;
using System.Globalization;
using System.Resources;
using System.Runtime.CompilerServices;

namespace launcher_updater.exe.Properties
{
  [DebuggerNonUserCode]
  [GeneratedCode("System.Resources.Tools.StronglyTypedResourceBuilder", "4.0.0.0")]
  [CompilerGenerated]
  internal class Resources
  {
    private static ResourceManager resourceMan;
    private static CultureInfo resourceCulture;

    [EditorBrowsable(EditorBrowsableState.Advanced)]
    internal static ResourceManager ResourceManager
    {
      get
      {
        if (object.ReferenceEquals((object) Resources.resourceMan, (object) null))
          Resources.resourceMan = new ResourceManager("launcher_updater.exe.Properties.Resources", typeof (Resources).Assembly);
        return Resources.resourceMan;
      }
    }

    [EditorBrowsable(EditorBrowsableState.Advanced)]
    internal static CultureInfo Culture
    {
      get
      {
        return Resources.resourceCulture;
      }
      set
      {
        Resources.resourceCulture = value;
      }
    }

    internal static string לא
    {
      get
      {
        return Resources.ResourceManager.GetString("לא", Resources.resourceCulture);
      }
    }

    internal Resources()
    {
    }
  }
}
