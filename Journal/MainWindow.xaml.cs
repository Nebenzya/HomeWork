using System;
using System.Collections.Generic;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;

namespace Journal;

// Сделать приложение-аналог журнала урока.Внешний вид примерно как на приложенном скриншоте.
// В шапке название группы, предмет и тема.
// Ниже список студентов:
// - фото
// -ФИО
// -радио-кнопка присутствия на занятии(2 состояния, присутствует и отсутствует)
// -работа в классе, выпадающий список, оценка от 1 до 5
// -поле комментария


// В этой задаче я решил подойти нестандартным путём, реализуя разметку через код

public partial class MainWindow : Window
{
    List<Student> students = new()
    {
        new Student() { Foto = null, FullName = "Пупкин Василий Иванович"},
        new Student() { Foto = null, FullName = "Безымянный Безымяни Безымяни"},
        new Student() { Foto = null, FullName = "Фамилия Имя Отчество"}
    };
    public MainWindow()
    {
        InitializeComponent();
        InitStudentsList();
    }

    private void InitStudentsList()
    {
        foreach (var item in students)
        {
            mainSP.Children.Add(RowTemplate.CreateRow(item));
            mainSP.Children.Add(new Border() { BorderBrush = Brushes.Cyan, BorderThickness = new Thickness(0.5)});
        }
    }
}

class Student
{
    public Image Foto { get; set; }
    public string FullName { get; set; }
}

static class RowTemplate
{
    public const double COLUMN_WIDTH = 150;
    public const double IMAGE_WIDTH = 100;

    public static StackPanel CreateRow(Student student)
    {
        var result = new StackPanel() {
            Orientation = Orientation.Horizontal,
            Height = 50,
            VerticalAlignment = VerticalAlignment.Top
        };

        // Фото студента
        result.Children.Add(
            new Image()
            {
                Height = result.Height,
                Width = IMAGE_WIDTH,
                Stretch = Stretch.Fill,
                Source = student.Foto?.Source
            });

        // ФИО студента
        result.Children.Add(
            new TextBlock()
            {
                Width = COLUMN_WIDTH,
                TextWrapping = TextWrapping.Wrap,
                TextAlignment = TextAlignment.Center,
                Text = student.FullName
            });

        //отметить присутствие на занятие
        result.Children.Add(CreatePresenceRadioButton(student.FullName));

        // для выставления оценки
        result.Children.Add(CreateComboBox(5));

        // для комментариев
        result.Children.Add(
            new TextBox()
            {
                Width = COLUMN_WIDTH,
                TextWrapping = TextWrapping.Wrap,
                TextAlignment = TextAlignment.Center
            });

        return result;
    }

    private static Grid CreatePresenceRadioButton(string name)
    {
        var result = new Grid() { Width = COLUMN_WIDTH };
        var rb = new Grid() { Width = 60, Height = 20 };

        rb.Children.Add(
            new RadioButton() 
            {
                GroupName = name,
                BorderBrush = Brushes.Green,
                BorderThickness = new Thickness(2),
                HorizontalAlignment = HorizontalAlignment.Left
            });

        rb.Children.Add(
            new RadioButton()
            {
                GroupName = name,
                BorderBrush = Brushes.Red,
                BorderThickness = new Thickness(2),
                HorizontalAlignment = HorizontalAlignment.Right
            });

        result.Children.Add(rb);

        return result;
    }

    private static Grid CreateComboBox(int cbItemCount)
    {
        var result = new Grid() { Width = COLUMN_WIDTH };
        var cb = new ComboBox() 
        { 
            Height = 30,
            Width = 100,
            BorderBrush = Brushes.White
        };

        List<int> grade = new();
        for (int i = 0; i < cbItemCount; i++)
        {
            grade.Add(i+1);
        }
        cb.ItemsSource = grade;

        result.Children.Add(cb);
        return result;
    }
}


