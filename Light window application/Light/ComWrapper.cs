using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO.Ports;

namespace Light
{
    class ComWrapper
    {
        SerialPort Port;
        String Data;
        static String StaryPort = "";

        public delegate void EventDelegate(string data);
        public event EventDelegate DataReceived;

        public ComWrapper()
        {
            Port = new SerialPort();
        }

        public bool PortOpen()
        {

            string[] PortNames;
            
            PortNames = SerialPort.GetPortNames();
            string DodatkowyPort = "";
            if (PortNames.Length == 0)
            {
                return false;
            }
            else
            {
                DodatkowyPort = PortNames[2];
                
            }

            if (StaryPort != "") DodatkowyPort = StaryPort;
            else StaryPort = DodatkowyPort;

            Port = new SerialPort()
            {

                PortName = DodatkowyPort,
                Parity = Parity.None,
                DataBits = 8,
                BaudRate = 9600,
                StopBits = StopBits.One
            };
            
            
            Port.DataReceived += Port_DataReceived;
            
            Port.Open();
            return true;
        }

        public bool IsOpen()
        {
            return Port.IsOpen;
        }

        void Port_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            
                Data += Port.ReadExisting();

                if (null != DataReceived)
                {
                    DataReceived(Data);
                    Data = String.Empty;
                }
            
        }
        
        public bool Send(String data)
        {
            try
            {
                Port.Write(data);
                return true;
            }
            catch (Exception)
            {
                return false;
            }
        }

        public SerialPort MyPort()
        {
            return this.Port;
        }
    }
}
