using System.Data.SqlClient;

string connectionString = @"Data Source=USER\SQLEXPRESS;Initial Catalog=userdb;Integrated Security=True";

Console.WriteLine("Введите название продукта:");
string name = Console.ReadLine();

Console.WriteLine("Введите стоимость:");
int.TryParse(Console.ReadLine(), out int price);

string sqlExpression = $"INSERT INTO Product([Name],[Price]) VALUES ('{name}', {price})";

Insert(connectionString, sqlExpression);


ShowAllItems(connectionString, "Product");


void Insert(string connectionString, string sqlExpression)
{
    using (SqlConnection connection = new SqlConnection(connectionString))
    {
        connection.Open();
        SqlCommand command = new SqlCommand(sqlExpression, connection);
        //int number = command.ExecuteNonQuery();
        //Console.WriteLine("Добавлено объектов: {0}", number);
    }
}


void ShowAllItems(string connectionString, string tableName)
{
    using (SqlConnection connection = new SqlConnection(connectionString))
    {
        connection.Open();
        SqlCommand command = new SqlCommand($"SELECT * FROM {tableName}", connection);
        var reader = command.ExecuteReader();

        while (reader.Read())
        {
            //далее читаем все нужные поля и выводим в удобном виде

            // object value1 = reader.GetValue(i)  
            // object value2 = reader.GetValue(i+1)
        }
    }
}