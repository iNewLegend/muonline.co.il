// Decompiled with JetBrains decompiler
// Type: Launcher_v2.Properties.Resources
// Assembly: Launcher_v2, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: 62AD7470-6E7C-4CD6-AD3C-47F3F5D3DB0B
// Assembly location: C:\Program Files (x86)\Mu Israel\Launcher_v2.exe

using System.CodeDom.Compiler;
using System.ComponentModel;
using System.Diagnostics;
using System.Drawing;
using System.Globalization;
using System.Resources;
using System.Runtime.CompilerServices;

namespace Launcher_v2.Properties
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
          Resources.resourceMan = new ResourceManager("Launcher_v2.Properties.Resources", typeof (Resources).Assembly);
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

    internal static Bitmap background1
    {
      get
      {
        return (Bitmap) Resources.ResourceManager.GetObject("background1", Resources.resourceCulture);
      }
    }

    internal static Bitmap close1
    {
      get
      {
        return (Bitmap) Resources.ResourceManager.GetObject("close1", Resources.resourceCulture);
      }
    }

    internal static Bitmap close2
    {
      get
      {
        return (Bitmap) Resources.ResourceManager.GetObject("close2", Resources.resourceCulture);
      }
    }

    internal static Bitmap minimize1
    {
      get
      {
        return (Bitmap) Resources.ResourceManager.GetObject("minimize1", Resources.resourceCulture);
      }
    }

    internal static Bitmap minimize2
    {
      get
      {
        return (Bitmap) Resources.ResourceManager.GetObject("minimize2", Resources.resourceCulture);
      }
    }


    internal Resources()
    {
    }
  }
}
