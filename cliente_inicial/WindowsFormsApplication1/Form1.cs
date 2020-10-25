using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Net;
using System.Net.Sockets;

namespace WindowsFormsApplication1
{
    public partial class Form1 : Form
    {
        Socket server;
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

           
        }

   
        private void button2_Click(object sender, EventArgs e)
        {
                //Miramos los radio buttons
                if (Longitud.Checked) //En este caso  si el radio button de longitud está activo
                {
                    // Quiere saber la longitud
                    string mensaje = "1/" + nombre.Text;
                    // Enviamos al servidor el nombre tecleado
                    byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje);//Tenemos que enviar un vector de bytes
                    server.Send(msg);//Lo enviamos por el socket

                    //Recibimos la respuesta del servidor
                    byte[] msg2 = new byte[80];//La respuesta será un vector de bytes
                    server.Receive(msg2);
                    mensaje = Encoding.ASCII.GetString(msg2).Split('\0')[0];
                    //Convertir el vector de bytes en string, este string esté partido en el stio que está al final de string
                    //y se queda el primer trozo
                    MessageBox.Show("La longitud de tu nombre es: " + mensaje);
                }
                else if (Bonito.Checked) //Para el servicio numero 2
                {
                    // Quiere saber si el nombre es bonito
                    string mensaje = "2/" + nombre.Text;
                    // Enviamos al servidor el nombre tecleado
                    byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
                    server.Send(msg);

                    //Recibimos la respuesta del servidor
                    byte[] msg2 = new byte[80];
                    server.Receive(msg2);
                    mensaje = Encoding.ASCII.GetString(msg2).Split('\0')[0];


                    if (mensaje == "SI")
                        MessageBox.Show("Tu nombre ES bonito.");
                    else
                        MessageBox.Show("Tu nombre NO bonito. Lo siento.");


                }

                else
                {
                    //Enviamos nombre y altura
                    string mensaje = "3/" + nombre.Text + "/" + textBox1.Text;
                    //Enviamos al servidor el nombre tecleado
                    byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
                    server.Send(msg);

                    //Recibimos la respuesta del servidor
                    byte[] msg2 = new byte[80];//La respuesta será un vector de bytes
                    server.Receive(msg2);
                    mensaje = Encoding.ASCII.GetString(msg2).Split('\0')[0];
                    //Convertir el vector de bytes en string, este string esté partido en el stio que está al final de string
                    //y se queda el primer trozo
                    MessageBox.Show(mensaje);

                }
            }

        private void button3_Click(object sender, EventArgs e)
        {
            //Mensaje de desconexión
            string mensaje = "0/";

            byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
            server.Send(msg);

            //Nos desconectamos
            this.BackColor = Color.Gray;
            server.Shutdown(SocketShutdown.Both);
            server.Close();
        }
        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void button1_Click_1(object sender, EventArgs e)
        {

            //Creamos un IPEndPoint con el ip del servidor y puerto del servidor 
            //al que deseamos conectarnos
            IPAddress direc = IPAddress.Parse("192.168.56.102");//Asginamos la dirección IP del servidor
            IPEndPoint ipep = new IPEndPoint(direc, 9050);//Puerto que estará escuchando el servidor


            //Creamos el socket 
            server = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            try
            {
                server.Connect(ipep);//Intentamos conectar el socket
                this.BackColor = Color.Green;//Pondremos el formulario en verde
            }

            catch (SocketException ex)
            {
                //Si hay excepciones imrpimimos error y salimos del programa con return
                MessageBox.Show("No se ha podido establecer conexión con el servidor");
                return;
            }
        }

   

     
    }
}
