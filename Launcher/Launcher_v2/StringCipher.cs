// Decompiled with JetBrains decompiler
// Type: Launcher_v2.StringCipher
// Assembly: Launcher_v2, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: 62AD7470-6E7C-4CD6-AD3C-47F3F5D3DB0B
// Assembly location: C:\Program Files (x86)\Mu Israel\Launcher_v2.exe

using System;
using System.IO;
using System.Security.Cryptography;
using System.Text;

namespace Launcher_v2
{
  public static class StringCipher
  {
    private static readonly byte[] initVectorBytes = Encoding.ASCII.GetBytes("fgjsdf4932da935d");
    private const int keysize = 256;

    public static string Encrypt(string plainText, string passPhrase)
    {
      byte[] bytes1 = Encoding.UTF8.GetBytes(plainText);
      using (PasswordDeriveBytes passwordDeriveBytes = new PasswordDeriveBytes(passPhrase, (byte[]) null))
      {
        byte[] bytes2 = passwordDeriveBytes.GetBytes(32);
        using (RijndaelManaged rijndaelManaged = new RijndaelManaged())
        {
          rijndaelManaged.Mode = CipherMode.CBC;
          using (ICryptoTransform encryptor = rijndaelManaged.CreateEncryptor(bytes2, StringCipher.initVectorBytes))
          {
            using (MemoryStream memoryStream = new MemoryStream())
            {
              using (CryptoStream cryptoStream = new CryptoStream((Stream) memoryStream, encryptor, CryptoStreamMode.Write))
              {
                cryptoStream.Write(bytes1, 0, bytes1.Length);
                cryptoStream.FlushFinalBlock();
                return Convert.ToBase64String(memoryStream.ToArray());
              }
            }
          }
        }
      }
    }

    public static string Decrypt(string cipherText, string passPhrase)
    {
      try
      {
        byte[] buffer = Convert.FromBase64String(cipherText);
        using (PasswordDeriveBytes passwordDeriveBytes = new PasswordDeriveBytes(passPhrase, (byte[]) null))
        {
          byte[] bytes = passwordDeriveBytes.GetBytes(32);
          using (RijndaelManaged rijndaelManaged = new RijndaelManaged())
          {
            rijndaelManaged.Mode = CipherMode.CBC;
            using (ICryptoTransform decryptor = rijndaelManaged.CreateDecryptor(bytes, StringCipher.initVectorBytes))
            {
              using (MemoryStream memoryStream = new MemoryStream(buffer))
              {
                using (CryptoStream cryptoStream = new CryptoStream((Stream) memoryStream, decryptor, CryptoStreamMode.Read))
                {
                  byte[] numArray = new byte[buffer.Length];
                  int count = cryptoStream.Read(numArray, 0, numArray.Length);
                  return Encoding.UTF8.GetString(numArray, 0, count);
                }
              }
            }
          }
        }
      }
      catch
      {
        return "1.0";
      }
    }
  }
}
