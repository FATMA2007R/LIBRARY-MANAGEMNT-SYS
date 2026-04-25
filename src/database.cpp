
#include<iostream>
#include <iomanip>
#include "database.h"

using namespace std;

// دالة الـ callback: دي المسؤولة عن شكل طباعة البيانات اللي جاية من قاعدة البيانات في شاشة البرنامج (Terminal)
static int callback(void* NotUsed, int argc, char** argv, char** azColName) {
    static int rowCount = 0;
    // لو ده أول صف، اطبع برواز الجدول وعناوين الأعمدة
    if (rowCount == 0) {
        cout << "\n" << setfill('=') << setw(65) << "" << endl;
        cout << "| " << left << setw(8) << "ID" << "| " << setw(25) << "NAME / TITLE" << "| " << setw(14) << "STATUS" << " |" << endl;
        cout << setfill('-') << setw(65) << "" << endl;
        cout << setfill(' ');
    }
    // بنحدد حالة الكتاب: لو القيمة 1 يبقى متاح (Available)، غير كدة يبقى مستعار (Borrowed)
    string statusTxt = (argc > 2 && argv[2] && string(argv[2]) == "1") ? "Available" : "Borrowed";
    // طباعة بيانات الصف (المعرف، الاسم، الحالة) بشكل منسق
    cout << "| " << left << setw(8) << (argv[0] ? argv[0] : "NULL") << "| " << setw(25) << (argv[1] ? argv[1] : "NULL") << "| " << setw(14) << statusTxt << " |" << endl;
    rowCount++;
    return 0;
}

// Constructor: بيبدأ  وبيخلي مؤشر قاعدة البيانات "فاضي" في البداية
Database::Database() : db(nullptr) {}

// دالة فتح قاعدة البيانات: بتحاول تفتح الملف وبترجع "صح" لو العملية تمت بنجاح
bool Database::openDB(const string& dbName) { return sqlite3_open(dbName.c_str(), &db) == SQLITE_OK; }

// دالة إغلاق قاعدة البيانات: بتقفل الاتصال عشان تحافظ على البيانات
void Database::closeDB() { if (db) sqlite3_close(db); }

// دالة إنشاء الجداول: بتبني الجداول (الكتب، الطلاب، الاستعارة) لو مش موجودين
void Database::createTables() {
    // جدول الاستعارة هنا متظبط عشان يشيل الأرقام والأسماء مع بعض زي ما طلبت
    string sql = "CREATE TABLE IF NOT EXISTS books (ID INTEGER PRIMARY KEY, TITLE TEXT, STATUS INTEGER);"
                 "CREATE TABLE IF NOT EXISTS users (ID INTEGER PRIMARY KEY, NAME TEXT);"
                 "CREATE TABLE IF NOT EXISTS borrowing (B_ID INTEGER, B_TITLE TEXT, U_ID INTEGER, U_NAME TEXT);";
    sqlite3_exec(db, sql.c_str(), 0, 0, 0);
}

// دالة إضافة كتاب جديد لقاعدة البيانات
bool Database::saveBook(int id, const string& title, int status) {
    string sql = "INSERT INTO books VALUES (" + to_string(id) + ", '" + title + "', " + to_string(status) + ");";
    return sqlite3_exec(db, sql.c_str(), 0, 0, 0) == SQLITE_OK;
}

// دالة إضافة طالب (مستخدم) جديد لقاعدة البيانات
bool Database::saveUser(int id, const string& name) {
    string sql = "INSERT INTO users VALUES (" + to_string(id) + ", '" + name + "');";
    return sqlite3_exec(db, sql.c_str(), 0, 0, 0) == SQLITE_OK;
}

// دالة عرض كل الكتب الموجودة في المكتبة
bool Database::loadBooks() { return sqlite3_exec(db, "SELECT * FROM books;", callback, 0, 0) == SQLITE_OK; }

// دالة تحديث حالة الكتاب (متاح أو غير متاح) بعد الاستعارة
bool Database::updateAvailability(int bookID, int status) {
    string sql = "UPDATE books SET STATUS = " + to_string(status) + " WHERE ID = " + to_string(bookID) + ";";
    return sqlite3_exec(db, sql.c_str(), 0, 0, 0) == SQLITE_OK;
}

// دالة الاستعارة:  البرنامج، بتتأكد من البيانات وتسجل العملية
bool Database::borrowBook(int bookID, int userID) {
    sqlite3_stmt* stmt;
    string sName = "", bTitle = "";

    // 1. التأكد إن الطالب مسجل في النظام وجلب اسمه
    sqlite3_prepare_v2(db, ("SELECT NAME FROM users WHERE ID=" + to_string(userID)).c_str(), -1, &stmt, 0);
    if (sqlite3_step(stmt) == SQLITE_ROW) sName = (const char*)sqlite3_column_text(stmt, 0);
    else { cout << "\n[!] Error: Student ID (" << userID << ") not found!\n"; sqlite3_finalize(stmt); return false; }
    sqlite3_finalize(stmt);

    // 2. التأكد إن الكتاب موجود ومتاح (Status = 1) وجلب اسمه
    sqlite3_prepare_v2(db, ("SELECT TITLE, STATUS FROM books WHERE ID=" + to_string(bookID)).c_str(), -1, &stmt, 0);
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        if (sqlite3_column_int(stmt, 1) == 0) { cout << "\n[!] Error: Book already borrowed!\n"; sqlite3_finalize(stmt); return false; }
        bTitle = (const char*)sqlite3_column_text(stmt, 0);
    } else { cout << "\n[!] Error: Book ID (" << bookID << ") not found!\n"; sqlite3_finalize(stmt); return false; }
    sqlite3_finalize(stmt);

    // 3. تسجيل عملية الاستعارة (حفظ الأرقام والأسماء مع بعض في جدول واحد)
    string sql = "INSERT INTO borrowing VALUES (" + to_string(bookID) + ", '" + bTitle + "', " + to_string(userID) + ", '" + sName + "');";
    
    if (sqlite3_exec(db, sql.c_str(), 0, 0, 0) == SQLITE_OK) {
        updateAvailability(bookID, 0); // تغيير حالة الكتاب لـ "مستعار"
        cout << "\n>> Success! [" << sName << "] took [" << bTitle << "]\n";
        return true;
    }
    return false;
}

// دالة تقرير الاستعارة: بتعرض جدول كامل فيه مين خد إيه بالأرقام والأسماء
bool Database::viewBorrowingReport() {
    sqlite3_stmt* stmt;
    string sql = "SELECT * FROM borrowing;";
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0);

    // رسم رأس الجدول
    cout << "\n" << string(85, '=') << endl;
    cout << "| " << left << setw(8) << "B_ID" << "| " << setw(20) << "BOOK TITLE" 
         << "| " << setw(8) << "U_ID" << "| " << setw(20) << "STUDENT NAME" << " |" << endl;
    cout << string(85, '-') << endl;

    // المرور على كل العمليات المسجلة وطباعتها
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        cout << "| " << left << setw(8) << sqlite3_column_int(stmt, 0) // رقم الكتاب
             << "| " << setw(20) << (const char*)sqlite3_column_text(stmt, 1) // اسم الكتاب
             << "| " << setw(8) << sqlite3_column_int(stmt, 2) // رقم الطالب
             << "| " << setw(20) << (const char*)sqlite3_column_text(stmt, 3) << " |" << endl; // اسم الطالب
    }
    sqlite3_finalize(stmt);
    cout << string(85, '=') << endl;
    return true;
}