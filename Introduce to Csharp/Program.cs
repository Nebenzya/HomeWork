using static System.Console;

string choice;

while (true)
{
    WriteLine("Выбирай: Викторина - В, Угадай число - Ч");
    choice = ReadLine();
    if (choice.ToLower() == "в")
        startQuiz();
    else if (choice.ToLower() == "ч")
        guessNumber();
    else
        WriteLine("Ты ввёл что то не то!");
}


static void startQuiz()
{
    List<Quiz> list = new()
            {
                new Quiz("Зимой и летом одним цветом?", "Это дерево!" ,new List<string>{ "ёлка","елка","ель","сосна" } ),
                new Quiz("Самая высокая гора?", "Начинается на \"Э\"" , new List<string>{ "эверест" } ),
                new Quiz( "Самая длинная река?", "Там ещё пираньи обитают...", new List<string>{ "амазонка" }),
                new Quiz("Самый большой океан?", "Он не громкий...", new List < string > { "тихий", "тихий океан" }),
                new Quiz("Самая большая планета?", "Находится перед Сатурном", new List < string > { "юпитер" })
            };

    string userAnswer;
    int counterOfRightAnswers = 0;

    foreach (var item in list)
    {
        WriteLine(item.question);

        for (int i = 0; i < 2; i++)
        {
            userAnswer = ReadLine().ToLower();
            if (item.answer.Contains(userAnswer))
            {
                counterOfRightAnswers++;
                WriteLine("Ответ верный!");
                break;
            }
            else
                WriteLine($"Ответ неверный! Подсказка: {item.hint}");

        }
    }

    if (counterOfRightAnswers > list.Count / 2)
        WriteLine($"Правильных ответов: {counterOfRightAnswers}.\nХорошо справился!");
    else
        WriteLine($"Можно было и лучше ответить!\nПравильных ответов: {counterOfRightAnswers}");

}

static void guessNumber()
{
    int magicNumber = new Random().Next(0, 100);
    int userNumber = 0;
    int count = 0, attempt = 10;

    do
    {
        Write("Введи число: ");
        userNumber = Int32.Parse(ReadLine());
        count++;
        if (userNumber < magicNumber)
        {
            WriteLine("Загаданное число больше!");
        }
        else if (userNumber > magicNumber)
        {
            WriteLine("Загаданное число меньше!");
        }
        else if (userNumber == magicNumber)
        {
            WriteLine("Ты угадал! Тебе понадобилось " + count + " попыток");
            break;
        }
        attempt--;

    } while (userNumber != magicNumber && attempt > 0);

    if (attempt <= 0)
        WriteLine("Ты не справился!");
}


class Quiz
{
    public string question, hint;
    public List<string> answer;

    public Quiz(string question, string hint, List<string> answer)
    {
        this.question = question;
        this.hint = hint;
        this.answer = answer;
    }
}

