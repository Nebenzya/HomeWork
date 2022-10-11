#include<Windows.h>
#include "Function.h"

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	char str[] = "000001D";

	cout << hex_to_dec(str) << endl << is_hex_number(str) << endl;

	return 0;
}