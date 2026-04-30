
#ifndef BOOK_H
#define BOOK_H

#include <string>

class Book {
private:
    int id;
    std::string title;
    bool isAvailable;

public:
    // ده اللي الأكواد بتاعتك محتاجاه عشان تشتغل
    int getId() const { return id; }
    std::string getTitle() const { return title; }
    bool getIsAvailable() const { return isAvailable; }
};

#endif