


#include "../include/mainwindow.h"
#include <QApplication>
 
// ════════════════════════════════════════════════════════════════
//  Constructor / Destructor
// ════════════════════════════════════════════════════════════════
 
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Open the SQLite database on startup
    m_db.openDB("library.db");
    m_db.createTables();
 
    applyQSS();
 
    m_stack = new QStackedWidget(this);
    setCentralWidget(m_stack);
 
    // Pages added in Page enum order
    m_stack->addWidget(buildLoginPage());     // 0 - PAGE_LOGIN
    m_stack->addWidget(buildAdminMenuPage()); // 1 - PAGE_ADMIN_MENU
    m_stack->addWidget(buildUserMenuPage());  // 2 - PAGE_USER_MENU
    m_stack->addWidget(buildAddPage());       // 3 - PAGE_ADD
    m_stack->addWidget(buildSearchPage());    // 4 - PAGE_SEARCH
    m_stack->addWidget(buildReturnPage());    // 5 - PAGE_RETURN
    m_stack->addWidget(buildBorrowPage());    // 6 - PAGE_BORROW
 
    m_stack->setCurrentIndex(PAGE_LOGIN);
}
 
MainWindow::~MainWindow()
{
    m_db.closeDB();
}
 
// ════════════════════════════════════════════════════════════════
//  Page builders
// ════════════════════════════════════════════════════════════════
 
QWidget* MainWindow::buildLoginPage()
{
    QWidget* page = new QWidget;
    page->setObjectName("loginPage");
 
    // Title bar
    QLabel* icon  = new QLabel("📖");
    icon->setObjectName("titleIcon");
 
    QLabel* title = new QLabel("Library Management System");
    title->setObjectName("titleLabel");
 
    QLabel* icon2 = new QLabel("📖");
    icon2->setObjectName("titleIcon");
 
    QHBoxLayout* titleRow = new QHBoxLayout;
    titleRow->addWidget(icon);
    titleRow->addSpacing(8);
    titleRow->addWidget(title);
    titleRow->addSpacing(8);
    titleRow->addWidget(icon2);
    titleRow->setAlignment(Qt::AlignCenter);
 
    QFrame* titleFrame = new QFrame;
    titleFrame->setObjectName("titleFrame");
    titleFrame->setLayout(titleRow);
    titleFrame->setFixedHeight(64);
    addShadow(titleFrame, 24, 6);
 
    // Subtitle
    QLabel* sub = new QLabel("Select your role to continue");
    sub->setObjectName("subtitleLabel");
    sub->setAlignment(Qt::AlignCenter);
 
    // Role buttons
    QPushButton* btnA = makeRoleBtn("A");
    QPushButton* btnU = makeRoleBtn("U");
    connect(btnA, &QPushButton::clicked, this, &MainWindow::onAdminClicked);
    connect(btnU, &QPushButton::clicked, this, &MainWindow::onUserClicked);
 
    QLabel* lblA = new QLabel("Admin");
    QLabel* lblU = new QLabel("User");
    lblA->setObjectName("roleCaption");
    lblU->setObjectName("roleCaption");
    lblA->setAlignment(Qt::AlignCenter);
    lblU->setAlignment(Qt::AlignCenter);
 
    QVBoxLayout* colA = new QVBoxLayout;
    colA->addWidget(btnA, 0, Qt::AlignCenter);
    colA->addWidget(lblA, 0, Qt::AlignCenter);
    colA->setSpacing(10);
 
    QVBoxLayout* colU = new QVBoxLayout;
    colU->addWidget(btnU, 0, Qt::AlignCenter);
    colU->addWidget(lblU, 0, Qt::AlignCenter);
    colU->setSpacing(10);
 
    QHBoxLayout* roleRow = new QHBoxLayout;
    roleRow->addStretch(2);
    roleRow->addLayout(colA);
    roleRow->addStretch(1);
    roleRow->addLayout(colU);
    roleRow->addStretch(2);
 
    QVBoxLayout* vl = new QVBoxLayout(page);
    vl->setContentsMargins(60, 40, 60, 40);
    vl->setSpacing(0);
    vl->addWidget(titleFrame);
    vl->addSpacing(28);
    vl->addWidget(sub);
    vl->addSpacing(36);
    vl->addLayout(roleRow);
    vl->addStretch();
 
    return page;
}
 
