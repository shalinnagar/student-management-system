#include <iostream>
#include <string>
using namespace std;

class Book {
public:
    int id;
    string title;
    string author;
    bool issued;

    void addBook() {
        cout << "Enter Book ID: ";
        cin >> id;
        cin.ignore();

        cout << "Enter Book Title: ";
        getline(cin, title);

        cout << "Enter Author Name: ";
        getline(cin, author);

        issued = false;
    }

    void displayBook() {
        cout << "\nBook ID: " << id;
        cout << "\nTitle: " << title;
        cout << "\nAuthor: " << author;
        cout << "\nStatus: " << (issued ? "Issued" : "Available") << endl;
    }
};

int main() {
    Book books[100];
    int count = 0;
    int choice;

    do {
        cout << "\n\n===== LIBRARY MANAGEMENT SYSTEM =====";
        cout << "\n1. Add Book";
        cout << "\n2. Display Books";
        cout << "\n3. Search Book";
        cout << "\n4. Issue Book";
        cout << "\n5. Return Book";
        cout << "\n6. Exit";
        cout << "\nEnter Choice: ";
        cin >> choice;

        switch(choice) {

        case 1:
            books[count].addBook();
            count++;
            cout << "Book Added Successfully!";
            break;

        case 2:
            if(count == 0) {
                cout << "No Books Available!";
            } else {
                for(int i=0; i<count; i++) {
                    books[i].displayBook();
                    cout << "\n-------------------";
                }
            }
            break;

        case 3: {
            string searchTitle;
            bool found = false;

            cin.ignore();
            cout << "Enter Book Title: ";
            getline(cin, searchTitle);

            for(int i=0; i<count; i++) {
                if(books[i].title == searchTitle) {
                    books[i].displayBook();
                    found = true;
                }
            }

            if(!found)
                cout << "Book Not Found!";
            break;
        }

        case 4: {
            int id;
            cout << "Enter Book ID to Issue: ";
            cin >> id;

            bool found = false;

            for(int i=0; i<count; i++) {
                if(books[i].id == id) {
                    if(!books[i].issued) {
                        books[i].issued = true;
                        cout << "Book Issued Successfully!";
                    } else {
                        cout << "Book Already Issued!";
                    }
                    found = true;
                }
            }

            if(!found)
                cout << "Book Not Found!";
            break;
        }

        case 5: {
            int id;
            cout << "Enter Book ID to Return: ";
            cin >> id;

            bool found = false;

            for(int i=0; i<count; i++) {
                if(books[i].id == id) {
                    if(books[i].issued) {
                        books[i].issued = false;
                        cout << "Book Returned Successfully!";
                    } else {
                        cout << "Book Already Available!";
                    }
                    found = true;
                }
            }

            if(!found)
                cout << "Book Not Found!";
            break;
        }

        case 6:
            cout << "Thank You!";
            break;

        default:
            cout << "Invalid Choice!";
        }

    } while(choice != 6);

    return 0;
}