#include "../include/reservation.h"

Reservation::Reservation(int bookid)
    : bookId(bookId), currentBorrowerId(-1) {}

// ------------------- Borrow -------------------

bool Reservation::borrowBook(int id) {
    if (currentBorrowerId == -1) {
        currentBorrowerId = id;
        return true;
    } else {
        addToWaitingList(id);
        return false;
    }
}

// ------------------- Return -------------------

void Reservation::returnBook() {
    if (!waitingList.empty()) {
        currentBorrowerId = waitingList.front();
        waitingList.erase(waitingList.begin());
    } else {
        currentBorrowerId = -1;
    }
}

// ------------------- Waiting List -------------------

void Reservation::addToWaitingList(int id) {
    waitingList.push_back(id);
}

int Reservation::getNextUser() {
    if (!waitingList.empty())
        return waitingList.front();
    return -1;
}

// ------------------- Getters -------------------

int Reservation::getBookId() const {
    return bookId;
}

bool Reservation::isBorrowed() const {
    return currentBorrowerId != -1;
}