QWidget* MainWindow::buildAdminMenuPage()
{
    QWidget* page = new QWidget;
    page->setObjectName("menuPage");
 
    QLabel* badge = new QLabel("A");
    badge->setObjectName("badge");
    badge->setAlignment(Qt::AlignCenter);
    badge->setFixedSize(52, 52);
 
    QPushButton* back = makeBackBtn();
    connect(back, &QPushButton::clicked, this, &MainWindow::onBackToLogin);
 
    QHBoxLayout* topRow = new QHBoxLayout;
    topRow->addWidget(badge, 0, Qt::AlignLeft | Qt::AlignVCenter);
    topRow->addStretch();
    topRow->addWidget(back,  0, Qt::AlignRight | Qt::AlignVCenter);
 
    QPushButton* btnAdd    = makeMenuBtn("Add Book",    "＋");
    QPushButton* btnSearch = makeMenuBtn("Search Book", "🔍");
    QPushButton* btnReturn = makeMenuBtn("Return Book", "↩");
    QPushButton* btnBorrow = makeMenuBtn("Borrow Book", "📚");
 
    connect(btnAdd,    &QPushButton::clicked, this, &MainWindow::onAddClicked);
    connect(btnSearch, &QPushButton::clicked, this, &MainWindow::onSearchClicked);
    connect(btnReturn, &QPushButton::clicked, this, &MainWindow::onReturnClicked);
    connect(btnBorrow, &QPushButton::clicked, this, &MainWindow::onBorrowClicked);
 
    QVBoxLayout* btnCol = new QVBoxLayout;
    btnCol->setSpacing(16);
    btnCol->addWidget(btnAdd);
    btnCol->addWidget(btnSearch);
    btnCol->addWidget(btnReturn);
    btnCol->addWidget(btnBorrow);
 
    QHBoxLayout* center = new QHBoxLayout;
    center->addStretch();
    center->addLayout(btnCol);
    center->addStretch();
 
    QVBoxLayout* vl = new QVBoxLayout(page);
    vl->setContentsMargins(30, 20, 30, 30);
    vl->setSpacing(18);
    vl->addLayout(topRow);
    vl->addLayout(center);
    vl->addStretch();
 
    return page;
}
 
QWidget* MainWindow::buildUserMenuPage()
{
    QWidget* page = new QWidget;
    page->setObjectName("menuPage");
 
    QLabel* badge = new QLabel("U");
    badge->setObjectName("badge");
    badge->setAlignment(Qt::AlignCenter);
    badge->setFixedSize(52, 52);
 
    QPushButton* back = makeBackBtn();
    connect(back, &QPushButton::clicked, this, &MainWindow::onBackToLogin);
 
    QHBoxLayout* topRow = new QHBoxLayout;
    topRow->addWidget(badge, 0, Qt::AlignLeft | Qt::AlignVCenter);
    topRow->addStretch();
    topRow->addWidget(back,  0, Qt::AlignRight | Qt::AlignVCenter);
 
    QPushButton* btnSearch = makeMenuBtn("Search Book", "🔍");
    QPushButton* btnReturn = makeMenuBtn("Return Book", "↩");
    QPushButton* btnBorrow = makeMenuBtn("Borrow Book", "📚");
 
    connect(btnSearch, &QPushButton::clicked, this, &MainWindow::onSearchClicked);
    connect(btnReturn, &QPushButton::clicked, this, &MainWindow::onReturnClicked);
    connect(btnBorrow, &QPushButton::clicked, this, &MainWindow::onBorrowClicked);
 
    QVBoxLayout* btnCol = new QVBoxLayout;
    btnCol->setSpacing(16);
    btnCol->addWidget(btnSearch);
    btnCol->addWidget(btnReturn);
    btnCol->addWidget(btnBorrow);
 
    QHBoxLayout* center = new QHBoxLayout;
    center->addStretch();
    center->addLayout(btnCol);
    center->addStretch();
 
    QVBoxLayout* vl = new QVBoxLayout(page);
    vl->setContentsMargins(30, 20, 30, 30);
    vl->setSpacing(18);
    vl->addLayout(topRow);
    vl->addLayout(center);
    vl->addStretch();
 
    return page;
}
 
