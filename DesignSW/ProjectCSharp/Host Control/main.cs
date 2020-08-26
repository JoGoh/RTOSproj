using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using System.IO.Ports;
using System.Diagnostics;
using System.Runtime.Serialization.Formatters.Binary;
using System.Runtime.InteropServices;


[Serializable] // BinaryFormatter needs this attribute
public struct MapPoint
{
    public Int32 x;
    public Int32 y;
};


namespace uCamReceiver
{
    public partial class Form1 : Form
    {
        // Variables
        private const byte RESP_DEV_CUR_XY      = 0x01;
        private const byte RESP_DEV_ACK         = 0x02;
        private const byte RESP_DEV_STS         = 0x03;
        private const byte RESP_DEV_MAP         = 0x04;
        private const byte RESP_DEV_SPEED       = 0x05;
        private const byte RESP_DEV_SETTING     = 0x06;

        private const byte CMD_HOST_START       = 0x01;
        private const byte CMD_HOST_STOP        = 0x02;
        private const byte CMD_HOST_MAP_SET     = 0x03;
        private const byte CMD_HOST_SYS_RESET   = 0x04;
        private const byte CMD_HOST_SET_REF     = 0x05;
        private const byte CMD_HOST_SET_CAL_MODE = 0x06;
        private const byte CMD_HOST_SAVE        = 0x07;
        private const byte CMD_HOST_MAP_REQ     = 0x08;
        private const byte CMD_HOST_CHANGE_SPEED = 0x09;
        private const byte CMD_HOST_CHANGE_PID  = 0x10;
        private const byte CMD_HOST_RESTORE     = 0x2E;
        private const byte CMD_HOST_REPORT_ON   = 0x2F;

        private const byte CMD_HOST_MOVE_FWD    = 0x30;
        private const byte CMD_HOST_MOVE_BWD    = 0x31;
        private const byte CMD_HOST_ROTATE_LEFT = 0x32;
        private const byte CMD_HOST_MOVE_FR     = 0x33;
        private const byte CMD_HOST_MOVE_RIGHT  = 0x34;
        private const byte CMD_HOST_MOVE_BR     = 0x35;
        private const byte CMD_HOST_ROTATE_RIGHT = 0x36;
        private const byte CMD_HOST_MOVE_BL     = 0x37;
        private const byte CMD_HOST_MOVE_LEFT   = 0x38;
        private const byte CMD_HOST_MOVE_FL     = 0x39;

        private const byte STX = 0x30;
        private const byte ETX = 0x31;
        byte[] buf = new byte[16];
        private string[] STR_MOTOR_HEADING_STATE = {
                                            "HEADING_DEFAULT",
                                            "HEADING_FRONT",
                                            "HEADING_BACK",
                                            "HEADING_LEFT",
                                            "HEADING_RIGHT" };


        private string[] STR_MOTOR_MOVE_STATE = {
                                                    "MOVE_NONE",
                                                    "MOVE_FWD",
                                                    "MOVE_BWD",
                                                    "MOVE_LEFT",
                                                    "MOVE_RIGHT",
                                                    "MOVE_FRONT_LEFT",
                                                    "MOVE_FRONT_RIGHT",
                                                    "MOVE_BACK_LEFT",
                                                    "MOVE_BACK_RIGHT",
                                                    "MOVE_ROTATE_LEFT",
                                                    "MOVE_ROTATE_RIGHT",
                                                    "MOVE_ADJUST_WAIT",
                                                    "MOVE_ADJUST_DONE",
                                                    "MOVE_STOP" };

        private int[] baudrate          = { 9600, 19200, 38400, 115200, 230400, 460800, 921600 };
        private SerialPort Serial       = new SerialPort();
        private Thread ControlThread;
        private  AutoResetEvent evtSerialOnRx    = new AutoResetEvent(false);
        private AutoResetEvent evtDevAck        = new AutoResetEvent(true);
        private AutoResetEvent evtMapReady      = new AutoResetEvent(true);
        private MapPoint[] map = new MapPoint[32];
        private int acc = 0;

        private string MoveState;
        private Int32 cX;
        private Int32 cY;
        private int point;
        private Int32 heading;
        private double dX;
        private double dY;
        private double dHeading;
        private int g_timebase = 0;
        int stop;
        int runtime;

        private Int32 nfeedbbackX;
        private Int32 nfeedbbackY;
        private int nfeedbbackIndex;

        double SpeedM1;
        double SpeedM2;
        double SpeedM3;
        double SpeedM4;
        double DRoll;
        double DPitch;
        double DYaw;
        Int32 KP;
        Int32 KI;
        Int32 KD;
        Int32 RPM;
        Int32 Interval = 100;

        public Form1()
        {
            InitializeComponent();
        }

        //http://genericgamedev.com/general/converting-between-structs-and-byte-arrays/

        public static byte[] Serialize<MapPoint>(MapPoint s)
        where MapPoint : struct
        {
            var size = Marshal.SizeOf(typeof(MapPoint));
            var array = new byte[size];
            var ptr = Marshal.AllocHGlobal(size);
            Marshal.StructureToPtr(s, ptr, true);
            Marshal.Copy(ptr, array, 0, size);
            Marshal.FreeHGlobal(ptr);
            return array;
        }

        public static MapPoint Deserialize<MapPoint>(byte[] array)
        where MapPoint : struct
        {
            var s = new MemoryStream(array);
            var sz = Marshal.SizeOf(typeof(MapPoint));
            var buf = new byte[sz];

            s.Read(buf, 0, sz);
            var handle = GCHandle.Alloc(buf, GCHandleType.Pinned);
            var t = (MapPoint)Marshal.PtrToStructure(handle.AddrOfPinnedObject(), typeof(MapPoint));
            handle.Free();
            return t;
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            CBoxM1.Checked = true;
            CBoxM2.Checked = true;
            CBoxM3.Checked = true;
            CBoxM4.Checked = true;

            for (int i=0; i<32; i++ )
            {
                map[i].x = -1;
                map[i].y = -1;
            }

            UpdateCOMPort();
            foreach(TabPage tab in tabCtrlPanel.TabPages)
            {
                tab.Enabled = false;
            }

            (tabCtrlPanel.TabPages[0] as TabPage).Enabled = true;
            // timer1.Start();

        }

