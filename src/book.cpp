#include "book.h"
using namespace std;
Book::Book() {
    bookid = 0;
    title = "";
    author = "";
    isavailable = true;
}

Book::Book(int bookid, const std::string& title, const std::string& author, bool isavailable) {
    this->bookid = bookid;
    this->title = title;
    this->author = author;
    this->isavailable = isavailable;
}

int Book::getbookid() const {
    return bookid;
}

std::string Book::gettitle() const {
    return title;
}

std::string Book::getauthor() const {
    return author;
}

bool Book::getisavailable() const {
    return isavailable;
}

void Book::setbookid(int bookid) {
    this->bookid = bookid;
}

void Book::settitle(const std::string& title) {
    this->title = title;
}

void Book::setauthor(const std::string& author) {
    this->author = author;
}

void Book::setisavailable(bool isavailable) {
    this->isavailable = isavailable;
}
