
#include "../include/fine.h"
#include <iostream>

Fine::Fine(int uId, int bId) : userId(uId), bookId(bId), amount(0.0), isPaid(false) {}

void Fine::calculateFine(int overdueDays) {
    if (overdueDays > 0) {
        amount = overdueDays * DAILY_FINE_RATE;
        isPaid = false;
    } else {
        amount = 0.0;
        isPaid = true;  
    }
}

double Fine::getAmount() const { return amount; }
bool Fine::getIsPaid() const { return isPaid; }
int Fine::getUserId() const { return userId; }
int Fine::getBookId() const { return bookId; }

void Fine::payFine() {
    if (amount > 0) {
        isPaid = true;
        amount = 0.0;
        std::cout << "Fine paid successfully for User ID: " << userId << "\n";
    } else {
        std::cout << "No fine to pay.\n";
    }
}