        private void UpdateCOMPort()
        {
            string[] Ports = System.IO.Ports.SerialPort.GetPortNames();
            cboxComPort.Items.Clear();
            cboxBaud.Items.Clear();

            foreach( var item in Ports )
            {
                cboxComPort.Items.Add( item );
            }

            foreach( var baud in baudrate )
            {
                cboxBaud.Items.Add( baud.ToString() );
            }
        }


        private void btConnect_Click(object sender, EventArgs e)
        {
            if ("Disconnect" == btnConnect.Text.ToString())
            {
                ControlThread.Abort();
                Serial.Close();

                btnConnect.Text = "Connect";
                cboxComPort.Enabled = true;
                cboxBaud.Enabled = true;

                stsStripDisplay.Items[0].Text = "Status: COM Port disconnected";
                return;
            }
#if false
            if (true == File.Exists("test.csv"))
            {
                string name = DateTime.Now.ToString();

                name = name.Replace('/','_');
                name = name.Replace(' ', '_');
                name = name.Replace(':', '_');

                string dest = name + ".csv";
                File.Move("test.csv", dest);
            }
#endif
            try
            {
                Serial.PortName = cboxComPort.SelectedItem.ToString();
            }
            catch
            {
                MessageBox.Show("Error! No COM Port selected");
                return;
            }

            try
            {
                Serial.BaudRate = int.Parse(cboxBaud.SelectedItem.ToString());
            }
            catch
            {
                MessageBox.Show("Error! No Baudrate selected");
                return;
            }

            timer1.Stop();

            Serial.Parity                   = Parity.None;
            Serial.DataBits                 = 8;
            Serial.ReceivedBytesThreshold   = 7;
            Serial.StopBits                 = StopBits.One;
            Serial.Handshake                = Handshake.None;
            Serial.WriteTimeout             = 3000;
  
            // Check if com port is opened by other application
            if (false == Serial.IsOpen)
            {
                // Com port available
                Serial.Open();
                Serial.DataReceived += new SerialDataReceivedEventHandler( SerialOnReceivedHandler );

                btnConnect.Text = "Disconnect";
                cboxComPort.Enabled = false;
                cboxBaud.Enabled = false;

                // double comform it is opened
                if (true == Serial.IsOpen)
                {
                    ControlThread = new Thread(new ThreadStart(ControlTask));
                    ControlThread.IsBackground = false;
                    ControlThread.Start();
                }
                else
                {
                    MessageBox.Show(" Error! Unable to open Serial port ");
                }

                stsStripDisplay.Items[0].Text = "Status: COM Port connected";

                foreach (TabPage tab in tabCtrlPanel.TabPages)
                {
                    tab.Enabled = true;
                }
            }
            else
            {
                MessageBox.Show(" Error! Selected Serial port in use");
            }
        }

        public delegate void updateAppPlot();
        public delegate void updateAppRouteList();
        public delegate void updateAppMotorSpeed();
        public delegate void updateAppSetting();

        private void updateSetting()
        {
            trackBarKP.Value = KP;
            trackBarKI.Value = KI;
            trackBarKD.Value = KD;
            trackBarRPM.Value = RPM;
            trackBarInterval.Value = Interval;

            labelKP.Text = "KP: " + Convert.ToDouble(KP/100.0);
            labelKI.Text = "KI: " + Convert.ToDouble(KI / 100.0);
            labelKD.Text = "KD: " + Convert.ToDouble(KD / 100.0);
            labelRPM.Text = "RPM: " + RPM.ToString();
            labelInterval.Text = "Interval: " + Interval.ToString() + "ms";
            labelOpr.Text = "Last Operation: Sync completed";
        }


        private void updateMotorSpeed()
        {
            labelSpeed.Text = "RPM: " + SpeedM1.ToString("N1")
                                + "  " + SpeedM2.ToString("N1")
                                + "  " + SpeedM3.ToString("N1")
                                + "  " + SpeedM4.ToString("N1")
                                + " Roll: " + DRoll.ToString()
                                + " Pitch: " + DPitch.ToString()
                                + " Yaw: " + DYaw.ToString();


            PlotPID.Series[0].Points.AddXY(g_timebase, SpeedM1);
            PlotPID.Series[1].Points.AddXY(g_timebase, SpeedM2);
            PlotPID.Series[2].Points.AddXY(g_timebase, SpeedM3);
            PlotPID.Series[3].Points.AddXY(g_timebase, SpeedM4);
            g_timebase += Interval;

            if (true == cBoxLogPID.Checked)
            {
                using (BinaryWriter log = new BinaryWriter(File.Open("PID.csv", FileMode.Append)))
                {
                    string data = "\r\n" + DateTime.Now.ToString("MM/dd/yy H:mm:ss:ffff") + "," + SpeedM1.ToString() + "," + SpeedM2.ToString() + "," + SpeedM3.ToString() + "," + SpeedM4.ToString();
                    log.Write(data.ToCharArray(), 0, data.Length);
                    log.Close();
                }
            }
        }

        private void updateRouteList()
        {
            labelRoute.Text += "\r\nP" + nfeedbbackIndex.ToString() 
                                + ":  " + "( " + nfeedbbackX.ToString() 
                                + " , " + nfeedbbackY.ToString() 
                                + " )";
        }

        private void updatePlot()
        {

            labelCurXY.Text = "Current location: ( "
                                + dX.ToString()
                                + ","
                                + dY.ToString()
                                + " ) "
                                + "Current Point:" + point.ToString()
                                + " Heading: "
                                + dHeading.ToString();


            labelInfo.Text = MoveState + " Stop: " + stop.ToString() + " runtime: " + runtime.ToString();
        }

