using System.Data.SqlClient;
using System.Configuration;
using System.Data;

string? connectionString = ConfigurationManager.AppSettings["connectionString"];

if (string.IsNullOrWhiteSpace(connectionString))
    throw new InvalidDataException("Check app.config! \"connectionString\" doesn't have to be empty");

Console.WriteLine("Введите название продукта:");
string name = Console.ReadLine();

Console.WriteLine("Введите стоимость:");
int.TryParse(Console.ReadLine(), out int price);

string sqlExpression = $"INSERT INTO Product([Name],[Price]) VALUES ('{name}', {price})";

var dbconn = new MyDBconnection(connectionString);

int affectedRows = await dbconn.Insert(sqlExpression);
Console.WriteLine($"Изменено строк {affectedRows}");

dbconn.ShowAllItems("Product");


class MyDBconnection
{
    private string connectionString;

    public MyDBconnection(string connectionString)
    {
        this.connectionString = connectionString;
    }

    public async Task<int> Insert(string sqlExpression)
    {
        using (SqlConnection connection = new SqlConnection(connectionString))
        {
            connection.Open();
            SqlCommand command = new SqlCommand(sqlExpression, connection);
            int number = await command.ExecuteNonQueryAsync();
            return number;
        }
    }

    public async void ShowAllItems(string tableName)
    {
        string sql = $"SELECT * FROM {tableName}";

        using (SqlConnection connection = new SqlConnection(connectionString))
        {
            SqlDataAdapter adapter = new SqlDataAdapter(sql, connection);
            DataSet ds = new DataSet();
            adapter.Fill(ds);

            foreach (DataTable dt in ds.Tables)
            {
                foreach (DataColumn column in dt.Columns)
                    Console.Write($"{column.ColumnName}\t");
                Console.WriteLine();

                foreach (DataRow row in dt.Rows)
                {
                    var cells = row.ItemArray;
                    foreach (object cell in cells)
                        Console.Write($"{cell}\t");
                    Console.WriteLine();
                }
            }
        }
    }
}