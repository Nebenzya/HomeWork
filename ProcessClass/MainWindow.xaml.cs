using System;
using System.Diagnostics;
using System.Windows;

namespace ProcessClass;
    
public partial class MainWindow : Window
{
    private Process _process;

    public MainWindow()
    {
        InitializeComponent();
        _process = new();
        _process.StartInfo = new ProcessStartInfo("notepad.exe");
        _process.Exited += Process_Exited;
    }

    private void Process_Exited(object? sender, EventArgs e)
    {
        inputText.Text = string.Empty;
    }

    private void start_Click(object sender, RoutedEventArgs e)
    {
        _process.StartInfo.Arguments = inputText.Text;
        _process.Start();
    }
}