        private void ControlTask()
        {
            bool evt;
            int acc = 0;
            bool bstart = false;

            SyncFromDevice();

            while (true)
            {
                evt = evtSerialOnRx.WaitOne( 200 ); // Wait Serialport On received event to be set
                if (false == evt)
                {
                    continue;
                }

                while (true)
                {
                    if (0 == Serial.BytesToRead)
                    {
                        break;
                    }

                    byte data = (byte)Serial.ReadByte();

                    if ( false == bstart )
                    {
                        if ( STX == data )
                        {
                            bstart = true;
                            acc = 0;
                        }

                        continue;
                    }

                    if (16 != acc)
                    {
                        buf[acc] = data;
                        acc++;

                        continue;
                    }
      
                    bstart = false;

                    if (ETX == data)
                    {
                        switch(buf[0] )
                        {
                            case RESP_DEV_CUR_XY:
                            break;

                            case RESP_DEV_ACK:
                                evtDevAck.Set();
                            break;

                            case RESP_DEV_SETTING:
                                RPM = Convert.ToInt32((buf[2] << 8) | buf[1]);
                                Interval = Convert.ToInt32((buf[4] << 8) | buf[3]);
                                KP = Convert.ToInt32((buf[6] << 8) | buf[5]);
                                KI = Convert.ToInt32((buf[8] << 8) | buf[7]);
                                KD = Convert.ToInt32((buf[10] << 8) | buf[9]);

                                Invoke(new updateAppSetting(updateSetting));
                                break;

                            case RESP_DEV_STS:
                                MoveState = STR_MOTOR_MOVE_STATE[buf[1]];
                                cX = (buf[5] << 24) | (buf[4] << 16) | (buf[3] << 8) | buf[2];
                                cY = (buf[9] << 24) | (buf[8] << 16) | (buf[7] << 8) | buf[6];
                                point = buf[10];
                                heading = (buf[14] << 24) | (buf[13] << 16) | (buf[12] << 8) | buf[11];
                                dX = (double)cX / 100.0;
                                dY = (double)cY / 100.0;
                                dHeading = (double)heading / 100.0;
               
                                stop = (int)(buf[15] & 0x01);
                                runtime = (int)(buf[15] >>1);

                                Invoke(new updateAppPlot(updatePlot));
                            break;

                            case RESP_DEV_MAP:
                                evtMapReady.Set();
                                nfeedbbackX = (buf[5] << 24) | (buf[4] << 16) | (buf[3] << 8) | buf[2];
                                nfeedbbackY = (buf[9] << 24) | (buf[8] << 16) | (buf[7] << 8) | buf[6];
                                nfeedbbackIndex = buf[1] + 1;

                                Invoke( new updateAppRouteList(updateRouteList) );
                            break;

                            case RESP_DEV_SPEED:
                                Int32 speed1 = (buf[2] << 8) | buf[1];
                                Int32 speed2 = (buf[4] << 8) | buf[3];
                                Int32 speed3 = (buf[6] << 8) | buf[5];
                                Int32 speed4 = (buf[8] << 8) | buf[7];
                                Int32 roll = (buf[10] << 8) | buf[9];
                                Int32 pitch = (buf[12] << 8) | buf[11];
                                Int32 yaw = (buf[14] << 8) | buf[13];
                              
                                SpeedM1 = Convert.ToDouble(speed1);
                                SpeedM2 = Convert.ToDouble(speed2);
                                SpeedM3 = Convert.ToDouble(speed3);
                                SpeedM4 = Convert.ToDouble(speed4);
                                DRoll = Convert.ToDouble( (short)roll / 100.0);
                                DPitch = Convert.ToDouble((short)pitch / 100.0);
                                DYaw = Convert.ToDouble((short)yaw / 100.0);
#if false
                                SpeedM1 = (double)speed1 / 78.0;
                                SpeedM2 = (double)speed2 / 78.0;
                                SpeedM3 = (double)speed3 / 78.0;
                                SpeedM4 = (double)speed4 / 78.0;
#endif
                                Invoke(new updateAppMotorSpeed(updateMotorSpeed));

  
                                break;

                            default:
                            break;
                        }

                    }
                }
            }
        }


        void SerialOnReceivedHandler(object sender, SerialDataReceivedEventArgs e)
        {
            evtSerialOnRx.Set();
        }


        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            Process.GetCurrentProcess().Kill();
        }

        private void btnSet_Click(object sender, EventArgs e)
        {
            double dx;
            double dy;
            try
            {
                dx = Convert.ToDouble(textPointX.Text);
                dy = Convert.ToDouble(textPointY.Text);

                map[acc].x = (Int32)(dx*100);
                map[acc].y = (Int32)(dy*100);
            }
            catch 
            {
                MessageBox.Show("Error! Invalid coordinate");
                return;
            }

            if ( 0 != acc )
            {
                if ((map[acc].x == map[acc - 1].x) && (map[acc].y == map[acc - 1].y))
                {
                    MessageBox.Show("Warning! coordinate overlap");
                    return;
                }
            }

            PlotDisp.Series[0].Points.AddXY(dx, dy);

            int index = acc + 1;
            labelRoute.Text += "P" + index.ToString() + ":  " + "( " + dx.ToString() + " , " + dy.ToString() + " )" + "\r\n";
            acc++;
        }

        private void btnStart_Click(object sender, EventArgs e)
        {
            byte[] cmd = new byte[12];

            cmd[0] = STX;
            cmd[1] = CMD_HOST_STOP;
            cmd[2] = 0;
            cmd[3] = 0;
            cmd[4] = 0;
            cmd[5] = 0;
            cmd[6] = 0;
            cmd[7] = 0;
            cmd[8] = 0;
            cmd[9] = 0;
            cmd[10] = 0;
            cmd[11] = ETX;

            if (true == Serial.IsOpen)
            {
                Serial.Write(cmd, 0, 12);
            }
            else
            {
                MessageBox.Show("Error. Serial port not connected.");
                return;
            }

            bool evt = evtDevAck.WaitOne( 500 ); // Wait Serialport On received event to be set
            if (false == evt)
            {
                MessageBox.Show( "Device no response" );
            }


            btnMoveFront.BackColor = Color.LightGray;
            btnMoveBack.BackColor = Color.LightGray;
            btnMoveLeft.BackColor = Color.LightGray;
            btnMoveRight.BackColor = Color.LightGray;
            btnMoveFR.BackColor = Color.LightGray;
            btnMoveFL.BackColor = Color.LightGray;
            btnMoveBR.BackColor = Color.LightGray;
            btnMoveBL.BackColor = Color.LightGray;
            btnRotateLeft.BackColor = Color.LightGray;
            btnRotateRight.BackColor = Color.LightGray;
            btnStart.BackColor = Color.LightGreen;
        }

