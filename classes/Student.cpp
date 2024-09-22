#include <iostream>
#include <string>
using namespace std;
class Student{
    public:
    bool operator==(const Student& other) const{
        return (this->student_number == other.student_number);
    }
    private:
     int student_number; 
     string name; 
     string surname; 
     string place_birth;
     string date_birth;



    public: Student(int student_number,string name,string surname, string place_birth, string date_birth){
        this->student_number = student_number; 
        this->name = name;
        this->surname = surname;
        this->place_birth = place_birth;
        this->date_birth = date_birth;
    }

    public:string getName(){
        return this->name;
    }
    public:int getStudentNumber(){
        return this->student_number;
    }

    public:string getSurname(){
        return this->surname;
    }
    public:string getPlaceBirth(){
        return this->place_birth;
    }
    public:string getDateBirth(){
        return this->date_birth;
    }
    public : void display_student(){
        cout <<"\tName = "<< this->name <<"\tSurname = "<< this->surname<<endl;
    }

};