#include <iostream>
#include <string>
using namespace std;

// Base class
class LibraryItem {
protected:
    string title;
    string author;
    int year;
    bool isCheckedOut;

public:
    LibraryItem(string t, string a, int y)
        : title(t), author(a), year(y), isCheckedOut(false) {}

    virtual void displayInfo() = 0;

    void checkoutItem() {
        if (isCheckedOut)
            cout << "Item already checked out.\n";
        else {
            isCheckedOut = true;
            cout << "Item checked out successfully.\n";
        }
    }

    void returnItem() {
        if (!isCheckedOut)
            cout << "Item was not checked out.\n";
        else {
            isCheckedOut = false;
            cout << "Item returned successfully.\n";
        }
    }

    virtual ~LibraryItem() {}
};

// Book class
class Book : public LibraryItem {
    int pages;

public:
    Book(string t, string a, int y, int p)
        : LibraryItem(t, a, y), pages(p) {}

    void displayInfo() {
        cout << "[Book] Title: " << title << ", Author: " << author
             << ", Year: " << year << ", Pages: " << pages
             << ", Status: " << (isCheckedOut ? "Checked Out" : "Available") << endl;
    }
};

// DVD class
class DVD : public LibraryItem {
    int duration;

public:
    DVD(string t, string d, int y, int dur)
        : LibraryItem(t, d, y), duration(dur) {}

    void displayInfo() {
        cout << "[DVD] Title: " << title << ", Director: " << author
             << ", Year: " << year << ", Duration: " << duration << " mins"
             << ", Status: " << (isCheckedOut ? "Checked Out" : "Available") << endl;
    }
};

// Magazine class
class Magazine : public LibraryItem {
    int issue;

public:
    Magazine(string t, string pub, int y, int i)
        : LibraryItem(t, pub, y), issue(i) {}

    void displayInfo() {
        cout << "[Magazine] Title: " << title << ", Publisher: " << author
             << ", Year: " << year << ", Issue: " << issue
             << ", Status: " << (isCheckedOut ? "Checked Out" : "Available") << endl;
    }
};


const int MAX_ITEMS = 10;

int main() {
    LibraryItem* items[MAX_ITEMS];
    int itemCount = 0;

    int numItems;
    cout << "How many items do you want to add (max " << MAX_ITEMS << ")? ";
    cin >> numItems;
    cin.ignore(); 
    if (numItems > MAX_ITEMS) numItems = MAX_ITEMS;

    for (int i = 0; i < numItems; ++i) {
        cout << "\nAdding item " << i + 1 << ":\n";
        cout << "Choose type (1=Book, 2=DVD, 3=Magazine): ";
        int type;
        cin >> type;
        cin.ignore();

        string title, author;
        int year;

        cout << "Enter title: ";
        getline(cin, title);
        cout << "Enter author/publisher/director: ";
        getline(cin, author);
        cout << "Enter year: ";
        cin >> year;

        if (type == 1) {
            int pages;
            cout << "Enter number of pages: ";
            cin >> pages;
            items[itemCount++] = new Book(title, author, year, pages);
        } else if (type == 2) {
            int duration;
            cout << "Enter duration (minutes): ";
            cin >> duration;
            items[itemCount++] = new DVD(title, author, year, duration);
        } else if (type == 3) {
            int issue;
            cout << "Enter issue number: ";
            cin >> issue;
            items[itemCount++] = new Magazine(title, author, year, issue);
        } else {
            cout << "Invalid type. Skipping this item.\n";
        }

        cin.ignore();
    }

    int choice;
    do {
        cout << "\nLibrary Menu:\n";
        cout << "1. Display All Items\n";
        cout << "2. Checkout Item\n";
        cout << "3. Return Item\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            for (int i = 0; i < itemCount; ++i) {
                cout << "Item " << i << ": ";
                items[i]->displayInfo();
            }
        } else if (choice == 2) {
            int idx;
            cout << "Enter item index to checkout: ";
            cin >> idx;
            if (idx >= 0 && idx < itemCount)
                items[idx]->checkoutItem();
            else
                cout << "Invalid index.\n";
        } else if (choice == 3) {
            int idx;
            cout << "Enter item index to return: ";
            cin >> idx;
            if (idx >= 0 && idx < itemCount)
                items[idx]->returnItem();
            else
                cout << "Invalid index.\n";
        } else if (choice != 4) {
            cout << "Invalid choice.\n";
        }

    } while (choice != 4);

    for (int i = 0; i < itemCount; ++i)
        delete items[i];

    return 0;
}
