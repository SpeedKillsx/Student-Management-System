#include <iostream>
#include <string>
#include "classes/StudentManager.cpp"
#include <sqlite3.h>

using namespace std;

struct Menu {
    void show(int choice, StudentManager &sm) {
        cout << "Good Morning to Student System Manager" << endl;
        cout << "--------------------------------------" << endl;

        do {
            cout << "Choose one of the proposed tasks (1,2,3,4,-1 to exit)" << endl;
            cout << "1 - Add a student" << endl;
            cout << "2 - Update Student" << endl;
            cout << "3 - Remove a student" << endl;
            cout << "4 - Show students" << endl;
            cout << "Enter your choice: ";

            while (!(cin >> choice)) {
                cin.clear();  // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Discard invalid input
                cout << "Invalid input. Please enter an integer: ";
            }

            switch (choice) {
                case 1: {
                    // Add a new student
                    int student_number;
                    string name, surname, place_birth, date_birth;

                    cout << "Introduce the student number: ";
                    cin >> student_number;
                    cout << "Introduce the student name: ";
                    cin >> name;
                    cout << "Introduce the student surname: ";
                    cin >> surname;
                    cout << "Introduce the student place of birth: ";
                    cin >> place_birth;
                    cout << "Introduce the student date of birth (dd/mm/yyyy): ";
                    cin >> date_birth;

                    Student new_student(student_number, name, surname, place_birth, date_birth);
                    sm.addStudent(new_student);
                    cout << "Student added successfully!" << endl;
                    break;
                }
                case 2: {
                    // Update a student
                    int student_number;
                    cout << "Enter the student number to update: ";
                    cin >> student_number;
                    Student student(student_number, "NewName", "NewSurname", "NewPlace", "01/01/2000"); // Update with new data
                    sm.updateStudent(student);
                    break;
                }
                case 3: {
                    // Remove a student
                    int student_number;
                    cout << "Enter the student number to remove: ";
                    cin >> student_number;
                    Student student(student_number, "DummyName", "DummySurname", "DummyPlace", "01/01/2000"); // Dummy data for removal
                    sm.removeStudent(student);
                    break;
                }
                case 4: {
                    // Show all students from the database
                    sm.showStudentsFromDatabase(); // Call to the new method
                    break;
                }
                case -1:
                    cout << "Exiting..." << endl;
                    break;
                default:
                    cout << "Invalid choice. Please choose a valid option!" << endl;
                    break;
            }
        } while (choice != -1);  // Use -1 to exit the menu
    }
};

int main() {
    // Initialize the StudentManager
    StudentManager sm;
    int rc = sm.ConnectDatabase("Student_gestion.db");
    printf("rc = %d\n", rc);

    // Check if the database is connected and display students
    if (rc == SQLITE_OK) {
        // Display initial students from the database
        sm.showStudentsFromDatabase();

        // Initialize the Menu
        Menu menu;
        int choice = 0;
        menu.show(choice, sm);
    }

    return 0;
}
