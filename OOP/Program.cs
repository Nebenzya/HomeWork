using static System.Console;

//Создать базовый класс «Музыкальный инструмент»
//и производные классы «Скрипка», «Тромбон», «Укулеле»,
//«Виолончель». С помощью конструктора установить имя
//каждого музыкального инструмента и его характеристики.
//Реализуйте для каждого из классов методы:
//■ Sound — издает звук музыкального инструмента
//(пишем текстом в консоль);
//■ Show — отображает название музыкального инструмента;
//■ Desc — отображает описание музыкального инструмента;
//■ History — отображает историю создания музыкального инструмента.

abstract class MusicalInstrument
{
    protected string name;
    protected string description;
    protected string history;

    public MusicalInstrument(string name, string description, string history)
    {
        this.name = name;
        this.description = description;
        this.history = history;
    }

    public virtual void Sound() => WriteLine($"{name} издает музыкальный звук.");

    public void Show() => WriteLine($"Название инструмента: {name}");
    public void Desc() => WriteLine($"Описание инструмента {name}: {description}");
    public void History() => WriteLine($"История создания инструмента {name}: {history}");
}

class Violin : MusicalInstrument
{
    public Violin(string name, string description, string history) : base( name, description, history){ }

    public override void Sound() => WriteLine($"{name} издает звук скрипки.");
}

class Trombone : MusicalInstrument
{
    public Trombone(string name, string description, string history) : base(name, description, history){ }

    public override void Sound() => WriteLine($"{name} издает звук тромбона.");
}

class Ukulele : MusicalInstrument
{
    public Ukulele(string name, string description, string history) : base(name, description, history) { }

    public override void Sound() => WriteLine($"{name} издает звук укулеле.");
}

class Violoncello : MusicalInstrument
{
    public Violoncello(string name, string description, string history) : base(name, description, history) { }

    public override void Sound() => WriteLine($"{name} издает звук виолончели.");
}
