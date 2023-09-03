/*
 Создайте приложение для поиска слова в некотором
файле. По итогам приложение должно показать сколько 
раз слово встретилось в файле
 */

string path = "Text.txt";
string word = "Поэта";

Console.WriteLine($"слово \"{word}\" найдено {await CountWord(path, word)} раз(а)");

async Task<int> CountWord(string path, string uniqWord)
{
    if (string.IsNullOrWhiteSpace(path) || string.IsNullOrWhiteSpace(uniqWord)) return 0;

    int count = default;

    try
    {
        using (var reader = new StreamReader(path))
        {
            string text = await reader.ReadToEndAsync();
            char[] separators = { ' ', '.', ',', ';', ':', '?', '\n', '\r' };

            string[] words = text.Split(separators);
            string uw = uniqWord.ToLower();

            count = words.Count(w => w.ToLower() == uw);
        }
    }
    catch (Exception)
    {
        return 0;
    }

    return count;
}