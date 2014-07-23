#include <iostream>
#include <QApplication>
#include <QMessageBox>
#include "a.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    std::cout << "Hello :d";
    QMessageBox::information(NULL, "titel", "kek");
    app.exec();
    return 0;
}
