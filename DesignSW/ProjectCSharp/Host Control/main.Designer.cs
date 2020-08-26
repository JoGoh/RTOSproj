namespace uCamReceiver
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea1 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
            System.Windows.Forms.DataVisualization.Charting.Legend legend1 = new System.Windows.Forms.DataVisualization.Charting.Legend();
            System.Windows.Forms.DataVisualization.Charting.Series series1 = new System.Windows.Forms.DataVisualization.Charting.Series();
            System.Windows.Forms.DataVisualization.Charting.Series series2 = new System.Windows.Forms.DataVisualization.Charting.Series();
            System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea2 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
            System.Windows.Forms.DataVisualization.Charting.Legend legend2 = new System.Windows.Forms.DataVisualization.Charting.Legend();
            System.Windows.Forms.DataVisualization.Charting.Series series3 = new System.Windows.Forms.DataVisualization.Charting.Series();
            System.Windows.Forms.DataVisualization.Charting.Series series4 = new System.Windows.Forms.DataVisualization.Charting.Series();
            System.Windows.Forms.DataVisualization.Charting.Series series5 = new System.Windows.Forms.DataVisualization.Charting.Series();
            System.Windows.Forms.DataVisualization.Charting.Series series6 = new System.Windows.Forms.DataVisualization.Charting.Series();
            this.cboxBaud = new System.Windows.Forms.ComboBox();
            this.btnConnect = new System.Windows.Forms.Button();
            this.cboxComPort = new System.Windows.Forms.ComboBox();
            this.stsStripDisplay = new System.Windows.Forms.StatusStrip();
            this.toolStripStatusLabel1 = new System.Windows.Forms.ToolStripStatusLabel();
            this.toolStripProgressBar1 = new System.Windows.Forms.ToolStripProgressBar();
            this.statuslabelReport = new System.Windows.Forms.ToolStripStatusLabel();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.btnCOMRefresh = new System.Windows.Forms.Button();
            this.labelInfo = new System.Windows.Forms.Label();
            this.PlotDisp = new System.Windows.Forms.DataVisualization.Charting.Chart();
            this.btnReset = new System.Windows.Forms.Button();
            this.btnSet = new System.Windows.Forms.Button();
            this.btnStart = new System.Windows.Forms.Button();
            this.btnMap = new System.Windows.Forms.Button();
            this.textPointX = new System.Windows.Forms.TextBox();
            this.textPointY = new System.Windows.Forms.TextBox();
            this.labelRoute = new System.Windows.Forms.Label();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.btnMapStart = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.btnClearPlot = new System.Windows.Forms.Button();
            this.btnClearMap = new System.Windows.Forms.Button();
            this.labelCurXY = new System.Windows.Forms.Label();
            this.groupBox5 = new System.Windows.Forms.GroupBox();
            this.button1 = new System.Windows.Forms.Button();
            this.btnCal = new System.Windows.Forms.Button();
            this.btnRefSet = new System.Windows.Forms.Button();
            this.label8 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.txtRefY3 = new System.Windows.Forms.TextBox();
            this.txtRefX3 = new System.Windows.Forms.TextBox();
            this.txtRefY2 = new System.Windows.Forms.TextBox();
            this.txtRefX2 = new System.Windows.Forms.TextBox();
            this.txtRefY1 = new System.Windows.Forms.TextBox();
            this.txtRefX1 = new System.Windows.Forms.TextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.tabCtrlPanel = new System.Windows.Forms.TabControl();
            this.tabSetup = new System.Windows.Forms.TabPage();
            this.tabControl = new System.Windows.Forms.TabPage();
            this.btnReport = new System.Windows.Forms.Button();
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.btnRotateLeft = new System.Windows.Forms.Button();
            this.btnRotateRight = new System.Windows.Forms.Button();
            this.btnMoveBR = new System.Windows.Forms.Button();
            this.btnMoveFR = new System.Windows.Forms.Button();
            this.btnMoveBL = new System.Windows.Forms.Button();
            this.btnMoveFL = new System.Windows.Forms.Button();
            this.btnMoveLeft = new System.Windows.Forms.Button();
            this.btnMoveRight = new System.Windows.Forms.Button();
            this.btnMoveBack = new System.Windows.Forms.Button();
            this.btnMoveFront = new System.Windows.Forms.Button();
            this.tabPIDADJ = new System.Windows.Forms.TabPage();
            this.groupBox8 = new System.Windows.Forms.GroupBox();
            this.btnPIDStart = new System.Windows.Forms.Button();
            this.cBoxPIDDir = new System.Windows.Forms.ComboBox();
            this.btnSpeed = new System.Windows.Forms.Button();
            this.groupBox7 = new System.Windows.Forms.GroupBox();
            this.cBoxLogPID = new System.Windows.Forms.CheckBox();
            this.CBoxM4 = new System.Windows.Forms.CheckBox();
            this.btnClearPIDPlot = new System.Windows.Forms.Button();
            this.CBoxM3 = new System.Windows.Forms.CheckBox();
            this.CBoxM2 = new System.Windows.Forms.CheckBox();
            this.CBoxM1 = new System.Windows.Forms.CheckBox();
            this.groupBox6 = new System.Windows.Forms.GroupBox();
            this.labelInterval = new System.Windows.Forms.Label();
            this.trackBarInterval = new System.Windows.Forms.TrackBar();
            this.labelRPM = new System.Windows.Forms.Label();
            this.labelKD = new System.Windows.Forms.Label();
            this.labelKI = new System.Windows.Forms.Label();
            this.labelKP = new System.Windows.Forms.Label();
            this.trackBarRPM = new System.Windows.Forms.TrackBar();
            this.trackBarKD = new System.Windows.Forms.TrackBar();
            this.trackBarKI = new System.Windows.Forms.TrackBar();
            this.trackBarKP = new System.Windows.Forms.TrackBar();
            this.labelPIDXY = new System.Windows.Forms.Label();
            this.PlotPID = new System.Windows.Forms.DataVisualization.Charting.Chart();
            this.tabCal = new System.Windows.Forms.TabPage();
            this.tabMap = new System.Windows.Forms.TabPage();
            this.btnSaveMap = new System.Windows.Forms.Button();
            this.btnLoad = new System.Windows.Forms.Button();
            this.btnUrgentStop = new System.Windows.Forms.Button();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.labelSpeed = new System.Windows.Forms.Label();
            this.DialogBrowse = new System.Windows.Forms.OpenFileDialog();
            this.DialogSave = new System.Windows.Forms.SaveFileDialog();
            this.labelOpr = new System.Windows.Forms.Label();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.helpToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.stsStripDisplay.SuspendLayout();
            this.groupBox1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.PlotDisp)).BeginInit();
            this.groupBox2.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.groupBox5.SuspendLayout();
            this.tabCtrlPanel.SuspendLayout();
            this.tabSetup.SuspendLayout();
            this.tabControl.SuspendLayout();
            this.groupBox4.SuspendLayout();
            this.tabPIDADJ.SuspendLayout();
            this.groupBox8.SuspendLayout();
            this.groupBox7.SuspendLayout();
            this.groupBox6.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarInterval)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarRPM)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarKD)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarKI)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarKP)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.PlotPID)).BeginInit();
            this.tabCal.SuspendLayout();
            this.tabMap.SuspendLayout();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // cboxBaud
            // 
            this.cboxBaud.FormattingEnabled = true;
            this.cboxBaud.Location = new System.Drawing.Point(4, 48);
            this.cboxBaud.Name = "cboxBaud";
            this.cboxBaud.Size = new System.Drawing.Size(103, 25);
            this.cboxBaud.TabIndex = 1;
            // 
            // btnConnect
            // 
            this.btnConnect.Location = new System.Drawing.Point(113, 20);
            this.btnConnect.Name = "btnConnect";
            this.btnConnect.Size = new System.Drawing.Size(114, 56);
            this.btnConnect.TabIndex = 2;
            this.btnConnect.Text = "Connect";
            this.btnConnect.UseVisualStyleBackColor = true;
            this.btnConnect.Click += new System.EventHandler(this.btConnect_Click);
            // 
            // cboxComPort
            // 
            this.cboxComPort.FormattingEnabled = true;
            this.cboxComPort.Location = new System.Drawing.Point(5, 20);
            this.cboxComPort.Name = "cboxComPort";
            this.cboxComPort.Size = new System.Drawing.Size(103, 25);
            this.cboxComPort.TabIndex = 0;
            // 
            // stsStripDisplay
            // 
            this.stsStripDisplay.ImageScalingSize = new System.Drawing.Size(20, 20);
            this.stsStripDisplay.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripStatusLabel1,
            this.toolStripProgressBar1,
            this.statuslabelReport});
            this.stsStripDisplay.Location = new System.Drawing.Point(0, 709);
            this.stsStripDisplay.Name = "stsStripDisplay";
            this.stsStripDisplay.Size = new System.Drawing.Size(858, 25);
            this.stsStripDisplay.TabIndex = 5;
            this.stsStripDisplay.Text = "statusStrip1";
            // 
            // toolStripStatusLabel1
            // 
            this.toolStripStatusLabel1.Name = "toolStripStatusLabel1";
            this.toolStripStatusLabel1.Size = new System.Drawing.Size(101, 20);
            this.toolStripStatusLabel1.Text = "Status: Offline";
            // 
            // toolStripProgressBar1
            // 
            this.toolStripProgressBar1.Name = "toolStripProgressBar1";
            this.toolStripProgressBar1.Size = new System.Drawing.Size(100, 19);
            // 
            // statuslabelReport
            // 
            this.statuslabelReport.Name = "statuslabelReport";
            this.statuslabelReport.Size = new System.Drawing.Size(15, 20);
            this.statuslabelReport.Text = "-";
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.btnCOMRefresh);
            this.groupBox1.Controls.Add(this.cboxComPort);
            this.groupBox1.Controls.Add(this.cboxBaud);
            this.groupBox1.Controls.Add(this.btnConnect);
            this.groupBox1.Location = new System.Drawing.Point(12, 18);
            this.groupBox1.Margin = new System.Windows.Forms.Padding(2);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Padding = new System.Windows.Forms.Padding(2);
            this.groupBox1.Size = new System.Drawing.Size(355, 96);
            this.groupBox1.TabIndex = 16;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "COM Port";
            // 
            // btnCOMRefresh
            // 
            this.btnCOMRefresh.Location = new System.Drawing.Point(233, 20);
            this.btnCOMRefresh.Name = "btnCOMRefresh";
            this.btnCOMRefresh.Size = new System.Drawing.Size(114, 56);
            this.btnCOMRefresh.TabIndex = 3;
            this.btnCOMRefresh.Text = "Refresh";
            this.btnCOMRefresh.UseVisualStyleBackColor = true;
            this.btnCOMRefresh.Click += new System.EventHandler(this.btnCOMRefresh_Click);
            // 
            // labelInfo
            // 
            this.labelInfo.AutoSize = true;
            this.labelInfo.Location = new System.Drawing.Point(13, 686);
            this.labelInfo.Name = "labelInfo";
            this.labelInfo.Size = new System.Drawing.Size(82, 17);
            this.labelInfo.TabIndex = 23;
            this.labelInfo.Text = "Information:";
            // 
            // PlotDisp
            // 
            chartArea1.AxisX.LineColor = System.Drawing.Color.Gray;
            chartArea1.AxisX.LineDashStyle = System.Windows.Forms.DataVisualization.Charting.ChartDashStyle.Dot;
            chartArea1.AxisX.MajorGrid.LineColor = System.Drawing.Color.Gray;
            chartArea1.AxisX.MajorGrid.LineDashStyle = System.Windows.Forms.DataVisualization.Charting.ChartDashStyle.Dash;
            chartArea1.AxisX2.LineColor = System.Drawing.Color.Red;
            chartArea1.AxisX2.LineDashStyle = System.Windows.Forms.DataVisualization.Charting.ChartDashStyle.Dot;
            chartArea1.AxisY.LineColor = System.Drawing.Color.Gray;
            chartArea1.AxisY.LineDashStyle = System.Windows.Forms.DataVisualization.Charting.ChartDashStyle.Dot;
            chartArea1.AxisY.MajorGrid.LineColor = System.Drawing.Color.Gray;
            chartArea1.AxisY.MajorGrid.LineDashStyle = System.Windows.Forms.DataVisualization.Charting.ChartDashStyle.Dash;
            chartArea1.AxisY.MaximumAutoSize = 100F;
            chartArea1.AxisY2.LineColor = System.Drawing.Color.Chartreuse;
            chartArea1.AxisY2.LineDashStyle = System.Windows.Forms.DataVisualization.Charting.ChartDashStyle.Dot;
            chartArea1.BorderColor = System.Drawing.Color.Gray;
            chartArea1.BorderDashStyle = System.Windows.Forms.DataVisualization.Charting.ChartDashStyle.Dash;
            chartArea1.IsSameFontSizeForAllAxes = true;
            chartArea1.Name = "ChartArea1";
            this.PlotDisp.ChartAreas.Add(chartArea1);
            this.PlotDisp.Cursor = System.Windows.Forms.Cursors.Cross;
            legend1.Docking = System.Windows.Forms.DataVisualization.Charting.Docking.Bottom;
            legend1.Name = "Legend1";
            this.PlotDisp.Legends.Add(legend1);
            this.PlotDisp.Location = new System.Drawing.Point(7, 6);
            this.PlotDisp.Margin = new System.Windows.Forms.Padding(2);
            this.PlotDisp.Name = "PlotDisp";
            series1.ChartArea = "ChartArea1";
            series1.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Line;
            series1.Color = System.Drawing.Color.Red;
            series1.Legend = "Legend1";
            series1.MarkerBorderColor = System.Drawing.Color.Lime;
            series1.MarkerColor = System.Drawing.Color.Lime;
            series1.MarkerSize = 8;
            series1.MarkerStyle = System.Windows.Forms.DataVisualization.Charting.MarkerStyle.Circle;
            series1.Name = "Planned";
            series2.ChartArea = "ChartArea1";
            series2.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Line;
            series2.Legend = "Legend1";
            series2.MarkerBorderColor = System.Drawing.Color.MediumBlue;
            series2.MarkerColor = System.Drawing.Color.MediumBlue;
            series2.MarkerSize = 8;
            series2.MarkerStyle = System.Windows.Forms.DataVisualization.Charting.MarkerStyle.Star5;
            series2.Name = "Current";
            this.PlotDisp.Series.Add(series1);
            this.PlotDisp.Series.Add(series2);
            this.PlotDisp.Size = new System.Drawing.Size(572, 450);
            this.PlotDisp.TabIndex = 25;
            this.PlotDisp.Text = "chart1";
            this.PlotDisp.Click += new System.EventHandler(this.PlotDisp_Click);
            // 
            // btnReset
            // 
            this.btnReset.Location = new System.Drawing.Point(719, 35);
            this.btnReset.Margin = new System.Windows.Forms.Padding(2);
            this.btnReset.Name = "btnReset";
            this.btnReset.Size = new System.Drawing.Size(110, 55);
            this.btnReset.TabIndex = 26;
            this.btnReset.Text = "Reset";
            this.btnReset.UseVisualStyleBackColor = true;
            this.btnReset.Click += new System.EventHandler(this.btnReset_Click);
            // 
            // btnSet
            // 
            this.btnSet.Location = new System.Drawing.Point(81, 19);
            this.btnSet.Margin = new System.Windows.Forms.Padding(2);
            this.btnSet.Name = "btnSet";
            this.btnSet.Size = new System.Drawing.Size(81, 28);
            this.btnSet.TabIndex = 31;
            this.btnSet.Text = "Add Point";
            this.btnSet.UseVisualStyleBackColor = true;
            this.btnSet.Click += new System.EventHandler(this.btnSet_Click);
            // 
            // btnStart
            // 
            this.btnStart.Location = new System.Drawing.Point(140, 106);
            this.btnStart.Margin = new System.Windows.Forms.Padding(2);
            this.btnStart.Name = "btnStart";
            this.btnStart.Size = new System.Drawing.Size(100, 166);
            this.btnStart.TabIndex = 34;
            this.btnStart.Text = "Stop";
            this.btnStart.UseVisualStyleBackColor = true;
            this.btnStart.Click += new System.EventHandler(this.btnStart_Click);
            // 
            // btnMap
            // 
            this.btnMap.Location = new System.Drawing.Point(81, 48);
            this.btnMap.Margin = new System.Windows.Forms.Padding(2);
            this.btnMap.Name = "btnMap";
            this.btnMap.Size = new System.Drawing.Size(81, 28);
            this.btnMap.TabIndex = 35;
            this.btnMap.Text = "Set Map";
            this.btnMap.UseVisualStyleBackColor = true;
            this.btnMap.Click += new System.EventHandler(this.btnMap_Click);
            // 
            // textPointX
            // 
            this.textPointX.Location = new System.Drawing.Point(26, 21);
            this.textPointX.Margin = new System.Windows.Forms.Padding(2);
            this.textPointX.Name = "textPointX";
            this.textPointX.Size = new System.Drawing.Size(51, 23);
            this.textPointX.TabIndex = 36;
            // 
            // textPointY
            // 
            this.textPointY.Location = new System.Drawing.Point(26, 51);
            this.textPointY.Margin = new System.Windows.Forms.Padding(2);
            this.textPointY.Name = "textPointY";
            this.textPointY.Size = new System.Drawing.Size(51, 23);
            this.textPointY.TabIndex = 37;
            this.textPointY.TextChanged += new System.EventHandler(this.textPointY_TextChanged);
            // 
            // labelRoute
            // 
            this.labelRoute.AutoSize = true;
            this.labelRoute.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.labelRoute.Location = new System.Drawing.Point(17, 16);
            this.labelRoute.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.labelRoute.Name = "labelRoute";
            this.labelRoute.Size = new System.Drawing.Size(0, 20);
            this.labelRoute.TabIndex = 38;
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.labelRoute);
            this.groupBox2.Location = new System.Drawing.Point(584, 111);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(260, 377);
            this.groupBox2.TabIndex = 39;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Route list";
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.btnMapStart);
            this.groupBox3.Controls.Add(this.label2);
            this.groupBox3.Controls.Add(this.label1);
            this.groupBox3.Controls.Add(this.textPointX);
            this.groupBox3.Controls.Add(this.textPointY);
            this.groupBox3.Controls.Add(this.btnMap);
            this.groupBox3.Controls.Add(this.btnSet);
            this.groupBox3.Location = new System.Drawing.Point(584, 6);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(260, 81);
            this.groupBox3.TabIndex = 40;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Map Setting";
            // 
            // btnMapStart
            // 
            this.btnMapStart.Location = new System.Drawing.Point(178, 20);
            this.btnMapStart.Name = "btnMapStart";
            this.btnMapStart.Size = new System.Drawing.Size(75, 55);
            this.btnMapStart.TabIndex = 40;
            this.btnMapStart.Text = "Start";
            this.btnMapStart.UseVisualStyleBackColor = true;
            this.btnMapStart.Click += new System.EventHandler(this.btnMapStart_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(3, 48);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(21, 17);
            this.label2.TabIndex = 39;
            this.label2.Text = "Y:";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(3, 24);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(21, 17);
            this.label1.TabIndex = 38;
            this.label1.Text = "X:";
            // 
            // btnClearPlot
            // 
            this.btnClearPlot.Location = new System.Drawing.Point(298, 428);
            this.btnClearPlot.Margin = new System.Windows.Forms.Padding(2);
            this.btnClearPlot.Name = "btnClearPlot";
            this.btnClearPlot.Size = new System.Drawing.Size(81, 28);
            this.btnClearPlot.TabIndex = 41;
            this.btnClearPlot.Text = "Clear Plot";
            this.btnClearPlot.UseVisualStyleBackColor = true;
            this.btnClearPlot.Click += new System.EventHandler(this.btnClearPlot_Click);
            // 
            // btnClearMap
            // 
            this.btnClearMap.Location = new System.Drawing.Point(298, 460);
            this.btnClearMap.Margin = new System.Windows.Forms.Padding(2);
            this.btnClearMap.Name = "btnClearMap";
            this.btnClearMap.Size = new System.Drawing.Size(81, 28);
            this.btnClearMap.TabIndex = 40;
            this.btnClearMap.Text = "Clear All";
            this.btnClearMap.UseVisualStyleBackColor = true;
            this.btnClearMap.Click += new System.EventHandler(this.btnClearMap_Click);
            // 
            // labelCurXY
            // 
            this.labelCurXY.AutoSize = true;
            this.labelCurXY.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.labelCurXY.Location = new System.Drawing.Point(12, 654);
            this.labelCurXY.Name = "labelCurXY";
            this.labelCurXY.Size = new System.Drawing.Size(231, 25);
            this.labelCurXY.TabIndex = 42;
            this.labelCurXY.Text = "Current location: ( X , Y ) ";
            // 
            // groupBox5
            // 
            this.groupBox5.Controls.Add(this.button1);
            this.groupBox5.Controls.Add(this.btnCal);
            this.groupBox5.Controls.Add(this.btnRefSet);
            this.groupBox5.Controls.Add(this.label8);
            this.groupBox5.Controls.Add(this.label7);
            this.groupBox5.Controls.Add(this.label5);
            this.groupBox5.Controls.Add(this.label4);
            this.groupBox5.Controls.Add(this.label3);
            this.groupBox5.Controls.Add(this.txtRefY3);
            this.groupBox5.Controls.Add(this.txtRefX3);
            this.groupBox5.Controls.Add(this.txtRefY2);
            this.groupBox5.Controls.Add(this.txtRefX2);
            this.groupBox5.Controls.Add(this.txtRefY1);
            this.groupBox5.Controls.Add(this.txtRefX1);
            this.groupBox5.Location = new System.Drawing.Point(12, 17);
            this.groupBox5.Name = "groupBox5";
            this.groupBox5.Size = new System.Drawing.Size(270, 127);
            this.groupBox5.TabIndex = 43;
            this.groupBox5.TabStop = false;
            this.groupBox5.Text = "Reference Points Setting";
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(184, 89);
            this.button1.Margin = new System.Windows.Forms.Padding(2);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(81, 28);
            this.button1.TabIndex = 51;
            this.button1.Text = "Save";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // btnCal
            // 
            this.btnCal.Location = new System.Drawing.Point(184, 24);
            this.btnCal.Margin = new System.Windows.Forms.Padding(2);
            this.btnCal.Name = "btnCal";
            this.btnCal.Size = new System.Drawing.Size(81, 28);
            this.btnCal.TabIndex = 50;
            this.btnCal.Text = "Calibrate";
            this.btnCal.UseVisualStyleBackColor = true;
            this.btnCal.Click += new System.EventHandler(this.btnCal_Click);
            // 
            // btnRefSet
            // 
            this.btnRefSet.Location = new System.Drawing.Point(184, 57);
            this.btnRefSet.Margin = new System.Windows.Forms.Padding(2);
            this.btnRefSet.Name = "btnRefSet";
            this.btnRefSet.Size = new System.Drawing.Size(81, 28);
            this.btnRefSet.TabIndex = 41;
            this.btnRefSet.Text = "Set";
            this.btnRefSet.UseVisualStyleBackColor = true;
            this.btnRefSet.Click += new System.EventHandler(this.btnRefSet_Click);
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(6, 96);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(53, 17);
            this.label8.TabIndex = 49;
            this.label8.Text = "Resp3:";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(6, 68);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(53, 17);
            this.label7.TabIndex = 48;
            this.label7.Text = "Resp2:";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(6, 41);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(53, 17);
            this.label5.TabIndex = 47;
            this.label5.Text = "Resp1:";
            this.label5.Click += new System.EventHandler(this.label5_Click);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(132, 19);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(29, 17);
            this.label4.TabIndex = 41;
            this.label4.Text = "Yn:";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(73, 19);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(29, 17);
            this.label3.TabIndex = 41;
            this.label3.Text = "Xn:";
            // 
            // txtRefY3
            // 
            this.txtRefY3.Location = new System.Drawing.Point(120, 94);
            this.txtRefY3.Margin = new System.Windows.Forms.Padding(2);
            this.txtRefY3.Name = "txtRefY3";
            this.txtRefY3.Size = new System.Drawing.Size(51, 23);
            this.txtRefY3.TabIndex = 46;
            // 
            // txtRefX3
            // 
            this.txtRefX3.Location = new System.Drawing.Point(62, 94);
            this.txtRefX3.Margin = new System.Windows.Forms.Padding(2);
            this.txtRefX3.Name = "txtRefX3";
            this.txtRefX3.Size = new System.Drawing.Size(51, 23);
            this.txtRefX3.TabIndex = 45;
            // 
            // txtRefY2
            // 
            this.txtRefY2.Location = new System.Drawing.Point(120, 67);
            this.txtRefY2.Margin = new System.Windows.Forms.Padding(2);
            this.txtRefY2.Name = "txtRefY2";
            this.txtRefY2.Size = new System.Drawing.Size(51, 23);
            this.txtRefY2.TabIndex = 44;
            // 
            // txtRefX2
            // 
            this.txtRefX2.Location = new System.Drawing.Point(62, 67);
            this.txtRefX2.Margin = new System.Windows.Forms.Padding(2);
            this.txtRefX2.Name = "txtRefX2";
            this.txtRefX2.Size = new System.Drawing.Size(51, 23);
            this.txtRefX2.TabIndex = 43;
            // 
            // txtRefY1
            // 
            this.txtRefY1.Location = new System.Drawing.Point(120, 40);
            this.txtRefY1.Margin = new System.Windows.Forms.Padding(2);
            this.txtRefY1.Name = "txtRefY1";
            this.txtRefY1.Size = new System.Drawing.Size(51, 23);
            this.txtRefY1.TabIndex = 42;
            // 
            // txtRefX1
            // 
            this.txtRefX1.Location = new System.Drawing.Point(62, 40);
            this.txtRefX1.Margin = new System.Windows.Forms.Padding(2);
            this.txtRefX1.Name = "txtRefX1";
            this.txtRefX1.Size = new System.Drawing.Size(51, 23);
            this.txtRefX1.TabIndex = 41;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(19, 516);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(194, 17);
            this.label6.TabIndex = 48;
            this.label6.Text = "All distance measured in (cm)";
            // 
            // tabCtrlPanel
            // 
            this.tabCtrlPanel.Controls.Add(this.tabSetup);
            this.tabCtrlPanel.Controls.Add(this.tabControl);
            this.tabCtrlPanel.Controls.Add(this.tabPIDADJ);
            this.tabCtrlPanel.Controls.Add(this.tabCal);
            this.tabCtrlPanel.Controls.Add(this.tabMap);
            this.tabCtrlPanel.Dock = System.Windows.Forms.DockStyle.Top;
            this.tabCtrlPanel.Location = new System.Drawing.Point(0, 28);
            this.tabCtrlPanel.Name = "tabCtrlPanel";
            this.tabCtrlPanel.SelectedIndex = 0;
            this.tabCtrlPanel.Size = new System.Drawing.Size(858, 595);
            this.tabCtrlPanel.TabIndex = 50;
            // 
            // tabSetup
            // 
            this.tabSetup.Controls.Add(this.groupBox1);
            this.tabSetup.Location = new System.Drawing.Point(4, 26);
            this.tabSetup.Name = "tabSetup";
            this.tabSetup.Padding = new System.Windows.Forms.Padding(3);
            this.tabSetup.Size = new System.Drawing.Size(850, 565);
            this.tabSetup.TabIndex = 0;
            this.tabSetup.Text = "Setup";
            this.tabSetup.UseVisualStyleBackColor = true;
            // 
            // tabControl
            // 
            this.tabControl.Controls.Add(this.btnReport);
            this.tabControl.Controls.Add(this.groupBox4);
            this.tabControl.Controls.Add(this.btnReset);
            this.tabControl.Location = new System.Drawing.Point(4, 26);
            this.tabControl.Name = "tabControl";
            this.tabControl.Padding = new System.Windows.Forms.Padding(3);
            this.tabControl.Size = new System.Drawing.Size(850, 565);
            this.tabControl.TabIndex = 1;
            this.tabControl.Text = "Control";
            this.tabControl.UseVisualStyleBackColor = true;
            // 
            // btnReport
            // 
            this.btnReport.Location = new System.Drawing.Point(719, 101);
            this.btnReport.Margin = new System.Windows.Forms.Padding(2);
            this.btnReport.Name = "btnReport";
            this.btnReport.Size = new System.Drawing.Size(110, 55);
            this.btnReport.TabIndex = 42;
            this.btnReport.Text = "Status ON";
            this.btnReport.UseVisualStyleBackColor = true;
            this.btnReport.Click += new System.EventHandler(this.btnReport_Click);
            // 
            // groupBox4
            // 
            this.groupBox4.Controls.Add(this.btnRotateLeft);
            this.groupBox4.Controls.Add(this.btnStart);
            this.groupBox4.Controls.Add(this.btnRotateRight);
            this.groupBox4.Controls.Add(this.btnMoveBR);
            this.groupBox4.Controls.Add(this.btnMoveFR);
            this.groupBox4.Controls.Add(this.btnMoveBL);
            this.groupBox4.Controls.Add(this.btnMoveFL);
            this.groupBox4.Controls.Add(this.btnMoveLeft);
            this.groupBox4.Controls.Add(this.btnMoveRight);
            this.groupBox4.Controls.Add(this.btnMoveBack);
            this.groupBox4.Controls.Add(this.btnMoveFront);
            this.groupBox4.Location = new System.Drawing.Point(223, 35);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Size = new System.Drawing.Size(372, 385);
            this.groupBox4.TabIndex = 41;
            this.groupBox4.TabStop = false;
            this.groupBox4.Text = "Remote Control";
            // 
            // btnRotateLeft
            // 
            this.btnRotateLeft.Location = new System.Drawing.Point(17, 267);
            this.btnRotateLeft.Margin = new System.Windows.Forms.Padding(2);
            this.btnRotateLeft.Name = "btnRotateLeft";
            this.btnRotateLeft.Size = new System.Drawing.Size(100, 40);
            this.btnRotateLeft.TabIndex = 43;
            this.btnRotateLeft.Text = "Rotate Left";
            this.btnRotateLeft.UseVisualStyleBackColor = true;
            this.btnRotateLeft.Click += new System.EventHandler(this.btnRotateLeft_Click);
            // 
            // btnRotateRight
            // 
            this.btnRotateRight.Location = new System.Drawing.Point(259, 267);
            this.btnRotateRight.Margin = new System.Windows.Forms.Padding(2);
            this.btnRotateRight.Name = "btnRotateRight";
            this.btnRotateRight.Size = new System.Drawing.Size(100, 40);
            this.btnRotateRight.TabIndex = 33;
            this.btnRotateRight.Text = "Rotate Right";
            this.btnRotateRight.UseVisualStyleBackColor = true;
            this.btnRotateRight.Click += new System.EventHandler(this.btnRotateRight_Click);
            // 
            // btnMoveBR
            // 
            this.btnMoveBR.Location = new System.Drawing.Point(259, 207);
            this.btnMoveBR.Margin = new System.Windows.Forms.Padding(2);
            this.btnMoveBR.Name = "btnMoveBR";
            this.btnMoveBR.Size = new System.Drawing.Size(100, 40);
            this.btnMoveBR.TabIndex = 42;
            this.btnMoveBR.Text = "Back Right";
            this.btnMoveBR.UseVisualStyleBackColor = true;
            this.btnMoveBR.Click += new System.EventHandler(this.btnMoveBR_Click);
            // 
            // btnMoveFR
            // 
            this.btnMoveFR.Location = new System.Drawing.Point(259, 81);
            this.btnMoveFR.Margin = new System.Windows.Forms.Padding(2);
            this.btnMoveFR.Name = "btnMoveFR";
            this.btnMoveFR.Size = new System.Drawing.Size(100, 40);
            this.btnMoveFR.TabIndex = 41;
            this.btnMoveFR.Text = "Front Right";
            this.btnMoveFR.UseVisualStyleBackColor = true;
            this.btnMoveFR.Click += new System.EventHandler(this.btnMoveFR_Click);
            // 
            // btnMoveBL
            // 
            this.btnMoveBL.Location = new System.Drawing.Point(17, 207);
            this.btnMoveBL.Margin = new System.Windows.Forms.Padding(2);
            this.btnMoveBL.Name = "btnMoveBL";
            this.btnMoveBL.Size = new System.Drawing.Size(100, 40);
            this.btnMoveBL.TabIndex = 39;
            this.btnMoveBL.Text = "Back Left";
            this.btnMoveBL.UseVisualStyleBackColor = true;
            this.btnMoveBL.Click += new System.EventHandler(this.btnMoveBL_Click);
            // 
            // btnMoveFL
            // 
            this.btnMoveFL.Location = new System.Drawing.Point(17, 81);
            this.btnMoveFL.Margin = new System.Windows.Forms.Padding(2);
            this.btnMoveFL.Name = "btnMoveFL";
            this.btnMoveFL.Size = new System.Drawing.Size(100, 40);
            this.btnMoveFL.TabIndex = 38;
            this.btnMoveFL.Text = "Front Left";
            this.btnMoveFL.UseVisualStyleBackColor = true;
            this.btnMoveFL.Click += new System.EventHandler(this.btnMoveFL_Click);
            // 
            // btnMoveLeft
            // 
            this.btnMoveLeft.Location = new System.Drawing.Point(17, 146);
            this.btnMoveLeft.Margin = new System.Windows.Forms.Padding(2);
            this.btnMoveLeft.Name = "btnMoveLeft";
            this.btnMoveLeft.Size = new System.Drawing.Size(100, 40);
            this.btnMoveLeft.TabIndex = 37;
            this.btnMoveLeft.Text = "Left";
            this.btnMoveLeft.UseVisualStyleBackColor = true;
            this.btnMoveLeft.Click += new System.EventHandler(this.btnMoveLeft_Click);
            // 
            // btnMoveRight
            // 
            this.btnMoveRight.Location = new System.Drawing.Point(259, 146);
            this.btnMoveRight.Margin = new System.Windows.Forms.Padding(2);
            this.btnMoveRight.Name = "btnMoveRight";
            this.btnMoveRight.Size = new System.Drawing.Size(100, 40);
            this.btnMoveRight.TabIndex = 36;
            this.btnMoveRight.Text = "Right";
            this.btnMoveRight.UseVisualStyleBackColor = true;
            this.btnMoveRight.Click += new System.EventHandler(this.btnMoveRight_Click);
            // 
            // btnMoveBack
            // 
            this.btnMoveBack.Location = new System.Drawing.Point(140, 317);
            this.btnMoveBack.Margin = new System.Windows.Forms.Padding(2);
            this.btnMoveBack.Name = "btnMoveBack";
            this.btnMoveBack.Size = new System.Drawing.Size(100, 40);
            this.btnMoveBack.TabIndex = 35;
            this.btnMoveBack.Text = "Backward";
            this.btnMoveBack.UseVisualStyleBackColor = true;
            this.btnMoveBack.Click += new System.EventHandler(this.btnMoveBack_Click);
            // 
            // btnMoveFront
            // 
            this.btnMoveFront.Location = new System.Drawing.Point(140, 30);
            this.btnMoveFront.Margin = new System.Windows.Forms.Padding(2);
            this.btnMoveFront.Name = "btnMoveFront";
            this.btnMoveFront.Size = new System.Drawing.Size(100, 40);
            this.btnMoveFront.TabIndex = 34;
            this.btnMoveFront.Text = "Forward";
            this.btnMoveFront.UseVisualStyleBackColor = true;
            this.btnMoveFront.Click += new System.EventHandler(this.btnMoveFront_Click);
            // 
            // tabPIDADJ
            // 
            this.tabPIDADJ.Controls.Add(this.groupBox8);
            this.tabPIDADJ.Controls.Add(this.groupBox7);
            this.tabPIDADJ.Controls.Add(this.groupBox6);
            this.tabPIDADJ.Controls.Add(this.labelPIDXY);
            this.tabPIDADJ.Controls.Add(this.PlotPID);
            this.tabPIDADJ.Location = new System.Drawing.Point(4, 26);
            this.tabPIDADJ.Name = "tabPIDADJ";
            this.tabPIDADJ.Size = new System.Drawing.Size(850, 565);
            this.tabPIDADJ.TabIndex = 4;
            this.tabPIDADJ.Text = "PID Adjustment";
            this.tabPIDADJ.UseVisualStyleBackColor = true;
            // 
            // groupBox8
            // 
            this.groupBox8.Controls.Add(this.btnPIDStart);
            this.groupBox8.Controls.Add(this.cBoxPIDDir);
            this.groupBox8.Controls.Add(this.btnSpeed);
            this.groupBox8.Location = new System.Drawing.Point(12, 447);
            this.groupBox8.Name = "groupBox8";
            this.groupBox8.Size = new System.Drawing.Size(335, 115);
            this.groupBox8.TabIndex = 64;
            this.groupBox8.TabStop = false;
            this.groupBox8.Text = "Control";
            // 
            // btnPIDStart
            // 
            this.btnPIDStart.Location = new System.Drawing.Point(117, 15);
            this.btnPIDStart.Name = "btnPIDStart";
            this.btnPIDStart.Size = new System.Drawing.Size(89, 35);
            this.btnPIDStart.TabIndex = 55;
            this.btnPIDStart.Text = "Start";
            this.btnPIDStart.UseVisualStyleBackColor = true;
            this.btnPIDStart.Click += new System.EventHandler(this.btnPIDStart_Click);
            // 
            // cBoxPIDDir
            // 
            this.cBoxPIDDir.FormattingEnabled = true;
            this.cBoxPIDDir.Items.AddRange(new object[] {
            "Forward",
            "Backward",
            "Left",
            "Right",
            "Front Left",
            "Front Right",
            "Back Left",
            "Back Right"});
            this.cBoxPIDDir.Location = new System.Drawing.Point(8, 21);
            this.cBoxPIDDir.Name = "cBoxPIDDir";
            this.cBoxPIDDir.Size = new System.Drawing.Size(103, 25);
            this.cBoxPIDDir.TabIndex = 54;
            // 
            // btnSpeed
            // 
            this.btnSpeed.Location = new System.Drawing.Point(212, 15);
            this.btnSpeed.Name = "btnSpeed";
            this.btnSpeed.Size = new System.Drawing.Size(91, 35);
            this.btnSpeed.TabIndex = 4;
            this.btnSpeed.Text = "Snyc";
            this.btnSpeed.UseVisualStyleBackColor = true;
            this.btnSpeed.Click += new System.EventHandler(this.btnSpeed_Click);
            // 
            // groupBox7
            // 
            this.groupBox7.Controls.Add(this.cBoxLogPID);
            this.groupBox7.Controls.Add(this.CBoxM4);
            this.groupBox7.Controls.Add(this.btnClearPIDPlot);
            this.groupBox7.Controls.Add(this.CBoxM3);
            this.groupBox7.Controls.Add(this.CBoxM2);
            this.groupBox7.Controls.Add(this.CBoxM1);
            this.groupBox7.Location = new System.Drawing.Point(12, 351);
            this.groupBox7.Name = "groupBox7";
            this.groupBox7.Size = new System.Drawing.Size(334, 90);
            this.groupBox7.TabIndex = 63;
            this.groupBox7.TabStop = false;
            this.groupBox7.Text = "Line Selection";
            // 
            // cBoxLogPID
            // 
            this.cBoxLogPID.AutoSize = true;
            this.cBoxLogPID.Location = new System.Drawing.Point(6, 48);
            this.cBoxLogPID.Name = "cBoxLogPID";
            this.cBoxLogPID.Size = new System.Drawing.Size(102, 21);
            this.cBoxLogPID.TabIndex = 62;
            this.cBoxLogPID.Text = "Log Enable";
            this.cBoxLogPID.UseVisualStyleBackColor = true;
            this.cBoxLogPID.CheckedChanged += new System.EventHandler(this.cBoxLogPID_CheckedChanged);
            // 
            // CBoxM4
            // 
            this.CBoxM4.AutoSize = true;
            this.CBoxM4.Location = new System.Drawing.Point(250, 21);
            this.CBoxM4.Name = "CBoxM4";
            this.CBoxM4.Size = new System.Drawing.Size(78, 21);
            this.CBoxM4.TabIndex = 61;
            this.CBoxM4.Text = "Motor 4";
            this.CBoxM4.UseVisualStyleBackColor = true;
            this.CBoxM4.CheckStateChanged += new System.EventHandler(this.CBoxM4_CheckStateChanged_1);
            // 
            // btnClearPIDPlot
            // 
            this.btnClearPIDPlot.Location = new System.Drawing.Point(212, 48);
            this.btnClearPIDPlot.Name = "btnClearPIDPlot";
            this.btnClearPIDPlot.Size = new System.Drawing.Size(91, 35);
            this.btnClearPIDPlot.TabIndex = 53;
            this.btnClearPIDPlot.Text = "Clear";
            this.btnClearPIDPlot.UseVisualStyleBackColor = true;
            this.btnClearPIDPlot.Click += new System.EventHandler(this.btnClearPIDPlot_Click);
            // 
            // CBoxM3
            // 
            this.CBoxM3.AutoSize = true;
            this.CBoxM3.Location = new System.Drawing.Point(166, 22);
            this.CBoxM3.Name = "CBoxM3";
            this.CBoxM3.Size = new System.Drawing.Size(78, 21);
            this.CBoxM3.TabIndex = 60;
            this.CBoxM3.Text = "Motor 3";
            this.CBoxM3.UseVisualStyleBackColor = true;
            this.CBoxM3.CheckStateChanged += new System.EventHandler(this.CBoxM3_CheckStateChanged_1);
            // 
            // CBoxM2
            // 
            this.CBoxM2.AutoSize = true;
            this.CBoxM2.Location = new System.Drawing.Point(82, 22);
            this.CBoxM2.Name = "CBoxM2";
            this.CBoxM2.Size = new System.Drawing.Size(78, 21);
            this.CBoxM2.TabIndex = 59;
            this.CBoxM2.Text = "Motor 2";
            this.CBoxM2.UseVisualStyleBackColor = true;
            this.CBoxM2.CheckStateChanged += new System.EventHandler(this.CBoxM2_CheckStateChanged_1);
            // 
            // CBoxM1
            // 
            this.CBoxM1.AutoSize = true;
            this.CBoxM1.Location = new System.Drawing.Point(6, 21);
            this.CBoxM1.Name = "CBoxM1";
            this.CBoxM1.Size = new System.Drawing.Size(78, 21);
            this.CBoxM1.TabIndex = 58;
            this.CBoxM1.Text = "Motor 1";
            this.CBoxM1.UseVisualStyleBackColor = true;
            this.CBoxM1.CheckStateChanged += new System.EventHandler(this.CBoxM1_CheckStateChanged_1);
            // 
            // groupBox6
            // 
            this.groupBox6.Controls.Add(this.labelInterval);
            this.groupBox6.Controls.Add(this.trackBarInterval);
            this.groupBox6.Controls.Add(this.labelRPM);
            this.groupBox6.Controls.Add(this.labelKD);
            this.groupBox6.Controls.Add(this.labelKI);
            this.groupBox6.Controls.Add(this.labelKP);
            this.groupBox6.Controls.Add(this.trackBarRPM);
            this.groupBox6.Controls.Add(this.trackBarKD);
            this.groupBox6.Controls.Add(this.trackBarKI);
            this.groupBox6.Controls.Add(this.trackBarKP);
            this.groupBox6.Location = new System.Drawing.Point(353, 351);
            this.groupBox6.Name = "groupBox6";
            this.groupBox6.Size = new System.Drawing.Size(494, 211);
            this.groupBox6.TabIndex = 62;
            this.groupBox6.TabStop = false;
            this.groupBox6.Text = "Parameters";
            // 
            // labelInterval
            // 
            this.labelInterval.AutoSize = true;
            this.labelInterval.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(192)))), ((int)(((byte)(255)))), ((int)(((byte)(192)))));
            this.labelInterval.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.labelInterval.Location = new System.Drawing.Point(6, 168);
            this.labelInterval.Name = "labelInterval";
            this.labelInterval.Size = new System.Drawing.Size(68, 20);
            this.labelInterval.TabIndex = 70;
            this.labelInterval.Text = "Interval:";
            // 
            // trackBarInterval
            // 
            this.trackBarInterval.AutoSize = false;
            this.trackBarInterval.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(192)))), ((int)(((byte)(255)))), ((int)(((byte)(192)))));
            this.trackBarInterval.Location = new System.Drawing.Point(146, 168);
            this.trackBarInterval.Maximum = 1000;
            this.trackBarInterval.Name = "trackBarInterval";
            this.trackBarInterval.Size = new System.Drawing.Size(320, 30);
            this.trackBarInterval.TabIndex = 69;
            this.trackBarInterval.ValueChanged += new System.EventHandler(this.trackBarInterval_ValueChanged);
            this.trackBarInterval.KeyUp += new System.Windows.Forms.KeyEventHandler(this.trackBarInterval_KeyUp);
            this.trackBarInterval.MouseUp += new System.Windows.Forms.MouseEventHandler(this.trackBarInterval_MouseUp);
            // 
            // labelRPM
            // 
            this.labelRPM.AutoSize = true;
            this.labelRPM.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(255)))), ((int)(((byte)(192)))));
            this.labelRPM.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.labelRPM.Location = new System.Drawing.Point(6, 132);
            this.labelRPM.Name = "labelRPM";
            this.labelRPM.Size = new System.Drawing.Size(51, 20);
            this.labelRPM.TabIndex = 68;
            this.labelRPM.Text = "RPM:";
            // 
            // labelKD
            // 
            this.labelKD.AutoSize = true;
            this.labelKD.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(192)))), ((int)(((byte)(255)))));
            this.labelKD.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.labelKD.Location = new System.Drawing.Point(6, 96);
            this.labelKD.Name = "labelKD";
            this.labelKD.Size = new System.Drawing.Size(38, 20);
            this.labelKD.TabIndex = 67;
            this.labelKD.Text = "KD:";
            // 
            // labelKI
            // 
            this.labelKI.AutoSize = true;
            this.labelKI.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(192)))), ((int)(((byte)(192)))));
            this.labelKI.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.labelKI.Location = new System.Drawing.Point(6, 60);
            this.labelKI.Name = "labelKI";
            this.labelKI.Size = new System.Drawing.Size(29, 20);
            this.labelKI.TabIndex = 66;
            this.labelKI.Text = "KI:";
            // 
            // labelKP
            // 
            this.labelKP.AutoSize = true;
            this.labelKP.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(192)))), ((int)(((byte)(255)))), ((int)(((byte)(255)))));
            this.labelKP.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.labelKP.Location = new System.Drawing.Point(6, 24);
            this.labelKP.Name = "labelKP";
            this.labelKP.Size = new System.Drawing.Size(36, 20);
            this.labelKP.TabIndex = 63;
            this.labelKP.Text = "KP:";
            // 
            // trackBarRPM
            // 
            this.trackBarRPM.AutoSize = false;
            this.trackBarRPM.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(255)))), ((int)(((byte)(192)))));
            this.trackBarRPM.Location = new System.Drawing.Point(146, 132);
            this.trackBarRPM.Maximum = 200;
            this.trackBarRPM.Name = "trackBarRPM";
            this.trackBarRPM.Size = new System.Drawing.Size(320, 30);
            this.trackBarRPM.TabIndex = 65;
            this.trackBarRPM.ValueChanged += new System.EventHandler(this.trackBarRPM_ValueChanged);
            this.trackBarRPM.KeyUp += new System.Windows.Forms.KeyEventHandler(this.trackBarRPM_KeyUp);
            this.trackBarRPM.MouseUp += new System.Windows.Forms.MouseEventHandler(this.trackBarRPM_MouseUp);
            // 
            // trackBarKD
            // 
            this.trackBarKD.AutoSize = false;
            this.trackBarKD.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(192)))), ((int)(((byte)(255)))));
            this.trackBarKD.Location = new System.Drawing.Point(146, 96);
            this.trackBarKD.Maximum = 500;
            this.trackBarKD.Name = "trackBarKD";
            this.trackBarKD.Size = new System.Drawing.Size(320, 30);
            this.trackBarKD.TabIndex = 64;
            this.trackBarKD.ValueChanged += new System.EventHandler(this.trackBarKD_ValueChanged);
            this.trackBarKD.KeyUp += new System.Windows.Forms.KeyEventHandler(this.trackBarKD_KeyUp);
            this.trackBarKD.MouseUp += new System.Windows.Forms.MouseEventHandler(this.trackBarKD_MouseUp);
            // 
            // trackBarKI
            // 
            this.trackBarKI.AutoSize = false;
            this.trackBarKI.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(192)))), ((int)(((byte)(192)))));
            this.trackBarKI.Location = new System.Drawing.Point(146, 60);
            this.trackBarKI.Maximum = 500;
            this.trackBarKI.Name = "trackBarKI";
            this.trackBarKI.Size = new System.Drawing.Size(320, 30);
            this.trackBarKI.TabIndex = 63;
            this.trackBarKI.ValueChanged += new System.EventHandler(this.trackBarKI_ValueChanged);
            this.trackBarKI.KeyUp += new System.Windows.Forms.KeyEventHandler(this.trackBarKI_KeyUp);
            this.trackBarKI.MouseUp += new System.Windows.Forms.MouseEventHandler(this.trackBarKI_MouseUp);
            // 
            // trackBarKP
            // 
            this.trackBarKP.AutoSize = false;
            this.trackBarKP.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(192)))), ((int)(((byte)(255)))), ((int)(((byte)(255)))));
            this.trackBarKP.Location = new System.Drawing.Point(146, 24);
            this.trackBarKP.Maximum = 500;
            this.trackBarKP.Name = "trackBarKP";
            this.trackBarKP.Size = new System.Drawing.Size(320, 30);
            this.trackBarKP.TabIndex = 62;
            this.trackBarKP.ValueChanged += new System.EventHandler(this.trackBarKP_ValueChanged);
            this.trackBarKP.KeyUp += new System.Windows.Forms.KeyEventHandler(this.trackBarKP_KeyUp);
            this.trackBarKP.MouseUp += new System.Windows.Forms.MouseEventHandler(this.trackBarKP_MouseUp);
            // 
            // labelPIDXY
            // 
            this.labelPIDXY.AutoSize = true;
            this.labelPIDXY.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.labelPIDXY.Location = new System.Drawing.Point(542, 313);
            this.labelPIDXY.Name = "labelPIDXY";
            this.labelPIDXY.Size = new System.Drawing.Size(41, 20);
            this.labelPIDXY.TabIndex = 53;
            this.labelPIDXY.Text = "(x,y)";
            // 
            // PlotPID
            // 
            chartArea2.AxisX.LineColor = System.Drawing.Color.Gray;
            chartArea2.AxisX.LineDashStyle = System.Windows.Forms.DataVisualization.Charting.ChartDashStyle.Dot;
            chartArea2.AxisX.MajorGrid.LineColor = System.Drawing.Color.Gray;
            chartArea2.AxisX.MajorGrid.LineDashStyle = System.Windows.Forms.DataVisualization.Charting.ChartDashStyle.Dash;
            chartArea2.AxisX2.LineColor = System.Drawing.Color.Red;
            chartArea2.AxisX2.LineDashStyle = System.Windows.Forms.DataVisualization.Charting.ChartDashStyle.Dot;
            chartArea2.AxisY.LineColor = System.Drawing.Color.Gray;
            chartArea2.AxisY.LineDashStyle = System.Windows.Forms.DataVisualization.Charting.ChartDashStyle.Dot;
            chartArea2.AxisY.MajorGrid.LineColor = System.Drawing.Color.Gray;
            chartArea2.AxisY.MajorGrid.LineDashStyle = System.Windows.Forms.DataVisualization.Charting.ChartDashStyle.Dash;
            chartArea2.AxisY.MaximumAutoSize = 100F;
            chartArea2.AxisY2.LineColor = System.Drawing.Color.Chartreuse;
            chartArea2.AxisY2.LineDashStyle = System.Windows.Forms.DataVisualization.Charting.ChartDashStyle.Dot;
            chartArea2.BorderColor = System.Drawing.Color.Gray;
            chartArea2.BorderDashStyle = System.Windows.Forms.DataVisualization.Charting.ChartDashStyle.Dash;
            chartArea2.CursorX.IsUserEnabled = true;
            chartArea2.CursorX.LineColor = System.Drawing.Color.FromArgb(((int)(((byte)(128)))), ((int)(((byte)(255)))), ((int)(((byte)(128)))));
            chartArea2.CursorY.IsUserEnabled = true;
            chartArea2.CursorY.LineColor = System.Drawing.Color.FromArgb(((int)(((byte)(128)))), ((int)(((byte)(255)))), ((int)(((byte)(128)))));
            chartArea2.IsSameFontSizeForAllAxes = true;
            chartArea2.Name = "ChartArea1";
            this.PlotPID.ChartAreas.Add(chartArea2);
            this.PlotPID.Cursor = System.Windows.Forms.Cursors.Cross;
            legend2.Docking = System.Windows.Forms.DataVisualization.Charting.Docking.Bottom;
            legend2.Name = "Motor 1";
            this.PlotPID.Legends.Add(legend2);
            this.PlotPID.Location = new System.Drawing.Point(7, 0);
            this.PlotPID.Margin = new System.Windows.Forms.Padding(2);
            this.PlotPID.Name = "PlotPID";
            series3.ChartArea = "ChartArea1";
            series3.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Line;
            series3.Color = System.Drawing.Color.Red;
            series3.Legend = "Motor 1";
            series3.MarkerBorderColor = System.Drawing.Color.Lime;
            series3.MarkerColor = System.Drawing.Color.Lime;
            series3.Name = "Motor 1";
            series4.ChartArea = "ChartArea1";
            series4.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Line;
            series4.Legend = "Motor 1";
            series4.MarkerBorderColor = System.Drawing.Color.Blue;
            series4.MarkerColor = System.Drawing.Color.Blue;
            series4.Name = "Motor 2";
            series5.ChartArea = "ChartArea1";
            series5.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Line;
            series5.Legend = "Motor 1";
            series5.MarkerBorderColor = System.Drawing.Color.Brown;
            series5.MarkerColor = System.Drawing.Color.FromArgb(((int)(((byte)(192)))), ((int)(((byte)(0)))), ((int)(((byte)(0)))));
            series5.Name = "Motor 3";
            series6.ChartArea = "ChartArea1";
            series6.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Line;
            series6.Legend = "Motor 1";
            series6.Name = "Motor 4";
            this.PlotPID.Series.Add(series3);
            this.PlotPID.Series.Add(series4);
            this.PlotPID.Series.Add(series5);
            this.PlotPID.Series.Add(series6);
            this.PlotPID.Size = new System.Drawing.Size(841, 346);
            this.PlotPID.TabIndex = 26;
            this.PlotPID.Text = "chart1";
            this.PlotPID.MouseMove += new System.Windows.Forms.MouseEventHandler(this.PlotPID_MouseMove);
            // 
            // tabCal
            // 
            this.tabCal.Controls.Add(this.groupBox5);
            this.tabCal.Location = new System.Drawing.Point(4, 26);
            this.tabCal.Name = "tabCal";
            this.tabCal.Padding = new System.Windows.Forms.Padding(3);
            this.tabCal.Size = new System.Drawing.Size(850, 565);
            this.tabCal.TabIndex = 2;
            this.tabCal.Text = "Calibration";
            this.tabCal.UseVisualStyleBackColor = true;
            // 
            // tabMap
            // 
            this.tabMap.Controls.Add(this.btnSaveMap);
            this.tabMap.Controls.Add(this.btnLoad);
            this.tabMap.Controls.Add(this.btnClearMap);
            this.tabMap.Controls.Add(this.btnClearPlot);
            this.tabMap.Controls.Add(this.label6);
            this.tabMap.Controls.Add(this.groupBox2);
            this.tabMap.Controls.Add(this.groupBox3);
            this.tabMap.Controls.Add(this.PlotDisp);
            this.tabMap.Location = new System.Drawing.Point(4, 26);
            this.tabMap.Name = "tabMap";
            this.tabMap.Padding = new System.Windows.Forms.Padding(3);
            this.tabMap.Size = new System.Drawing.Size(850, 565);
            this.tabMap.TabIndex = 3;
            this.tabMap.Text = "IPS Map";
            this.tabMap.UseVisualStyleBackColor = true;
            // 
            // btnSaveMap
            // 
            this.btnSaveMap.Location = new System.Drawing.Point(383, 460);
            this.btnSaveMap.Margin = new System.Windows.Forms.Padding(2);
            this.btnSaveMap.Name = "btnSaveMap";
            this.btnSaveMap.Size = new System.Drawing.Size(99, 28);
            this.btnSaveMap.TabIndex = 43;
            this.btnSaveMap.Text = "Save Map";
            this.btnSaveMap.UseVisualStyleBackColor = true;
            this.btnSaveMap.Click += new System.EventHandler(this.btnSaveMap_Click);
            // 
            // btnLoad
            // 
            this.btnLoad.Location = new System.Drawing.Point(383, 428);
            this.btnLoad.Margin = new System.Windows.Forms.Padding(2);
            this.btnLoad.Name = "btnLoad";
            this.btnLoad.Size = new System.Drawing.Size(99, 28);
            this.btnLoad.TabIndex = 42;
            this.btnLoad.Text = "Load Map";
            this.btnLoad.UseVisualStyleBackColor = true;
            this.btnLoad.Click += new System.EventHandler(this.btnLoad_Click);
            // 
            // btnUrgentStop
            // 
            this.btnUrgentStop.BackColor = System.Drawing.Color.Red;
            this.btnUrgentStop.Location = new System.Drawing.Point(749, 636);
            this.btnUrgentStop.Margin = new System.Windows.Forms.Padding(2);
            this.btnUrgentStop.Name = "btnUrgentStop";
            this.btnUrgentStop.Size = new System.Drawing.Size(103, 55);
            this.btnUrgentStop.TabIndex = 42;
            this.btnUrgentStop.Text = "Emergency Stop";
            this.btnUrgentStop.UseVisualStyleBackColor = false;
            this.btnUrgentStop.Click += new System.EventHandler(this.btnUrgentStop_Click);
            // 
            // timer1
            // 
            this.timer1.Interval = 3000;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // labelSpeed
            // 
            this.labelSpeed.AutoSize = true;
            this.labelSpeed.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.labelSpeed.Location = new System.Drawing.Point(12, 629);
            this.labelSpeed.Name = "labelSpeed";
            this.labelSpeed.Size = new System.Drawing.Size(147, 25);
            this.labelSpeed.TabIndex = 51;
            this.labelSpeed.Text = "Current RPM: 0";
            // 
            // DialogBrowse
            // 
            this.DialogBrowse.FileName = "Map.txt";
            // 
            // DialogSave
            // 
            this.DialogSave.FileName = "Map.txt";
            // 
            // labelOpr
            // 
            this.labelOpr.AutoSize = true;
            this.labelOpr.Location = new System.Drawing.Point(617, 709);
            this.labelOpr.Name = "labelOpr";
            this.labelOpr.Size = new System.Drawing.Size(125, 17);
            this.labelOpr.TabIndex = 49;
            this.labelOpr.Text = "Last Operation: ---";
            // 
            // menuStrip1
            // 
            this.menuStrip1.ImageScalingSize = new System.Drawing.Size(20, 20);
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem,
            this.helpToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(858, 28);
            this.menuStrip1.TabIndex = 52;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(44, 24);
            this.fileToolStripMenuItem.Text = "File";
            // 
            // helpToolStripMenuItem
            // 
            this.helpToolStripMenuItem.Name = "helpToolStripMenuItem";
            this.helpToolStripMenuItem.Size = new System.Drawing.Size(53, 24);
            this.helpToolStripMenuItem.Text = "Help";
            this.helpToolStripMenuItem.Click += new System.EventHandler(this.helpToolStripMenuItem_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 17F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(858, 734);
            this.Controls.Add(this.labelOpr);
            this.Controls.Add(this.labelSpeed);
            this.Controls.Add(this.btnUrgentStop);
            this.Controls.Add(this.tabCtrlPanel);
            this.Controls.Add(this.labelCurXY);
            this.Controls.Add(this.labelInfo);
            this.Controls.Add(this.stsStripDisplay);
            this.Controls.Add(this.menuStrip1);
            this.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "Form1";
            this.Text = "SEP200/SEP250 [SEEMS]";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.Form1_FormClosed);
            this.Load += new System.EventHandler(this.Form1_Load);
            this.stsStripDisplay.ResumeLayout(false);
            this.stsStripDisplay.PerformLayout();
            this.groupBox1.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.PlotDisp)).EndInit();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.groupBox5.ResumeLayout(false);
            this.groupBox5.PerformLayout();
            this.tabCtrlPanel.ResumeLayout(false);
            this.tabSetup.ResumeLayout(false);
            this.tabControl.ResumeLayout(false);
            this.groupBox4.ResumeLayout(false);
            this.tabPIDADJ.ResumeLayout(false);
            this.tabPIDADJ.PerformLayout();
            this.groupBox8.ResumeLayout(false);
            this.groupBox7.ResumeLayout(false);
            this.groupBox7.PerformLayout();
            this.groupBox6.ResumeLayout(false);
            this.groupBox6.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarInterval)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarRPM)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarKD)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarKI)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarKP)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.PlotPID)).EndInit();
            this.tabCal.ResumeLayout(false);
            this.tabMap.ResumeLayout(false);
            this.tabMap.PerformLayout();
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ComboBox cboxBaud;
        private System.Windows.Forms.Button btnConnect;
        private System.Windows.Forms.ComboBox cboxComPort;
        private System.Windows.Forms.StatusStrip stsStripDisplay;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel1;
        private System.Windows.Forms.ToolStripProgressBar toolStripProgressBar1;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label labelInfo;
        private System.Windows.Forms.DataVisualization.Charting.Chart PlotDisp;
        private System.Windows.Forms.Button btnReset;
        private System.Windows.Forms.Button btnSet;
        private System.Windows.Forms.Button btnStart;
        private System.Windows.Forms.Button btnMap;
        private System.Windows.Forms.TextBox textPointX;
        private System.Windows.Forms.TextBox textPointY;
        private System.Windows.Forms.Label labelRoute;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button btnClearMap;
        private System.Windows.Forms.Label labelCurXY;
        private System.Windows.Forms.ToolStripStatusLabel statuslabelReport;
        private System.Windows.Forms.GroupBox groupBox5;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox txtRefY3;
        private System.Windows.Forms.TextBox txtRefX3;
        private System.Windows.Forms.TextBox txtRefY2;
        private System.Windows.Forms.TextBox txtRefX2;
        private System.Windows.Forms.TextBox txtRefY1;
        private System.Windows.Forms.TextBox txtRefX1;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Button btnRefSet;
        private System.Windows.Forms.Button btnClearPlot;
        private System.Windows.Forms.Button btnCal;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.TabControl tabCtrlPanel;
        private System.Windows.Forms.TabPage tabSetup;
        private System.Windows.Forms.TabPage tabCal;
        private System.Windows.Forms.TabPage tabMap;
        private System.Windows.Forms.Button btnMapStart;
        private System.Windows.Forms.Button btnUrgentStop;
        private System.Windows.Forms.Button btnCOMRefresh;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.GroupBox groupBox4;
        private System.Windows.Forms.Button btnRotateLeft;
        private System.Windows.Forms.Button btnRotateRight;
        private System.Windows.Forms.Button btnMoveBR;
        private System.Windows.Forms.Button btnMoveFR;
        private System.Windows.Forms.Button btnMoveBL;
        private System.Windows.Forms.Button btnMoveFL;
        private System.Windows.Forms.Button btnMoveLeft;
        private System.Windows.Forms.Button btnMoveRight;
        private System.Windows.Forms.Button btnMoveBack;
        private System.Windows.Forms.Button btnMoveFront;
        private System.Windows.Forms.TabPage tabControl;
        private System.Windows.Forms.Button btnReport;
        private System.Windows.Forms.Label labelSpeed;
        private System.Windows.Forms.Button btnLoad;
        private System.Windows.Forms.OpenFileDialog DialogBrowse;
        private System.Windows.Forms.Button btnSaveMap;
        private System.Windows.Forms.SaveFileDialog DialogSave;
        private System.Windows.Forms.TabPage tabPIDADJ;
        private System.Windows.Forms.DataVisualization.Charting.Chart PlotPID;
        private System.Windows.Forms.Button btnSpeed;
        private System.Windows.Forms.Button btnClearPIDPlot;
        private System.Windows.Forms.Label labelPIDXY;
        private System.Windows.Forms.GroupBox groupBox6;
        private System.Windows.Forms.Label labelRPM;
        private System.Windows.Forms.Label labelKD;
        private System.Windows.Forms.Label labelKI;
        private System.Windows.Forms.Label labelKP;
        private System.Windows.Forms.TrackBar trackBarRPM;
        private System.Windows.Forms.TrackBar trackBarKD;
        private System.Windows.Forms.TrackBar trackBarKI;
        private System.Windows.Forms.TrackBar trackBarKP;
        private System.Windows.Forms.Label labelOpr;
        private System.Windows.Forms.Label labelInterval;
        private System.Windows.Forms.TrackBar trackBarInterval;
        private System.Windows.Forms.GroupBox groupBox8;
        private System.Windows.Forms.GroupBox groupBox7;
        private System.Windows.Forms.CheckBox CBoxM4;
        private System.Windows.Forms.CheckBox CBoxM3;
        private System.Windows.Forms.CheckBox CBoxM2;
        private System.Windows.Forms.CheckBox CBoxM1;
        private System.Windows.Forms.CheckBox cBoxLogPID;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem helpToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ComboBox cBoxPIDDir;
        private System.Windows.Forms.Button btnPIDStart;
    }
}

