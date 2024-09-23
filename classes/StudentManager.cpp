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
    public : void addStudent(Student s){
        this->Student_vector.push_back( s);
    }

    void removeStudent(Student &s) {
        auto it = std::find(this->Student_vector.begin(), this->Student_vector.end(), s);
        
        if (it != this->Student_vector.end()) {
            this->Student_vector.erase(it);
            std::cout << "Etudiant supprime." << std::endl;
        } else {
            std::cout << "Etudiant non trouve." << std::endl;
        }
    }

    void updateStudent(Student& s){
    
        cout<<s.getName()<<endl;
        s.setName("alli");
        cout<<s.getName()<<endl;

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
        int student_number = sqlite3_column_int(stmt, 0);  // Assuming first column is student number
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
    }

    sqlite3_finalize(stmt);  // Clean up statement
    cout << "Finished executing statement." << endl;
}

};