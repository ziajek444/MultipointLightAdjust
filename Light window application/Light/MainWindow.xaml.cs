using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Threading.Tasks;
using System.Windows.Threading;

namespace Light
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        #region Init
        ComWrapper Connection = new ComWrapper();
        String SendBuffor = "";
        int good = 0;
        String Frame="";
        int flaga = 0; // 1 -> szukam b ; 0-> czekam na PC0 ; 2 -> czekam na refresh ; 
        string s_help;
        bool INIT = true; //Checkboxy ; 
        int tooMuch = 0;
        bool DebugButtonState = true; //Wskazuje czy tryb dla developera jest włączony czy nie. true oznacza włączony, false wyłączony. Zmieniany przyciskiem DebugButton. Włączony tryb developerski oznacza ze bloki ReceiveBlock i SendBlock są widoczne.
        

        public MainWindow()
        {
            InitializeComponent();
            
        }
        #endregion

        #region Buttons
        private void Connect_Button_Click(object sender, RoutedEventArgs e)
        {
            
            if (!Connection.IsOpen() && Connection.PortOpen())
            {
                Connection.DataReceived += Connection_DataReceived;
                Task.Delay(50);
                CommunicationThread();
            }
            else
            {
                
                MessageBox.Show("Błąd połączenia.");
            }
        }
        private void DebugButton_Click(object sender, RoutedEventArgs e)
        {
            if (DebugButtonState)
            {
                ReceiveBlock.Visibility = Visibility.Hidden;
                SendBlock.Visibility = Visibility.Hidden;
                Receive_label.Visibility = Visibility.Hidden;
                Send_label.Visibility = Visibility.Hidden;
                DebugButtonState = false;
                DebugButton.Content = "Debug On";
            }
            else
            {
                ReceiveBlock.Visibility = Visibility.Visible;
                SendBlock.Visibility = Visibility.Visible;
                Receive_label.Visibility = Visibility.Visible;
                Send_label.Visibility = Visibility.Visible;
                DebugButtonState = true;
                DebugButton.Content = "Debug Off";
            }
        }
        #endregion

        #region Communication
        async void CommunicationThread()
        {
            CB01.IsEnabled = false; CB02.IsEnabled = false; CB03.IsEnabled = false; CB04.IsEnabled = false; CB05.IsEnabled = false; CB06.IsEnabled = false; CB07.IsEnabled = false; CB08.IsEnabled = false;
            CB10.IsEnabled = false; CB20.IsEnabled = false; CB30.IsEnabled = false; CB40.IsEnabled = false; CB50.IsEnabled = false; CB60.IsEnabled = false; CB70.IsEnabled = false; CB80.IsEnabled = false;
            
            while (true) //wszystkie zmiany wizualne
            {
                await Task.Delay(100);
                if (CarretCounter(SendBlock.Text)>20) Dispatcher.Invoke(() => { SendBlock.Text = SendBuffor + "\n"; });
                if (CarretCounter(ReceiveBlock.Text) > 15) Dispatcher.Invoke(() => { ReceiveBlock.Text = ""; });
            }

        }
        void Connection_DataReceived(string data)
        {
            for (int i = 0; i < data.Length; i++)
            {
                if (flaga == 0)
                {
                    
                    if (data[i] == 'P' || data[i] == 'C' || data[i] == '0')
                    {
                        if (Frame.Length == 0 && data[i] == 'P') Frame += data[i];
                        else if (Frame.Length == 1 && data[i] == 'C' && Frame[0]=='P') Frame += data[i];
                        else if (Frame.Length == 2 && data[i] == '0' && Frame[1]=='C') Frame += data[i];
                        else Frame = "";
                    }
                    else Frame = "";

                    if (Frame.Contains("PC0"))
                    {
                        SendBlock.Dispatcher.Invoke(() => { SendBlock.Text += "P_c0\n"; });//
                        flaga = 1;
                        Frame = "";
                        if (SendBuffor == "" && good==0)
                        {
                                tooMuch = 0;
                                good = 4;
                                Connection.Send("r");
                                Frame = "";
                                data = "";
                                Dispatcher.Invoke(() => { SendBlock.Text += "r\n"; });
                            
                        }
                        else if (SendBuffor == "" && good > 0)
                        {
                            good--;
                            Connection.Send("g");
                            Dispatcher.Invoke(() => { SendBlock.Text +=  "g\n"; });
                            flaga = 0;
                        }
                        else if (SendBuffor != "")
                        {
                            good=0;
                            Connection.Send("n");
                            Dispatcher.Invoke(() => { SendBlock.Text += "nowy\n"; });
                            flaga = 3;
                            data = "";
                        }
                    }
                }
                else if (flaga == 1)//odbiór długiej ramki zakonczonej e
                {
                    
                    if (data[i] != 'e')
                    {
                        Dispatcher.Invoke(() => { SendBlock.Text = Frame; });
                        Frame += data[i];
                        tooMuch++;
                        if (tooMuch > 340)
                        {
                            MessageBox.Show("Błąd połączenia");
                            Frame = "";
                            data = "";
                            flaga = 0;
                            break;
                        }
                    }
                    else
                    {
                        flaga = 2;
                    }
                }
                else if (flaga == 2)//analiza ramki refresh
                {
                    ReceiveBlock.Dispatcher.Invoke(() => { ReceiveBlock.Text += Frame + "\n"; });

                    if (Frame.Length % 15 == 0)
                    {
                        for (int I = 0; I < Frame.Length; I += 15)
                        {
                            s_help = Frame[I + 7].ToString() + Frame[I + 8].ToString() + Frame[I + 9].ToString() + Frame[I + 10].ToString() + Frame[I + 11].ToString() + Frame[I + 12].ToString() + Frame[I + 13].ToString();
                            //Dispatcher.Invoke(() => { TB.Text += Frame[I]; });
                            if (Frame[I] == 'c') //czujnik
                            {
                                if      (Frame[I+5]=='1')
                                {
                                    Dispatcher.Invoke(() =>
                                    {
                                        if (CB01.IsChecked == false) CB01.IsChecked = true;
                                        C01_LX.Value = Convert.ToInt32(s_help);
                                        C01_LX_int.Content = s_help;
                                        Cname01.Text = Frame[I + 2].ToString() + Frame[I + 3].ToString() + Frame[I + 4].ToString() + Frame[I + 5].ToString();
                                    });
                                }
                                else if (Frame[I + 5] == '2')
                                {
                                    Dispatcher.Invoke(() =>
                                    {
                                        if (CB02.IsChecked == false) CB02.IsChecked = true;
                                        C02_LX.Value = Convert.ToInt32(s_help);
                                        C02_LX_int.Content = s_help;
                                        Cname02.Text = Frame[I + 2].ToString() + Frame[I + 3].ToString() + Frame[I + 4].ToString() + Frame[I + 5].ToString();
                                    });
                                }
                                else if (Frame[I + 5] == '3')
                                {
                                    Dispatcher.Invoke(() =>
                                    {
                                        if (CB03.IsChecked == false) CB03.IsChecked = true;
                                        C03_LX.Value = Convert.ToInt32(s_help);
                                        C03_LX_int.Content = s_help;
                                        Cname03.Text = Frame[I + 2].ToString() + Frame[I + 3].ToString() + Frame[I + 4].ToString() + Frame[I + 5].ToString();
                                    });
                                }
                                else if (Frame[I + 5] == '4')
                                {
                                    Dispatcher.Invoke(() =>
                                    {
                                        if (CB04.IsChecked == false) CB04.IsChecked = true;
                                        C04_LX.Value = Convert.ToInt32(s_help);
                                        C04_LX_int.Content = s_help;
                                        Cname04.Text = Frame[I + 2].ToString() + Frame[I + 3].ToString() + Frame[I + 4].ToString() + Frame[I + 5].ToString();
                                    });
                                }
                                else if (Frame[I + 5] == '5')
                                {
                                    Dispatcher.Invoke(() =>
                                    {
                                        if (CB05.IsChecked == false) CB05.IsChecked = true;
                                        C05_LX.Value = Convert.ToInt32(s_help);
                                        C05_LX_int.Content = s_help;
                                        Cname05.Text = Frame[I + 2].ToString() + Frame[I + 3].ToString() + Frame[I + 4].ToString() + Frame[I + 5].ToString();
                                    });
                                }
                                else if (Frame[I + 5] == '6')
                                {
                                    Dispatcher.Invoke(() =>
                                    {
                                        if (CB06.IsChecked == false) CB06.IsChecked = true;
                                        C06_LX.Value = Convert.ToInt32(s_help);
                                        C06_LX_int.Content = s_help;
                                        Cname06.Text = Frame[I + 2].ToString() + Frame[I + 3].ToString() + Frame[I + 4].ToString() + Frame[I + 5].ToString();
                                    });
                                }
                                else if (Frame[I + 5] == '7')
                                {
                                    Dispatcher.Invoke(() =>
                                    {
                                        if (CB07.IsChecked == false) CB07.IsChecked = true;
                                        C07_LX.Value = Convert.ToInt32(s_help);
                                        C07_LX_int.Content = s_help;
                                        Cname07.Text = Frame[I + 2].ToString() + Frame[I + 3].ToString() + Frame[I + 4].ToString() + Frame[I + 5].ToString();
                                    });
                                }
                                else if (Frame[I + 5] == '8')
                                {
                                    Dispatcher.Invoke(() =>
                                    {
                                        if (CB08.IsChecked == false) CB08.IsChecked = true;
                                        C08_LX.Value = Convert.ToInt32(s_help);
                                        C08_LX_int.Content = s_help;
                                        Cname08.Text = Frame[I + 2].ToString() + Frame[I + 3].ToString() + Frame[I + 4].ToString() + Frame[I + 5].ToString();
                                    });
                                }
                            }
                            else if (Frame[I] == 'r') //regulator
                            {
                                if (Frame[I + 5] == '1')
                                {
                                    Dispatcher.Invoke(() => {
                                        if (CB10.IsChecked == false) CB10.IsChecked = true;
                                        PWM01.Text = Convert.ToInt32(s_help).ToString();
                                        Rname01.Text = Frame[I + 2].ToString() + Frame[I + 3].ToString() + Frame[I + 4].ToString() + Frame[I + 5].ToString();
                                    });
                                }
                                else if (Frame[I + 5] == '2')
                                {
                                    Dispatcher.Invoke(() => {
                                        if (CB20.IsChecked == false) CB20.IsChecked = true;
                                        PWM02.Text = Convert.ToInt32(s_help).ToString();
                                        Rname02.Text = Frame[I + 2].ToString() + Frame[I + 3].ToString() + Frame[I + 4].ToString() + Frame[I + 5].ToString();
                                    });
                                }
                                else if (Frame[I + 5] == '3')
                                {
                                    Dispatcher.Invoke(() => {
                                        if (CB30.IsChecked == false) CB30.IsChecked = true;
                                        PWM03.Text = Convert.ToInt32(s_help).ToString();
                                        Rname03.Text = Frame[I + 2].ToString() + Frame[I + 3].ToString() + Frame[I + 4].ToString() + Frame[I + 5].ToString();
                                    });
                                }
                                else if (Frame[I + 5] == '4')
                                {
                                    Dispatcher.Invoke(() => {
                                        if (CB40.IsChecked == false) CB40.IsChecked = true;
                                        PWM04.Text = Convert.ToInt32(s_help).ToString();
                                        Rname04.Text = Frame[I + 2].ToString() + Frame[I + 3].ToString() + Frame[I + 4].ToString() + Frame[I + 5].ToString();
                                    });
                                }
                                else if (Frame[I + 5] == '5')
                                {
                                    Dispatcher.Invoke(() =>
                                    {
                                        if (CB50.IsChecked == false) CB50.IsChecked = true;
                                        PWM05.Text = Convert.ToInt32(s_help).ToString();
                                        Rname05.Text = Frame[I + 2].ToString() + Frame[I + 3].ToString() + Frame[I + 4].ToString() + Frame[I + 5].ToString();
                                    });
                                }
                                else if (Frame[I + 5] == '6')
                                {
                                    Dispatcher.Invoke(() =>
                                    {
                                        if (CB60.IsChecked == false) CB60.IsChecked = true;
                                        PWM06.Text = Convert.ToInt32(s_help).ToString();
                                        Rname06.Text = Frame[I + 2].ToString() + Frame[I + 3].ToString() + Frame[I + 4].ToString() + Frame[I + 5].ToString();
                                    });
                                }
                                else if (Frame[I + 5] == '7')
                                {
                                    Dispatcher.Invoke(() =>
                                    {
                                        if (CB70.IsChecked == false) CB70.IsChecked = true;
                                        PWM07.Text = Convert.ToInt32(s_help).ToString();
                                        Rname07.Text = Frame[I + 2].ToString() + Frame[I + 3].ToString() + Frame[I + 4].ToString() + Frame[I + 5].ToString();
                                    });
                                }
                                else if (Frame[I + 5] == '8')
                                {
                                    Dispatcher.Invoke(() =>
                                    {
                                        if (CB70.IsChecked == false) CB80.IsChecked = true;
                                        PWM08.Text = Convert.ToInt32(s_help).ToString();
                                        Rname08.Text = Frame[I + 2].ToString() + Frame[I + 3].ToString() + Frame[I + 4].ToString() + Frame[I + 5].ToString();
                                    });
                                }
                            }       
                        }
                    }
                    Task.Delay(1000);
                    INIT = false;
                    Frame = "";
                    flaga = 0;
                    Dispatcher.Invoke(() =>
                                    {
                    CB01.IsEnabled = true; CB02.IsEnabled = true; CB03.IsEnabled = true; CB04.IsEnabled = true; CB05.IsEnabled = true; CB06.IsEnabled = true; CB07.IsEnabled = true; CB08.IsEnabled = true;
                    CB10.IsEnabled = true; CB20.IsEnabled = true; CB30.IsEnabled = true; CB40.IsEnabled = true; CB50.IsEnabled = true; CB60.IsEnabled = true; CB70.IsEnabled = true; CB80.IsEnabled = true;
                                    });
                }
                else if (flaga == 3)//wysyłanie nowych konfiguracji
                {
                    //2 etapy -> 1. sprawdzenie czy sterownik jest juz gotowy na odbiór danych
                    //2. Wysłanie bufora
                    if (data[i] == 'g')
                    {
                        Dispatcher.Invoke(() => { SendBlock.Text += "poprawnie dodaje nowy: "+SendBuffor + "\n"; });
                        Connection.Send(SendBuffor);
                        SendBuffor = "";
                        flaga = 4;
                    }
                    else
                    {
                        Dispatcher.Invoke(() => { SendBlock.Text += "What the hell?"+ data +"\n"; });
                        flaga = 3;//to jest specjalnie zle
                    }
                }
                else if (flaga == 4)//wysyłanie nowych konfiguracji
                {
                    //2 etapy -> 1. sprawdzenie czy sterownik jest juz gotowy na odbiór danych
                    //2. Wysłanie bufora
                    if (data[i] == 'g')
                    {
                        Dispatcher.Invoke(() => { SendBlock.Text += "elegandzko dodane" + SendBuffor + "\n"; });
                        Connection.Send(SendBuffor);
                        SendBuffor = "";
                        flaga = 0;
                        Dispatcher.Invoke(() => {
                        CB01.IsEnabled = true; CB02.IsEnabled = true; CB03.IsEnabled = true; CB04.IsEnabled = true; CB05.IsEnabled = true; CB06.IsEnabled = true; CB07.IsEnabled = true; CB08.IsEnabled = true;
                        CB10.IsEnabled = true; CB20.IsEnabled = true; CB30.IsEnabled = true; CB40.IsEnabled = true; CB50.IsEnabled = true; CB60.IsEnabled = true; CB70.IsEnabled = true; CB80.IsEnabled = true;
                        });
                    }
                    else
                    {
                        Dispatcher.Invoke(() => { SendBlock.Text += "What the hell 2. ?" + data + "\n"; });
                        flaga = 0;//to jest specjalnie zle
                    }
                }
                
                
            }//for
        }
        #endregion

        #region Sliders
        private void Slider_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            //Zakres.Content = "Zakres: " + Sowak.Value.ToString();
            try
            {
                int i_help = (int)Sowak.Value;
                int i_help2 = i_help;
                int i_help3 = ZakresMax(i_help);

                Dispatcher.Invoke(() => { Zakres.Text = "Zakres: " + i_help2.ToString() + " : " + i_help3.ToString(); });
            }
            catch { }
            //Sowak.Dispatcher.Invoke(() => { elo = "Zakres: " + Sowak.Value.ToString(); });
            //Zakres.Dispatcher.Invoke(() => { Zakres.Content ="asd"; });
           // Dispatcher.Invoke(() => {  });
        }
        #endregion

        #region Boxes

        #region C1R1
        private void CB01_Unchecked(object sender, RoutedEventArgs e)
        {//delete czujnik C01
           
                char c_help = '1';
                SendBuffor = "d" + c_help;//usun czujnik//delete+ID
                Dispatcher.Invoke(() => { SendBlock.Text += SendBuffor + " (" + SendBuffor.Length + ")\n"; });
                CB01.IsEnabled = false; CB02.IsEnabled = false; CB03.IsEnabled = false; CB04.IsEnabled = false; CB05.IsEnabled = false; CB06.IsEnabled = false; CB07.IsEnabled = false; CB08.IsEnabled = false;
                CB10.IsEnabled = false; CB20.IsEnabled = false; CB30.IsEnabled = false; CB40.IsEnabled = false; CB50.IsEnabled = false; CB60.IsEnabled = false; CB70.IsEnabled = false; CB80.IsEnabled = false;
          
        }
        private void CB01_Checked(object sender, RoutedEventArgs e)
        {//add czujnik C01
           
                char c_help = '1';
                SendBuffor = "a" + c_help + liczba(Convert.ToInt32(Sowak.Value)) + "c";//dodaj nowy czujnik//add+ID+MAX
                Dispatcher.Invoke(() => { SendBlock.Text += SendBuffor + " (" + SendBuffor.Length + ")\n"; });
                CB01.IsEnabled = false; CB02.IsEnabled = false; CB03.IsEnabled = false; CB04.IsEnabled = false; CB05.IsEnabled = false; CB06.IsEnabled = false; CB07.IsEnabled = false; CB08.IsEnabled = false;
                CB10.IsEnabled = false; CB20.IsEnabled = false; CB30.IsEnabled = false; CB40.IsEnabled = false; CB50.IsEnabled = false; CB60.IsEnabled = false; CB70.IsEnabled = false; CB80.IsEnabled = false;
                C01_LX.Value = 0;
                C01_LX_int.Content = '-';
        }
        private void CB10_Unchecked(object sender, RoutedEventArgs e)
        {//delete regulator R01
           
                char c_help = '2';
                SendBuffor = "d" + c_help;//usun regulator//delete+ID
                Dispatcher.Invoke(() => { SendBlock.Text += SendBuffor + " (" + SendBuffor.Length + ")\n"; });
                CB01.IsEnabled = false; CB02.IsEnabled = false; CB03.IsEnabled = false; CB04.IsEnabled = false; CB05.IsEnabled = false; CB06.IsEnabled = false; CB07.IsEnabled = false; CB08.IsEnabled = false;
                CB10.IsEnabled = false; CB20.IsEnabled = false; CB30.IsEnabled = false; CB40.IsEnabled = false; CB50.IsEnabled = false; CB60.IsEnabled = false; CB70.IsEnabled = false; CB80.IsEnabled = false;  
         
        }
        private void CB10_Checked(object sender, RoutedEventArgs e)
        {//add regulator R01
           
                char c_help = '2';
                SendBuffor = "a" + c_help + "r";//dodaj nowy regulator//add+ID+MAX
                Dispatcher.Invoke(() => { SendBlock.Text += SendBuffor + " (" + SendBuffor.Length + ")\n"; });
                CB01.IsEnabled = false; CB02.IsEnabled = false; CB03.IsEnabled = false; CB04.IsEnabled = false; CB05.IsEnabled = false; CB06.IsEnabled = false; CB07.IsEnabled = false; CB08.IsEnabled = false;
                CB10.IsEnabled = false; CB20.IsEnabled = false; CB30.IsEnabled = false; CB40.IsEnabled = false; CB50.IsEnabled = false; CB60.IsEnabled = false; CB70.IsEnabled = false; CB80.IsEnabled = false;  
          
        }
        #endregion

        #region C2R2
        private void CB02_Checked(object sender, RoutedEventArgs e)
        {//add czujnik C02
          
                char c_help = '3';
                SendBuffor = "a" + c_help + liczba(Convert.ToInt32(Sowak.Value)) + "c";//dodaj nowy czujnik//add+ID+MAX
                Dispatcher.Invoke(() => { SendBlock.Text += SendBuffor + " (" + SendBuffor.Length + ")\n"; });
                CB01.IsEnabled = false; CB02.IsEnabled = false; CB03.IsEnabled = false; CB04.IsEnabled = false; CB05.IsEnabled = false; CB06.IsEnabled = false; CB07.IsEnabled = false; CB08.IsEnabled = false;
                CB10.IsEnabled = false; CB20.IsEnabled = false; CB30.IsEnabled = false; CB40.IsEnabled = false; CB50.IsEnabled = false; CB60.IsEnabled = false; CB70.IsEnabled = false; CB80.IsEnabled = false;  
          
        }
        private void CB02_Unchecked(object sender, RoutedEventArgs e)
        {//delete czujnik C02
           
                char c_help = '3';
                SendBuffor = "d" + c_help;//usun czujnik//delete+ID
                Dispatcher.Invoke(() => { SendBlock.Text += SendBuffor + " (" + SendBuffor.Length + ")\n"; });
                CB01.IsEnabled = false; CB02.IsEnabled = false; CB03.IsEnabled = false; CB04.IsEnabled = false; CB05.IsEnabled = false; CB06.IsEnabled = false; CB07.IsEnabled = false; CB08.IsEnabled = false;
                CB10.IsEnabled = false; CB20.IsEnabled = false; CB30.IsEnabled = false; CB40.IsEnabled = false; CB50.IsEnabled = false; CB60.IsEnabled = false; CB70.IsEnabled = false; CB80.IsEnabled = false;
                C02_LX.Value = 0;
                C02_LX_int.Content = '-';
        }
        private void CB20_Checked(object sender, RoutedEventArgs e)
        {//add regulator R02
           
                char c_help = '4';
                SendBuffor = "a" + c_help + "r";//dodaj nowy regulator//add+ID+MAX
                Dispatcher.Invoke(() => { SendBlock.Text += SendBuffor + " (" + SendBuffor.Length + ")\n"; });
                CB01.IsEnabled = false; CB02.IsEnabled = false; CB03.IsEnabled = false; CB04.IsEnabled = false; CB05.IsEnabled = false; CB06.IsEnabled = false; CB07.IsEnabled = false; CB08.IsEnabled = false;
                CB10.IsEnabled = false; CB20.IsEnabled = false; CB30.IsEnabled = false; CB40.IsEnabled = false; CB50.IsEnabled = false; CB60.IsEnabled = false; CB70.IsEnabled = false; CB80.IsEnabled = false;  
           
        }
        private void CB20_Unchecked(object sender, RoutedEventArgs e)
        {//delete regulator R02
           
                char c_help = '4';
                SendBuffor = "d" + c_help;//usun regulator//delete+ID
                Dispatcher.Invoke(() => { SendBlock.Text += SendBuffor + " (" + SendBuffor.Length + ")\n"; });
                CB01.IsEnabled = false; CB02.IsEnabled = false; CB03.IsEnabled = false; CB04.IsEnabled = false; CB05.IsEnabled = false; CB06.IsEnabled = false; CB07.IsEnabled = false; CB08.IsEnabled = false;
                CB10.IsEnabled = false; CB20.IsEnabled = false; CB30.IsEnabled = false; CB40.IsEnabled = false; CB50.IsEnabled = false; CB60.IsEnabled = false; CB70.IsEnabled = false; CB80.IsEnabled = false;  
          
        }
        #endregion

        #region C3R3
        private void CB03_Checked(object sender, RoutedEventArgs e)
        {//add czujnik 
            
                char c_help = '5';
                SendBuffor = "a" + c_help.ToString() + liczba(Convert.ToInt32(Sowak.Value)) + "c";//dodaj nowy czujnik//add+ID+MAX
                Dispatcher.Invoke(() => { SendBlock.Text += SendBuffor + " (" + SendBuffor.Length + ")\n"; });
                CB01.IsEnabled = false; CB02.IsEnabled = false; CB03.IsEnabled = false; CB04.IsEnabled = false; CB05.IsEnabled = false; CB06.IsEnabled = false; CB07.IsEnabled = false; CB08.IsEnabled = false;
                CB10.IsEnabled = false; CB20.IsEnabled = false; CB30.IsEnabled = false; CB40.IsEnabled = false; CB50.IsEnabled = false; CB60.IsEnabled = false; CB70.IsEnabled = false; CB80.IsEnabled = false;  
          
        }
        private void CB03_Unchecked(object sender, RoutedEventArgs e)
        {//delete czujnik 
           
                char c_help = '5';
                SendBuffor = "d" + c_help.ToString();//usun czujnik//delete+ID
                Dispatcher.Invoke(() => { SendBlock.Text += SendBuffor + " (" + SendBuffor.Length + ")\n"; });
                CB01.IsEnabled = false; CB02.IsEnabled = false; CB03.IsEnabled = false; CB04.IsEnabled = false; CB05.IsEnabled = false; CB06.IsEnabled = false; CB07.IsEnabled = false; CB08.IsEnabled = false;
                CB10.IsEnabled = false; CB20.IsEnabled = false; CB30.IsEnabled = false; CB40.IsEnabled = false; CB50.IsEnabled = false; CB60.IsEnabled = false; CB70.IsEnabled = false; CB80.IsEnabled = false;
                C03_LX.Value = 0;
                C03_LX_int.Content = '-';
        }
        private void CB30_Checked(object sender, RoutedEventArgs e)
        {//add regulator 
           
                char c_help = '6';
                SendBuffor = "a" + c_help.ToString() + "r";//dodaj nowy regulator//add+ID+MAX
                Dispatcher.Invoke(() => { SendBlock.Text += SendBuffor + " (" + SendBuffor.Length + ")\n"; });
                CB01.IsEnabled = false; CB02.IsEnabled = false; CB03.IsEnabled = false; CB04.IsEnabled = false; CB05.IsEnabled = false; CB06.IsEnabled = false; CB07.IsEnabled = false; CB08.IsEnabled = false;
                CB10.IsEnabled = false; CB20.IsEnabled = false; CB30.IsEnabled = false; CB40.IsEnabled = false; CB50.IsEnabled = false; CB60.IsEnabled = false; CB70.IsEnabled = false; CB80.IsEnabled = false;  
          
        }
        private void CB30_Unchecked(object sender, RoutedEventArgs e)
        {//delete regulator 
           
                char c_help = '6';
                SendBuffor = "d" + c_help.ToString();//usun regulator//delete+ID
                Dispatcher.Invoke(() => { SendBlock.Text += SendBuffor + " (" + SendBuffor.Length + ")\n"; });
                CB01.IsEnabled = false; CB02.IsEnabled = false; CB03.IsEnabled = false; CB04.IsEnabled = false; CB05.IsEnabled = false; CB06.IsEnabled = false; CB07.IsEnabled = false; CB08.IsEnabled = false;
                CB10.IsEnabled = false; CB20.IsEnabled = false; CB30.IsEnabled = false; CB40.IsEnabled = false; CB50.IsEnabled = false; CB60.IsEnabled = false; CB70.IsEnabled = false; CB80.IsEnabled = false;  
          
        }
        #endregion

        #region C4R4
        private void CB04_Checked(object sender, RoutedEventArgs e)
        {//add czujnik 
           
                char c_help = '7';
                SendBuffor = "a" + c_help.ToString() + liczba(Convert.ToInt32(Sowak.Value)) + "c";//dodaj nowy czujnik//add+ID+MAX
                Dispatcher.Invoke(() => { SendBlock.Text += SendBuffor + " (" + SendBuffor.Length + ")\n"; });
                CB01.IsEnabled = false; CB02.IsEnabled = false; CB03.IsEnabled = false; CB04.IsEnabled = false; CB05.IsEnabled = false; CB06.IsEnabled = false; CB07.IsEnabled = false; CB08.IsEnabled = false;
                CB10.IsEnabled = false; CB20.IsEnabled = false; CB30.IsEnabled = false; CB40.IsEnabled = false; CB50.IsEnabled = false; CB60.IsEnabled = false; CB70.IsEnabled = false; CB80.IsEnabled = false;  
                
           
        }
        private void CB04_Unchecked(object sender, RoutedEventArgs e)
        {//delete czujnik 
           
                char c_help = '7';
                SendBuffor = "d" + c_help.ToString();//usun czujnik//delete+ID
                Dispatcher.Invoke(() => { SendBlock.Text += SendBuffor + " (" + SendBuffor.Length + ")\n"; });
                CB01.IsEnabled = false; CB02.IsEnabled = false; CB03.IsEnabled = false; CB04.IsEnabled = false; CB05.IsEnabled = false; CB06.IsEnabled = false; CB07.IsEnabled = false; CB08.IsEnabled = false;
                CB10.IsEnabled = false; CB20.IsEnabled = false; CB30.IsEnabled = false; CB40.IsEnabled = false; CB50.IsEnabled = false; CB60.IsEnabled = false; CB70.IsEnabled = false; CB80.IsEnabled = false;
                C04_LX.Value = 0;
                C04_LX_int.Content = '-';
        }
        private void CB40_Checked(object sender, RoutedEventArgs e)
        {//add regulator 
           
                char c_help = '8';
                SendBuffor = "a" + c_help.ToString() + "r";//dodaj nowy regulator//add+ID+MAX
                Dispatcher.Invoke(() => { SendBlock.Text += SendBuffor + " (" + SendBuffor.Length + ")\n"; });
                CB01.IsEnabled = false; CB02.IsEnabled = false; CB03.IsEnabled = false; CB04.IsEnabled = false; CB05.IsEnabled = false; CB06.IsEnabled = false; CB07.IsEnabled = false; CB08.IsEnabled = false;
                CB10.IsEnabled = false; CB20.IsEnabled = false; CB30.IsEnabled = false; CB40.IsEnabled = false; CB50.IsEnabled = false; CB60.IsEnabled = false; CB70.IsEnabled = false; CB80.IsEnabled = false;  
         
        }
        private void CB40_Unchecked(object sender, RoutedEventArgs e)
        {//delete regulator 
           
                char c_help = '8';
                SendBuffor = "d" + c_help.ToString().ToString();//usun regulator//delete+ID
                Dispatcher.Invoke(() => { SendBlock.Text += SendBuffor + " (" + SendBuffor.Length + ")\n"; });
                CB01.IsEnabled = false; CB02.IsEnabled = false; CB03.IsEnabled = false; CB04.IsEnabled = false; CB05.IsEnabled = false; CB06.IsEnabled = false; CB07.IsEnabled = false; CB08.IsEnabled = false;
                CB10.IsEnabled = false; CB20.IsEnabled = false; CB30.IsEnabled = false; CB40.IsEnabled = false; CB50.IsEnabled = false; CB60.IsEnabled = false; CB70.IsEnabled = false; CB80.IsEnabled = false;  
            
           
        }
        #endregion

        #region C5R5
        private void CB05_Checked(object sender, RoutedEventArgs e)
        {//add czujnik 
           
                char c_help = (char)(9 + 48);
                SendBuffor = "a" + c_help.ToString() + liczba(Convert.ToInt32(Sowak.Value)) + "c";//dodaj nowy czujnik//add+ID+MAX
                Dispatcher.Invoke(() => { SendBlock.Text += SendBuffor + " (" + SendBuffor.Length + ")\n"; });
                CB01.IsEnabled = false; CB02.IsEnabled = false; CB03.IsEnabled = false; CB04.IsEnabled = false; CB05.IsEnabled = false; CB06.IsEnabled = false; CB07.IsEnabled = false; CB08.IsEnabled = false;
                CB10.IsEnabled = false; CB20.IsEnabled = false; CB30.IsEnabled = false; CB40.IsEnabled = false; CB50.IsEnabled = false; CB60.IsEnabled = false; CB70.IsEnabled = false; CB80.IsEnabled = false;  
         
        }
        private void CB05_Unchecked(object sender, RoutedEventArgs e)
        {//delete czujnik 
           
                char c_help = (char)(9 + 48);
                SendBuffor = "d" + c_help.ToString();//usun czujnik//delete+ID
                Dispatcher.Invoke(() => { SendBlock.Text += SendBuffor + " (" + SendBuffor.Length + ")\n"; });
                CB01.IsEnabled = false; CB02.IsEnabled = false; CB03.IsEnabled = false; CB04.IsEnabled = false; CB05.IsEnabled = false; CB06.IsEnabled = false; CB07.IsEnabled = false; CB08.IsEnabled = false;
                CB10.IsEnabled = false; CB20.IsEnabled = false; CB30.IsEnabled = false; CB40.IsEnabled = false; CB50.IsEnabled = false; CB60.IsEnabled = false; CB70.IsEnabled = false; CB80.IsEnabled = false;
                C05_LX.Value = 0;
                C05_LX_int.Content = '-';
        }
        private void CB50_Checked(object sender, RoutedEventArgs e)
        {//add regulator 
           
                char c_help = (char)(10+48);
                SendBuffor = "a" + c_help.ToString() + "r";//dodaj nowy regulator//add+ID+MAX
                Dispatcher.Invoke(() => { SendBlock.Text += SendBuffor + " (" + SendBuffor.Length + ")\n"; });
                CB01.IsEnabled = false; CB02.IsEnabled = false; CB03.IsEnabled = false; CB04.IsEnabled = false; CB05.IsEnabled = false; CB06.IsEnabled = false; CB07.IsEnabled = false; CB08.IsEnabled = false;
                CB10.IsEnabled = false; CB20.IsEnabled = false; CB30.IsEnabled = false; CB40.IsEnabled = false; CB50.IsEnabled = false; CB60.IsEnabled = false; CB70.IsEnabled = false; CB80.IsEnabled = false;  
          
        }
        private void CB50_Unchecked(object sender, RoutedEventArgs e)
        {//delete regulator 
   
                char c_help = (char)(10 + 48);
                SendBuffor = "d" + c_help.ToString();//usun regulator//delete+ID
                Dispatcher.Invoke(() => { SendBlock.Text += SendBuffor + " (" + SendBuffor.Length + ")\n"; });
                CB01.IsEnabled = false; CB02.IsEnabled = false; CB03.IsEnabled = false; CB04.IsEnabled = false; CB05.IsEnabled = false; CB06.IsEnabled = false; CB07.IsEnabled = false; CB08.IsEnabled = false;
                CB10.IsEnabled = false; CB20.IsEnabled = false; CB30.IsEnabled = false; CB40.IsEnabled = false; CB50.IsEnabled = false; CB60.IsEnabled = false; CB70.IsEnabled = false; CB80.IsEnabled = false;  
            
          
        }
        #endregion

        #region C6R6
        private void CB06_Checked(object sender, RoutedEventArgs e)
        {//add czujnik 

                char c_help = (char)(11 + 48);
                SendBuffor = "a" + c_help.ToString() + liczba(Convert.ToInt32(Sowak.Value)) + "c";//dodaj nowy czujnik//add+ID+MAX
                Dispatcher.Invoke(() => { SendBlock.Text += SendBuffor + " (" + SendBuffor.Length + ")\n"; });
                CB01.IsEnabled = false; CB02.IsEnabled = false; CB03.IsEnabled = false; CB04.IsEnabled = false; CB05.IsEnabled = false; CB06.IsEnabled = false; CB07.IsEnabled = false; CB08.IsEnabled = false;
                CB10.IsEnabled = false; CB20.IsEnabled = false; CB30.IsEnabled = false; CB40.IsEnabled = false; CB50.IsEnabled = false; CB60.IsEnabled = false; CB70.IsEnabled = false; CB80.IsEnabled = false;  

        }
        private void CB06_Unchecked(object sender, RoutedEventArgs e)
        {//delete czujnik 

                char c_help = (char)(11 + 48);
                SendBuffor = "d" + c_help.ToString();//usun czujnik//delete+ID
                Dispatcher.Invoke(() => { SendBlock.Text += SendBuffor + " (" + SendBuffor.Length + ")\n"; });
                CB01.IsEnabled = false; CB02.IsEnabled = false; CB03.IsEnabled = false; CB04.IsEnabled = false; CB05.IsEnabled = false; CB06.IsEnabled = false; CB07.IsEnabled = false; CB08.IsEnabled = false;
                CB10.IsEnabled = false; CB20.IsEnabled = false; CB30.IsEnabled = false; CB40.IsEnabled = false; CB50.IsEnabled = false; CB60.IsEnabled = false; CB70.IsEnabled = false; CB80.IsEnabled = false;
                C06_LX.Value = 0;
                C06_LX_int.Content = '-';
        }
        private void CB60_Checked(object sender, RoutedEventArgs e)
        {//add regulator 

                char c_help = (char)(12 + 48);
                SendBuffor = "a" + c_help.ToString() + "r";//dodaj nowy regulator//add+ID+MAX
                Dispatcher.Invoke(() => { SendBlock.Text += SendBuffor + " (" + SendBuffor.Length + ")\n"; });
                CB01.IsEnabled = false; CB02.IsEnabled = false; CB03.IsEnabled = false; CB04.IsEnabled = false; CB05.IsEnabled = false; CB06.IsEnabled = false; CB07.IsEnabled = false; CB08.IsEnabled = false;
                CB10.IsEnabled = false; CB20.IsEnabled = false; CB30.IsEnabled = false; CB40.IsEnabled = false; CB50.IsEnabled = false; CB60.IsEnabled = false; CB70.IsEnabled = false; CB80.IsEnabled = false;  

        }
        private void CB60_Unchecked(object sender, RoutedEventArgs e)
        {//delete regulator 

                char c_help = (char)(12 + 48);
                SendBuffor = "d" + c_help.ToString();//usun regulator//delete+ID
                Dispatcher.Invoke(() => { SendBlock.Text += SendBuffor + " (" + SendBuffor.Length + ")\n"; });
                CB01.IsEnabled = false; CB02.IsEnabled = false; CB03.IsEnabled = false; CB04.IsEnabled = false; CB05.IsEnabled = false; CB06.IsEnabled = false; CB07.IsEnabled = false; CB08.IsEnabled = false;
                CB10.IsEnabled = false; CB20.IsEnabled = false; CB30.IsEnabled = false; CB40.IsEnabled = false; CB50.IsEnabled = false; CB60.IsEnabled = false; CB70.IsEnabled = false; CB80.IsEnabled = false;  

        }
        #endregion

        #region C7R7
        private void CB07_Checked(object sender, RoutedEventArgs e)
        {//add czujnik 

                char c_help = (char)(13 + 48);
                SendBuffor = "a" + c_help + liczba(Convert.ToInt32(Sowak.Value)) + "c";//dodaj nowy czujnik//add+ID+MAX
                Dispatcher.Invoke(() => { SendBlock.Text += SendBuffor + " (" + SendBuffor.Length + ")\n"; });
                CB01.IsEnabled = false; CB02.IsEnabled = false; CB03.IsEnabled = false; CB04.IsEnabled = false; CB05.IsEnabled = false; CB06.IsEnabled = false; CB07.IsEnabled = false; CB08.IsEnabled = false;
                CB10.IsEnabled = false; CB20.IsEnabled = false; CB30.IsEnabled = false; CB40.IsEnabled = false; CB50.IsEnabled = false; CB60.IsEnabled = false; CB70.IsEnabled = false; CB80.IsEnabled = false;  
            
        }
        private void CB07_Unchecked(object sender, RoutedEventArgs e)
        {//delete czujnik 

                char c_help = (char)(13 + 48);
                SendBuffor = "d" + c_help;//usun czujnik//delete+ID
                Dispatcher.Invoke(() => { SendBlock.Text += SendBuffor + " (" + SendBuffor.Length + ")\n"; });
                CB01.IsEnabled = false; CB02.IsEnabled = false; CB03.IsEnabled = false; CB04.IsEnabled = false; CB05.IsEnabled = false; CB06.IsEnabled = false; CB07.IsEnabled = false; CB08.IsEnabled = false;
                CB10.IsEnabled = false; CB20.IsEnabled = false; CB30.IsEnabled = false; CB40.IsEnabled = false; CB50.IsEnabled = false; CB60.IsEnabled = false; CB70.IsEnabled = false; CB80.IsEnabled = false;
                C07_LX.Value = 0;
                C07_LX_int.Content = '-';
        }
        private void CB70_Checked(object sender, RoutedEventArgs e)
        {//add regulator 

                char c_help = (char)(14 + 48);
                SendBuffor = "a" + c_help + "r";//dodaj nowy regulator//add+ID+MAX
                Dispatcher.Invoke(() => { SendBlock.Text += SendBuffor + " (" + SendBuffor.Length + ")\n"; });
                CB01.IsEnabled = false; CB02.IsEnabled = false; CB03.IsEnabled = false; CB04.IsEnabled = false; CB05.IsEnabled = false; CB06.IsEnabled = false; CB07.IsEnabled = false; CB08.IsEnabled = false;
                CB10.IsEnabled = false; CB20.IsEnabled = false; CB30.IsEnabled = false; CB40.IsEnabled = false; CB50.IsEnabled = false; CB60.IsEnabled = false; CB70.IsEnabled = false; CB80.IsEnabled = false;  

        }
        private void CB70_Unchecked(object sender, RoutedEventArgs e)
        {//delete regulator 

                char c_help = (char)(14 + 48);
                SendBuffor = "d" + c_help;//usun regulator//delete+ID
                Dispatcher.Invoke(() => { SendBlock.Text += SendBuffor + " (" + SendBuffor.Length + ")\n"; });
                CB01.IsEnabled = false; CB02.IsEnabled = false; CB03.IsEnabled = false; CB04.IsEnabled = false; CB05.IsEnabled = false; CB06.IsEnabled = false; CB07.IsEnabled = false; CB08.IsEnabled = false;
                CB10.IsEnabled = false; CB20.IsEnabled = false; CB30.IsEnabled = false; CB40.IsEnabled = false; CB50.IsEnabled = false; CB60.IsEnabled = false; CB70.IsEnabled = false; CB80.IsEnabled = false;  

        }
        #endregion

        #region C8R8
        private void CB08_Checked(object sender, RoutedEventArgs e)
        {//add czujnik 

                char c_help = (char)(15 + 48);
                SendBuffor = "a" + c_help + liczba(Convert.ToInt32(Sowak.Value)) + "c";//dodaj nowy czujnik//add+ID+MAX
                Dispatcher.Invoke(() => { SendBlock.Text += SendBuffor + " (" + SendBuffor.Length + ")\n"; });
                CB01.IsEnabled = false; CB02.IsEnabled = false; CB03.IsEnabled = false; CB04.IsEnabled = false; CB05.IsEnabled = false; CB06.IsEnabled = false; CB07.IsEnabled = false; CB08.IsEnabled = false;
                CB10.IsEnabled = false; CB20.IsEnabled = false; CB30.IsEnabled = false; CB40.IsEnabled = false; CB50.IsEnabled = false; CB60.IsEnabled = false; CB70.IsEnabled = false; CB80.IsEnabled = false;  

        }
        private void CB08_Unchecked(object sender, RoutedEventArgs e)
        {//delete czujnik 

                char c_help = (char)(15 + 48);
                SendBuffor = "d" + c_help;//usun czujnik//delete+ID
                Dispatcher.Invoke(() => { SendBlock.Text += SendBuffor + " (" + SendBuffor.Length + ")\n"; });
                CB01.IsEnabled = false; CB02.IsEnabled = false; CB03.IsEnabled = false; CB04.IsEnabled = false; CB05.IsEnabled = false; CB06.IsEnabled = false; CB07.IsEnabled = false; CB08.IsEnabled = false;
                CB10.IsEnabled = false; CB20.IsEnabled = false; CB30.IsEnabled = false; CB40.IsEnabled = false; CB50.IsEnabled = false; CB60.IsEnabled = false; CB70.IsEnabled = false; CB80.IsEnabled = false;
                C08_LX.Value = 0;
                C08_LX_int.Content = '-';
        }
        private void CB80_Checked(object sender, RoutedEventArgs e)
        {//add regulator 

                char c_help = (char)(16 + 48);
                SendBuffor = "a" + c_help + "r";//dodaj nowy regulator//add+ID+MAX
                Dispatcher.Invoke(() => { SendBlock.Text += SendBuffor + " (" + SendBuffor.Length + ")\n"; });
                CB01.IsEnabled = false; CB02.IsEnabled = false; CB03.IsEnabled = false; CB04.IsEnabled = false; CB05.IsEnabled = false; CB06.IsEnabled = false; CB07.IsEnabled = false; CB08.IsEnabled = false;
                CB10.IsEnabled = false; CB20.IsEnabled = false; CB30.IsEnabled = false; CB40.IsEnabled = false; CB50.IsEnabled = false; CB60.IsEnabled = false; CB70.IsEnabled = false; CB80.IsEnabled = false;  

        }
        private void CB80_Unchecked(object sender, RoutedEventArgs e)
        {//delete regulator 

                char c_help = (char)(16 + 48);
                SendBuffor = "d" + c_help;//usun regulator//delete+ID
                Dispatcher.Invoke(() => { SendBlock.Text += SendBuffor + " (" + SendBuffor.Length + ")\n"; });
                CB01.IsEnabled = false; CB02.IsEnabled = false; CB03.IsEnabled = false; CB04.IsEnabled = false; CB05.IsEnabled = false; CB06.IsEnabled = false; CB07.IsEnabled = false; CB08.IsEnabled = false;
                CB10.IsEnabled = false; CB20.IsEnabled = false; CB30.IsEnabled = false; CB40.IsEnabled = false; CB50.IsEnabled = false; CB60.IsEnabled = false; CB70.IsEnabled = false; CB80.IsEnabled = false;  

        }
        #endregion

        #endregion

        #region Functions
        /// <summary>
        /// Zwraca maksymalny zakres, w jakim światło może przewyższyć natężenie bezpieczne.
        /// </summary>
private int ZakresMax(int Wb)//Wb wartość bezpieczna
{
    int Wm = 0;
    int Wb20pr = Wb / 5; //20% z Wb //(Wb*20)/100

    if (Wb20pr <= 50) Wm = Wb + 50;
    else if (Wb20pr > 50 && Wb20pr <= 200) Wm = Wb + Wb20pr;
    else if (Wb20pr > 200) Wm = Wb + 200;
    else return -1;

    return Wm;
}
public string liczba(int liczb)
{
	//Max 9 999 999
	//char[] zwrot=new char[8];
    string wtf="";
	int i_help = 10;

	for(int i=6;i>=0;i--)
		{
			wtf += (char)((liczb%i_help)+48);
			liczb /= 10;

		}
    return Reverse(wtf);
}
public string Reverse(string str)
{
    char[] charArray = str.ToCharArray();
    Array.Reverse(charArray);
    return new string(charArray);
}
public int CarretCounter(string str)
{
    int crt = 0;
    for (int i = 0; i < str.Length; i++)
    {
        if (str[i] == '\n') crt++;
    }
        return crt;
}

        #endregion


    }
}
