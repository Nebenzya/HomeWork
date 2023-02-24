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