QWidget* MainWindow::buildAddPage()
{
    QWidget* page = new QWidget;
    page->setObjectName("inputPage");
 
    QPushButton* back = makeBackBtn();
    connect(back, &QPushButton::clicked, this, &MainWindow::onBackToMenu);
 
    QLabel* pageTitle = new QLabel("Add New Book");
    pageTitle->setObjectName("pageTitle");
 
    QHBoxLayout* topRow = new QHBoxLayout;
    topRow->addWidget(back);
    topRow->addSpacing(16);
    topRow->addWidget(pageTitle);
    topRow->addStretch();
 
    // Book ID
    QLabel* idLabel = new QLabel("Book ID");
    idLabel->setObjectName("fieldLabel");
    m_addIdInput = new QLineEdit;
    m_addIdInput->setObjectName("inputField");
    m_addIdInput->setPlaceholderText("Enter numeric book ID…");
    addShadow(m_addIdInput, 14, 3);
 
    // Book Title
    QLabel* titleLabel = new QLabel("Book Title");
    titleLabel->setObjectName("fieldLabel");
    m_addTitleInput = new QLineEdit;
    m_addTitleInput->setObjectName("inputField");
    m_addTitleInput->setPlaceholderText("Enter book title…");
    addShadow(m_addTitleInput, 14, 3);
 
    // Author (optional)
    QLabel* authorLabel = new QLabel("Author  (optional)");
    authorLabel->setObjectName("fieldLabel");
    m_addAuthorInput = new QLineEdit;
    m_addAuthorInput->setObjectName("inputField");
    m_addAuthorInput->setPlaceholderText("Leave blank for \"Unknown\"…");
    addShadow(m_addAuthorInput, 14, 3);
 
    // Result label
    QLabel* result = new QLabel("");
    result->setObjectName("resultLabel");
    result->setWordWrap(true);
 
    QPushButton* submitBtn = new QPushButton("  Add Book  ＋");
    submitBtn->setObjectName("submitBtn");
    addShadow(submitBtn, 14, 4);
 
    // Connect submit — calls backend
    connect(submitBtn, &QPushButton::clicked, this, [this, result]() {
        bool idOk;
        int bookId = m_addIdInput->text().trimmed().toInt(&idOk);
        QString title  = m_addTitleInput->text().trimmed();
        QString author = m_addAuthorInput->text().trimmed();
 
        if (!idOk || title.isEmpty()) {
            showResult(result, "⚠  Please enter a valid ID and title.", false);
            return;
        }
 
        // Use "Unknown" if author left blank
        std::string authorStr = author.isEmpty() ? "Unknown" : author.toStdString();
 
        // ── BACKEND CALL ──────────────────────────────────────
        Book newBook(bookId, title.toStdString(), authorStr, true);
        m_library.addBook(newBook);
        bool saved = m_db.saveBook(bookId, title.toStdString(), 1);
        // ─────────────────────────────────────────────────────
 
        if (saved) {
            showResult(result, "✔  Book \"" + title + "\" added successfully!", true);
            m_addIdInput->clear();
            m_addTitleInput->clear();
            m_addAuthorInput->clear();
        } else {
            showResult(result, "✘  Failed to save book. Check ID is unique.", false);
        }
    });
 
    connect(m_addAuthorInput, &QLineEdit::returnPressed, submitBtn, &QPushButton::click);
 
    QHBoxLayout* submitRow = new QHBoxLayout;
    submitRow->addStretch();
    submitRow->addWidget(submitBtn);
 
    QVBoxLayout* form = new QVBoxLayout;
    form->setSpacing(10);
    form->addWidget(idLabel);
    form->addWidget(m_addIdInput);
    form->addSpacing(6);
    form->addWidget(titleLabel);
    form->addWidget(m_addTitleInput);
    form->addSpacing(6);
    form->addWidget(authorLabel);
    form->addWidget(m_addAuthorInput);
    form->addSpacing(14);
    form->addLayout(submitRow);
    form->addSpacing(10);
    form->addWidget(result);
 
    QHBoxLayout* formCenter = new QHBoxLayout;
    formCenter->addStretch(1);
    formCenter->addLayout(form, 4);
    formCenter->addStretch(1);
 
    QVBoxLayout* vl = new QVBoxLayout(page);
    vl->setContentsMargins(40, 24, 40, 30);
    vl->setSpacing(20);
    vl->addLayout(topRow);
    vl->addLayout(formCenter);
    vl->addStretch();
 
    return page;
}
 
