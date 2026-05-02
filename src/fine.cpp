
#include "../include/fine.h"
#include <iostream>

Fine::Fine(int uId, int bId) : id(uId), bookid(bId), Amount(0.0), isPaid(false) {}

void Fine::calculateFine(int overdueDays) {
    if (overdueDays > 0) {
        Amount = overdueDays * DAILY_FINE_RATE;
        isPaid = false;
    } else {
        Amount = 0.0;
        isPaid = true;  
    }
}

double Fine::getAmount() const { return Amount; }
bool Fine::getIsPaid() const { return isPaid; }
int Fine::getUserId() const { return id; }
int Fine::getBookId() const { return bookid; }

void Fine::payFine() {
    if (Amount > 0) {
        isPaid = true;
        Amount = 0.0;
        std::cout << "Fine paid successfully for User ID: " << id << "\n";
    } else {
        std::cout << "No fine to pay.\n";
    }
}