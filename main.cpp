#include <iostream>
#include <string>
#include "classes/StudentManager.cpp" // Assuming this contains the StudentManager class
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
                    Student student (3, "Dani", "Olmo", "tizi", "08/08/2000");
                    
                        sm.updateStudent(student);
                        
                  
                    break;
                }
                case 3: {
                    // Remove a student
                    int student_number;
                    cout << "Enter the student number to remove: ";
                    cin >> student_number;

                    Student student (3, "Dani", "Olmo", "tizi", "08/08/2000");
                    
                        sm.removeStudent(student);
                    
                    break;
                }
                case 4: {
                    // Show all students
                    sm.display_students();
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
    // Create some sample students
    Student s1(1, "lab", "ama", "alger", "08/08/2000");
    Student s2(2, "bip", "bip", "oran", "08/08/2000");
    Student s3(3, "Dani", "Olmo", "tizi", "08/08/2000");

    // Initialize the StudentManager
    StudentManager sm;
    sm.addStudent(s1);
    sm.addStudent(s2);
    sm.addStudent(s3);

    // Display initial students
    sm.display_students();

    // Initialize the Menu
    Menu menu;
    int choice = 0;
    menu.show(choice, sm);

    return 0;
}
