//Задание 5
//Разработать приложение «убегающий статик»:) Суть приложения:
//на форме расположен статический элемент управления («статик»).
//Пользователь пытается подвести курсор мыши к «статику», и, если
//курсор находиться близко со статиком, элемент управления «убегает».
//Предусмотреть перемещение «статика» только в пределах формы. 


using System;
using System.Windows;
using System.Windows.Controls;

namespace Forms_2
{
    public partial class MainWindow : Window
    {
        Random random;
        int max_X, max_Y;
        public MainWindow()
        {
            InitializeComponent();
            random = new Random();
            max_X = (int)(this.Width - lbStatic.Width);
            max_Y = (int)(this.Height - lbStatic.Height);

        }

        private void lbStatic_MouseEnter(object sender, System.Windows.Input.MouseEventArgs e)
        {
            Canvas.SetLeft(lbStatic, random.Next(max_X));
            Canvas.SetTop(lbStatic, random.Next(max_Y));
        }
    }
}
