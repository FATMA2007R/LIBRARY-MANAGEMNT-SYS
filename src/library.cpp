#include "../include/library.h"

// -------------------- Books --------------------

void Library::addBook(const Book& book) {
    books.push_back(book);
}

Book* Library::searchBook(int bookid) {
    for (auto& book : books) {
        if (book.getbookid() == bookid) {
            return &book;
        }
    }
    return nullptr;
}

// -------------------- Users --------------------

void Library::addUser(const User& user) {
    users.push_back(user);
}

User* Library::searchUser(int id) {
    for (auto& user : users) {
        if (user.getId() == id) {
            return &user;
        }
    }
    return nullptr;
}

// -------------------- Borrow Book --------------------

bool Library::borrowBook(int bookid, int id) {
    Book* book = searchBook(bookid);
    User* user = searchUser(id);

    if (book && user && book->getisavailable()) {
        book->setisavailable(false);
        return true;
    }
    return false;
}

// -------------------- Return Book --------------------

bool Library::returnBook(int bookid, int id) {
    Book* book = searchBook(bookid);
    User* user = searchUser(id);

    if (book && user && !book->getisavailable()) {
        book->setisavailable(true);
        return true;
    }
    return false;
}

// -------------------- Getters --------------------

std::vector<Book>& Library::getBooks() {
    return books;
}


// ------------------- Users -------------------
