#include "authdialog.h"
#include "ui_authdialog.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

AuthDialog::AuthDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AuthDialog)
{
    ui->setupUi(this);
    setFixedSize(width(), height());
    ui->passwordEdit->setEchoMode(QLineEdit::Password);

    QPixmap bkgnd("/Users/senior/Desktop/BSUIR/ОАиП/Курсач/Картинки/Окно авторизации.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);
    this->setAutoFillBackground(true);

}

AuthDialog::~AuthDialog() {
    delete ui;
}

bool AuthDialog::userExists(const QString &login) {
    QFile file("/Users/senior/Desktop/BSUIR/ОАиП/Курсач/Hitori/build/Desktop_arm_darwin_generic_mach_o_64bit-Debug/users.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        if (line.startsWith(login + ":"))
            return true;
    }
    return false;
}

void AuthDialog::saveUser(const QString &login, const QString &password) {
    QFile file("/Users/senior/Desktop/BSUIR/ОАиП/Курсач/Hitori/build/Desktop_arm_darwin_generic_mach_o_64bit-Debug/users.txt");
    if (!file.open(QIODevice::Append | QIODevice::Text))
        return;

    QTextStream out(&file);
    out << login << ":" << password << "\n";
    file.close();

    QFile StatFile
        ("/Users/senior/Desktop/BSUIR/ОАиП/Курсач/Hitori/build/Desktop_arm_darwin_generic_mach_o_64bit-Debug/statistics/" + login + ".txt");

    if (!StatFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Не удалось открыть файл для записи!";
        return;
    }

    QTextStream statout(&StatFile);
    statout << "0\n";
    statout << "0\n";
    statout << "0\n";
    statout << "0\n";
    statout << "0\n";
    statout << "0\n";
    statout << "0\n";
    statout << "0\n";
    statout << "0\n";
    StatFile.close();
}

void AuthDialog::on_loginButton_clicked() {
    QString login = ui->loginEdit->text();
    QString password = ui->passwordEdit->text();

    if (login.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Логин и пароль не могут быть пустыми!");
        return;
    }

    QFile file("/Users/senior/Desktop/BSUIR/ОАиП/Курсач/Hitori/build/Desktop_arm_darwin_generic_mach_o_64bit-Debug/users.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Ошибка", "База пользователей не найдена!");
        return;
    }

    QTextStream in(&file);
    bool found = false;
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(":");
        if (parts[0] == login && parts[1] == password) {
            found = true;
            break;
        }
    }

    if (found) {
        accept();  // Закрываем диалог с результатом QDialog::Accepted
    } else {
        QMessageBox::warning(this, "Ошибка", "Неверный логин или пароль!");
    }
}

void AuthDialog::on_registerButton_clicked() {
    QString login = ui->loginEdit->text();
    QString password = ui->passwordEdit->text();

    if (login.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Логин и пароль не могут быть пустыми!");
        return;
    }

    if (userExists(login)) {
        QMessageBox::warning(this, "Ошибка", "Пользователь уже существует!");
        return;
    }

    saveUser(login, password);
    QMessageBox::information(this, "Успех", "Регистрация завершена!");
}


QString AuthDialog::getUsername() {
    return ui->loginEdit->text();
}