QWidget* MainWindow::buildSearchPage()
{
    QWidget* page = new QWidget;
    page->setObjectName("inputPage");
 
    QPushButton* back = makeBackBtn();
    connect(back, &QPushButton::clicked, this, &MainWindow::onBackToMenu);
 
    QLabel* pageTitle = new QLabel("Search Book");
    pageTitle->setObjectName("pageTitle");
 
    QHBoxLayout* topRow = new QHBoxLayout;
    topRow->addWidget(back);
    topRow->addSpacing(16);
    topRow->addWidget(pageTitle);
    topRow->addStretch();
 
    QLabel* idLabel = new QLabel("Book ID");
    idLabel->setObjectName("fieldLabel");
 
    m_searchInput = new QLineEdit;
    m_searchInput->setObjectName("inputField");
    m_searchInput->setPlaceholderText("Enter book ID to search…");
    addShadow(m_searchInput, 14, 3);
 
    m_searchResult = new QLabel("");
    m_searchResult->setObjectName("resultLabel");
    m_searchResult->setWordWrap(true);
 
    QPushButton* submitBtn = new QPushButton("  Search  🔍");
    submitBtn->setObjectName("submitBtn");
    addShadow(submitBtn, 14, 4);
 
    connect(submitBtn, &QPushButton::clicked, this, &MainWindow::onSearchSubmit);
    connect(m_searchInput, &QLineEdit::returnPressed, this, &MainWindow::onSearchSubmit);
 
    QHBoxLayout* submitRow = new QHBoxLayout;
    submitRow->addStretch();
    submitRow->addWidget(submitBtn);
 
    QVBoxLayout* form = new QVBoxLayout;
    form->setSpacing(10);
    form->addWidget(idLabel);
    form->addWidget(m_searchInput);
    form->addSpacing(14);
    form->addLayout(submitRow);
    form->addSpacing(10);
    form->addWidget(m_searchResult);
 
    QHBoxLayout* formCenter = new QHBoxLayout;
    formCenter->addStretch(1);
    formCenter->addLayout(form, 4);
    formCenter->addStretch(1);
 
    QVBoxLayout* vl = new QVBoxLayout(page);
    vl->setContentsMargins(40, 24, 40, 30);
    vl->setSpacing(20);
    vl->addLayout(topRow);
    vl->addLayout(formCenter);
    vl->addStretch();
 
    return page;
}
 
