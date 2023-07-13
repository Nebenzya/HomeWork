using System.ComponentModel.DataAnnotations;

namespace EF_CodeFirst
{
    public class Author
    {
        [Key]
        public int Id { get; set; }
        public string FirstName { get; set; }
        public string LastName { get; set; }

        public List<Book> Books { get; set; }
    }

    public class Publisher
    {
        [Key]
        public int Id { get; set; }
        public string PublisherName { get; set; }
        public string Address { get; set; }

        public List<Book> Books { get; set; }
    }

    public class Book
    {
        [Key]
        public int Id { get; set; }
        public string Title { get; set; }
        public int AuthorId { get; set; }
        public int Pages { get; set; }
        public decimal Price { get; set; }
        public int PublisherId { get; set; }

        public Author Author { get; set; }
        public Publisher Publisher { get; set; }
    }
}
