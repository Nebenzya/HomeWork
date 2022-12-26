#include<iostream>
#include<fstream>
#include<string>
#include<map>
#include<list>
using std::cin;
using std::cout;
using std::endl;
using std::string;


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
	const int get_id() { return id; }
	Crime(int violation, const std::string& place = "")
		:id(violation), place(place) {}
	~Crime() {}
	friend std::ostream& operator<<(std::ostream& os, const Crime& obj);
};

std::ostream& operator<<(std::ostream& os, const Crime& obj)
{
	return os << violation.at(obj.id) << ", " << obj.place;
}

const std::string FILENAME = "Base.txt";
const string CAR_NUMBER_STR = "number: ";
const string CAR_CRIME_STR = "crime: ";
const size_t CAR_NUMBER_SIZE = 5;

void SaveBase(const std::map<std::string, std::list<Crime>>& base) {

	std::ofstream fout;
	fout.open(FILENAME);
	for (auto i : base)
	{
		fout << CAR_NUMBER_STR << i.first << ": ";
		for (auto j : i.second)
		{
			fout << CAR_CRIME_STR << j.get_id() << ", ";
		}
		fout << endl;
	}
	fout.close();
}

std::map<std::string, std::list<Crime>> LoadBase() {

	std::map<std::string, std::list<Crime>> result;

	std::ifstream fin(FILENAME);
	if (fin.is_open())
	{
		while (!fin.eof())
		{
			string buffer;
			std::getline(fin, buffer);

			size_t car_found = buffer.find(CAR_NUMBER_STR);

			if (car_found != string::npos) 
			{
				string car_number;
				car_number.assign(buffer, car_found + CAR_NUMBER_STR.length(), CAR_NUMBER_SIZE);

				std::list<Crime> crime_lst;

				while(buffer.find(CAR_CRIME_STR) != string::npos)
				{
					size_t car_crime_found = buffer.find(CAR_CRIME_STR);
					size_t last_pos = car_crime_found + CAR_CRIME_STR.length() + 1;

					crime_lst.push_back(Crime((int)buffer[last_pos]));
					buffer.erase(car_crime_found, last_pos);
				}

				result[car_number] = crime_lst;
			}
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

	SaveBase(base);
	auto result = LoadBase();

	for (auto i : result)
	{
		cout << i.first << ":\t";
		for (auto j : i.second)
		{
			cout << j << ";";
		}
		cout << endl;
	}

}

