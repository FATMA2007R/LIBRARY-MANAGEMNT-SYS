#include "../include/reportmanger.h"

int ReportManager::getTotalBooks(const std::vector<Book>& libraryBooks) {
    return libraryBooks.size();
}

int ReportManager::getAvailableBooksCount(const std::vector<Book>& libraryBooks) {
    int count = 0;
    for (const auto& book : libraryBooks) {
        // السطر اللي كان لوحده هنا اتمسح عشان كان غلط
        if (book.getIsAvailable()) { 
            count++;
        }
    }
    return count;
}

std::string ReportManager::getMostPopularBook(const std::vector<Book>& libraryBooks, const std::map<int, int>& borrowHistory) {
    if (borrowHistory.empty() || libraryBooks.empty()) {
        return "No data available";
    }

    int mostPopularBookId = -1;
    int maxBorrows = -1;

    for (const auto& pair : borrowHistory) {
        if (pair.second > maxBorrows) {
            maxBorrows = pair.second;
            mostPopularBookId = pair.first;
        }
    }

    for (const auto& book : libraryBooks) {
        if (book.getId() == mostPopularBookId) {
            return book.getTitle(); 
        }
    }
    return "Book not found";
}