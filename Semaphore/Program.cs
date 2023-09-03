
var rand = new Random();
var sem = new Semaphore(3, 3);

for (int i = 1; i < 9; i++)
{
    Reader(i);
}

void Reader(int i)
{
    var myThread = new Thread(Read)
    { Name = $"Пользователь {i}" };
    myThread.Start();
}

void Read()
{
    sem.WaitOne();

    string userName = Thread.CurrentThread.Name;

    Console.WriteLine($"{userName} подключился!");

    try
    {
        for (int i = 3; i > 0; i--)
        {
            Thread.Sleep(1000);

            switch (GetActionId())
            {
                case 0: Console.WriteLine($"#{userName} подписался на новости"); break;
                case 1: Console.WriteLine($"#{userName} послущал музыку"); break;
                case 2: Console.WriteLine($"#{userName} купил продукцию в магазине"); break;
                case 3: Console.WriteLine($"#{userName} отправил сообщение"); break;
                default: Console.WriteLine($"!!Случился дисконнект {userName}"); throw new Exception();
            }
        }
    }
    catch (Exception)
    {

    }
    finally
    {
        Thread.Sleep(1000);
        Console.WriteLine($"{userName} вышел!");
        sem.Release();
    }
}

int GetActionId() => rand.Next(0, 5);


