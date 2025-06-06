#include <iostream>
#include <vector>
#include <string>
#include <ctime>
using namespace std;

struct Book {
    string title;
    string author;
    string isbn;
    bool isAvailable = true;
    time_t dueDate = 0;
};

struct Borrower {
    string name;
    string borrowedISBN;
    time_t borrowDate;
};

vector<Book> books;
vector<Borrower> borrowers;

void addBook() {
    Book b;
    cout << "Enter Title: ";
    cin.ignore();
    getline(cin, b.title);
    cout << "Enter Author: ";
    getline(cin, b.author);
    cout << "Enter ISBN: ";
    getline(cin, b.isbn);
    books.push_back(b);
    cout << "Book added successfully!\n";
}

void searchBook() {
    string keyword;
    cout << "Enter title, author or ISBN to search: ";
    cin.ignore();
    getline(cin, keyword);

    bool found = false;
    for (const auto& b : books) {
        if (b.title.find(keyword) != string::npos || 
            b.author.find(keyword) != string::npos ||
            b.isbn.find(keyword) != string::npos) {
            cout << "Title: " << b.title << ", Author: " << b.author 
                 << ", ISBN: " << b.isbn 
                 << ", Status: " << (b.isAvailable ? "Available" : "Checked Out") << "\n";
            found = true;
        }
    }

    if (!found)
        cout << "No matching books found.\n";
}

void checkoutBook() {
    string isbn, name;
    cout << "Enter borrower's name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter ISBN of book to checkout: ";
    getline(cin, isbn);

    for (auto& b : books) {
        if (b.isbn == isbn && b.isAvailable) {
            b.isAvailable = false;
            b.dueDate = time(nullptr) + (7 * 24 * 60 * 60); 

            borrowers.push_back({name, isbn, time(nullptr)});
            cout << "Book checked out successfully! Due in 7 days.\n";
            return;
        }
    }
    cout << "Book not available or invalid ISBN.\n";
}

void returnBook() {
    string isbn;
    cout << "Enter ISBN of book to return: ";
    cin.ignore();
    getline(cin, isbn);

    for (auto& b : books) {
        if (b.isbn == isbn && !b.isAvailable) {
            b.isAvailable = true;

            for (auto it = borrowers.begin(); it != borrowers.end(); ++it) {
                if (it->borrowedISBN == isbn) {
                    time_t now = time(nullptr);
                    double daysLate = difftime(now, b.dueDate) / (60 * 60 * 24);

                    if (daysLate > 0) {
                        double fine = daysLate * 5; // Rs.5 per day
                        cout << "Book returned late. Fine: Rs." << fine << "\n";
                    } else {
                        cout << "Book returned on time. No fine.\n";
                    }

                    borrowers.erase(it);
                    b.dueDate = 0;
                    return;
                }
            }
        }
    }

    cout << "Invalid return. Book might not be checked out.\n";
}

void displayBooks() {
    if (books.empty()) {
        cout << "No books in the library.\n";
        return;
    }

    cout << "--- Book List ---\n";
    for (const auto& b : books) {
        cout << "Title: " << b.title << ", Author: " << b.author 
             << ", ISBN: " << b.isbn 
             << ", Status: " << (b.isAvailable ? "Available" : "Checked Out") << "\n";
    }
}

void showMenu() {
    cout << "\n--- Library Management System ---\n";
    cout << "1. Add Book\n";
    cout << "2. Search Book\n";
    cout << "3. Checkout Book\n";
    cout << "4. Return Book\n";
    cout << "5. View All Books\n";
    cout << "6. Exit\n";
    cout << "Choose an option: ";
}

int main() {
    int choice;
    do {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1: addBook(); break;
            case 2: searchBook(); break;
            case 3: checkoutBook(); break;
            case 4: returnBook(); break;
            case 5: displayBooks(); break;
            case 6: cout << "Exiting system. Goodbye!\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 6);

    return 0;
}
