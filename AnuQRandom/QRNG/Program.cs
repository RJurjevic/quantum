using AnuQRandom;
using AnuQRandom.Model;
using System.Diagnostics.Meyer.Contracts;

namespace QRNG
{
    public static class Program
    {
        private static async Task GetNumbers_OldApi()
        {
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
                    QRNGConsole.Instance.OutputToConsole("Fetching data from ANU QRNG (Australian National University Quantum Random Number Generator)...");
                    RequestedData data = await client.RequestAsync();
                    Contract.Assert(data != null, "data != null");
                    QRNGConsole.Instance.OutputToConsole("Data fetched.");
                    if (data.Success)
                    {
                        QRNGConsole.Instance.OutputToConsole("Processing data...");
                        int[] qrngData = data.DataNumbers.ToArray();
                        Contract.Assert(qrngData != null, "qrngData != null");
                        string output = $"{j:0000} {data.Length}: {string.Join(" ", qrngData.Select(num => $"{num:000}"))}";
                        QRNGConsole.Instance.OutputToConsole(output);
                        byte[] byteArray = new byte[qrngData.Length];
                        for (int i = 0; i < qrngData.Length; i++)
                        {
                            byteArray[i] = (byte)qrngData[i];
                        }
                        QRNGConsole.Instance.OutputToConsole("Data processed.");
                        bool success = false;
                        int writeCount = 10;
                        while (writeCount > 0 && !success)
                        {
                            try
                            {
                                using (FileStream fs = new FileStream("data.bin", FileMode.Create, FileAccess.Write, FileShare.None))
                                {
                                    QRNGConsole.Instance.OutputToConsole("Writing data to file...");
                                    fs.Write(byteArray, 0, byteArray.Length);
                                    success = true;
                                }
                            }
                            catch (IOException ex)
                            {
                                writeCount--;
                                QRNGConsole.Instance.OutputToConsole($"Failed to write to file, retrying... ({10 - writeCount}/10)");
                                System.Threading.Thread.Sleep(1000);
                            }
                        }

                        if (!success)
                        {
                            QRNGConsole.Instance.OutputToConsole("Failed to write data to file after multiple retries.");
                        }
                        j++;
                    }
                }
                catch (Exception ex)
                {
                    Console.WriteLine($"Error: {ex.Message}");
                }
                QRNGConsole.Instance.OutputToConsole("Waiting...");
                System.Threading.Thread.Sleep(140 * 1000);
            }
        }

        public static void Main() => GetNumbers_OldApi().GetAwaiter().GetResult();
    }
}


