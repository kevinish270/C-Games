
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

// GENRE
enum Genre {
    fiction, nonfiction, periodical, biography, children
};

string genreName(Genre g) {
    switch (g) {
        case fiction: return "Fiction";
        case nonfiction: return "Nonfiction";
        case periodical: return "Periodical";
        case biography: return "Biography";
        case children: return "Children";
    }
    return "Unknown";
}

// ACTIVITY
enum Activity {
    check_out, check_in
};


// 1. BOOK CLASS
class Book {
private:
    string ISBN, title, author;
    int copyrightDate;
    bool checked_out;
    Genre genre;

public:
    Book(string i, string t, string a, int d, Genre g) {
        ISBN = i;
        title = t;
        author = a;
        copyrightDate = d;
        genre = g;
        checked_out = false;
    }

    string getISBN() { return ISBN; }
    string getTitle() { return title; }
    string getAuthor() { return author; }
    int getCopyrightDate() { return copyrightDate; }
    bool isCheckedOut() { return checked_out; }
    Genre getGenre() { return genre; }

    void checkOut() {
        checked_out = true;
    }

    void checkIn() {
        checked_out = false;
    }

    // Restore book status from file
    void setCheckedOut(bool status) {
        checked_out = status;
    }

    bool operator==(Book b) {
        return ISBN == b.ISBN;
    }

    bool operator!=(Book b) {
        return ISBN != b.ISBN;
    }

    friend ostream& operator<<(ostream& out, Book b) {
        out << "Title: " << b.title << endl;
        out << "Author: " << b.author << endl;
        out << "ISBN: " << b.ISBN << endl;
        out << "Genre: " << genreName(b.genre) << endl;
        return out;
    }
};


// 2. PATRON CLASS
class Patron {
private:
    string username, cardNumber;
    int owedFees;

public:
    Patron(string u, string c, int f) {
        username = u;
        cardNumber = c;
        owedFees = f;
    }

    string getUsername() { return username; }
    string getCardNumber() { return cardNumber; }
    int getOwedFees() { return owedFees; }

    bool owesFees() {
        return owedFees > 0;
    }

    void setFees(int f) {
        owedFees = f;
    }
};


// 3. TRANSACTION CLASS
class Transaction {
private:
    Book book;
    Patron patron;
    Activity activity;
    string date;

public:
    Transaction(Book b, Patron p, Activity a, string d)
        : book(b), patron(p), activity(a), date(d) {
    }

    void display() {
        cout << "\nBook: " << book.getTitle() << endl;
        cout << "Patron: " << patron.getUsername() << endl;

        if (activity == check_out)
            cout << "Activity: Check out" << endl;
        else
            cout << "Activity: Check in" << endl;

        cout << "Date: " << date << endl;
    }
};


// 4. LIBRARY CLASS
class Library {
private:
    vector<Book> books;
    vector<Patron> patrons;
    vector<Transaction> transactions;

public:

    // LOAD BOOKS FROM FILE
    void loadBooks() {
        ifstream file("books.txt");

        if (!file) {
            cout << "Books file not found. Creating a new one.\n";
            ofstream newFile("books.txt");
            newFile.close();
            return;
        }

        string isbn, title, author;
        int year, g, status;

        while (getline(file, isbn, '|')) {

            if (!getline(file, title, '|')) break;
            if (!getline(file, author, '|')) break;
            if (!(file >> year)) break;
            file.ignore();

            if (!(file >> g)) break;
            file.ignore();

            if (!(file >> status)) break;
            file.ignore();

            if (g < 0 || g > 4 || (status != 0 && status != 1)) {
                cout << "Invalid book record skipped.\n";
                continue;
            }

            Book b(isbn, title, author, year, (Genre)g);
            b.setCheckedOut(status);

            books.push_back(b);
        }

        file.close();
        cout << books.size() << " book(s) loaded successfully.\n";
    }


    // LOAD PATRONS FROM FILE
    void loadPatrons() {
        ifstream file("patrons.txt");

        if (!file) {
            cout << "Patrons file not found. Creating a new one.\n";
            ofstream newFile("patrons.txt");
            newFile.close();
            return;
        }

        string username, card;
        int fees;

        while (getline(file, username, '|')) {

            if (!getline(file, card, '|')) break;
            if (!(file >> fees)) break;
            file.ignore();

            if (fees < 0) {
                cout << "Invalid patron record skipped.\n";
                continue;
            }

            Patron p(username, card, fees);
            patrons.push_back(p);
        }

        file.close();
        cout << patrons.size() << " patron(s) loaded successfully.\n";
    }


