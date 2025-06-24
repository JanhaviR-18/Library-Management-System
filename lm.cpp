#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <map>
#include <fstream> 

using namespace std;

class Book {
public:
    int id;
    string title;
    string author;
    bool available;

    Book(int i, string t, string a) {
        id = i;
        title = t;
        author = a;
        available = true;
    }
};

class User {
protected:
    int userId;
    string name;
public:
    User(int id, string n) : userId(id), name(n) {}
    virtual void showUserType() = 0;
    string getName() { return name; }
    int getId() { return userId; }
};

class Student : public User {
    map<int, time_t> borrowDates; 
public:
    Student(int id, string name) : User(id, name) {}

    void borrowBook(int bookId) {
        time_t now = time(0);
        borrowDates[bookId] = now;
    }

    void returnBook(int bookId) {
        time_t borrowedTime = borrowDates[bookId];
        double seconds = difftime(time(0), borrowedTime);
        int days = seconds / (60 * 60 * 24);
        if (days > 14) {
            int fine = (days - 14) * 5;
            cout << "Book returned late. Fine = ₹" << fine << endl;
        } else {
            cout << "Book returned on time. No fine.\n";
        }
        borrowDates.erase(bookId);
    }

    void showUserType() override {
        cout << "User Type: Student\n";
    }
};

class Librarian : public User {
public:
    Librarian(int id, string name) : User(id, name) {}

    void showUserType() override {
        cout << "User Type: Librarian\n";
    }
};

class Library {
    vector<Book> books;

public:
    void loadBooks() {
        ifstream file("books.txt");
        if (!file.is_open()) return;

        books.clear();
        int id;
        string title, author;
        while (file >> id) {
            file.ignore(); // skip newline or space
            getline(file, title);
            getline(file, author);
            books.push_back(Book(id, title, author));
        }
        file.close();
    }

    void saveBooks() {
        ofstream file("books.txt");
        for (auto &b : books) {
            file << b.id << endl;
            file << b.title << endl;
            file << b.author << endl;
        }
        file.close();
    }

    void addBook(Book b) {
        books.push_back(b);
        saveBooks();
        cout << "Book added successfully!\n";
    }

    void listBooks() {
        if (books.empty()) {
            cout << "No books in library.\n";
            return;
        }
        for (auto &b : books) {
            cout << "Book ID: " << b.id << ", Title: " << b.title << ", Author: " << b.author
                 << ", Available: " << (b.available ? "Yes" : "No") << endl;
        }
    }

    bool issueBook(int bookId, Student &s) {
        for (auto &b : books) {
            if (b.id == bookId && b.available) {
                b.available = false;
                s.borrowBook(bookId);
                cout << "Book issued successfully.\n";
                return true;
            }
        }
        cout << "Book not available or does not exist.\n";
        return false;
    }

    bool returnBook(int bookId, Student &s) {
        for (auto &b : books) {
            if (b.id == bookId && !b.available) {
                b.available = true;
                s.returnBook(bookId);
                return true;
            }
        }
        cout << "Invalid return.\n";
        return false;
    }
};

int main() {
    Library lib;
    lib.loadBooks(); 

    User *currentUser = nullptr;
    Student student(1, "Janhavi");
    Librarian librarian(2, "Admin");

    cout << "Are you a Student or Librarian? (s/l): ";
    char userType;
    cin >> userType;

    if (userType == 's' || userType == 'S') {
        currentUser = &student;
    } else if (userType == 'l' || userType == 'L') {
        currentUser = &librarian;
    } else {
        cout << "Invalid input. Exiting.\n";
        return 0;
    }

    int choice;
    do {
        cout << "\n--- Library Management Menu ---\n";
        if (userType == 'l' || userType == 'L') {
            cout << "1. Add Book\n";
        }
        cout << "2. List Books\n";
        cout << "3. Issue Book\n";
        cout << "4. Return Book\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if ((userType == 'l' || userType == 'L') && choice == 1) {
            int id;
            string title, author;
            cout << "Enter Book ID: ";
            cin >> id;
            cin.ignore();
            cout << "Enter Title: ";
            getline(cin, title);
            cout << "Enter Author: ";
            getline(cin, author);
            lib.addBook(Book(id, title, author));
        } else if (choice == 2) {
            lib.listBooks();
        } else if (choice == 3) {
            int id;
            cout << "Enter Book ID to issue: ";
            cin >> id;
            if (userType == 's' || userType == 'S')
                lib.issueBook(id, student);
            else
                cout << "Only students can issue books.\n";
        } else if (choice == 4) {
            int id;
            cout << "Enter Book ID to return: ";
            cin >> id;
            if (userType == 's' || userType == 'S')
                lib.returnBook(id, student);
            else
                cout << "Only students can return books.\n";
        } else if (choice == 5) {
            cout << "Exiting program...\n";
        } else {
            cout << "Invalid choice.\n";
        }

    } while (choice != 5);

    return 0;
}
