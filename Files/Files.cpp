#include<iostream>
#include<fstream>
#include "../Academy/Academy.cpp"
using namespace std;

void main()
{
	setlocale(LC_ALL, "");
	std::string fileName = "group.txt";
	const int SIZE = 6;
	Human* group[SIZE] =
	{
		new Student("Pinkman", "Jessie", 25, "Chemistry", "WW_220", 90, 95),
		new Teacher("White", "Walter", 50, "Chemistry", 20),
		new Undergrad("Schreder", "Hank", 40, "Criminalistic", "WW_220", 95, 80, "How to catch Heisenberg"),
		new Student("Vercetti", "Tomas", 30, "Criminalistic", "Vice", 98, 99),
		new Teacher("Diaz", "Ricardo", 50, "Weapons distribution", 15),
		new Teacher("Einstein", "Albert", 143, "Astronomy", 120)
	};


	std::ofstream fout;	
	fout.open(fileName, std::ios::app);
	
	for (size_t i = 0; i < SIZE; i++)
	{
		fout << group[i]->toString() << endl;

		delete group[i];
	}
	fout.close();			

	int n = 0;
	Human** newGroup = Load(fileName, n);
}