    // SAVE BOOKS TO FILE
    void saveBooks() {
        ofstream file("books.txt");

        if (!file) {
            cout << "Error saving books.\n";
            return;
        }

        for (int i = 0; i < books.size(); i++) {
            file << books[i].getISBN() << "|"
                 << books[i].getTitle() << "|"
                 << books[i].getAuthor() << "|"
                 << books[i].getCopyrightDate() << "|"
                 << books[i].getGenre() << "|"
                 << books[i].isCheckedOut() << endl;
        }

        file.close();
    }


    // SAVE PATRONS TO FILE
    void savePatrons() {
        ofstream file("patrons.txt");

        if (!file) {
            cout << "Error saving patrons.\n";
            return;
        }

        for (int i = 0; i < patrons.size(); i++) {
            file << patrons[i].getUsername() << "|"
                 << patrons[i].getCardNumber() << "|"
                 << patrons[i].getOwedFees() << endl;
        }

        file.close();
    }


    // ADD BOOK
    void addBook(Book b) {
        for (int i = 0; i < books.size(); i++) {
            if (books[i].getISBN() == b.getISBN()) {
                cout << "Error: A book with this ISBN already exists.\n";
                return;
            }
        }

        books.push_back(b);
        saveBooks();

        cout << "Book added successfully.\n";
    }


    // ADD PATRON
    void addPatron(Patron p) {
        for (int i = 0; i < patrons.size(); i++) {
            if (patrons[i].getCardNumber() == p.getCardNumber()) {
                cout << "Error: This card number is already registered.\n";
                return;
            }
        }

        patrons.push_back(p);
        savePatrons();

        cout << "Patron added successfully.\n";
    }


    // DISPLAY ALL BOOKS
    void displayBooks() {
        if (books.empty()) {
            cout << "No books available.\n";
            return;
        }

        for (int i = 0; i < books.size(); i++) {
            cout << "\nBook " << i + 1 << endl;
            cout << books[i];
            cout << "Status: ";

            if (books[i].isCheckedOut())
                cout << "Checked out\n";
            else
                cout << "Available\n";
        }
    }


    // DISPLAY ALL PATRONS
    void displayPatrons() {
        if (patrons.empty()) {
            cout << "No patrons registered.\n";
            return;
        }

        for (int i = 0; i < patrons.size(); i++) {
            cout << "\nUsername: " << patrons[i].getUsername() << endl;
            cout << "Card number: " << patrons[i].getCardNumber() << endl;
            cout << "Owed fees: " << patrons[i].getOwedFees() << endl;
        }
    }


    // CHECK OUT BOOK
    void borrowBook(string isbn, string card, string date) {

        int bookIndex = -1;
        int patronIndex = -1;

        // Find book
        for (int i = 0; i < books.size(); i++) {
            if (books[i].getISBN() == isbn) {
                bookIndex = i;
                break;
            }
        }

        // Find patron
        for (int i = 0; i < patrons.size(); i++) {
            if (patrons[i].getCardNumber() == card) {
                patronIndex = i;
                break;
            }
        }

        if (bookIndex == -1) {
            cout << "Error: Book not found.\n";
            return;
        }

        if (patronIndex == -1) {
            cout << "Error: Patron not found.\n";
            return;
        }

        if (patrons[patronIndex].owesFees()) {
            cout << "Error: Patron owes library fees.\n";
            return;
        }

        if (books[bookIndex].isCheckedOut()) {
            cout << "Error: Book is already checked out.\n";
            return;
        }

        // Update book status
        books[bookIndex].checkOut();

        // Create transaction
        Transaction t(books[bookIndex], patrons[patronIndex],
                      check_out, date);

        transactions.push_back(t);

        saveBooks();

        cout << "Book borrowed successfully.\n";
    }


    // CHECK IN BOOK
    void returnBook(string isbn, string card, string date) {

        int bookIndex = -1;
        int patronIndex = -1;

        for (int i = 0; i < books.size(); i++) {
            if (books[i].getISBN() == isbn) {
                bookIndex = i;
                break;
            }
        }

        for (int i = 0; i < patrons.size(); i++) {
            if (patrons[i].getCardNumber() == card) {
                patronIndex = i;
                break;
            }
        }

        if (bookIndex == -1 || patronIndex == -1) {
            cout << "Error: Book or patron not found.\n";
            return;
        }

        if (!books[bookIndex].isCheckedOut()) {
            cout << "Error: Book has not been borrowed.\n";
            return;
        }

        books[bookIndex].checkIn();

        Transaction t(books[bookIndex], patrons[patronIndex],
                      check_in, date);

        transactions.push_back(t);

        saveBooks();

        cout << "Book returned successfully.\n";
    }


