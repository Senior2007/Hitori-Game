#include "mainwindow.h"
#include "authdialog.h"
#include "mainmenu.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AuthDialog auth;
    if (auth.exec() == QDialog::Accepted) {
        QString username = auth.getUsername();
        MainMenu menu(username);
        menu.exec();
    }
    return a.exec();
}