QWidget* MainWindow::buildReturnPage()
{
    QWidget* page = new QWidget;
    page->setObjectName("inputPage");
 
    QPushButton* back = makeBackBtn();
    connect(back, &QPushButton::clicked, this, &MainWindow::onBackToMenu);
 
    QLabel* pageTitle = new QLabel("Return Book");
    pageTitle->setObjectName("pageTitle");
 
    QHBoxLayout* topRow = new QHBoxLayout;
    topRow->addWidget(back);
    topRow->addSpacing(16);
    topRow->addWidget(pageTitle);
    topRow->addStretch();
 
    QLabel* bookLabel = new QLabel("Book ID");
    bookLabel->setObjectName("fieldLabel");
    m_returnBookId = new QLineEdit;
    m_returnBookId->setObjectName("inputField");
    m_returnBookId->setPlaceholderText("Enter book ID…");
    addShadow(m_returnBookId, 14, 3);
 
    QLabel* userLabel = new QLabel("User ID");
    userLabel->setObjectName("fieldLabel");
    m_returnUserId = new QLineEdit;
    m_returnUserId->setObjectName("inputField");
    m_returnUserId->setPlaceholderText("Enter user ID…");
    addShadow(m_returnUserId, 14, 3);
 
    m_returnResult = new QLabel("");
    m_returnResult->setObjectName("resultLabel");
    m_returnResult->setWordWrap(true);
 
    QPushButton* submitBtn = new QPushButton("  Return Book  ↩");
    submitBtn->setObjectName("submitBtn");
    addShadow(submitBtn, 14, 4);
 
    connect(submitBtn, &QPushButton::clicked, this, &MainWindow::onReturnSubmit);
    connect(m_returnUserId, &QLineEdit::returnPressed, this, &MainWindow::onReturnSubmit);
 
    QHBoxLayout* submitRow = new QHBoxLayout;
    submitRow->addStretch();
    submitRow->addWidget(submitBtn);
 
    QVBoxLayout* form = new QVBoxLayout;
    form->setSpacing(10);
    form->addWidget(bookLabel);
    form->addWidget(m_returnBookId);
    form->addSpacing(6);
    form->addWidget(userLabel);
    form->addWidget(m_returnUserId);
    form->addSpacing(14);
    form->addLayout(submitRow);
    form->addSpacing(10);
    form->addWidget(m_returnResult);
 
    QHBoxLayout* formCenter = new QHBoxLayout;
    formCenter->addStretch(1);
    formCenter->addLayout(form, 4);
    formCenter->addStretch(1);
 
    QVBoxLayout* vl = new QVBoxLayout(page);
    vl->setContentsMargins(40, 24, 40, 30);
    vl->setSpacing(20);
    vl->addLayout(topRow);
    vl->addLayout(formCenter);
    vl->addStretch();
 
    return page;
}
 
QWidget* MainWindow::buildBorrowPage()
{
    QWidget* page = new QWidget;
    page->setObjectName("inputPage");
 
    QPushButton* back = makeBackBtn();
    connect(back, &QPushButton::clicked, this, &MainWindow::onBackToMenu);
 
    QLabel* pageTitle = new QLabel("Borrow Book");
    pageTitle->setObjectName("pageTitle");
 
    QHBoxLayout* topRow = new QHBoxLayout;
    topRow->addWidget(back);
    topRow->addSpacing(16);
    topRow->addWidget(pageTitle);
    topRow->addStretch();
 
    QLabel* bookLabel = new QLabel("Book ID");
    bookLabel->setObjectName("fieldLabel");
    m_borrowBookId = new QLineEdit;
    m_borrowBookId->setObjectName("inputField");
    m_borrowBookId->setPlaceholderText("Enter book ID…");
    addShadow(m_borrowBookId, 14, 3);
 
    QLabel* userLabel = new QLabel("User ID");
    userLabel->setObjectName("fieldLabel");
    m_borrowUserId = new QLineEdit;
    m_borrowUserId->setObjectName("inputField");
    m_borrowUserId->setPlaceholderText("Enter user ID…");
    addShadow(m_borrowUserId, 14, 3);
 
    m_borrowResult = new QLabel("");
    m_borrowResult->setObjectName("resultLabel");
    m_borrowResult->setWordWrap(true);
 
    QPushButton* submitBtn = new QPushButton("  Borrow Book  📚");
    submitBtn->setObjectName("submitBtn");
    addShadow(submitBtn, 14, 4);
 
    connect(submitBtn, &QPushButton::clicked, this, &MainWindow::onBorrowSubmit);
    connect(m_borrowUserId, &QLineEdit::returnPressed, this, &MainWindow::onBorrowSubmit);
 
    QHBoxLayout* submitRow = new QHBoxLayout;
    submitRow->addStretch();
    submitRow->addWidget(submitBtn);
 
    QVBoxLayout* form = new QVBoxLayout;
    form->setSpacing(10);
    form->addWidget(bookLabel);
    form->addWidget(m_borrowBookId);
    form->addSpacing(6);
    form->addWidget(userLabel);
    form->addWidget(m_borrowUserId);
    form->addSpacing(14);
    form->addLayout(submitRow);
    form->addSpacing(10);
    form->addWidget(m_borrowResult);
 
    QHBoxLayout* formCenter = new QHBoxLayout;
    formCenter->addStretch(1);
    formCenter->addLayout(form, 4);
    formCenter->addStretch(1);
 
    QVBoxLayout* vl = new QVBoxLayout(page);
    vl->setContentsMargins(40, 24, 40, 30);
    vl->setSpacing(20);
    vl->addLayout(topRow);
    vl->addLayout(formCenter);
    vl->addStretch();
 
    return page;
}
 
