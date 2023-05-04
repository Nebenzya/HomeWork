using System.Collections.Generic;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;

/*
 Необходимо разработать приложение содержащее
набор кнопок, занимающих 2/3 ширины окна при любых
его размерах.
Каждая кнопка в качестве содержимого отображает название цвета и
обладает наружным отступом равным 2.0
Также соответствующий цвет должен использоваться в 
качестве переднего плана кнопки.
Необходимо использовать следующий набор цветов: Navy,
Blue, Aqua, Teal, Olive, Green, Lime, Yellow, Orange, Red,
Maroon, Fuchsia, Purple, Black, Silver, Gray, White.
 
 */


namespace Introdice_to_WPF;

public partial class MainWindow : Window
{
    private Dictionary<string, SolidColorBrush> brushes = new Dictionary<string, SolidColorBrush>()
    {
        [nameof(Brushes.Navy)] = Brushes.Navy,
        [nameof(Brushes.Blue)] = Brushes.Blue,
        [nameof(Brushes.Aqua)] = Brushes.Aqua,
        [nameof(Brushes.Teal)] = Brushes.Teal,
        [nameof(Brushes.Olive)] = Brushes.Olive,
        [nameof(Brushes.Green)] = Brushes.Green,
        [nameof(Brushes.Lime)] = Brushes.Lime,
        [nameof(Brushes.Yellow)] = Brushes.Yellow,
        [nameof(Brushes.Orange)] = Brushes.Orange,
        [nameof(Brushes.Red)] = Brushes.Red,
        [nameof(Brushes.Maroon)] = Brushes.Maroon,
        [nameof(Brushes.Fuchsia)] = Brushes.Fuchsia,
        [nameof(Brushes.Purple)] = Brushes.Purple,
        [nameof(Brushes.Black)] = Brushes.Black,
        [nameof(Brushes.Silver)] = Brushes.Silver,
        [nameof(Brushes.Gray)] = Brushes.Gray,
        [nameof(Brushes.White)] = Brushes.White
    };

    public MainWindow()
    {
        InitializeComponent();
    }

    private void Window_Loaded(object sender, RoutedEventArgs e)
    {
        foreach (var brush in brushes)
        {
            panelForButton.Children.Add(new Button()
            {
                Background = brush.Value,
                Content = brush.Key,
                Height = 25,
                Width = 60,
                Margin = new Thickness(2)
            });
        }
    }
}
