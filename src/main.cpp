
#include <iostream>
#include <string> // مكتبة التعامل مع النصوص
#include <limits> // مكتبة للتحكم في حدود البيانات (تستخدم لتنظيف المدخلات)
#include "database.h" //استدعاء ملف التعامل مع قاعدة date

using namespace std;

// دالة للتأكد إن الاسم أو العنوان مفيهوش أرقام (حروف بس)
bool isValidName(const string& str) {
    if (str.empty()) return false; // لو النص فاضي ارفض
    for (char const &c : str) {
        if (isdigit(c)) return false; // لو لقى أي رقم وسط الحروف ارفض
    }
    return true; // لو كله حروف يبقى تمام
}

// دالة لتنظيف الذاكرة المؤقتة (Buffer) في حالة إدخال بيانات غلط
void cleanCin() {
    cin.clear(); // مسح علامة الخطأ من cin
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // تجاهل باقي الكلام اللي اتكتب غلط
}

int main() {
    Database myDB; // إنشاء كائن من كلاس قاعدة البيانات
    if (!myDB.openDB()) { cout << "DB Error!\n"; return 1; } // فتح القاعدة ولو فشل يقفل البرنامج
    myDB.createTables(); // التأكد إن الجداول موجودة أو إنشائها

    int choice; // متغير لحفظ اختيار المستخدم من القائمة
    while (true) {
        // عرض قائمة الاختيارات الرئيسية للنظام
        cout << "\n========================================" << endl;
        cout << " LIBRARY MANAGEMENT SYSTEM" << endl;
        cout << "========================================" << endl;
        cout << "1. Add Book\n2. Add Student\n3. View All Books\n4. Borrow Book\n5. View Borrowing Report\n6. Exit\n";
        cout << "----------------------------------------" << endl;
        cout << "Your Choice: ";

        // لو المستخدم دخل حرف بدل رقم في الاختيار
        if (!(cin >> choice)) {
            cout << "\n>> Invalid! Please enter a number (1-6).\n";
            cleanCin(); continue; // نظف المدخلات وارجع من أول اللوب
        }

        if (choice == 6) break; // لو اختار 6 يخرج من البرنامج

        switch (choice) {
            case 1: { // حالة إضافة كتاب جديد
                int id; string title;
                cout << "Book ID (Numbers): "; cin >> id;
                if (cin.fail()) { cout << ">> Numbers only for ID!\n"; cleanCin(); break; } // فحص رقم الكتاب
                cin.ignore(); // مسح الـ newline من الذاكرة قبل الـ getline
                cout << "Book Title: "; getline(cin, title);
                
                // فحص عنوان الكتاب (ممنوع أرقام)
                if (!isValidName(title)) { 
                    cout << ">> Error: Title must be letters only (No numbers)!\n"; 
                    break; 
                }
                
                myDB.saveBook(id, title, 1); // حفظ الكتاب في القاعدة (1 تعني متاح)
                cout << ">> Book Saved!\n";
                break;
            }
            case 2: { // حالة تسجيل طالب جديد
                int id; string name;
                cout << "Student ID (Numbers): "; cin >> id;
                if (cin.fail()) { cout << ">> Numbers only for ID!\n"; cleanCin(); break; } // فحص رقم الطالب
                cin.ignore();
                cout << "Student Name: "; getline(cin, name);
                
                // فحص اسم الطالب (ممنوع أرقام)
                if (!isValidName(name)) { 
                    cout << ">> Error: Name must be letters only (No numbers)!\n"; 
                    break; 
                }
                
                myDB.saveUser(id, name); // حفظ بيانات الطالب في القاعدة
                cout << ">> Student Registered!\n";
                break;
            }
            case 3: // عرض قائمة كل الكتب
                myDB.loadBooks();
                break;
            case 4: { // عملية استعارة كتاب
                int bid, uid;
                cout << "Student ID: "; cin >> uid;
                cout << "Book ID: "; cin >> bid;
                if (cin.fail()) { cout << ">> Invalid IDs!\n"; cleanCin(); break; } // فحص صحة الأرقام المدخلة
                if (myDB.borrowBook(bid, uid)) cout << ">> Borrowing Successful!\n"; // تنفيذ الاستعارة
                break;
            }
            case 5: // عرض تقرير العمليات بالأسماء والأرقام
                myDB.viewBorrowingReport();
                break;
            default: // في حالة اختيار رقم مش موجود في القائمة
                cout << ">> Choice out of range!\n";
        }
    }
    myDB.closeDB(); // إغلاق قاعدة البيانات قبل قفل البرنامج
    return 0; 
}