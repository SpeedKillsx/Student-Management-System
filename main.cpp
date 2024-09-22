#include <iostream>
#include <string>
#include "classes/StudentManager.cpp"

int main(){
    Student s(1,"lab","ama","alger","08/08/2000");
    Student s2(2,"bip","bip","oran","08/08/2000");
    Student s3(3,"Dani","Olmo","tizi","08/08/2000");
    
    //s.display_student();
    StudentManager sm;
    sm.addStudent(s);
    sm.display_students();
    sm.addStudent(s2);
    sm.addStudent(s3);
    sm.display_students();
    sm.removeStudent(s2);
    sm.display_students();
    sm.updateStudent(s3);
    s3.display_student();
    return 0;
}