    // UPDATE PATRON FEES
    void updateFees(string card, int fees) {
        for (int i = 0; i < patrons.size(); i++) {
            if (patrons[i].getCardNumber() == card) {
                patrons[i].setFees(fees);

                savePatrons();

                cout << "Fees updated successfully.\n";
                return;
            }
        }

        cout << "Patron not found.\n";
    }


    // RETURN NAMES OF PATRONS WHO OWE FEES
    vector<string> patronsWithFees() {
        vector<string> names;

        for (int i = 0; i < patrons.size(); i++) {
            if (patrons[i].owesFees()) {
                names.push_back(patrons[i].getUsername());
            }
        }

        return names;
    }


    // DISPLAY TRANSACTIONS
    void displayTransactions() {
        if (transactions.empty()) {
            cout << "No transactions available.\n";
            return;
        }

        for (int i = 0; i < transactions.size(); i++) {
            cout << "\nTransaction " << i + 1 << endl;
            transactions[i].display();
        }
    }

};


// MAIN FUNCTION
int main() {

    Library library;

    // Load saved books and patrons when program starts
    cout << "\nLoading library information...\n";

    library.loadBooks();
    library.loadPatrons();

    int choice;

    do {
        cout << "\n====== LIBRARY MANAGEMENT SYSTEM ======\n";
        cout << "1. Add Book\n";
        cout << "2. Register Patron\n";
        cout << "3. Display Books\n";
        cout << "4. Display Patrons\n";
        cout << "5. Borrow Book\n";
        cout << "6. Return Book\n";
        cout << "7. Update Patron Fees\n";
        cout << "8. Display Patrons Who Owe Fees\n";
        cout << "9. Display Transactions\n";
        cout << "0. Exit\n";

        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            string isbn, title, author;
            int year, g;

            cout << "Enter ISBN: ";
            cin >> isbn;

            cout << "Enter title: ";
            cin >> ws;
            getline(cin, title);

            cout << "Enter author: ";
            getline(cin, author);

            cout << "Enter copyright year: ";
            cin >> year;

            cout << "Choose genre:\n";
            cout << "0. Fiction\n1. Nonfiction\n2. Periodical\n";
            cout << "3. Biography\n4. Children\n";
            cout << "Enter genre number: ";
            cin >> g;

            if (g < 0 || g > 4) {
                cout << "Invalid genre.\n";
            } else {
                Book b(isbn, title, author, year, (Genre)g);
                library.addBook(b);
            }
        }

        else if (choice == 2) {
            string username, card;
            int fees;

            cout << "Enter username: ";
            cin >> ws;
            getline(cin, username);

            cout << "Enter card number: ";
            cin >> card;

            cout << "Enter owed fees: ";
            cin >> fees;

            if (fees < 0) {
                cout << "Fees cannot be negative.\n";
            } else {
                Patron p(username, card, fees);
                library.addPatron(p);
            }
        }

        else if (choice == 3) {
            library.displayBooks();
        }

        else if (choice == 4) {
            library.displayPatrons();
        }

        else if (choice == 5) {
            string isbn, card, date;

            cout << "Enter book ISBN: ";
            cin >> isbn;

            cout << "Enter patron card number: ";
            cin >> card;

            cout << "Enter date (DD/MM/YYYY): ";
            cin >> date;

            library.borrowBook(isbn, card, date);
        }

        else if (choice == 6) {
            string isbn, card, date;

            cout << "Enter book ISBN: ";
            cin >> isbn;

            cout << "Enter patron card number: ";
            cin >> card;

            cout << "Enter date (DD/MM/YYYY): ";
            cin >> date;

            library.returnBook(isbn, card, date);
        }

        else if (choice == 7) {
            string card;
            int fees;

            cout << "Enter patron card number: ";
            cin >> card;

            cout << "Enter new fees: ";
            cin >> fees;

            if (fees < 0) {
                cout << "Fees cannot be negative.\n";
            } else {
                library.updateFees(card, fees);
            }
        }

        else if (choice == 8) {
            vector<string> names = library.patronsWithFees();

            cout << "\nPatrons who owe fees:\n";

            if (names.empty()) {
                cout << "No patrons owe fees.\n";
            } else {
                for (int i = 0; i < names.size(); i++) {
                    cout << names[i] << endl;
                }
            }
        }

        else if (choice == 9) {
            library.displayTransactions();
        }

        else if (choice != 0) {
            cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 0);

    cout << "Thank you for using the library system.\n";

    return 0;
}

