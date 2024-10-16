using System.Diagnostics.Meyer.Contracts;
using System.Reflection;

namespace QRNG
{
    public class QRNGConsole
    {
        private string GetTimeStamp()
        {
            return DateTime.Now.ToString("dd-MM-yyyy HH:mm:ss.fff");
        }

        private string Badge()
        {
            System.Reflection.Assembly assembly = System.Reflection.Assembly.GetExecutingAssembly();
            string name = AssemblyName.GetAssemblyName(assembly.Location).Name;
            System.Diagnostics.FileVersionInfo info = System.Diagnostics.FileVersionInfo.GetVersionInfo(assembly.Location);
            string version = info.FileVersion;
            string badge = String.Format(@"{0} v{1}", name, version);
            Contract.Ensure(badge != null, "badge != null");
            return badge;
        }

        private static readonly Lazy<QRNGConsole> instance = new Lazy<QRNGConsole>(() => new QRNGConsole());

        public QRNGConsole()
        {
        }

        public static QRNGConsole Instance
        {
            get
            {
                return instance.Value;
            }
        }

        public void OutputToConsole(string text)
        {
            Contract.Require(text != null, "text != null");
            System.Console.WriteLine(String.Format(@"{0} {1}", GetTimeStamp(), text));
        }

        public void OutputBadgeToConsole()
        {
            this.OutputToConsole(Badge());
        }
    }
}
