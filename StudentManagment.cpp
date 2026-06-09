#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Student {
private:
    int rollNo;
    string name;
    float marks;

    public:

  
    void addStudent() {
        ofstream file("students.txt", ios::app);

        cout << "Enter Roll No: " << endl;
        cin >> rollNo;
        cout << "Enter Name: " << endl;
        cin.ignore();
        getline(cin, name);
        cout << "Enter Marks: " << endl;
        cin >> marks;

        file << rollNo << "\n" << name << "\n" << marks << "\n";
        file.close();

        cout << " Student added successfully!" << endl;
    }

   
    void displayAll() {
        ifstream file("students.txt");

        if (!file) {
            cout << "No records found!" << endl;
            return;
        }

        cout << "\n----------------------------- << endl";
        cout << "  Roll |  Name        | Marks" << endl;
        cout << "-----------------------------" << endl;

        while (file >> rollNo) {
            file.ignore();
            getline(file, name);
            file >> marks;
            file.ignore();

            cout << "  " << rollNo
                 << "    |  " << name
                 << "  |  " << marks << endl;
        }
        cout << "-----------------------------" << endl;
        file.close();
    }

   
    void deleteStudent() {
        int target;
        cout << "Enter Roll No to delete: ";
        cin >> target;

        ifstream file("students.txt");
        ofstream temp("temp.txt");
        bool found = false;

        while (file >> rollNo) {
            file.ignore();
            getline(file, name);
            file >> marks;
            file.ignore();

            if (rollNo != target) {
                temp << rollNo << "\n" << name << "\n" << marks << "\n";
            } else {
                found = true;  
            }
        }

        file.close();
        temp.close();

        remove("students.txt");
        rename("temp.txt", "students.txt");

        if (found)
            cout << "✔ Student deleted successfully!"<< endl;
        else
            cout << "✘ Roll No not found!" << endl;
    }

  
    void updateStudent() {
        int target;
        cout << "Enter Roll No to update: ";
        cin >> target;

        ifstream file("students.txt");
        ofstream temp("temp.txt");
        bool found = false;

        while (file >> rollNo) {
            file.ignore();
            getline(file, name);
            file >> marks;
            file.ignore();

            if (rollNo == target) {
                found = true;
                cout << "Enter new Name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter new Marks: ";
                cin >> marks;
            }

            temp << rollNo << "\n" << name << "\n" << marks << "\n";
        }

        file.close();
        temp.close();

        remove("students.txt");
        rename("temp.txt", "students.txt");

        if (found)
            cout << "✔ Student updated successfully!" << endl;
        else
            cout << "✘ Roll No not found!" << endl;
    }

  
    void showMenu() {
        int choice;

        do {
            cout << "\n============================\n";
            cout << " Student Management System\n";
            cout << "============================\n";
            cout << " 1. Add Student\n";
            cout << " 2. Display All Students\n";
            cout << " 3. Update Student\n";
            cout << " 4. Delete Student\n";
            cout << " 5. Exit\n";
            cout << "============================\n";
            cout << " Enter choice: ";
            cin >> choice;

            switch (choice) {
                case 1: addStudent();    break;
                case 2: displayAll();    break;
                case 3: updateStudent(); break;
                case 4: deleteStudent(); break;
                case 5: cout << "Goodbye!\n"; break;
                default: cout << "Invalid! Try again.\n";
            }

        } while (choice != 5);
    }

}; 

int main() {
    Student sm;  
    sm.showMenu(); 
    return 0;
}