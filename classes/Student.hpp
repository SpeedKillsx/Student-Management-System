#include<string>
#ifndef STUDENT_H
#define STUDENT_H
using namespace std;
class Student{
    private:
        int student_number; 
        string name; 
        string surname; 
        string place_birth;
        string date_birth;
    
    
    public:
    Student(int student_number,string name,string surname, string place_birth, string date_birth);
    int getStudentNumber();
    string getName();
    string getPlaceBirth();
    string getSurname();
    string getPlaceBirth();
    string getDateBirth();
    void display_student();
};
#endif