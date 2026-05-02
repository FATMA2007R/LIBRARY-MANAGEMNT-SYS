#ifndef RESERVATION_H
#define RESERVATION_H

#include <vector>

class Reservation {
private:
    int bookId;
    std::vector<int> waitingList;   // user IDs
    int currentBorrowerId;           // -1 if not borrowed

public:
    Reservation(int bookid);

    // Borrowing
    bool borrowBook(int id);
    void returnBook();

    // Waiting list
    void addToWaitingList(int id);
    int getNextUser();

    // Getters
    int getBookId() const;
    bool isBorrowed() const;
};

#endif
;
