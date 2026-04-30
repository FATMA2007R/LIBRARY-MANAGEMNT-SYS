
#ifndef FINE_H
#define FINE_H
class Fine {
private:
    int userId;
    int bookId;
    double amount;
    bool isPaid;
    // قيمة الغرامة عن كل يوم تأخير 
    const double DAILY_FINE_RATE = 5.0; 
public:
    // Constructor
    Fine(int uId, int bId);
    //  الغرامة حسب ايام التأخير
    void calculateFine(int overdueDays);

    // Getters
    double getAmount() const;
    bool getIsPaid() const;
    int getUserId() const;
    int getBookId() const;

    // Setter دفع الغرامة 
    void payFine();
};
#endif // FINE_H