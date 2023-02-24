using static System.Console;

#if false
//Дан двумерный массив размерностью 5×5, заполненный случайными числами из диапазона от –100 до 100.
//Определить сумму элементов массива, расположенных
//между минимальным и максимальным элементами.

const int row = 5, column = 5;
int[,] array = new int[row, column];
Random rand = new Random();

// Заполнение массива случайными числами
for (int i = 0; i < row; i++)
    for (int j = 0; j < column; j++)
        array[i, j] = rand.Next(-100, 101);

// Поиск минимального и максимального элементов
int min = array[0, 0];
int max = array[0, 0];
int minI = 0, minJ = 0, maxI = 0, maxJ = 0;

for (int i = 0; i < row; i++)
{
    for (int j = 0; j < column; j++)
    {
        if (array[i, j] < min)
        {
            min = array[i, j];
            minI = i;
            minJ = j;
        }
        if (array[i, j] > max)
        {
            max = array[i, j];
            maxI = i;
            maxJ = j;
        }
    }
}

// Подсчет суммы элементов между минимальным и максимальным
int sum = 0;
int startI = Math.Min(minI, maxI) + 1;
int endI = Math.Max(minI, maxI);

for (int i = startI; i < endI; i++)
{
    int startJ = (i == minI || i == maxI) ? Math.Min(minJ, maxJ) + 1 : 0;
    int endJ = (i == minI || i == maxI) ? Math.Max(minJ, maxJ) : 4;

    for (int j = startJ; j <= endJ; j++)
        sum += array[i, j];
}

Console.WriteLine("Сумма элементов между минимальным и максимальным значением: " + sum);

#endif

//Пользователь с клавиатуры вводит в строку арифметическое выражение. Приложение должно посчитать
//его результат. Необходимо поддерживать только две
//операции: +и –.

WriteLine("Введите арифметическое выражение (только + и -):");
string expression = ReadLine();

int result = 0;
int operand = 0;
char lastOperator = '+';

for (int i = 0; i < expression.Length; i++)
{
    char c = expression[i];

    if (char.IsDigit(c))
        operand = operand * 10 + (c - '0');

    if (!char.IsDigit(c) || i == expression.Length - 1)
    {
        if (lastOperator == '+')
            result += operand;
        else
            result -= operand;

        operand = 0;
        lastOperator = c;
    }
}

Console.WriteLine("Результат: " + result);