using System;
using System.Collections.Generic;
using System.IO;
using System.Windows;
using System.Windows.Media.Imaging;
using System.Windows.Threading;

namespace Tamagotchi
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private string[] data = { "Покормить", "Погулять", "Уложить спать", "Полечить", "Поиграть" };
        private DispatcherTimer timer;
        private List<Request> requests;
        private Request prevRequest;

        public MainWindow()
        {
            InitializeComponent();
            mainImage.Source = new BitmapImage(new Uri($"{Directory.GetCurrentDirectory()}\\main.png"));

            requests = new();
            foreach (var item in data)
                requests.Add(new Request(item));

            timer = new() { Interval = TimeSpan.FromSeconds(2) };
            timer.Tick += Timer_Tick;
            timer.Start();
        }

        private void Timer_Tick(object? sender, EventArgs e)
        {
            timer.Stop();
            Request acctualRequest;

            do
            {
                acctualRequest = requests[new Random().Next(requests.Count)];

            } while (prevRequest == acctualRequest);

            if (MessageBox.Show(acctualRequest.Message, string.Empty, MessageBoxButton.OKCancel) != MessageBoxResult.OK)
                acctualRequest.Fail();


            if (acctualRequest.IsEnd)
            {
                if (MessageBox.Show("Питомец заболел! Нужно срочно полечить!", string.Empty, MessageBoxButton.OKCancel) != MessageBoxResult.OK)
                    GameOver();
                else
                    acctualRequest.ResetFail();
            }

            prevRequest = acctualRequest;
            timer.Start();
        }

        private void GameOver()
        {
            MessageBox.Show("Вы проиграли!");
            this.Close();
        }
    }
}


class Request
{
    public string Message { get; private set; }
    public bool IsEnd
    {
        get { return countFail >= 3; }
    }
    private uint countFail;

    public Request(string message) => Message = message;
    public void Fail() => countFail++;
    public void ResetFail() => countFail = 0;
}
