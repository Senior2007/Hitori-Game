#pragma once

#include <QDialog>

namespace Ui {
class AuthDialog;
}

class AuthDialog : public QDialog {
    Q_OBJECT

public:
    explicit AuthDialog(QWidget *parent = nullptr);
    ~AuthDialog();
    QString getUsername();

private slots:
    void on_loginButton_clicked();
    void on_registerButton_clicked();

private:
    Ui::AuthDialog *ui;

    bool userExists(const QString &login);
    void saveUser(const QString &login, const QString &password);
};
