#include <cmath>
#include "Function.h"

void to_upper(char str[]) {
	for (int i = 0; str[i]; i++)
	{
		if (str[i] >= 'a' && str[i] <= 'z')
			str[i] -= ' ';
		else if (str[i] >= 'а' && str[i] <= 'я')
			str[i] -= ' ';
		else if (str[i] == 'ё') 
			str[i] = 'Ё';
	}
}
void to_lower(char str[]) {
	for (int i = 0; str[i]; i++)
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] += ' ';
		else if (str[i] >= 'А' && str[i] <= 'Я')
			str[i] += ' ';
		else if (str[i] == 'Ё')
			str[i] = 'ё';
	}
}

void remove_symbol(char str[], const char symbol)
{
	for (int i = 0; str[i]; i++)
	{
		while (str[i] == symbol)
		{
			for (int j = i; str[j]; j++)str[j] = str[j + 1];
		}
	}
}
void shrink(char str[]) {
	for (int i = 0; str[i]; i++)
	{
		while (str[i] == ' ' && str[i + 1] == ' ')
		{
			for (int j = i + 1; str[j]; j++)
			{
				str[j] = str[j + 1];
			}
		}
	}
}
bool is_palindrome(const char str[]) {
	char* buffer = new char[strlen(str) + 1]{};
	//strcpy(buffer, str);
	to_lower(buffer);
	remove_symbol(buffer, ' ');
	int size = strlen(buffer);
	for (int i = 0; i < size; i++)
	{
		if (buffer[i] != buffer[size - 1 - i])
		{
			delete[] buffer;
			return false;
		}
	}
	delete[] buffer;
	return true;
}

// ==========================================

bool is_int_number(const char str[]) {

	for (int i = 0; str[i]; i++)
	{
		if (str[i] < '0' || str[i] > '9')
			return false;
	}
	return true;
}

int  to_int_number(char str[]) {

	int size = strlen(str), value = 0, j = 0;

	if (is_int_number(str)) {
		for (int i = size - 1, j = 0; i > -1; i--)
		{
			value += (str[i] - 48) * pow(10, j);
			j++;
		}
		
		return value;
	}
}

bool is_bin_number(const char str[]) {

	for (int i = 0; str[i]; i++)
	{
		if (!(str[i] == '0' || str[i] == '1'))
			return false;
	}
	return true;
}

int  bin_to_dec(char str[]) {

	if (is_bin_number(str))
	{
		int value = 0, j = 0;
		for (int i = strlen(str) - 1; i > -1; i--) {

			value += (str[i]-48) * pow(2, j);
			j++;
		}
		return value;
	}
}

bool is_hex_number(const char str[]) {

	for (int i = 0; str[i]; i++)
	{
		if (!((str[i] >= '0' && str[i] <= '9') || (str[i] >= 'A' && str[i] <= 'F')))
			return false;
	}
	return true;

}

int  hex_to_dec(char str[]) {

	if(is_hex_number(str))
	{
		int sum = 0, value, size = strlen(str) - 1;
		for (int i = 0; str[i]; i++)
		{
			switch (toupper(str[i])) {
				case '1': value = 1; break;
				case '2': value = 2; break;
				case '3': value = 3; break;
				case '4': value = 4; break;
				case '5': value = 5; break;
				case '6': value = 6; break;
				case '7': value = 7; break;
				case '8': value = 8; break;
				case '9': value = 9; break;
				case '0': value = 0; break;
				case 'A': value = 10; break;
				case 'B': value = 11; break;
				case 'C': value = 12; break;
				case 'D': value = 13; break;
				case 'E': value = 14; break;
				case 'F': value = 15; break;
			}
			sum += value * pow(16, size);
			size--;
		}
		return sum;
	}
}