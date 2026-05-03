#include <QApplication>
#include <QFont>
#include "../include/mainwindow.h"
 
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("Library Management System");
    app.setFont(QFont("Segoe UI", 11));
 
    MainWindow window;
    window.setWindowTitle("Library Management System");
    window.setMinimumSize(800, 540);
    window.resize(900, 600);
    window.show();
 
    return app.exec();
}
 