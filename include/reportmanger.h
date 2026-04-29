
#ifndef REPORTMANAGER_H
#define REPORTMANAGER_H

#include <vector>
#include <map>
#include <string>

//يتربط ب Person 1
#include "Book.h" 

class ReportManager {
public:
   
    static int getTotalBooks(const std::vector<Book>& libraryBooks);

 
    static int getAvailableBooksCount(const std::vector<Book>& libraryBooks);

   
    static std::string getMostPopularBook(const std::vector<Book>& libraryBooks, const std::map<int, int>& borrowHistory);
};

#endif // REPORTMANAGER_H