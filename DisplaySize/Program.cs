//Разработать приложение, позволяющее определить
//размер диагонали монитора текущего компьютера в дюймах

using System.Windows.Devices.Display;

DisplayMonitor dm = new();
Console.WriteLine(dm.PhysicalSizeInInches);