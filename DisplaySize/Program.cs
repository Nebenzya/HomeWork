//Разработать приложение, позволяющее определить
//размер диагонали монитора текущего компьютера в дюймах

using Windows.Devices.Display;

DisplayMonitor dm = new();
Console.WriteLine(dm.PhysicalSizeInInches);