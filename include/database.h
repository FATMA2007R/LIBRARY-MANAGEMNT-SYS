
#ifndef DATABASE_H // شرط أمان بيمنع تكرار تعريف الملف ده أكتر من مرة
#define DATABASE_H
#include <string> // استدعاء مكتبة النصوص
#include "../include/sqlite3.h" // استدعاء مكتبة التعامل مع قاعدة بيانات SQLite

class Database { // تعريف الكلاس اللي هيجمع كل شغل قاعدة البيانات
private:
    sqlite3* db; // المؤشر الأساسي اللي بيمسك "خيط" الاتصال بملف القاعدة
public:
    Database(); // الدالة اللي بتبدأ الشغل وبتصفر المؤشر في البداية
    bool openDB(const std::string& dbName = "library.db"); // دالة لفتح ملف القاعدة (باسم library.db)
    void closeDB(); // دالة لغلق الاتصال بالقاعدة عشان البيانات متضيعش
    void createTables(); // دالة بتبني الجداول (كتب، طلاب، استعارة) لو مش موجودين
    bool saveBook(int id, const std::string& title, int status); // دالة لإضافة كتاب جديد للجدول
    bool loadBooks(); // دالة لعرض كل الكتب اللي عندنا في المكتبة
    bool updateAvailability(int bookid, int status); // دالة بتغير حالة الكتاب من متاح لمستعار والعكس
    bool saveUser(int id, const std::string& name); // دالة لتسجيل طالب جديد في النظام
    bool borrowBook(int bookid, int id); // دالة تنفيذ عملية الاستعارة وتسجيلها في الجدول
    bool viewBorrowingReport(); // دالة بتعرض جدول فيه كل العمليات (مين خد إيه)
};
#endif // نهاية شرط الأمان الخاص بالملف