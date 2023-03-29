
//1. Разработать абстрактный класс «автомобиль»
//(класс Car). Собрать в нем все общие поля, свойства
//(например, скорость) методы (например, ехать).
// Разработать классы автомобилей с конкретной
//реализацией конструкторов и методов, свойств.

//2.Класс игры должен производить запуск соревнований автомобилей, выводить сообщения о текущем
//положении автомобилей, выводить сообщение об
//автомобиле, победившем в гонках. Создать делегаты, обеспечивающие вызов методов из классов
//автомобилей (например, выйти на старт, начать
//гонку).

//3.Игра заканчивается, когда какой-то из автомобилей
//проехал определенное расстояние (старт в положении 0, финиш в положении 100). Уведомление об
//окончании гонки (прибытии какого-либо автомобиля на финиш)

Game game = new();
List<Car> cars = new()
{
    new ParticularCar("sportCar",240),
    new ParticularCar("passenger car", 180),
    new ParticularCar("truck", 160)
};

foreach (var car in cars)
{
    game.Started += car.Drive;
    game.Finished += car.Stop;
}

game.StartGame(cars, 100);

abstract class Car
{
    public string Name { get; private set; }
    private double _speed;
    private double _maxSpeed;

    public double Speed
    {
        get => _speed;
        set
        {
            _speed = value;

            if (_speed < 0)
                _speed = 0;
            else if (_speed > _maxSpeed)
                _speed = _maxSpeed;

        }
    }
    public double Distance { get; set; }
    public bool IsStart { get; private set; }

    public Car(string name, double maxSpeed)
    {
        Name = name;
        _maxSpeed = maxSpeed;
    }

    public virtual void Drive() => IsStart = true;
    public virtual void Stop() => IsStart = false;

    public virtual void Info()
    {
        Console.WriteLine($"Car: {Name}\nCurrent _speed: {Speed}\nTotal distance: {Distance}");
    }
    public override string ToString() => Name;
}

class ParticularCar : Car
{
    public ParticularCar(string name, double maxSpeed) : base(name, maxSpeed)
    {
    }
}


class Game
{
    public delegate void CarDelegate();
    public event CarDelegate Started;
    public event CarDelegate Finished;

    private bool _gameOver;
    private Random random = new Random();

    public void StartGame(List<Car> cars, double lengthRaceTrack)
    {
        object winner = new();
        Started.Invoke();
        while (!_gameOver)
        {

            foreach (var car in cars)
            {
                car.Speed += random.Next(10);
                car.Distance += car.Speed;
                if (car.Distance >= lengthRaceTrack)
                {
                    _gameOver = true;
                    winner = car;
                }
                car.Info();
                Console.WriteLine();
            }
            Console.WriteLine("===============================");
            Thread.Sleep(1000);
        }
        Finished.Invoke();
        Console.WriteLine($"Game over!\nWinner is {winner}");
    }
}