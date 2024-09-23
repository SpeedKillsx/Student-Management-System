#include<iostream>
#include<sqlite3.h>
#include"Database.hpp"
using namespace std;
Database::Database(const char* file_path)
{
    this->data_file=file_path;
}
Database::Database(string username, string password, const  char* file_path){
    this->username=username;
    this->password = password;
    this->data_file = file_path;
}
std::string Database::getUsername(){
    return this->username;
}
std::string Database::getPassword(){
    return this->password;
}
const char* Database::getDataFile(){
    return this->data_file;
}

int Database::connect(sqlite3 **db){
    int rc = sqlite3_open(this->data_file, db);
    cout<<db<<endl;
    return rc;
}