// ════════════════════════════════════════════════════════════════
//  Navigation slots
// ════════════════════════════════════════════════════════════════
 
void MainWindow::onAdminClicked()
{
    m_userRole = PAGE_ADMIN_MENU;
    m_stack->setCurrentIndex(PAGE_ADMIN_MENU);
}
 
void MainWindow::onUserClicked()
{
    m_userRole = PAGE_USER_MENU;
    m_stack->setCurrentIndex(PAGE_USER_MENU);
}
 
void MainWindow::onAddClicked()    { m_stack->setCurrentIndex(PAGE_ADD); }
void MainWindow::onSearchClicked() { m_stack->setCurrentIndex(PAGE_SEARCH); }
void MainWindow::onReturnClicked() { m_stack->setCurrentIndex(PAGE_RETURN); }
void MainWindow::onBorrowClicked() { m_stack->setCurrentIndex(PAGE_BORROW); }
void MainWindow::onBackToLogin()   { m_stack->setCurrentIndex(PAGE_LOGIN); }
void MainWindow::onBackToMenu()    { m_stack->setCurrentIndex(m_userRole); }
 
// ════════════════════════════════════════════════════════════════
//  Action slots — BACKEND CONNECTED HERE
// ════════════════════════════════════════════════════════════════
 
void MainWindow::onAddSubmit()
{
    // Handled inline via lambda in buildAddPage()
}
 
void MainWindow::onSearchSubmit()
{
    bool ok;
    int bookId = m_searchInput->text().trimmed().toInt(&ok);
    if (!ok) {
        showResult(m_searchResult, "⚠  Please enter a valid numeric Book ID.", false);
        return;
    }
 
    // ── BACKEND CALL ──────────────────────────────────────────
    Book* found = m_library.searchBook(bookId);
    // ─────────────────────────────────────────────────────────
 
    if (found) {
        QString info = QString("✔  Found: \"%1\"  |  Author: %2  |  ID: %3  |  Status: %4")
            .arg(QString::fromStdString(found->gettitle()))
            .arg(QString::fromStdString(found->getauthor()))
            .arg(found->getbookid())
            .arg(found->getisavailable() ? "Available" : "Borrowed");
        showResult(m_searchResult, info, true);
    } else {
        showResult(m_searchResult, "✘  No book found with ID: " + QString::number(bookId), false);
    }
}
 
void MainWindow::onReturnSubmit()
{
    bool bokOk, usrOk;
    int bookId = m_returnBookId->text().trimmed().toInt(&bokOk);
    int userId = m_returnUserId->text().trimmed().toInt(&usrOk);
 
    if (!bokOk || !usrOk) {
        showResult(m_returnResult, "⚠  Please enter valid numeric IDs for both fields.", false);
        return;
    }
 
    // ── BACKEND CALL ──────────────────────────────────────────
    bool ok = m_library.returnBook(bookId, userId);
    if (ok) m_db.updateAvailability(bookId, 1); // 1 = available again
    // ─────────────────────────────────────────────────────────
 
    if (ok) {
        showResult(m_returnResult,
            QString("✔  Book ID %1 returned by User ID %2.").arg(bookId).arg(userId), true);
        m_returnBookId->clear();
        m_returnUserId->clear();
    } else {
        showResult(m_returnResult, "✘  Return failed. Check IDs and try again.", false);
    }
}
 
