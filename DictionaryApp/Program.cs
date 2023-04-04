//Создавать словарь.При создании нужно указать тип словаря.
//Например, англо-русский или русско-английский.
//■ Добавлять слово и его перевод в уже существующий словарь.
//■ Удалять слово или перевод. Если удаляется слово, все его переводы удаляются
//вместе с ним.Нельзя удалить перевод слова, если это последний вариант перевода.
//■ Словари должны храниться в файлах.
//■ Слово и варианты его переводов можно экспортировать в отдельный файл результата.
//■ При старте программы необходимо показывать меню для работы с программой.
//Если выбор пункта меню открывает подменю, то тогда в нем требуется предусмотреть возможность возврата в предыдущее меню.


bool exit = false;
MyDictionary myDictionary = null;

while (!exit)
{
    Console.WriteLine("Введите одну из команд:\n" +
        "new - создать новый словарь\n" +
        "save - сохранить текущий словарь в файл\n" +
        "add - команда для добавления слова или перевода\n" +
        "delete - команда для удаления слова или перевода\n" +
        "exit - выйти из программы");

    MenuCommands(Console.ReadLine());
}

Console.WriteLine("Всего доброго!");


void MenuCommands(string input)
{
    switch (input.ToLower().Trim())
    {
        case "new":
            CreateDictionary();
            break;
        case "save":
            SaveDictionary();
            break;
        case "add":
            AddCommand();
            break;
        case "delete":
            DeleteCommand();
            break;
        case "exit":
            exit = true;
            break;
        default:
            Console.WriteLine("Неверная команда! Попробуйте снова.");
            break;
    }
}

void SaveDictionary()
{
    if(myDictionary != null)
    {

    }
    else 
    {
        Console.WriteLine("Ошибка! Создайте сначала словарь.");
    }
}

void CreateDictionary()
{
    myDictionary = new MyDictionary();
    Console.WriteLine("Укажите с какого языка будете переводить:");
    myDictionary.FromLanguage = Console.ReadLine();
    Console.WriteLine("Укажите на какой языка будете переводить:");
    myDictionary.ToLanguage = Console.ReadLine();

    Console.WriteLine("Словарь создан!");
}

void AddCommand()
{
    if (myDictionary != null)
    {
        while (true)
        {
            Console.Clear();
            Console.WriteLine("Выбирите действие:\nappend - добавить новое слово в словарь\ninsert - добавить перевод к существующему слову\nback - вернуться в предыдущее меню");
            switch (Console.ReadLine().ToLower())
            {
                case "append":
                    AddNewWord();
                    return;
                case "insert":
                    AddNewTranslate();
                    return;
                case "back":
                    return;
                default:
                    Console.WriteLine("Неверная команда! Попробуйте снова.");
                    break;
            }
        }

    }
    else
    {
        Console.WriteLine("Ошибка! Создайте сначала словарь.");
    }
}

void AddNewWord()
{
    Console.WriteLine("Введите слово:");
    string word = Console.ReadLine().ToLower();

    Console.WriteLine("Введите перевод:");
    myDictionary.Words.Add(word, new List<string>() { Console.ReadLine().ToLower() });

    Console.WriteLine($"Слово \"{word}\" добавлено в словарь");
}

void AddNewTranslate()
{
    Console.WriteLine("Введите слово к которому хотите добавить перевод:");
    string word = Console.ReadLine().ToLower();
    if (myDictionary.Words.ContainsKey(word))
    {
        Console.WriteLine("Введите перевод:");
        myDictionary.Words.Add(word, new List<string>() { Console.ReadLine() });

        Console.WriteLine($"Слово \"{word}\" добавлено в словарь");
    }
    else
    {
        Console.WriteLine("Такого слова нет!");
    }
}

void DeleteCommand()
{
    if (myDictionary != null)
    {
        while (true)
        {
            Console.Clear();
            Console.WriteLine("Выбирите действие:\nerase - удалить слово из словаря\npop - удалить перевод у существующего слова\nback - вернуться в предыдущее меню");
            switch (Console.ReadLine().ToLower())
            {
                case "erase":
                    DeleteWord();
                    return;
                case "pop":
                    DeleteTranslate();
                    return;
                case "back":
                    return;
                default:
                    Console.WriteLine("Неверная команда! Попробуйте снова.");
                    break;
            }
        }

    }
    else
    {
        Console.WriteLine("Ошибка! Создайте сначала словарь.");
    }
}

void DeleteTranslate()
{
    Console.WriteLine("Введите слово у которого хотите удалить перевод:");
    string word = Console.ReadLine().ToLower();
    if (myDictionary.Words.ContainsKey(word))
    {
        Console.WriteLine("Введите перевод:");
        string translate = Console.ReadLine().ToLower();
        if (myDictionary.Words[word].Contains(translate) || myDictionary.Words.Count > 1)
        {
            myDictionary.Words[word].Remove(translate);
        }
        else
        {
            Console.WriteLine("Операция невозможна!");
            return;
        }

        Console.WriteLine($"Перевод \"{translate}\" удалён у слова \"{word}\"");
    }
    else
    {
        Console.WriteLine("Такого слова нет!");
    }
}

void DeleteWord()
{
    Console.WriteLine("Введите слово которое хотите удалить из словаря:");
    string word = Console.ReadLine().ToLower();
    if (myDictionary.Words.ContainsKey(word))
    {
        myDictionary.Words.Remove(word);
        Console.WriteLine($"Слово \"{word}\" удалено из словаря");
    }
    else
    {
        Console.WriteLine("Такого слова нет!");
    }
}

class MyDictionary
{
    public string FromLanguage { set; get; }
    public string ToLanguage { set; get; }
    public Dictionary<string, List<string>> Words { get; }

    private readonly string path = $"{Directory.GetCurrentDirectory()}\\dictionary.txt";
    private FileInfo fileInf;

    public MyDictionary()
    {
        Words = new();
        fileInf = new FileInfo(path);
    }

    public void Save()
    {
        if (fileInf.Exists)
        {
            using (StreamWriter writer = fileInf.AppendText())
            {
                writer.WriteLine(Words.ToString());
            }
            Console.WriteLine($"Словарь сохранён в файл по адресу: {path}");
        }
    }
}