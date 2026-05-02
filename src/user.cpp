#include "../include/user.h"

User::User(int i, string n ) {
    id = i;
    name = n;
    
}

int User::getId() {
    return id;
}
