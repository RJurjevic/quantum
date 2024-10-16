using AnuQRandom;
using AnuQRandom.Entities;
using AnuQRandom.Model;
using System.Diagnostics.Meyer.Contracts;
using System.Net;
using System.Net.Sockets;

namespace QRNG
{
    public static class Program
    {
        private static async Task GetNumbers_OldApi()
        {
            IPEndPoint endPoint = new IPEndPoint(IPAddress.Loopback, 1200); 
            Contract.Assert(endPoint != null, "endPoint != null");
            Socket socket = new Socket(AddressFamily.InterNetwork, SocketType.Dgram, ProtocolType.Udp);
            Contract.Assert(socket != null, "socket != null");
            long j = 0; 
            while (true) 
            {
                try
                {
                    OldAnuClient client = new OldAnuClient()
                    {
                        arrayLength = 0x400 // Get 1024 numbers
                    };
                    Contract.Assert(client != null, "client != null");
                    QRNGConsole.Instance.OutputToConsole("Fetchng data from ANU QRNG (Australian National University Quantum Random Number Generator)...");
                    RequestedData data = await client.RequestAsync();
                    Contract.Assert(data != null, "data != null");
                    QRNGConsole.Instance.OutputToConsole("Data fetched.");
                    if (data.Success)
                    {
                        QRNGConsole.Instance.OutputToConsole("Processing data...");
                        int[] qrngData = new int[data.Data.Count]; 
                        Contract.Assert(qrngData != null, "qrngData != null");
                        int i = 0; 
                        foreach (int number in data.DataNumbers) 
                        {
                            qrngData[i] = number;
                            i++;
                        }
                        QRNGConsole.Instance.OutputToConsole(@"---");
                        string output = String.Format(@"{0} {1}: ", String.Format("{0:0000}", j), data.Length);
                        for (i = 0; i < data.Length; i++)
                        {
                            output += String.Format(@"{0} ", String.Format("{0:000}", qrngData[i]));
                        }
                        QRNGConsole.Instance.OutputToConsole(output);
                        byte[] byteArray = new byte[qrngData.Length * sizeof(int)];
                        Contract.Assert(byteArray != null, "byteArray != null");
                        Buffer.BlockCopy(qrngData, 0, byteArray, 0, byteArray.Length);
                        QRNGConsole.Instance.OutputToConsole("Data processed.");
                        QRNGConsole.Instance.OutputToConsole("Sending data to socket...");
                        try
                        {
                            socket.SendTo(byteArray, endPoint);
                            QRNGConsole.Instance.OutputToConsole("Data sent to socket."); 
                        }
                        catch (Exception e)
                        {
                            Console.WriteLine("Exception: " + e.Message);
                        }
                        j++;
                    }
                }
                catch (Exception ex)
                {
                    Console.WriteLine(String.Format(@"{0}", ex.Message));
                }
                QRNGConsole.Instance.OutputToConsole("Waiting...");
                System.Threading.Thread.Sleep(140*1000);
            }
        }

        public static void Main() => GetNumbers_OldApi().GetAwaiter().GetResult();
    }
}


