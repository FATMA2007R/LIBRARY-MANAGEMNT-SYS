#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
using namespace std;

class User {
private:
    int id;
    string name;
    string role;

public:
    User(int i, string n, string r);
    string getRole();
};

#endif