void MainWindow::onBorrowSubmit()
{
    bool bokOk, usrOk;
    int bookId = m_borrowBookId->text().trimmed().toInt(&bokOk);
    int userId = m_borrowUserId->text().trimmed().toInt(&usrOk);
 
    if (!bokOk || !usrOk) {
        showResult(m_borrowResult, "⚠  Please enter valid numeric IDs for both fields.", false);
        return;
    }
 
    // ── BACKEND CALL ──────────────────────────────────────────
    bool ok = m_library.borrowBook(bookId, userId);
    if (ok) m_db.updateAvailability(bookId, 0); // 0 = borrowed
    // ─────────────────────────────────────────────────────────
 
    if (ok) {
        showResult(m_borrowResult,
            QString("✔  Book ID %1 borrowed by User ID %2.").arg(bookId).arg(userId), true);
        m_borrowBookId->clear();
        m_borrowUserId->clear();
    } else {
        showResult(m_borrowResult, "✘  Borrow failed. Book may be unavailable or IDs invalid.", false);
    }
}
 
// ════════════════════════════════════════════════════════════════
//  Widget factories
// ════════════════════════════════════════════════════════════════
 
QPushButton* MainWindow::makeMenuBtn(const QString& text, const QString& icon)
{
    QPushButton* btn = new QPushButton("  " + icon + "  " + text);
    btn->setObjectName("menuBtn");
    btn->setMinimumSize(300, 58);
    btn->setCursor(Qt::PointingHandCursor);
    addShadow(btn, 16, 4);
    return btn;
}
 
QPushButton* MainWindow::makeRoleBtn(const QString& letter)
{
    QPushButton* btn = new QPushButton(letter);
    btn->setObjectName("roleBtn");
    btn->setFixedSize(96, 96);
    btn->setCursor(Qt::PointingHandCursor);
    addShadow(btn, 22, 6);
    return btn;
}
 
QPushButton* MainWindow::makeBackBtn()
{
    QPushButton* btn = new QPushButton("← Back");
    btn->setObjectName("backBtn");
    btn->setFixedHeight(32);
    btn->setCursor(Qt::PointingHandCursor);
    return btn;
}
 
void MainWindow::addShadow(QWidget* w, int blur, int yOffset)
{
    QGraphicsDropShadowEffect* s = new QGraphicsDropShadowEffect(w);
    s->setBlurRadius(blur);
    s->setColor(QColor(0, 0, 0, 90));
    s->setOffset(0, yOffset);
    w->setGraphicsEffect(s);
}
 
void MainWindow::showResult(QLabel* lbl, const QString& msg, bool success)
{
    lbl->setText(msg);
    lbl->setStyleSheet(success
        ? "color: #7de8a0; font-size: 13px; font-weight: 600;"
        : "color: #f08080; font-size: 13px; font-weight: 600;");
}
 
// ════════════════════════════════════════════════════════════════
//  QSS Stylesheet
// ════════════════════════════════════════════════════════════════
 
void MainWindow::applyQSS()
{
    const QString qss = R"(
 
/* ── Base ─────────────────────────────────────────────────────── */
QMainWindow, QWidget {
    background-color: #0f2744;
    color: #dce8f5;
    font-family: "Segoe UI", "Helvetica Neue", Arial, sans-serif;
    font-size: 13px;
}
 
/* ── Login page ───────────────────────────────────────────────── */
#loginPage {
    background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
        stop:0 #0f2744, stop:0.55 #222324, stop:1 #0b1e35);
}
 
#titleFrame {
    background-color: rgba(255,255,255,0.08);
    border: 1px solid rgba(255,255,255,0.15);
    border-radius: 14px;
}
 
