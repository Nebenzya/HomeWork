using static System.Console;

//Задание 1

#if false

if (int.TryParse(ReadLine(), out int num))
{
    if (num > 0 && num < 101)
    {
        if (num % 3 == 0) WriteLine("Fizz");
        if (num % 5 == 0) WriteLine("Buzz");
        if (num % 3 != 0 && num % 5 != 0) WriteLine(num);
    }
    else
        WriteLine("Error");
} 
#endif


//Задание 2

#if false

if (int.TryParse(ReadLine(), out int num2) && int.TryParse(ReadLine(), out int perс))
{
    WriteLine(num2 * ((double)perс / 100));
} 
#endif


//Задание 3

#if false

string str = string.Empty;

for (int i = 0; i < 4; i++)
{
    str += ReadLine();
}

WriteLine(str);

#endif


//Задание 4

#if false
string str = ReadLine();
int index1 = int.Parse(ReadLine()), index2 = int.Parse(ReadLine());

if (str.Length == 6 || int.TryParse(str, out int x))
{
    char buf = str[index1];
    str = str.Replace(str[index1], str[index2]);
    WriteLine(str.Replace(str[index2], buf));
}

#endif


//Задание 5

#if false

DateTime inputDate = DateTime.Parse(ReadLine());

if (inputDate.Month == 1 || inputDate.Month == 2 || inputDate.Month == 12) Write("Winter ");
else if (inputDate.Month > 2 && inputDate.Month < 6) Write("Spring ");
else if (inputDate.Month > 5 && inputDate.Month < 9) Write("Summer ");
else Write("Autumn ");

WriteLine(inputDate.DayOfWeek.ToString());

#endif


//Задание 6

#if false
if (float.TryParse(ReadLine(), out float temp))
{
    string toConvert = ReadLine();
    if (toConvert == "C" || toConvert == "c") WriteLine($"{5.0f / 9 * (temp - 32)}C");
    else if (toConvert == "F" || toConvert == "f") WriteLine($"{temp * 9.0f / 5 + 32}F");
} 
#endif


//Задание 7

if (int.TryParse(ReadLine(), out int x) && int.TryParse(ReadLine(), out int y))
{
    int min, max;
    if (x > y) { min = y; max = x; }
    else { min = x; max = y; }
    for (; min < max; min++)
        if (min % 2 == 0) Write(min + " ");
}