        private void btnMap_Click(object sender, EventArgs e)
        {
            byte[] cmd = new byte[12];
            byte[] src = new byte[12];
            int size = Marshal.SizeOf(typeof(MapPoint));

            labelRoute.Text = "";
            for (int i = 0; i < acc; i++ )
            {
                Array.Copy( Serialize(map[i]), 0, cmd, 3, 8 );

                cmd[0] = STX;
                cmd[1] = 0x03;
                cmd[2] = (byte)i;
                cmd[11] = ETX;

                if (true == Serial.IsOpen)
                {
                    Serial.Write(cmd, 0, 12 );
                }
                else
                {
                    MessageBox.Show("Error. Serial port not connected.");
                    return;
                }

                int cnt = i + 1;

                bool evt = evtDevAck.WaitOne(500); // Wait Serialport On received event to be set
                if (false == evt)
                {
                    labelRoute.Text += "\r\n Upload P" + cnt.ToString() + " Failed!";
                    continue;
                }

                
                labelRoute.Text += "\r\n Upload P" + cnt.ToString() + " completed!";
            }

            labelRoute.Text += "\r\nRetrieve:";

            cmd[0] = STX;
            cmd[1] = CMD_HOST_MAP_REQ;
            cmd[2] = 0;
            cmd[11] = ETX;

            if (true == Serial.IsOpen)
            {
                Serial.Write(cmd, 0, 12);
            }
            else
            {
                MessageBox.Show("Error. Serial port not connected.");
                return;
            } 
        }
      

        private void textPointY_TextChanged(object sender, EventArgs e)
        {

        }

        private void btnClearMap_Click(object sender, EventArgs e)
        {
            labelRoute.Text = null;
            PlotDisp.Series[0].Points.Clear();
            PlotDisp.Series[1].Points.Clear();
            for (int i = 0; i < 32; i++)
            {
                map[i].x = -1;
                map[i].y = -1;
            }
            acc = 0;
        }

        private void label5_Click(object sender, EventArgs e)
        {

        }

        private void btnRefSet_Click(object sender, EventArgs e)
        {
            byte[] cmd = new byte[12];
            Int16[] refPointX = new Int16[3];
            Int16[] refPointY = new Int16[3];

            try
            {
                refPointX[0] = Convert.ToInt16(txtRefX1.Text);
                refPointY[0] = Convert.ToInt16(txtRefY1.Text);
                refPointX[1] = Convert.ToInt16(txtRefX2.Text);
                refPointY[1] = Convert.ToInt16(txtRefY2.Text);
                refPointX[2] = Convert.ToInt16(txtRefX3.Text);
                refPointY[2] = Convert.ToInt16(txtRefY3.Text);
            }
            catch
            {
                MessageBox.Show( "Error. Reference point cannot be empty" );
                return;
            }

     
            labelRoute.Text = "";
            for (int i = 0; i < 3; i++)
            {
                cmd[0] = STX;
                cmd[1] = CMD_HOST_SET_REF;
                cmd[2] = (byte)i;
                cmd[3] = (byte)(refPointX[i] & 0xff);
                cmd[4] = (byte)((refPointX[i] >> 8) & 0xff);
                cmd[5] = (byte)(refPointY[i] & 0xff);
                cmd[6] = (byte)((refPointY[i] >> 8) & 0xff);
                cmd[11] = ETX;

                if (true == Serial.IsOpen)
                {
                    Serial.Write(cmd, 0, 12);
                }
                else
                {
                    MessageBox.Show( "Error. Serial port not connected." );
                    return;
                }

                int cnt = i + 1;

                bool evt = evtDevAck.WaitOne(500); // Wait Serialport On received event to be set
                if (false == evt)
                {
                    labelRoute.Text += "\r\n Upload P" + cnt.ToString() + " Failed!";
                    continue;
                }


                labelRoute.Text += "\r\n Upload P" + cnt.ToString() + " completed!";
            }

        }

        private void btnClearPlot_Click(object sender, EventArgs e)
        {
            //PlotDisp.Series[0].Points.Clear();
            PlotDisp.Series[1].Points.Clear();
        }

