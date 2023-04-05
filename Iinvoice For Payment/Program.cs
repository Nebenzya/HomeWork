//Разработать класс «Счет для оплаты». В классе предусмотреть следующие поля:
//■ оплата за день;
//■ количество дней;
//■ штраф за один день задержки оплаты;
//■ количество дней задержи оплаты;
//■ сумма к оплате без штрафа (вычисляемое поле);
//■ штраф(вычисляемое поле);
//■ общая сумма к оплате (вычисляемое поле).
//В классе объявить статическое свойство типа bool,
//значение которого влияет на процесс форматирования
//объектов этого класса. Если значение этого свойства равно true, тогда сериализуются и десериализируются все
//поля, если false — вычисляемые поля не сериализуются.
//Разработать приложение, в котором необходимо продемонстрировать использование этого класса, результаты
//должны записываться и считываться из файла.

using System.Xml.Serialization;


Invoice.SerializeXML(new Invoice(20, 30, 5, 7));
Invoice count = Invoice.DeSerialize();
Console.WriteLine(count);
Console.ReadLine();

public class Invoice
{
    public static bool FormatProcess = true;
    public static string Path { get; } = "Invoice.xml";

    public decimal TotalCost { get { return costPerDay * dayCounter; } }
    public decimal TotalPenalty { get { return penaltyPerDay * delayCounter; } }
    public decimal ResultPayment { get { return TotalCost + TotalPenalty; } }

    private readonly uint dayCounter;
    private readonly uint delayCounter;
    private readonly decimal costPerDay;
    private readonly decimal penaltyPerDay;

    public Invoice() { }
    public Invoice(decimal costPerDay, uint numberOfDays, decimal penaltyPerDay, uint numberOfDelay = 0)
    {
        this.costPerDay = costPerDay;
        this.penaltyPerDay = penaltyPerDay;
        dayCounter = numberOfDays;
        delayCounter = numberOfDelay;
    }


    public static void SerializeXML(Invoice obj)
    {
        try
        {
            if (!FormatProcess) throw new Exception("Formatting is not available");

            using (FileStream fs = new FileStream(Path, FileMode.OpenOrCreate))
            {
                new XmlSerializer(typeof(Invoice)).Serialize(fs, obj);
                Console.WriteLine("Object has been serialized");
            }
        }
        catch (Exception)
        {
            throw;
        }

    }


    public static Invoice? DeSerialize()
    {
        try
        {
            if (!FormatProcess) throw new Exception("Formatting is not available");

            using FileStream fStream = File.OpenRead(Path);
            return (Invoice)new XmlSerializer(typeof(Invoice)).Deserialize(fStream);
        }
        catch (Exception)
        {
            throw;
        }
    }
}
