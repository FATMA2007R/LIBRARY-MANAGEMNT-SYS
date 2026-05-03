


#ifndef MAINWINDOW_H
#define MAINWINDOW_H
 
#include <QMainWindow>
#include <QStackedWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QFrame>
#include <QTextEdit>
#include <QGraphicsDropShadowEffect>
#include <QMessageBox>
#include <QString>
#include <QSpinBox>
 
// ── Your backend headers ───────────────────────────────────────
#include "../include/library.h"
#include "../include/database.h"
#include "../include/book.h"
#include "../include/user.h"
 
class MainWindow : public QMainWindow
{
    Q_OBJECT
 
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
 
    // Page indices — must stay in this order
    enum Page {
        PAGE_LOGIN      = 0,
        PAGE_ADMIN_MENU = 1,
        PAGE_USER_MENU  = 2,
        PAGE_ADD        = 3,
        PAGE_SEARCH     = 4,
        PAGE_RETURN     = 5,
        PAGE_BORROW     = 6
    };
 
private slots:
    // Navigation
    void onAdminClicked();
    void onUserClicked();
    void onAddClicked();
    void onSearchClicked();
    void onReturnClicked();
    void onBorrowClicked();
    void onBackToLogin();
    void onBackToMenu();
 
    // Actions — these call your backend
    void onAddSubmit();
    void onSearchSubmit();
    void onReturnSubmit();
    void onBorrowSubmit();
 
private:
    // Page builders
    QWidget* buildLoginPage();
    QWidget* buildAdminMenuPage();
    QWidget* buildUserMenuPage();
    QWidget* buildAddPage();
    QWidget* buildSearchPage();
    QWidget* buildReturnPage();
    QWidget* buildBorrowPage();
 
    // Widget factories
    QPushButton* makeMenuBtn(const QString& text, const QString& icon);
    QPushButton* makeRoleBtn(const QString& letter);
    QPushButton* makeBackBtn();
    void         addShadow(QWidget* w, int blur = 20, int yOffset = 4);
    void         applyQSS();
    void         showResult(QLabel* lbl, const QString& msg, bool success);
 
    // ── Core widgets ──────────────────────────────────────────
    QStackedWidget* m_stack = nullptr;
 
    // Add page inputs
    QLineEdit* m_addIdInput     = nullptr;
    QLineEdit* m_addTitleInput  = nullptr;
    QLineEdit* m_addAuthorInput = nullptr;
 
    // Search page inputs
    QLineEdit* m_searchInput   = nullptr;
    QLabel*    m_searchResult  = nullptr;
 
    // Return page inputs
    QLineEdit* m_returnBookId  = nullptr;
    QLineEdit* m_returnUserId  = nullptr;
    QLabel*    m_returnResult  = nullptr;
 
    // Borrow page inputs
    QLineEdit* m_borrowBookId  = nullptr;
    QLineEdit* m_borrowUserId  = nullptr;
    QLabel*    m_borrowResult  = nullptr;
 
    // ── Backend objects ───────────────────────────────────────
    Library  m_library;
    Database m_db;
 
    // Which menu to go back to (Admin=1, User=2)
    int m_userRole = PAGE_ADMIN_MENU;
};
 
#endif
