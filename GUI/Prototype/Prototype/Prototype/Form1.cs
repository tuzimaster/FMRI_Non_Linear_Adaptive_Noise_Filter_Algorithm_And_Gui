using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Diagnostics;
using System.IO;
using System.Windows.Forms.DataVisualization.Charting;
using System.Threading;

namespace Prototype
{
    public partial class Form1 : Form
    {
        Boolean up = true;

        public Form1()
        {
            InitializeComponent();
            
        }

        Boolean switch1 = true;

        private void button2_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Choose the original input file.");
            openFileDialog1.ShowDialog();
            
            StreamReader sr = new StreamReader(openFileDialog1.FileName);

            MessageBox.Show("Choose the output file.");
            openFileDialog1.ShowDialog();
            StreamReader sr2 = new StreamReader(openFileDialog1.FileName);

            while (!sr2.EndOfStream)
            {
                string line = sr2.ReadLine();
                string[] lineb = line.Split('\t');

                if (!String.IsNullOrEmpty(line) && Int16.Parse(lineb[0]) == Int16.Parse(numericUpDown1.Value.ToString()))
                {
                    while (!sr.EndOfStream)
                    {
                        string line2 = sr.ReadLine();
                        string[] line2b = line2.Split('\t');

                        if (!String.IsNullOrEmpty(line2) && Int16.Parse(line2b[0]) == Int16.Parse(numericUpDown1.Value.ToString()))
                        {
                            textBox3.Text = line;
                            textBox4.Text = line2;
                            sr.Close();
                            sr2.Close();

                            drawGraph(lineb, line2b);

                            return;
                        }
                    }
                }
            }
        }

        private void drawGraph(string[] lineb, string[] line2b)
        {
            int i = 0;

            double max = 0;
            double min = 0;
            double parseresult = 0;
            this.chart1.Series["Original"].Points.Clear();
            this.chart1.Series["Modified"].Points.Clear();
            foreach (string a in lineb)
            {
                try
                {
                    parseresult = double.Parse(a);
                    if (parseresult < min && i > 3)
                    {
                        min = parseresult;
                    }

                    parseresult = double.Parse(a);

                    if (parseresult > max && i > 3)
                    {
                        max = parseresult;
                    }
                }
                catch
                {

                }
            }

            foreach (string a in line2b)
            {
                
                try
                {
                    parseresult = double.Parse(a);
                    if (parseresult < min && i > 3)
                    {
                        min = parseresult;
                    }

                    parseresult = double.Parse(a);

                    if (parseresult > max && i > 3)
                    {
                        max = parseresult;
                    }
                }
                catch
                {

                }
            }

            foreach(string a in lineb)
            {
                if(!String.IsNullOrEmpty(a) && i > 3)
                {
                    this.chart1.Series["Original"].Points.AddXY((double)(i-3), double.Parse(a) );
                }

                i++;
            }

            chart1.Series["Original"].ChartType =
                        SeriesChartType.FastLine;
            chart1.Series["Original"].Color = Color.Red;

            i = 0;

            foreach (string a in line2b)
            {
                if (!String.IsNullOrEmpty(a) && i > 3)
                {
                    chart1.Series["Modified"].Points.AddXY((double)(i-3),double.Parse(a));
                }

                i++;
            }

            chart1.Series["Modified"].ChartType =
            SeriesChartType.FastLine;
            chart1.Series["Modified"].Color = Color.Blue;
            
            chart1.ChartAreas["ChartArea1"].AxisX.Minimum = 0;
            chart1.ChartAreas["ChartArea1"].AxisX.Maximum = 100;
            chart1.ChartAreas["ChartArea1"].AxisX.Interval = 1;

            chart1.ChartAreas["ChartArea1"].AxisY.Minimum = min-10;
            chart1.ChartAreas["ChartArea1"].AxisY.Maximum = max+10;
            chart1.ChartAreas["ChartArea1"].AxisY.Interval = 1;
            
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (String.IsNullOrEmpty(comboBox1.SelectedItem.ToString()) || String.IsNullOrEmpty(textBox2.Text))
            {
                MessageBox.Show("Please set the standard deviation or windows size before proceeding.");
                return;
            }

            openFileDialog1.ShowDialog();
            string inputFile = openFileDialog1.FileName;

            try
            {
                Int16.Parse(textBox2.Text);
            }
            catch
            {
                MessageBox.Show("Standard Deviation is not an integer!");
                return;
            }

            Boolean pass = true;
            try
            {
                button1.Enabled = false;
                button2.Enabled = false;
                textBox2.Enabled = false;
                textBox3.Enabled = false;
                textBox4.Enabled = false;
                numericUpDown1.Enabled = false;
                comboBox1.Enabled = false;

                progressBar1.Visible = true;

                timer.Tick += new EventHandler(timer_Tick);
                timer.Interval = 100;
                timer.Enabled = true;

                string[] args = new string[4];
                args[0] = inputFile;
                args[1] = comboBox1.SelectedItem.ToString();
                args[2] = textBox2.Text;
                args[3] = "True";
                MessageBox.Show("Starting Process...");
                backgroundWorker1.RunWorkerAsync(args);
            }
            catch
            {
            }
        }

        public static void InitializeThread(object messageObj1)
        {

        }

        void timer_Tick(object sender, EventArgs e)
        {
            if (up && this.progressBar1.Value < 100)
            {
                this.progressBar1.Value += 1;
            }
            else
            {
                up = false;

                if (this.progressBar1.Value > 0)
                {
                    this.progressBar1.Value -= 1;
                }
                else
                {
                    up = true;
                    this.progressBar1.Value += 1;
                }
            }
        }

        private void backgroundWorker1_DoWork(object sender, DoWorkEventArgs e)
        {
            System.Diagnostics.ProcessStartInfo psi = new System.Diagnostics.ProcessStartInfo();
            psi.FileName = "C:\\Project1.exe";

            psi.CreateNoWindow = true;
            //psi.WindowStyle = System.Diagnostics.ProcessWindowStyle.Hidden;
            psi.UseShellExecute = false;
            psi.Arguments = ((string[])e.Argument)[0] + " " + " " + ((string[])e.Argument)[1] + "  " + ((string[])e.Argument)[2];

            using (Process exeProcess = Process.Start(psi))
            {
                exeProcess.WaitForExit();
            }
        }

        private void backgroundWorker1_RunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e)
        {
            MessageBox.Show("Process completed successfully.");

            progressBar1.Visible = false;
            timer.Enabled = false;
            button1.Enabled = true;
            button2.Enabled = true;
            textBox2.Enabled = true;
            textBox3.Enabled = true;
            textBox4.Enabled = true;
            numericUpDown1.Enabled = true;
            comboBox1.Enabled = true;
        }
    }
}
