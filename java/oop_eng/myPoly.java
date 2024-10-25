class Publication
{
	protected String Title;
    protected double Price;
    protected int Copies;

	Publication(String Title, double Price, int Copies)
    {
        this.Title = Title;
        this.Price = Price;
        this.Copies = Copies;
    }

    void saleCopy()
    {
        System.out.println("Sale : " + Copies +" copies of " + Title + ". Total Amount : " + (Price * Copies));
    }
}

class Book extends Publication
{
    private String author;

    Book (String Title, double Price, int Copies, String author)
    {
        super(Title, Price, Copies);
        this.author = author;
    }

    public void orderCopies()
    {
        System.out.println("Ordered " + Copies + " copies of book " + Title + " by " + author);
    }
}

class Magazine extends Publication
{
    private int currentIssue;

    public Magazine(String Title, double Price, int Copies, int currentIssue)
    {
        super(Title, Price, Copies);
        this.currentIssue = currentIssue;
    }

    public void orderQty()
    {
            System.out.println("Ordered " + Copies + " copies of Magazin " + Title + ".");
    }

    public void displayCurrentIssue()
    {
            System.out.println("Current Issue of Magazin " + Title + " : " + currentIssue + ".");
    }

    public void receiveIssue()
    {
            System.out.println("Received new issue of magazine of " + Title + ". Current issue : " + currentIssue + ".");
    }

}

class myPoly
{
    public static void main(String[] args)
    {
        Book book = new Book("Java Programming", 29.99, 100, "John Doe");
        Magazine magazine = new Magazine("Tech Today", 5.99, 500, 10);

        Publication pubBook = book;
        Publication pubMagazine = magazine;

        pubBook.saleCopy();
        pubMagazine.saleCopy();

        book.orderCopies();
        magazine.orderQty();
        magazine.displayCurrentIssue();
        magazine.receiveIssue();
        magazine.displayCurrentIssue();

    }
}
