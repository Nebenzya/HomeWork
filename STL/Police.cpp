#include<iostream>
#include<fstream>
#include<string>
#include<map>
#include<list>
using std::cin;
using std::cout;
using std::endl;


const std::string filename = "Base.txt";

const std::map<int, std::string> violation =
{
	{0, "driving without a license"},
	{1, "speeding"},
	{2, "driving through a red light"},
	{3, "parking in the wrong place"},
	{4, "drunk driving"},
	{5, "overtaking through solid"},
	{6, "lack of insurance"}
};

class Crime
{
	int id;
	std::string place;
public:
	Crime(int violation, const std::string& place)
		:id(violation), place(place) {}
	~Crime() {}
	friend std::ostream& operator<<(std::ostream& os, const Crime& obj);
};

std::ostream& operator<<(std::ostream& os, const Crime& obj)
{
	return os << violation.at(obj.id) << ", " << obj.place;
}

void SaveBase(const std::map<std::string, std::list<Crime>>& base) {

	std::ofstream fout;
	fout.open(filename);
	for (auto i : base)
	{
		cout << i.first << ": ";
		for (auto j : i.second)
		{
			cout << j << " ";
		}
		cout << endl;
	}
	fout.close();
}

std::map<std::string, std::list<Crime>> LoadBase() {

	std::map<std::string, std::list<Crime>> result;

	std::ifstream fin(filename);
	if (fin.is_open())
	{
		std::string buffer;
		while (!fin.eof())
		{
			std::list<Crime> crime_lst;
			std::getline(fin, buffer);

			// Deserialization logic:
			// Do something with "buffer"
			// in the loop: crime_lst.push_back(new Crime());

			// result.insert(std::pair< name, crime_lst);
		}
	}
	return result;
}

void main()
{
	setlocale(LC_ALL, "");
	std::map<std::string, std::list<Crime>> base =
	{
		{"a777bb", {Crime(0, "street"), Crime(6, "street"), Crime(3, "square")}},
		{"m123ab", {Crime(1, "highway")}},
		{"a234bb", {Crime(5, "highway"), Crime(4, "street")}}
	};

	for (auto i : base)
	{
		cout << i.first << ":\t";
		for (auto j : i.second)
		{
			cout << j << ";";
		}
		cout << endl;
	}
}

