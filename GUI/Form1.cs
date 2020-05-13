using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;

namespace serial
{
    public partial class Form1 : Form
    {
        
        string dataIIN;
        int dataOUT;
        public Form1()
        {
            InitializeComponent();
            getAvailablePorts();
        }

        void getAvailablePorts()
        {
            String[] ports = SerialPort.GetPortNames();
            comboBox1.Items.AddRange(ports);
        }



        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                if (comboBox1.Text == "" || comboBox2.Text == "")
                {
                    string message = "Please select Port/Baud Rate settings";
                    string title = "                       Warning";
                    MessageBox.Show(message, title, MessageBoxButtons.OK, MessageBoxIcon.Warning);
                }
                else
                {
                    serialPort1.PortName = comboBox1.Text;
                    serialPort1.BaudRate = Convert.ToInt32(comboBox2.Text);
                    serialPort1.Open();
                    progressBar1.Value = 100;
                    button1.Enabled = false;
                    button2.Enabled = true;
                   
                    tb_RD.Enabled = true;
                    button4.Enabled = true;

                }
            }
            catch (UnauthorizedAccessException)
            {
                tb_RD.Text = "Unauthorized Access";
                string message = "Unauthorized Access";
                string title = "                       Warning";
                MessageBox.Show(message, title, MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }
        //read -> byte to int 
        //write -> int to byte

        private void comboBox2_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void Form1_Load(object sender, EventArgs e)
        {
            button1.Enabled = true;
            button2.Enabled = false;
            
            tb_RD.Enabled = false;
            
            button4.Enabled = false;

        }

        private void button2_Click(object sender, EventArgs e)
        {
            serialPort1.Close();
            progressBar1.Value = 0;
            button1.Enabled = true;
            button2.Enabled = false;
            
            tb_RD.Enabled = false;
            
            button4.Enabled = false;

        }

        private void button4_Click(object sender, EventArgs e)
        {
            try
            {
                while(true){
                    //int string, byte,int,string,output 
                    int dataIIN = serialPort1.ReadByte();
                    Console.WriteLine(dataIIN);
                    tb_RD.Text = dataIIN.ToString();
                    if (dataIIN != 0)
                    {
                        tb_RD.Text = dataIIN.ToString();

                    }
                }

            }
            catch (TimeoutException)
            {
                string message = "Timeout Exception";
                string title = "                       Error";
                MessageBox.Show(message, title, MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
        }

        private void Label3_Click(object sender, EventArgs e)
        {

        }

        

    }
}