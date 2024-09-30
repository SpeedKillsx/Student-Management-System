#include <iostream>
#include <string>
#include "Student.cpp"
#include <vector>
#include<algorithm>
#include<sqlite3.h>
#include "Database.hpp"
using namespace std;
class StudentManager{
    private:
    vector<Student> Student_vector;
    sqlite3 *db;
    public: StudentManager(){
        
    }

    public:void display_students(){
        for (int i = 0; i< this->Student_vector.size(); i++)
        {
            this->Student_vector[i].display_student();
            cout<<"--------------------------------------"<<endl;

        }
        
    }
    string quotesql( const string& s ) {
        return string("'") + s + string("'");
    }
    public : void addStudent(){
        
        
        int student_number;
        string name, surname, date, place;
        cout<<"Enter the informations of the student : "<<endl; 
        cout<<"Enter the student number : "<<endl;
        cin >> student_number;
        cout<<"Enter the name of the student : "<<endl;
        cin>> name;
        cout<<"Enter the surname of the student : "<<endl;
        cin>> surname;
        cout<<"Enter the birth date of the student : "<<endl;
        cin>> date;
        cout<<"Enter the birth place of the student : "<<endl;
        cin>>place;
        string sql = "INSERT into STUDENT values ("+quotesql(to_string(student_number))+","+quotesql(name)+","+quotesql(surname)+","+quotesql(date)+","+quotesql(place)+")";
        
        sqlite3_stmt *stmt;
        
        int rc = sqlite3_prepare_v2(this->db, sql.c_str(), -1, &stmt, 0);
        if (rc != SQLITE_OK) {
            cout << "Failed to prepare statement. Error: " << sqlite3_errmsg(this->db) << endl;
            return;  // Early exit if preparation fails
        } else {
            cout << "SQL statement prepared successfully." << endl;
        }
        cout << "Executing insert  statement..." << endl;
        sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, surname.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 3, date.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 4, place.c_str(), -1, SQLITE_STATIC);
        // Execute the statement
        
        if (sqlite3_step(stmt) != SQLITE_DONE) {
            cout << "Failed to execute statement. Error: " << sqlite3_errmsg(this->db) << endl;
        } else {
            cout << "Student added successfully." << endl;
        }
        
