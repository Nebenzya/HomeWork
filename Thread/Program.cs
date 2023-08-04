
//слушатель подключений пользователей(имитация сервера)
ThreadStart ts = new ThreadStart(ListenerClient);
Thread ListenerThread = new Thread(ts);
ListenerThread.Start();


void ListenerClient()
{
    int Counter = 0;
    while (true)
    {
        Console.WriteLine("Нажмите любую клавишу для симуляции подключения");
        Console.ReadKey(true);
        ParameterizedThreadStart pts = new ParameterizedThreadStart(UserThreadMethod);
        Thread userThread = new Thread(pts);
        userThread.Start(Counter.ToString() as object);
        Counter++;
    }
}

void UserThreadMethod(object obj)
{
    string? userName = obj as string;
    Console.WriteLine($"Пользователь #{userName} подключился");
    while (true)
    {
        switch (GetUserCommands())
        {
            case 1:
                Console.WriteLine($"{userName} подписался на новости");
                break;
            case 2:
                Console.WriteLine($"{userName} начал чат");
                break;
            case 3:
                Console.WriteLine($"{userName} купил продуцию в магазине");
                break;
            case 4:
                Console.WriteLine($"{userName} отправил сообщение");
                break;
            case 0:
                Console.WriteLine($"{userName} отключился");

                return;
        }
    }
}

int GetUserCommands()
{
    if (int.TryParse(Console.ReadLine(), out int command))
    {
        if (command > 0 && command < 5)
            return command;
    }
    return 0;
}