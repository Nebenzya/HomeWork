using static System.Console;

//Напишите метод, который отображает квадрат из
//некоторого символа. Метод принимает в качестве параметра: длину стороны квадрата, символ.

void DrawSquare(int length, char token)
{
	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < length; j++)
			Write(token);
		WriteLine();
	}
}

//Напишите метод, который проверяет является ли
//переданное число «палиндромом». Число передаётся в
//качестве параметра. Если число палиндром нужно вернуть из метода true, иначе false.
//Палиндром — число, которое читается одинаково как
//справа налево, так и слева направо.

bool IsPalindrome(int number)
{
    int reversedNumber = 0;
    int originalNumber = number;

    while (number != 0)
    {
        reversedNumber = reversedNumber * 10 + number % 10;
        number /= 10;
    }

    return originalNumber == reversedNumber;
}


//Напишите метод, фильтрующий массив на основании
//переданных параметров. Метод принимает параметры:
//оригинальный_массив, массив_с_данными_для_фильтрации.
//Метод возвращает оригинальный массив без элементов, которые есть в массиве для фильтрации

int[] FilterArray(int[] originalArray, int[] filterArray)
{
    List<int> result = new();

    foreach (int element in originalArray)
        if (!filterArray.Contains(element))
            result.Add(element);

    return result.ToArray();
}


//Создайте класс «Журнал». Необходимо хранить в
//полях класса: название журнала, год основания, описание журнала, контактный телефон, контактный e-mail.
//Реализуйте методы класса для ввода данных, вывода
//данных, реализуйте доступ к отдельным полям через
//методы класса.

class Magazine
{
    private string _name;
    private int _yearFounded;
    private string _description;
    private string _phone;
    private string _email;

    public Magazine(string name, int yearFounded, string description, string phone, string email)
    {
        _name = name;
        _yearFounded = yearFounded;
        _description = description;
        _phone = phone;
        _email = email;
    }

    public string GetName() => _name;
    public int GetYearFounded() => _yearFounded;
    public string GetDescription() => _description;
    public string GetPhone() => _phone;
    public string GetEmail() => _email;

    public void EnterData()
    {
        Write("Введите название журнала: ");
        _name = ReadLine();
        Write("Введите год основания журнала: ");
        _yearFounded = int.Parse(ReadLine());
        Write("Введите описание журнала: ");
        _description = ReadLine();
        Write("Введите контактный телефон журнала: ");
        _phone = ReadLine();
        Write("Введите контактный e-mail журнала: ");
        _email = ReadLine();
    }

    public void PrintData()
    {
        WriteLine("Название журнала: " + _name);
        WriteLine("Год основания журнала: " + _yearFounded);
        WriteLine("Описание журнала: " + _description);
        WriteLine("Контактный телефон журнала: " + _phone);
        WriteLine("Контактный e-mail журнала: " + _email);
    }
}
