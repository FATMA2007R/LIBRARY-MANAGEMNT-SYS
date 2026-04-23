#include "../include/user.h"

User::User(int i, string n, string r) {
    id = i;
    name = n;
    role = r;
}

string User::getRole() {
    return role;
}
