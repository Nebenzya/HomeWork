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
	Undergrad(const Student& st, string topic) : Student(st)
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

//  =============================  VARIANT #1 =====================================
ostream& operator<<(ostream& os, const Human& obj) { return os << obj.toString(); }
ostream& operator<<(ostream& os, const Student& obj) { return os << obj.toString(); }
ostream& operator<<(ostream& os, const Teacher& obj) { return os << obj.toString(); }
ostream& operator<<(ostream& os, const Undergrad& obj) { return os << obj.toString(); }

//  =============================  VARIANT #2 =====================================
ostream& operator<<(ostream& os, const Human* obj) { return os << obj->toString(); }


#define delimiter cout << "\n------------------------------------------\n" << endl;

void main()
{
	//  =============================  VARIANT #1 =====================================
	Human hum("Schreder", "Hank", 40);
	cout << hum << endl;
	delimiter

	Student stud(hum, "Criminalistic", "WW_220", 95, 80);
	cout << stud << endl;
	delimiter

	Undergrad und(stud, "How to catch Heisenberg");
	cout << und << endl;
	delimiter

	//  =============================  VARIANT #2 =====================================
	Human* h = &und;
	cout << h << endl;
	delimiter
}