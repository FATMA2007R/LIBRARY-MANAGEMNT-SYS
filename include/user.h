#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
using namespace std;

class User {
private:
    int id;
    string name;
    

public:
    User(int i, string n);
    int getId();
};

#endif