#titleLabel {
    font-size: 24px;
    font-weight: 700;
    color: #ffffff;
    letter-spacing: 0.5px;
}
 
#titleIcon {
    font-size: 22px;
}
 
#subtitleLabel {
    font-size: 12px;
    color: rgba(180,210,240,0.65);
    letter-spacing: 2.5px;
}
 
#roleCaption {
    font-size: 12px;
    color: rgba(58, 58, 59, 0.6);
    letter-spacing: 1.5px;
}
 
/* Role A/U buttons */
#roleBtn {
    background-color: rgba(255,255,255,0.09);
    border: 2px solid rgba(255,255,255,0.20);
    border-radius: 18px;
    font-size: 34px;
    font-weight: 700;
    color: #ffffff;
}
#roleBtn:hover {
    background-color: rgba(255,255,255,0.18);
    border-color: rgba(120,180,255,0.60);
}
#roleBtn:pressed {
    background-color: rgba(255,255,255,0.28);
}
 
/* ── Menu pages ───────────────────────────────────────────────── */
#menuPage {
    background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
        stop:0 #0f2744, stop:1 #363738);
}
 
#badge {
    background-color: rgba(255,255,255,0.12);
    border: 2px solid rgba(255,255,255,0.25);
    border-radius: 26px;
    font-size: 20px;
    font-weight: 700;
    color: #ffffff;
}
 
#menuBtn {
    background-color: rgba(255,255,255,0.08);
    border: 1px solid rgba(255,255,255,0.16);
    border-radius: 12px;
    font-size: 15px;
    font-weight: 600;
    color: #e8f2ff;
    text-align: left;
    padding: 0 20px;
}
#menuBtn:hover {
    background-color: rgba(100,160,255,0.18);
    border-color: rgba(100,160,255,0.45);
    color: #ffffff;
}
#menuBtn:pressed {
    background-color: rgba(100,160,255,0.30);
    padding-left: 24px;
}
 
/* ── Input pages ──────────────────────────────────────────────── */
#inputPage {
    background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
        stop:0 #3d3e40, stop:1 #0b1e35);
}
 
#pageTitle {
    font-size: 20px;
    font-weight: 700;
    color: #ffffff;
}
 
#fieldLabel {
    font-size: 12px;
    font-weight: 600;
    color: rgba(48, 49, 49, 0.8);
    letter-spacing: 1.2px;
    margin-bottom: 2px;
}
 
#inputField {
    background-color: rgba(255,255,255,0.08);
    border: 1px solid rgba(255,255,255,0.18);
    border-radius: 8px;
    padding: 10px 14px;
    font-size: 14px;
    color: #ffffff;
    min-height: 40px;
    selection-background-color: #2e6fd4;
}
#inputField:focus {
    border: 1.5px solid rgba(80,160,255,0.70);
    background-color: rgba(255,255,255,0.13);
    outline: none;
}
 
#submitBtn {
    background-color: #2c2c2d;
    border: none;
    border-radius: 9px;
    font-size: 14px;
    font-weight: 600;
    color: #ffffff;
    padding: 0 30px;
    min-height: 42px;
    min-width: 160px;
}
#submitBtn:hover {
    background-color: #2e2f30;
}
#submitBtn:pressed {
    background-color: #373737;
}
 
#resultLabel {
    font-size: 13px;
    font-weight: 600;
    min-height: 28px;
    padding: 6px 2px;
}
 
/* ── Back button ──────────────────────────────────────────────── */
#backBtn {
    background-color: transparent;
    border: 1px solid rgba(255,255,255,0.22);
    border-radius: 7px;
    font-size: 12px;
    color: rgba(180,210,240,0.80);
    padding: 4px 14px;
    min-width: 70px;
}
#backBtn:hover {
    background-color: rgba(255,255,255,0.09);
    color: #ffffff;
}
#backBtn:pressed {
    background-color: rgba(255,255,255,0.16);
}
 
    )";
 
    qApp->setStyleSheet(qss);
}