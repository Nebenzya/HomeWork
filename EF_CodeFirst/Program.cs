using EF_CodeFirst;
using Microsoft.EntityFrameworkCore;

#region Add Content

using (var db = CreateContext())
{
    Author shakespeare = new Author { FirstName = "William", LastName = "Shakespeare" };
    Author hamingway = new Author { FirstName = "Ernest", LastName = "Hamingway" };
    Author rowling = new Author { FirstName = "Joan", LastName = "Rowling" };
    db.Authors.AddRange(shakespeare, hamingway, rowling);

    Publisher eksmo = new Publisher { PublisherName = "Eksmo", Address = "221b, Baker street" };
    Publisher rosmen = new Publisher { PublisherName = "Rosmen", Address = "54321, Moscow, Lenina street" };
    db.Publishers.AddRange(eksmo, rosmen);


    db.Books.AddRange(new Book { Author = hamingway, Pages = 200, Price = 550, Publisher = eksmo, Title = "Old man and the sea" },
        new Book { Author = hamingway, Pages = 300, Price = 750, Publisher = eksmo, Title = "Whom bell tolls" },
        new Book { Author = rowling, Pages = 450, Price = 850, Publisher = rosmen, Title = "Harry Potter and the chamber of secrets" },
        new Book { Author = rowling, Pages = 650, Price = 1050, Publisher = rosmen, Title = "Harry Potter and Half-blood Prince" },
        new Book { Author = shakespeare, Pages = 350, Price = 350, Publisher = eksmo, Title = "Hamlet" },
        new Book { Author = shakespeare, Pages = 250, Price = 600, Publisher = eksmo, Title = "Romeo and Juliet" });
    db.SaveChanges();
}

#endregion

#region Show Content

using (var db = CreateContext())
{
    Console.WriteLine("Показать всех авторов: ");
    var authors = from author in db.Authors select author;
    foreach (var author in authors)
    {
        Console.WriteLine($"{author.FirstName} {author.LastName}");
    }
    Console.WriteLine();

    Console.WriteLine("Показать всех издателей: ");
    var publishers = from publisher in db.Publishers select publisher;
    foreach (var publisher in publishers)
    {
        Console.WriteLine($"Publisher Name: {publisher.PublisherName}, Address: {publisher.Address}");
    }
    Console.WriteLine();

    Console.WriteLine("Показать все книги издательства, заканчивающегося на 'men': ");
    var books = from book in db.Books.Include(b => b.Publisher) where EF.Functions.Like(book.Publisher.PublisherName, "%men") select book;
    foreach (var book in books)
    {
        Console.WriteLine($"{book.Title}, Price: {book.Price}, Publisher: {book.Publisher.PublisherName}");
    }
    Console.WriteLine();

    Console.WriteLine("Показать книгу с id 3: ");
    Book findBook = db.Books.Find(3);
    Console.WriteLine($"{findBook.Title}, Price: {findBook.Price}, Publisher: {findBook.Publisher.PublisherName}");
    Console.WriteLine();

    Console.WriteLine("Показать книгу c количеством страниц больше 500: ");
    Book pageBook = db.Books.FirstOrDefault(p => p.Pages > 500);
    Console.WriteLine($"{pageBook.Title}, Price: {pageBook.Price}, Publisher: {pageBook.Publisher.PublisherName}");
    Console.WriteLine();

    Console.WriteLine("Показать полную информацию о книгах, используя данные других таблиц: ");
    var viewBooks = from book in db.Books join author in db.Authors on book.AuthorId equals author.Id join pub in db.Publishers on book.PublisherId equals pub.Id select new { Title = book.Title, AuthorName = author.FirstName, AuthorLastName = author.LastName, Pages = book.Pages, Price = book.Price, PublisherName = pub.PublisherName };
    foreach (var book in viewBooks)
    {
        Console.WriteLine($"{book.Title}, Author: {book.AuthorName} {book.AuthorLastName}, Price: {book.Price}, Pages: {book.Pages}. Publisher Name: {book.PublisherName}");
    }
    Console.WriteLine();

    Console.WriteLine("Показать количество книг по каждому издательству: ");
    var groups = from b in db.Books group b by b.Publisher.PublisherName into p select new { p.Key, Count = p.Count() };
    foreach (var group in groups)
    {
        Console.WriteLine($"{group.Key} - {group.Count}");
    }
    Console.WriteLine();
}

#endregion


Console.Read();

ApplicationContext CreateContext()
{
    var optionsBuilder = new DbContextOptionsBuilder<ApplicationContext>();
    optionsBuilder.UseSqlServer(@"Data Source=(localdb)\MSSQLLocalDB;Initial Catalog=LibraryDB;Integrated Security=True;");
    return new ApplicationContext(optionsBuilder.Options);
}