        private void btnCal_Click(object sender, EventArgs e)
        {
            byte[] cmd = new byte[12];

            if ( "Calibrate" == btnCal.Text.ToString() )
            {
                btnCal.Text = "Disable";
                cmd[2] = 0x01;
            }
            else
            {
                btnCal.Text = "Calibrate";
                cmd[2] = 0x00;
            }


            cmd[0] = STX;
            cmd[1] = CMD_HOST_SET_CAL_MODE;
            cmd[11] = ETX;

            if (true == Serial.IsOpen)
            {
                Serial.Write(cmd, 0, 12);
            }
            else
            {
                MessageBox.Show("Error. Serial port not connected.");
                return;
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            byte[] cmd = new byte[12];

            cmd[0] = STX;
            cmd[1] = CMD_HOST_SAVE;
            cmd[11] = ETX;

            if (true == Serial.IsOpen)
            {
                Serial.Write(cmd, 0, 12);
            }
            else
            {
                MessageBox.Show("Error. Serial port not connected.");
                return;
            }
        }

        private void PlotDisp_Click(object sender, EventArgs e)
        {

        }

        private void btnCOMRefresh_Click(object sender, EventArgs e)
        {
            UpdateCOMPort();
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            UpdateCOMPort();
        }

        private void RemoteControlCmd( byte Cmd )
        {
            byte[] cmd = new byte[12];

            cmd[0] = STX;
            cmd[1] = Cmd;
            cmd[2] = 0;
            cmd[3] = 0;
            cmd[4] = 0;
            cmd[5] = 0;
            cmd[6] = 0;
            cmd[7] = 0;
            cmd[8] = 0;
            cmd[9] = 0;
            cmd[10] = 0;
            cmd[11] = ETX;

            if (true == Serial.IsOpen)
            {
                try
                {
                    Serial.Write(cmd, 0, 12);
                }
                catch (Exception ex)
                {
                    MessageBox.Show( ex.ToString() );
                }
            }
            else
            {
                MessageBox.Show("Error. Serial port not connected.");
                return;
            }

            bool evt = evtDevAck.WaitOne(500); // Wait Serialport On received event to be set
            if (false == evt)
            {
                MessageBox.Show("Device no response");
            }
        }

        private void btnReset_Click(object sender, EventArgs e)
        {
            RemoteControlCmd(CMD_HOST_SYS_RESET);
            btnMoveFront.BackColor = Color.LightGray;
            btnMoveBack.BackColor = Color.LightGray;
            btnMoveLeft.BackColor = Color.LightGray;
            btnMoveRight.BackColor = Color.LightGray;
            btnMoveFR.BackColor = Color.LightGray;
            btnMoveFL.BackColor = Color.LightGray;
            btnMoveBR.BackColor = Color.LightGray;
            btnMoveBL.BackColor = Color.LightGray;
            btnRotateLeft.BackColor = Color.LightGray;
            btnRotateRight.BackColor = Color.LightGray;
            btnStart.BackColor = Color.LightGray;
        }

        private void btnMoveFront_Click(object sender, EventArgs e)
        {
            RemoteControlCmd( CMD_HOST_MOVE_FWD );

            btnMoveFront.BackColor = Color.LightGreen;
            btnMoveBack.BackColor = Color.LightGray;
            btnMoveLeft.BackColor = Color.LightGray;
            btnMoveRight.BackColor = Color.LightGray;
            btnMoveFR.BackColor = Color.LightGray;
            btnMoveFL.BackColor = Color.LightGray;
            btnMoveBR.BackColor = Color.LightGray;
            btnMoveBL.BackColor = Color.LightGray;
            btnRotateLeft.BackColor = Color.LightGray;
            btnRotateRight.BackColor = Color.LightGray;
            btnStart.BackColor = Color.LightGray;
        }

        private void btnMoveBack_Click(object sender, EventArgs e)
        {
            RemoteControlCmd(CMD_HOST_MOVE_BWD);

            btnMoveFront.BackColor = Color.LightGray;
            btnMoveBack.BackColor = Color.LightGreen;
            btnMoveLeft.BackColor = Color.LightGray;
            btnMoveRight.BackColor = Color.LightGray;
            btnMoveFR.BackColor = Color.LightGray;
            btnMoveFL.BackColor = Color.LightGray;
            btnMoveBR.BackColor = Color.LightGray;
            btnMoveBL.BackColor = Color.LightGray;
            btnRotateLeft.BackColor = Color.LightGray;
            btnRotateRight.BackColor = Color.LightGray;
            btnStart.BackColor = Color.LightGray;
        }

        private void btnRotateLeft_Click(object sender, EventArgs e)
        {
            RemoteControlCmd( CMD_HOST_ROTATE_LEFT );
            btnMoveFront.BackColor = Color.LightGray;
            btnMoveBack.BackColor = Color.LightGray;
            btnMoveLeft.BackColor = Color.LightGray;
            btnMoveRight.BackColor = Color.LightGray;
            btnMoveFR.BackColor = Color.LightGray;
            btnMoveFL.BackColor = Color.LightGray;
            btnMoveBR.BackColor = Color.LightGray;
            btnMoveBL.BackColor = Color.LightGray;
            btnRotateLeft.BackColor = Color.LightGreen;
            btnRotateRight.BackColor = Color.LightGray;
            btnStart.BackColor = Color.LightGray;
        }

        private void btnMoveFR_Click(object sender, EventArgs e)
        {
            RemoteControlCmd( CMD_HOST_MOVE_FR );

            btnMoveFront.BackColor = Color.LightGray;
            btnMoveBack.BackColor = Color.LightGray;
            btnMoveLeft.BackColor = Color.LightGray;
            btnMoveRight.BackColor = Color.LightGray;
            btnMoveFR.BackColor = Color.LightGreen;
            btnMoveFL.BackColor = Color.LightGray;
            btnMoveBR.BackColor = Color.LightGray;
            btnMoveBL.BackColor = Color.LightGray;
            btnRotateLeft.BackColor = Color.LightGray;
            btnRotateRight.BackColor = Color.LightGray;
            btnStart.BackColor = Color.LightGray;
        }

        private void btnMoveRight_Click(object sender, EventArgs e)
        {
            RemoteControlCmd( CMD_HOST_MOVE_RIGHT );

            btnMoveFront.BackColor = Color.LightGray;
            btnMoveBack.BackColor = Color.LightGray;
            btnMoveLeft.BackColor = Color.LightGray;
            btnMoveRight.BackColor = Color.LightGreen;
            btnMoveFR.BackColor = Color.LightGray;
            btnMoveFL.BackColor = Color.LightGray;
            btnMoveBR.BackColor = Color.LightGray;
            btnMoveBL.BackColor = Color.LightGray;
            btnRotateLeft.BackColor = Color.LightGray;
            btnRotateRight.BackColor = Color.LightGray;
            btnStart.BackColor = Color.LightGray;
        }

        private void btnMoveBR_Click(object sender, EventArgs e)
        {
            RemoteControlCmd( CMD_HOST_MOVE_BR );

            btnMoveFront.BackColor = Color.LightGray;
            btnMoveBack.BackColor = Color.LightGray;
            btnMoveLeft.BackColor = Color.LightGray;
            btnMoveRight.BackColor = Color.LightGray;
            btnMoveFR.BackColor = Color.LightGray;
            btnMoveFL.BackColor = Color.LightGray;
            btnMoveBR.BackColor = Color.LightGreen;
            btnMoveBL.BackColor = Color.LightGray;
            btnRotateLeft.BackColor = Color.LightGray;
            btnRotateRight.BackColor = Color.LightGray;
            btnStart.BackColor = Color.LightGray;
        }


        private void btnRotateRight_Click(object sender, EventArgs e)
        {
            RemoteControlCmd(CMD_HOST_ROTATE_RIGHT);

            btnMoveFront.BackColor = Color.LightGray;
            btnMoveBack.BackColor = Color.LightGray;
            btnMoveLeft.BackColor = Color.LightGray;
            btnMoveRight.BackColor = Color.LightGray;
            btnMoveFR.BackColor = Color.LightGray;
            btnMoveFL.BackColor = Color.LightGray;
            btnMoveBR.BackColor = Color.LightGray;
            btnMoveBL.BackColor = Color.LightGray;
            btnRotateLeft.BackColor = Color.LightGray;
            btnRotateRight.BackColor = Color.LightGreen;
            btnStart.BackColor = Color.LightGray;

        }

        private void btnMoveBL_Click(object sender, EventArgs e)
        {
            RemoteControlCmd(CMD_HOST_MOVE_BL);

            btnMoveFront.BackColor = Color.LightGray;
            btnMoveBack.BackColor = Color.LightGray;
            btnMoveLeft.BackColor = Color.LightGray;
            btnMoveRight.BackColor = Color.LightGray;
            btnMoveFR.BackColor = Color.LightGray;
            btnMoveFL.BackColor = Color.LightGray;
            btnMoveBR.BackColor = Color.LightGray;
            btnMoveBL.BackColor = Color.LightGreen;
            btnRotateLeft.BackColor = Color.LightGray;
            btnRotateRight.BackColor = Color.LightGray;
            btnStart.BackColor = Color.LightGray;
        }

        private void btnMoveLeft_Click(object sender, EventArgs e)
        {
            RemoteControlCmd(CMD_HOST_MOVE_LEFT);

            btnMoveFront.BackColor = Color.LightGray;
            btnMoveBack.BackColor = Color.LightGray;
            btnMoveLeft.BackColor = Color.LightGreen;
            btnMoveRight.BackColor = Color.LightGray;
            btnMoveFR.BackColor = Color.LightGray;
            btnMoveFL.BackColor = Color.LightGray;
            btnMoveBR.BackColor = Color.LightGray;
            btnMoveBL.BackColor = Color.LightGray;
            btnRotateLeft.BackColor = Color.LightGray;
            btnRotateRight.BackColor = Color.LightGray;
            btnStart.BackColor = Color.LightGray;
        }

        private void btnMoveFL_Click(object sender, EventArgs e)
        {
            RemoteControlCmd(CMD_HOST_MOVE_FL);

            btnMoveFront.BackColor = Color.LightGray;
            btnMoveBack.BackColor = Color.LightGray;
            btnMoveLeft.BackColor = Color.LightGray;
            btnMoveRight.BackColor = Color.LightGray;
            btnMoveFR.BackColor = Color.LightGray;
            btnMoveFL.BackColor = Color.LightGreen;
            btnMoveBR.BackColor = Color.LightGray;
            btnMoveBL.BackColor = Color.LightGray;
            btnRotateLeft.BackColor = Color.LightGray;
            btnRotateRight.BackColor = Color.LightGray;
            btnStart.BackColor = Color.LightGray;
        }

        private void btnUrgentStop_Click(object sender, EventArgs e)
        {
            //RemoteControlCmd(CMD_HOST_SYS_RESET);
            byte[] cmd = new byte[12];

            cmd[0] = STX;
            cmd[1] = CMD_HOST_STOP;
            cmd[2] = 0;
            cmd[3] = 0;
            cmd[4] = 0;
            cmd[5] = 0;
            cmd[6] = 0;
            cmd[7] = 0;
            cmd[8] = 0;
            cmd[9] = 0;
            cmd[10] = 0;
            cmd[11] = ETX;

            if (true == Serial.IsOpen)
            {
                Serial.Write(cmd, 0, 12);
            }
            else
            {
                MessageBox.Show("Error. Serial port not connected.");
                return;
            }

            bool evt = evtDevAck.WaitOne(500); // Wait Serialport On received event to be set
            if (false == evt)
            {
                MessageBox.Show("Device no response");
            }
        }

        private void btnMapStart_Click(object sender, EventArgs e)
        {
            byte[] cmd = new byte[12];

            cmd[0] = STX;
            cmd[1] = 0;
            cmd[2] = 0;
            cmd[3] = 0;
            cmd[4] = 0;
            cmd[5] = 0;
            cmd[6] = 0;
            cmd[7] = 0;
            cmd[8] = 0;
            cmd[9] = 0;
            cmd[10] = 0;
            cmd[11] = ETX;


            if ("Start" == btnMapStart.Text)
            {
                cmd[1] = CMD_HOST_START;
                btnMapStart.Text = "Stop";
            }
            else
            {
                cmd[1] = CMD_HOST_STOP;
                btnMapStart.Text = "Start";
            }

            if (true == Serial.IsOpen)
            {
                Serial.Write(cmd, 0, 12);
            }
            else
            {
                MessageBox.Show("Error. Serial port not connected.");
                return;
            }

            bool evt = evtDevAck.WaitOne(500); // Wait Serialport On received event to be set
            if (false == evt)
            {
                MessageBox.Show("Device no response");
            }
        }

        private void btnReport_Click(object sender, EventArgs e)
        {
              byte[] cmd = new byte[12];

            if ("Status ON" == btnReport.Text.ToString())
            {
                cmd[2] = 1;
                btnReport.Text = "Status OFF";
            }
            else
            {
                cmd[2] = 0;
                btnReport.Text = "Status ON";

            }

            cmd[0] = STX;
            cmd[1] = CMD_HOST_REPORT_ON;
            cmd[3] = 0;
            cmd[4] = 0;
            cmd[5] = 0;
            cmd[6] = 0;
            cmd[7] = 0;
            cmd[8] = 0;
            cmd[9] = 0;
            cmd[10] = 0;
            cmd[11] = ETX;

            if (true == Serial.IsOpen)
            {
                Serial.Write(cmd, 0, 12);
            }
            else
            {
                MessageBox.Show("Error. Serial port not connected.");
                return;
            }

            bool evt = evtDevAck.WaitOne( 500 ); // Wait Serialport On received event to be set
            if (false == evt)
            {
                MessageBox.Show( "Device no response" );
                btnReport.Text = "Status ON";
            }
        }

        private void btnLoad_Click(object sender, EventArgs e)
        {
            DialogResult result = DialogBrowse.ShowDialog(); // Show the dialog.
            if (result == DialogResult.OK) // Test result.
            {
                string file = DialogBrowse.FileName;
                try
                {
                    using (BinaryReader mapExport = new BinaryReader(File.Open(file, FileMode.Open, FileAccess.Read)))
                    {
                        byte[] buf = new byte[32*8];

                        mapExport.Read( buf, 0, 32 * 8);

                        int ptr = 0;
                        byte[] tmp = new byte[8];
                        acc = 0;
                        for (int i = 0; i < 32; i++)
                        {
                            Array.Copy(buf, ptr, tmp, 0, 8 );

                            var s = new MemoryStream(tmp);
                            var sz = Marshal.SizeOf(typeof(MapPoint));
                            var buf1 = new byte[sz];
                            s.Read(buf1, 0, sz);
                            var handle = GCHandle.Alloc(buf1, GCHandleType.Pinned);
                            var t = (MapPoint)Marshal.PtrToStructure(handle.AddrOfPinnedObject(), typeof(MapPoint));
                            handle.Free();

                            map[i] = t;
                            ptr += 8;

                            if((map[i].x != -1)&&(map[i].y != -1) )
                            {
                                acc++;
                                PlotDisp.Series[0].Points.AddXY(map[i].x/100, map[i].y/100);

                                labelRoute.Text += "P" + i.ToString() + ":  " + "( " + map[i].x.ToString() + " , " + map[i].y.ToString() + " )" + "\r\n";
                            }
                        }

                        mapExport.Close();


                    }
                }
                catch (IOException)
                {
                }
            }
        }

        private void btnSaveMap_Click(object sender, EventArgs e)
        {
            DialogResult result = DialogSave.ShowDialog(); // Show the dialog.
            if (result == DialogResult.OK) // Test result.
            {
                string file = DialogSave.FileName;
                try
                {
                    using (BinaryWriter mapExport = new BinaryWriter(File.Open(file, FileMode.Create)))
                    {
                        int size = Marshal.SizeOf(typeof(MapPoint));
                        int ptr = 0;
                        byte[] buf = new byte[size * 32];
                       for(int i=0; i< 32; i++)
                        {
                            Array.Copy(Serialize(map[i]), 0, buf, ptr, size );
                            ptr += 8;
                        }

                        mapExport.Write(buf, 0, size * 32);
                        mapExport.Close();
                    }

                    //using (FileStream fsSource = new FileStream(file, FileMode.CreateNew, FileAccess.Write))
                    //{
                    //    fsSource.Write(map.ToArray<byte>, 0, map.Length);
                    //    string len = fsSource.Length.ToString();
                    //    MessageBox.Show(len);
                    //}
                }
                catch (IOException)
                {
                }
            }
        }


        private void btnSpeed_Click(object sender, EventArgs e)
        {
            SyncFromDevice();
        }

        private void btnClearPIDPlot_Click(object sender, EventArgs e)
        {
            PlotPID.Series[0].Points.Clear();
            PlotPID.Series[1].Points.Clear();
            PlotPID.Series[2].Points.Clear();
            PlotPID.Series[3].Points.Clear();

            labelOpr.Text = "Last Operation: Plot Cleared";
        }

        private void CBoxM1_CheckStateChanged(object sender, EventArgs e)
        {
            if (true == CBoxM1.Checked)
            {
                PlotPID.Series[0].Enabled = true;
            }
            else
            {
                PlotPID.Series[0].Enabled = false;
            }
        }

        private void CBoxM2_CheckStateChanged(object sender, EventArgs e)
        {
            if (true == CBoxM2.Checked)
            {
                PlotPID.Series[1].Enabled = true;
            }
            else
            {
                PlotPID.Series[1].Enabled = false;
            }
        }

        private void CBoxM3_CheckStateChanged(object sender, EventArgs e)
        {
            if (true == CBoxM3.Checked)
            {
                PlotPID.Series[2].Enabled = true;
            }
            else
            {
                PlotPID.Series[2].Enabled = false;
            }
        }

        private void CBoxM4_CheckStateChanged(object sender, EventArgs e)
        {
            if (true == CBoxM4.Checked)
            {
                PlotPID.Series[3].Enabled = true;
            }
            else
            {
                PlotPID.Series[3].Enabled = false;
            }
        }

        private void PlotPID_MouseMove(object sender, MouseEventArgs e)
        {
            Point mousePoint = new Point(e.X, e.Y);

            PlotPID.ChartAreas[0].CursorX.SetCursorPixelPosition(mousePoint, true);
            PlotPID.ChartAreas[0].CursorY.SetCursorPixelPosition(mousePoint, true);

            // labelPIDXY.Text = "( " + e.X.ToString() + ", " + e.Y.ToString() + " )";
            try
            {
                double x = PlotPID.ChartAreas[0].AxisX.PixelPositionToValue(e.X);
                if (x < 0.0)
                {
                    x = 0.0;
                }

                double y = PlotPID.ChartAreas[0].AxisY.PixelPositionToValue(e.Y);
                if (y < 0.0)
                {
                    y = 0.0;
                }
                labelPIDXY.Text = "(" + x.ToString("f2") + ", " + y.ToString("f2") + ")";
            }
            catch (Exception ex)
            {
                labelPIDXY.Text = "( 0, 0 )";

            }
        }

        private void trackBarKP_ValueChanged(object sender, EventArgs e)
        {
            double value = trackBarKP.Value / 100.0;
            
            labelKP.Text = "KP: " + value.ToString();
        }

        private void trackBarKI_ValueChanged(object sender, EventArgs e)
        {
            double value = trackBarKI.Value / 100.0;

            labelKI.Text = "KI: " + value.ToString();
        }

        private void trackBarKD_ValueChanged(object sender, EventArgs e)
        {
            double value = trackBarKD.Value / 100.0;

            labelKD.Text = "KD: " + value.ToString();
        }

        private void trackBarRPM_ValueChanged(object sender, EventArgs e)
        {
            labelRPM.Text = "RPM: " + trackBarRPM.Value.ToString();
        }


        private void SyncFromDevice()
        {
            byte[] cmd = new byte[12];

            cmd[0] = STX;
            cmd[1] = CMD_HOST_RESTORE;
            cmd[11] = ETX;

            if (true == Serial.IsOpen)
            {
                try
                {
                    Serial.Write(cmd, 0, 12);
                }
                catch( Exception ex )
                {
                    MessageBox.Show( ex.ToString() );
                }
            }
            else
            {
                MessageBox.Show("Error. Serial port not connected.");
                return;
            }

            bool evt = evtDevAck.WaitOne(500); // Wait Serialport On received event to be set
            if (false == evt)
            {
                MessageBox.Show("Device no response");
                btnReport.Text = "Status ON";
            }
        }


        private void SyncToDevice()
        {
            byte[] cmd = new byte[12];
            Int32 kp = Convert.ToInt32(trackBarKP.Value);
            Int32 ki = Convert.ToInt32(trackBarKI.Value);
            Int32 kd = Convert.ToInt32(trackBarKD.Value);
            Int32 Interval = Convert.ToInt32(trackBarInterval.Value);

            cmd[0] = STX;
            cmd[1] = CMD_HOST_CHANGE_PID;
            cmd[2] = Convert.ToByte(kp & 0xff);
            cmd[3] = Convert.ToByte((kp >> 8) & 0xff);
            cmd[4] = Convert.ToByte(ki & 0xff);
            cmd[5] = Convert.ToByte((ki >> 8) & 0xff);
            cmd[6] = Convert.ToByte(kd & 0xff);
            cmd[7] = Convert.ToByte((kd >> 8) & 0xff);
            cmd[8] = Convert.ToByte(Interval & 0xff);
            cmd[9] = Convert.ToByte((Interval >> 8) & 0xff);
            cmd[10] = 0;
            cmd[11] = ETX;

            if (true == Serial.IsOpen)
            {
                Serial.Write(cmd, 0, 12);
            }
            else
            {
                MessageBox.Show("Error. Serial port not connected.");
                return;
            }
        }



        private void RPMToDevice()
        {
            byte[] cmd = new byte[12];
            Int32 speed = Convert.ToInt32(trackBarRPM.Value);

            cmd[0] = STX;
            cmd[1] = CMD_HOST_CHANGE_SPEED;
            cmd[2] = Convert.ToByte(speed & 0xff);
            cmd[3] = Convert.ToByte((speed >> 8) & 0xff);
            cmd[4] = Convert.ToByte((speed >> 16) & 0xff);
            cmd[5] = Convert.ToByte((speed >> 24) & 0xff);
            cmd[6] = 0;
            cmd[7] = 0;
            cmd[8] = 0;
            cmd[9] = 0;
            cmd[10] = 0;
            cmd[11] = ETX;

            if (true == Serial.IsOpen)
            {
                Serial.Write(cmd, 0, 12);
            }
            else
            {
                MessageBox.Show("Error. Serial port not connected.");
                return;
            }
        }


        private void trackBarRPM_MouseUp(object sender, MouseEventArgs e)
        {
            RPMToDevice();
        }

        private void trackBarKP_MouseUp(object sender, MouseEventArgs e)
        {
            SyncToDevice();
        }

        private void trackBarKI_MouseUp(object sender, MouseEventArgs e)
        {
            SyncToDevice();
        }

        private void trackBarKD_MouseUp(object sender, MouseEventArgs e)
        {
            SyncToDevice();
        }

        private void trackBarInterval_ValueChanged(object sender, EventArgs e)
        {
            labelInterval.Text = "Interval: " + trackBarInterval.Value.ToString();
        }

        private void trackBarInterval_MouseUp(object sender, MouseEventArgs e)
        {
            SyncToDevice();
        }

        private void trackBarKP_KeyUp(object sender, KeyEventArgs e)
        {
            SyncToDevice();
        }

        private void trackBarKI_KeyUp(object sender, KeyEventArgs e)
        {
            SyncToDevice();
        }

        private void trackBarKD_KeyUp(object sender, KeyEventArgs e)
        {
            SyncToDevice();
        }

        private void trackBarRPM_KeyUp(object sender, KeyEventArgs e)
        {
            RPMToDevice();
        }

        private void trackBarInterval_KeyUp(object sender, KeyEventArgs e)
        {
            SyncToDevice();
        }

        private void cBoxLogPID_CheckedChanged(object sender, EventArgs e)
        {
            if (true == cBoxLogPID.Checked)
            {
                if (true == File.Exists("PID.csv"))
                {
                    DateTime now = DateTime.Now;
                    long time = now.ToFileTime();

                    string oldPath = "PID_" + time.ToString() + ".csv";
                    File.Move("PID.csv", oldPath);
                }
            }
        }

        private void helpToolStripMenuItem_Click(object sender, EventArgs e)
        {
            MessageBox.Show( "Log Enable: a CSV file will store at root directory" );
        }

        private void CBoxM1_CheckStateChanged_1(object sender, EventArgs e)
        {
            if (true == CBoxM1.Checked)
            {
                PlotPID.Series[0].Enabled = true;
            }
            else
            {
                PlotPID.Series[0].Enabled = false;
            }
        }

        private void CBoxM2_CheckStateChanged_1(object sender, EventArgs e)
        {
            if (true == CBoxM2.Checked)
            {
                PlotPID.Series[1].Enabled = true;
            }
            else
            {
                PlotPID.Series[1].Enabled = false;
            }
        }

        private void CBoxM3_CheckStateChanged_1(object sender, EventArgs e)
        {
            if (true == CBoxM3.Checked)
            {
                PlotPID.Series[2].Enabled = true;
            }
            else
            {
                PlotPID.Series[2].Enabled = false;
            }
        }

        private void CBoxM4_CheckStateChanged_1(object sender, EventArgs e)
        {
            if (true == CBoxM4.Checked)
            {
                PlotPID.Series[3].Enabled = true;
            }
            else
            {
                PlotPID.Series[3].Enabled = false;
            }
        }

        private void btnPIDStart_Click(object sender, EventArgs e)
        {
            if( "Start" == btnPIDStart.Text )
            {
                btnPIDStart.Text = "Stop";
                string select = cBoxPIDDir.SelectedItem.ToString();

                switch (select)
                {
                    case "Forward":
                        RemoteControlCmd(CMD_HOST_MOVE_FWD);
                        break;

                    case "Backward":
                        RemoteControlCmd(CMD_HOST_MOVE_BWD);
                        break;

                    case "Left":
                        RemoteControlCmd(CMD_HOST_MOVE_LEFT);
                        break;

                    case "Right":
                        RemoteControlCmd(CMD_HOST_MOVE_RIGHT);
                        break;

                    case "Front Left":
                        RemoteControlCmd(CMD_HOST_MOVE_FL);
                        break;

                    case "Front Right":
                        RemoteControlCmd(CMD_HOST_MOVE_FR);
                        break;

                    case "Back Left":
                        RemoteControlCmd(CMD_HOST_MOVE_BL);
                        break;

                    case "Back Right":
                        RemoteControlCmd(CMD_HOST_MOVE_BR);
                        break;

                    default:
                        break;
                };
            }
            else
            {
                btnPIDStart.Text = "Start";

                byte[] cmd = new byte[12];

                cmd[0] = STX;
                cmd[1] = CMD_HOST_STOP;
                cmd[2] = 0;
                cmd[3] = 0;
                cmd[4] = 0;
                cmd[5] = 0;
                cmd[6] = 0;
                cmd[7] = 0;
                cmd[8] = 0;
                cmd[9] = 0;
                cmd[10] = 0;
                cmd[11] = ETX;

                if (true == Serial.IsOpen)
                {
                    try
                    {
                        Serial.Write(cmd, 0, 12);
                    }
                    catch( Exception ex )
                    {
                        MessageBox.Show(ex.ToString());
                    }
                }
                else
                {
                    MessageBox.Show("Error. Serial port not connected.");
                    return;
                }

                bool evt = evtDevAck.WaitOne(500); // Wait Serialport On received event to be set
                if (false == evt)
                {
                    MessageBox.Show("Device no response");
                }
            }
        }
    }
}
