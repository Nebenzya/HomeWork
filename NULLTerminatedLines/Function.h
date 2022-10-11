#pragma once
#include <iostream>
using namespace std;

void to_upper(char str[]);	//Переводит строку в верхний регистр
void to_lower(char str[]);	//Переводит строку в нижний регистр
void remove_symbol(char str[], const char symbol); //Удаляет все указанные символы из строки
void shrink(char str[]);	//Удаляет лишние пробелы из предложения
							//Хорошо      живет     на     свете      Винни      Пух
							//Хорошо живет на свете Винни Пух

bool is_palindrome(const char str[]);	//Проверяет, является ли строка палиндромом

bool is_int_number(const char str[]);	//Проверяет, является ли строка целым десятичным числом
int  to_int_number(char str[]);			//Если строка является целым десятичным числом, возвращает ее числовое значение
bool is_bin_number(const char str[]);	//Проверяет, является ли строка двоичным числом
int  bin_to_dec(char str[]);			//Если строка является двоичным числом, возвращает ее десятичное значение
bool is_hex_number(const char str[]);	//Проверяет, является ли строка шестнадцатеричным числом
int  hex_to_dec(char str[]);
