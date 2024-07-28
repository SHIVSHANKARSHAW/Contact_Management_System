#include<fstream>
#include<iostream>
#include<iomanip>
#include<string.h>
using namespace std;

class Book
{
protected:
    int BookId;
    char Title[20];
    char Author[20];
    char Category[20];
    int Pages;
    float Price;

public:
    // Accessor Functions
    int getID() const { return BookId; }
    const char* getTitle() const { return Title; }
    const char* getAuthor() const { return Author; }
    const char* getCategory() const { return Category; }
    float getPrice() const { return Price; }

    // Default constructor
    Book()
    {
        BookId = 0;
        strcpy(Title, "");
        strcpy(Author, "");
        strcpy(Category, "");
        Pages = 0;
        Price = 0;
    }

    // Virtual function to allow polymorphic behavior
    virtual void getBook()
    {
        cout << "\tEnter Book Id : ";
        cin >> BookId;
        cout << "\tEnter Book Title : ";
        cin.get();
        cin.getline(Title, 20);
        cout << "\tEnter Book Author: ";
        cin.getline(Author, 20);
        cout << "\tEnter Book Category: ";
        cin.getline(Category, 20);
        cout << "\tEnter No. of Pages : ";
        cin >> Pages;
        cout << "\tEnter Price of Book: ";
        cin >> Price;
        cout << endl;
    }

    virtual void showBook() const
    {
        cout << endl;
        cout << "Book ID      : " << BookId << endl;
        cout << "Book Title   : " << Title << endl;
        cout << "Author Name  : " << Author << endl;
        cout << "Category     : " << Category << endl;
        cout << "No. of Pages : " << Pages << endl;
        cout << "Price of Book: " << Price << endl;
    }

    virtual void header() const
    {
        cout.setf(ios::left);
        cout << setw(5) << "I.D."
             << setw(20) << "Book Title"
             << setw(20) << "Book Author"
             << setw(15) << "Category"
             << setw(6) << "Pages"
             << setw(6) << "Price" << endl;
        for (int i = 1; i <= 72; i++)
            cout << "=";
        cout << endl;
    }

    virtual void listView() const
    {
        cout.setf(ios::left);
        cout << setw(5) << BookId
             << setw(20) << Title
             << setw(20) << Author
             << setw(15) << Category
             << setw(6) << Pages
             << setw(6) << Price << endl;
    }
};

class Library : public Book
{
public:
    // Function prototyping for project
    void drawLine(char) const;      // Function for drawing line on screen.
    void heading() const;           // Function for heading to be displayed on each page.
    void menu();                    // Function for displaying program options.
    void searchMenu();              // Function for displaying searching options.
    void addBook();                 // Function for writing data to file.
    void displayBooks() const;      // Function for reading data from file.
    void searchByID() const;        // Function for searching data from file.
    void searchByTitle() const;     // Function for searching data from file.
    void searchByCategory() const;  // Function for searching data from file.
    void searchByPrice() const;     // Function for searching data from file.
    void searchByAuthor() const;    // Function for searching data from file.
    void dispose();                 // Function to shift books from main file to other file.
    void modify();                  // Function to modify the book details.
    void displayDisposed() const;   // Function to display the list of disposed off books
};

void Library::drawLine(char ch) const
{
    for (int i = 1; i < 80; i++)
        cout << ch;
    cout << endl;
}

void Library::heading() const
{
    drawLine('+');
    cout << "\t\tL I B R A R Y   M A N A G E M E N T   S Y S T E M\n";
    drawLine('+');
}

void Library::addBook()
{
    ofstream fout;
    fout.open("books.dat", ios::app);
    getBook();
    fout.write((char*)this, sizeof(*this));
    cout << "Book data saved in file...\n";
    fout.close();
}

void Library::displayBooks() const
{
    ifstream fin("books.dat");
    int rec = 0;
    while (fin.read((char*)this, sizeof(*this)))
    {
        if (rec < 1)
            header();
        listView();
        rec++;
    }
    fin.close();
    cout << "\nTotal " << rec << " Records in file...\n";
}

void Library::searchByID() const
{
    int n, flag = 0;
    ifstream fin("books.dat");
    cout << "Enter Book ID : ";
    cin >> n;
    while (fin.read((char*)this, sizeof(*this)))
    {
        if (n == getID())
        {
            showBook();
            flag++;
        }
    }
    fin.close();
    if (flag == 0)
        cout << "Book Number with ID:" << n << " not available...\n";
}

void Library::searchByTitle() const
{
    int flag = 0;
    char title[20];
    ifstream fin("books.dat");
    cout << "Enter Book Title : ";
    cin.ignore();
    cin.getline(title, 20);
    while (fin.read((char*)this, sizeof(*this)))
    {
        if (strcmp(title, getTitle()) == 0)
        {
            showBook();
            flag++;
        }
    }
    fin.close();
    if (flag == 0)
        cout << "Book with Title: " << title << " not available...\n";
}

