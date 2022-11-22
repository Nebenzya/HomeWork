#include<iostream>
#include<string>
#include<fstream>
using namespace std;

class Human
{
	string last_name;
	string first_name;
	unsigned int age;
public:
	const string& get_last_name()const { return last_name; }
	const string& get_first_name()const { return first_name; }
	unsigned int get_age()const { return age; }

	//				Constructors:
	Human(const string& last_name, const string& first_name, unsigned int age) :
		last_name(last_name), first_name(first_name), age(age)
	{}

	//				Methods:
	virtual string toString()const
	{
		return get_last_name() + " " + get_first_name() + " " + to_string(get_age());
	}

	
};

class Student : public Human
{
	string specialty;
	string group;

protected:
	double rating;
	double attendance;

public:
	const string& get_specialty()const { return specialty; }
	const string& get_group()const { return group; }
	double get_rating()const { return rating; }
	double get_attendance()const { return attendance; }

	void set_rating(double rating)
	{
		this->rating = rating;
	}
	void set_attendance(double attendance)
	{
		this->attendance = attendance;
	}

	//					Constructors:
	Student(const string& last_name, const string& first_name, unsigned int age, const string& specialty, const string& group, double rating, double attendance) : Human(last_name, first_name, age)
	{
		this->specialty = specialty;
		this->group = group;
		this->rating = rating;
		this->attendance = attendance;
	}

	//					Methods:
	string toString()const override
	{
		string str = Human::toString() + " " + get_specialty() + " " + get_group() +
			" " + to_string(get_rating()) + " " + to_string(get_attendance());
		return str;
	}
};

class Teacher :public Human
{
	string specialty;
	unsigned int experience;
public:
	const string& get_specialty()const { return specialty; }
	unsigned int get_experience()const { return experience; }
	void set_specialty(const string& specialty)
	{
		this->specialty = specialty;
	}
	void set_experience(unsigned int experience)
	{
		this->experience = experience;
	}

	//				Constructors:
	Teacher(const string& last_name, const string& first_name, unsigned int age, const string& specialty, unsigned int experience) : Human(last_name, first_name, age)
	{
		set_specialty(specialty);
		set_experience(experience);
	}

	//				Methods:
	string toString()const override
	{
		return Human::toString() + "\n" + get_specialty() + " " + to_string(get_experience());
	}
};

class Undergrad :public Student
{
	string topic;
public:
	const string& get_topic()const { return topic; }
	void set_topic(const string& topic) { this->topic = topic; }

	//				Constructors:
	Undergrad(const string& last_name, const string& first_name, unsigned int age, const string& specialty, const string& group, double rating, double attendance, string topic) : Student(last_name, first_name, age, specialty, group, rating, attendance)
	{
		set_topic(topic);
		cout << "GConstructor:\t" << this << endl;
	}
	~Undergrad()
	{
		cout << "GDestructor:\t" << this << endl;
	}
	//				Methods:
	string toString()const override
	{
		return Student::toString() + " " + get_topic();
	}
};

ostream& operator<<(ostream& os, const Human* obj) { return os << obj->toString(); }

void Save(Human* group[], const int n, const std::string& filename)
{
	std::ofstream fout(filename);
	for (int i = 0; i < n; i++)
	{
		fout.width(15);
		fout << std::left;
		fout << typeid(*group[i]).name() << ":\t";
		fout << group[i]->toString() << endl;
	}
	fout.close();
	std::string command = "notepad " + filename;
	system(command.c_str());
}

Human** Load(const std::string& filename, int& n)
{
	std::ifstream fin(filename);
	//1) Вычисляем размер массива:
	if (fin.is_open())
	{
		std::string buffer;
		for (n = 0; !fin.eof(); n++)
		{
			std::getline(fin, buffer);
		}
		n--;
	}

	Human** group = new Human * [n] {};

	fin.clear();
	fin.seekg(0);

	if (fin.is_open())
	{
		std::string type;
		for (int i = 0; i < n; i++)
		{
			std::getline(fin, type, ' ');
			group[i] = HumanFactory(type);
			fin >> *group[i];
		}
	}

	return group;
}