        sqlite3_finalize(stmt);  // Clean up statement
        cout << "Finished executing insert statement." << endl;
        this->Student_vector.push_back( Student(student_number, name, surname, date, place));
        RefreshVector();
    }
    /* Add the remove in the database , be sure to remove it from the vector*/
    void removeStudent(Student &s) {
        auto it = std::find(this->Student_vector.begin(), this->Student_vector.end(), s);
        
        if (it != this->Student_vector.end()) {
            this->Student_vector.erase(it);
            std::cout << "Etudiant supprime." << std::endl;
        } else {
            std::cout << "Etudiant non trouve." << std::endl;
        }
        RefreshVector();
    }

    void updateStudent(int student_number){
        Student s(student_number, "","","","");
        auto it = std::find(this->Student_vector.begin(), this->Student_vector.end(), s);
        if (it != this->Student_vector.end()){
                
                string name, surname, place_birth, date_birth;

                cout << "Introduce the student name: ";
                cin >> name;
                cout << "Introduce the student surname: ";
                cin >> surname;
                cout << "Introduce the student place of birth: ";
                cin >> place_birth;
                cout << "Introduce the student date of birth (dd/mm/yyyy): ";
                cin >> date_birth;
                string SQL_UPDATE = "UPDATE Student set name_student = "+quotesql(name)+", student_surname = "+quotesql(surname)+", date_birth ="+quotesql(date_birth)+", place_birth = "+quotesql(place_birth)+" where student_number = "+quotesql(to_string(student_number))+"";
                sqlite3_stmt *stmt;
        
                int rc = sqlite3_prepare_v2(this->db, SQL_UPDATE.c_str(), -1, &stmt, 0);
                if (rc != SQLITE_OK) {
                    cout << "Failed to prepare statement. Error: " << sqlite3_errmsg(this->db) << endl;
                    return;  // Early exit if preparation fails
                } else {
                    cout << "SQL statement prepared successfully." << endl;
                }
                cout << "Executing insert  statement..." << endl;
                sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);
                sqlite3_bind_text(stmt, 2, surname.c_str(), -1, SQLITE_STATIC);
                sqlite3_bind_text(stmt, 3, date_birth.c_str(), -1, SQLITE_STATIC);
                sqlite3_bind_text(stmt, 4, place_birth.c_str(), -1, SQLITE_STATIC);
                sqlite3_bind_text(stmt, 5, to_string(student_number).c_str(), -1, SQLITE_STATIC); // Add the last element of the request (condition 'where")

                if (sqlite3_step(stmt) != SQLITE_DONE) {
                    cout << "Failed to execute statement. Error: " << sqlite3_errmsg(this->db) << endl;
                } else {
                    cout << "Student added successfully." << endl;
                }
                
                sqlite3_finalize(stmt);  // Clean up statement
                cout << "Finished executing insert statement." << endl;
        }else  {
                cout << "The student doesn't exist in the database! ";
        }
        

    }
    int ConnectDatabase(const char * file){
        Database database(file);
        
        int rc = database.connect(&this->db);
        printf("%d", rc);
        if (rc!=SQLITE_OK){
            cout<<"Connection error!!!"<<endl;
        }else{
            cout<<"The database is connected"<<endl;
        }
        return rc;
    }

    void CloseDatabase(){
        sqlite3_close(this->db);
    }
    void RefreshVector(){
        this->Student_vector.clear();
        const char *sql = "SELECT * FROM Student";  // SQL query to select all students
        sqlite3_stmt *stmt;

        if (this->db == nullptr) {
            cout << "Database connection is not established." << endl;
            return;
        }

        int rc = sqlite3_prepare_v2(this->db, sql, -1, &stmt, 0);
        if (rc != SQLITE_OK) {
            cout << "Failed to prepare statement. Error: " << sqlite3_errmsg(this->db) << endl;
            return;  // Early exit if preparation fails
        }

        // Execute the statement and display results
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            // Retrieve student data
            int student_number = sqlite3_column_int(stmt, 0);  
            const char *name = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));  // Name
            const char *surname = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));  // Surname
            const char *date_birth = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3));  // Date of birth
            const char *place_birth = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 4));  // Place of birth

            this->Student_vector.push_back( Student(student_number, name, surname, date_birth, place_birth ));
        }
        sqlite3_finalize(stmt);
    }
    void showStudentsFromDatabase() {
        const char *sql = "SELECT * FROM Student";  // SQL query to select all students
        sqlite3_stmt *stmt;

        if (this->db == nullptr) {
            cout << "Database connection is not established." << endl;
            return;
        }

        cout << "Attempting to prepare SQL statement..." << endl;
        int rc = sqlite3_prepare_v2(this->db, sql, -1, &stmt, 0);
        if (rc != SQLITE_OK) {
            cout << "Failed to prepare statement. Error: " << sqlite3_errmsg(this->db) << endl;
            return;  // Early exit if preparation fails
        } else {
            cout << "SQL statement prepared successfully." << endl;
        }

        cout << "Executing statement..." << endl;
        // Execute the statement and display results
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            // Retrieve student data
            int student_number = sqlite3_column_int(stmt, 0);  
            const char *name = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));  // Name
            const char *surname = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));  // Surname
            const char *date_birth = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3));  // Date of birth
            const char *place_birth = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 4));  // Place of birth

            // Display student information
            cout << "Student Number: " << student_number 
                << ", Name: " << (name ? name : "NULL") 
                << ", Surname: " << (surname ? surname : "NULL") 
                << ", Date of Birth: " << (date_birth ? date_birth : "NULL") 
                << ", Place of Birth: " << (place_birth ? place_birth : "NULL") << endl;
        
            this->Student_vector.push_back( Student(student_number, name, surname, date_birth, place_birth ));
        }
        sqlite3_finalize(stmt);  // Clean up statement
        cout << "Finished executing statement." << endl;
}

};