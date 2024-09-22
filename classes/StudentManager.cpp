#include <iostream>
#include <string>
#include "Student.cpp"
#include <vector>
#include<algorithm>
using namespace std;
class StudentManager{
    private:
    vector<Student> Student_vector;

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
};