#include<iostream>
#include<string>
#include<vector>
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
	{
		cout << "HConstructor:\t" << this << endl;
	}
	~Human()
	{
		cout << "HDestructor:\t" << this << endl;
	}

	//				Methods:
	void print()const
	{
		cout << last_name << " " << first_name << " " << age << "\n";
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
	Student(const Human& homo, const string& specialty, const string& group, double rating, double attendance) : Human(homo)
	{
		this->specialty = specialty;
		this->group = group;
		this->rating = rating;
		this->attendance = attendance;
		cout << "SConstructor:\t" << this << endl;
	}
	~Student()
	{
		cout << "SDestructor:\t" << this << endl;
	}

	//					Methods:
	void print()const
	{
		Human::print();
		cout << specialty << " " << group << " " << rating << " " << attendance << endl;
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
	Teacher(const Human& homo, const string& specialty, unsigned int experience) : Human(homo)
	{
		set_specialty(specialty);
		set_experience(experience);
		cout << "TConstructor:\t" << this << endl;
	}
	~Teacher()
	{
		cout << "TDestructor:\t" << this << endl;
	}

	//				Methods:
	void print()const
	{
		Human::print();
		cout << specialty << " " << experience << endl;
	}
};


class Graduate : Student
{
	const double minRating = 60, minAttendance = 80;
	const int minDiplomSize = 3;

	vector<string>diplomProject;

public:
	Graduate(const Student& stud) : Student(stud)
	{
	}

	~Graduate()
	{
	}

	void WritingDiplom(const string str) 
	{
		diplomProject.push_back(str);
	}

	bool DiplomDone() const
	{
		return diplomProject.size() > minDiplomSize;
	}

	bool AdmissionToExam() const
	{
		return rating > minRating && attendance > minAttendance && DiplomDone();
	}

	void Print() 
	{
		Student::print();
	}
};



void main()
{
	setlocale(LC_ALL, "");
	Human human("Montana", "Antoio", 25);
	human.print();

	Student stud(human, "Chemistry", "WW_220", 90, 95);
	stud.print();

	Graduate grad(stud);

	while (!grad.DiplomDone())
	{
		string str;
		cin >> str;
		grad.WritingDiplom(str);
	}

	grad.Print();
	cout << "\nadmitted to the exam:\t" << grad.AdmissionToExam() << endl;
}