void Library::searchByCategory() const
{
    int flag = 0, rec = 0;
    char cat[20];
    ifstream fin("books.dat");
    cout << "Enter Book Category : ";
    cin.ignore();
    cin.getline(cat, 20);
    while (fin.read((char*)this, sizeof(*this)))
    {
        if (strcmp(cat, getCategory()) == 0)
        {
            if (rec < 1)
                header();
            listView();
            flag++;
            rec++;
        }
    }
    fin.close();
    if (flag == 0)
        cout << "Book with Category: " << cat << " not available...\n";
}

void Library::searchByAuthor() const
{
    int flag = 0, rec = 0;
    char aut[20];
    ifstream fin("books.dat");
    cout << "Enter Book Author : ";
    cin.ignore();
    cin.getline(aut, 20);
    while (fin.read((char*)this, sizeof(*this)))
    {
        if (strcmp(aut, getAuthor()) == 0)
        {
            if (rec < 1)
                header();
            listView();
            flag++;
            rec++;
        }
    }
    fin.close();
    if (flag == 0)
        cout << "Book with Author name: " << aut << " not available...\n";
}

void Library::searchByPrice() const
{
    int flag = 0, rec = 0;
    float minrate, maxrate;
    ifstream fin("books.dat");
    cout << "Enter Minimum Price of Book : ";
    cin >> minrate;
    cout << "Enter Maximum Price of Book : ";
    cin >> maxrate;

    while (fin.read((char*)this, sizeof(*this)))
    {
        if (getPrice() >= minrate && getPrice() <= maxrate)
        {
            if (rec < 1)
                header();
            listView();
            flag++;
            rec++;
        }
    }
    fin.close();
    if (flag == 0)
        cout << "Books between Price Range: " << minrate
             << " and " << maxrate << " not available...\n";
}

void Library::dispose()
{
    int n, flag = 0;
    ifstream fin("books.dat");
    ofstream fout("dispose.dat", ios::out);
    cout << "Enter Book ID : ";
    cin >> n;
    while (fin.read((char*)this, sizeof(*this)))
    {
        if (n == getID())
        {
            showBook();
            flag++;
        }
        else
        {
            fout.write((char*)this, sizeof(*this));
        }
    }
    fin.close();
    fout.close();
    if (flag == 0)
        cout << "Book Number with ID:" << n << " not available...\n";
}

void Library::modify()
{
    int n, flag = 0, pos;
    fstream fin("books.dat", ios::in | ios::out);
    cout << "Enter Book ID : ";
    cin >> n;
    while (fin.read((char*)this, sizeof(*this)))
    {
        if (n == getID())
        {
            pos = fin.tellg();
            cout << "Following data will be edited...\n";
            showBook();
            flag++;
            fin.seekg(pos - sizeof(*this));
            getBook();
            fin.write((char*)this, sizeof(*this));
            cout << "\nData Modified successfully...\n";
        }
    }
    fin.close();
    if (flag == 0)
        cout << "Book Number with ID:" << n << " not available...\n";
}

void Library::displayDisposed() const
{
    ifstream fin("dispose.dat");
    int rec = 0;
    while (fin.read((char*)this, sizeof(*this)))
    {
        if (rec < 1)
            header();
        listView();
        rec++;
    }
    fin.close();
    cout << "\nTotal " << rec << " Records in disposed off file...\n";
}

void Library::menu()
{
    int ch;
    do
    {
        system("cls");
        heading();
        cout << "0. EXIT.\n";
        cout << "1. Add New Book\n";
        cout << "2. Display All Books\n";
        cout << "3. Search Books\n";
        cout << "4. Disposed Off Books\n";
        cout << "5. Modify Details\n";
        cout << "6. List of Disposed Books\n";
        cout << "Enter Your Choice : ";
        cin >> ch;
        system("cls");
        heading();
        switch (ch)
        {
        case 1: addBook(); break;
        case 2: displayBooks(); break;
        case 3: searchMenu(); break;
        case 4: dispose(); break;
        case 5: modify(); break;
        case 6: displayDisposed(); break;
        }
        system("pause");
    } while (ch != 0);
}

void Library::searchMenu()
{
    int ch;
    do
    {
        system("cls");
        heading();
        cout << "BOOK SEARCH OPTIONS\n";
        cout << "0. Back\n";
        cout << "1. By ID\n";
        cout << "2. By Title\n";
        cout << "3. By Category\n";
        cout << "4. By Author\n";
        cout << "5. By Price Range\n";
        cout << "Enter Your Choice : ";
        cin >> ch;
        system("cls");
        heading();
        switch (ch)
        {
        case 1: searchByID(); break;
        case 2: searchByTitle(); break;
        case 3: searchByCategory(); break;
        case 4: searchByAuthor(); break;
        case 5: searchByPrice(); break;
        default: cout << "\a";
        }
        system("pause");
    } while (ch != 0);
}

int main()
{
    Library lib;
    lib.menu();
    return 0;
}
