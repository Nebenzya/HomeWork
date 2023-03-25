using System.Collections;
using static System.Console;


ArrayList auditory = new ArrayList
{
    new Student
    {   
        FirstName = "Harry",
        LastName = "Potter",
        BirthDate = new DateTime(1981, 11,30)
    },
    new Student
    {
        FirstName = "Drako",
        LastName = "Malfoy",
        BirthDate = new DateTime(1981,12,23)
    },
    new Student
    {
        FirstName = "Polumna",
        LastName = "Lovegood",
        BirthDate = new DateTime(1984, 3,14)
    },
    new Student
    {
        FirstName = "Vasuy",
        LastName = "Pupkin",
        BirthDate = new DateTime(988, 7,28)
    }
};


WriteLine("Список студентов: ");
foreach (Student student in auditory)
{
    WriteLine(student);
}

WriteLine("Сортировка студентов по фамилии: ");
auditory.Sort();
foreach (Student student in auditory)
{
    WriteLine(student);
}

WriteLine("Сортировка по дате рождения: ");
auditory.Sort(new StudentComparer(SortStudentBy.BirthDate));
foreach (Student student in auditory)
{
    WriteLine(student);
}

WriteLine("Сортировка по имени: ");

auditory.Sort(new StudentComparer(SortStudentBy.FirstName));
foreach (Student student in auditory)
{
    WriteLine(student);
}



enum SortStudentBy
{
    FirstName,
    LastName,
    BirthDate,
    OtherValue
}

class Student : IComparable
{
    public string FirstName { get; set; }
    public string LastName { get; set; }
    public DateTime BirthDate { get; set; }
    public int AnyOtherValue { get; set; }

    public int CompareTo(object obj)
    {
        if (obj is Student)
        {
            return LastName.CompareTo((obj as Student).LastName);
        }
        throw new NotImplementedException();
    }

    public override string ToString()
    {
        return $"Фамилия: {LastName}\nИмя: {FirstName}\nДата рождения: {BirthDate.ToShortDateString()}\n";
    }
}

class StudentComparer : IComparer
{
    readonly SortStudentBy sortby;

    public StudentComparer(SortStudentBy sortby)
    {
        this.sortby = sortby;
    }

    public int Compare(object x, object y)
    {
        if (x is Student && y is Student)
        {
            switch (sortby)
            {
                case SortStudentBy.FirstName:
                    return string.Compare((x as Student).FirstName, (y as Student).FirstName);
                case SortStudentBy.LastName:
                    return string.Compare((x as Student).LastName, (y as Student).LastName);
                case SortStudentBy.BirthDate:
                    return DateTime.Compare((x as Student).BirthDate, (y as Student).BirthDate);
                case SortStudentBy.OtherValue:
                    return string.Compare((x as Student).AnyOtherValue.ToString(), (y as Student).AnyOtherValue.ToString());
            }
        }
        throw new NotImplementedException();
    }
}