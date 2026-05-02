#ifndef LIBRARY_H
#define LIBRARY_H

#include <vector>
#include "book.h"
#include "user.h"

class Library {
private:
    std::vector<Book> books;
    std::vector<User> users;

public:
    // Books
    void addBook(const Book& book);
    Book* searchBook(int bookid);

    // Users
    void addUser(const User& user);
    User* searchUser(int id);

    // Borrow & Return
    bool borrowBook(int bookid, int id);
    bool returnBook(int bookid, int id);

    // Getters
    std::vector<Book>& getBooks();
};

#endif
