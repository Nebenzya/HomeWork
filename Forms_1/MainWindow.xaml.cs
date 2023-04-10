//Задание 1
//Вывести на экран свое (краткое!!!) резюме с помощью последовательности MessageBox’ов (числом не менее трех). Причем на заголовке
//последнего должно отобразиться среднее число символов на странице
//(общее количество символов в резюме / количество MessageBox’ов). 

using System.Linq;
using System.Threading;
using System.Windows;

namespace Forms_1
{
    public partial class MainWindow : Window
    {
        string[] messages = { "Имя: Алексей", "Фамилия: Небензя", "Должность: Разработчик", "И я хочу знать что курил автор ДЗ?" };

        public MainWindow()
        {
            InitializeComponent();
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            int counter = 0;
            string caption = string.Empty;
            int messageCount = messages.Count();

            for (int i = 0; i < messageCount; i++)
            {
                Thread.Sleep(1000);

                if (i != messageCount - 1)
                    counter += messages[i].Length;
                else
                    caption = (counter / i).ToString();

                MessageBox.Show(messages[i], caption);
            }
        }
    }
}
