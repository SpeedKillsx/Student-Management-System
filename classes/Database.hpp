#ifndef DATABSE_H
#define DATABSE_H
using namespace std;
#include<string>

    class Database{
        private:
            string username;
            string password;
            const char* data_file;
        public:
            Database(const char* file_path);
            Database(sqlite3 *db);
            Database(string username, string password,const char* file_path);
            std::string getUsername();
            std::string getPassword();
            const char* getDataFile();
            int connect(sqlite3** db);
            void close();
            
    };
#endif