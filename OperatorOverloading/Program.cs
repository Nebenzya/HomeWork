//Ранее в одном из практических заданий вы создавали
//класс «Журнал». Добавьте к уже созданному классу информацию о количестве сотрудников. Выполните перегрузку
//+ (для увеличения количества сотрудников на указанную
//величину), — (для уменьшения количества сотрудников
//на указанную величину), == (проверка на равенство количества сотрудников), < и > (проверка на меньше или
//больше количества сотрудников), != и Equals.Используйте
//механизм свойств для полей класса.

class Employee
{
    public string Name { get; set; }
    public string Position { get; set; }
}

class Magazine
{
    public string Name { get; set; }
    public int YearFoundation { get; set; }
    public string Description { get; set; }
    public string PhoneNumber { get; set; }
    public string Email { get; set; }
    public int EmployeesCount { get => _employees.Count; }

    private List<Employee> _employees;

    public Magazine(string name, int yearFoundation)
    {
        Name = name;
        YearFoundation = yearFoundation;
        _employees = new();
    }

    public override string ToString()
    {
        return $"Название журнала: {Name}\n" +
               $"Год основания журнала: {YearFoundation}\n" +
               $"Описание журнала: {Description}\n" +
               $"Контактный телефон журнала: {PhoneNumber}\n" +
               $"Контактный e-mail журнала: {Email}";
    }

    public void AddEmployee(Employee employee) => _employees.Add(employee);

    public void FireEmployee()
    {
        if (EmployeesCount > 0)
            _employees.RemoveAt(new Random().Next(0, EmployeesCount));
    }

    public static Magazine operator +(Magazine magazine, int countNewEmployees)
    {
        for (int i = 0; i < countNewEmployees; i++)
            magazine.AddEmployee(new Employee());

        return magazine;
    }

    public static Magazine operator -(Magazine magazine, int countNewEmployees)
    {
        for (int i = 0; i < countNewEmployees; i++)
            magazine.FireEmployee();

        return magazine;
    }

    public static bool operator ==(Magazine magazine1, Magazine magazine2) => magazine1.EmployeesCount == magazine2.EmployeesCount;
    public static bool operator !=(Magazine magazine1, Magazine magazine2) => magazine1.EmployeesCount != magazine2.EmployeesCount;
    public static bool operator >(Magazine magazine1, Magazine magazine2) => magazine1.EmployeesCount > magazine2.EmployeesCount;
    public static bool operator <(Magazine magazine1, Magazine magazine2) => magazine1.EmployeesCount < magazine2.EmployeesCount;
}
