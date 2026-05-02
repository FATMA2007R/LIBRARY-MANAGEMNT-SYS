#ifndef Book_h
#define Book_h

#include <string>
using namespace std;
class Book {
private:
    int bookid;
    std::string title;
    std::string author;
    bool isavailable;

public:
    Book();
    Book(int id, const string& title, const string& author, bool isavailable);
    int getbookid() const;
    std::string gettitle() const;
    std::string getauthor() const;
    bool getisavailable() const;
    void setbookid(int id);
    void settitle(const string& title);
    void setauthor(const string& author);
    void setisavailable(bool isavailable);
};

#endif