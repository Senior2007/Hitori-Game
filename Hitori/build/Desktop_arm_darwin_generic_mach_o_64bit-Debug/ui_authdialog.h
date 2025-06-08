/********************************************************************************
** Form generated from reading UI file 'authdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUTHDIALOG_H
#define UI_AUTHDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AuthDialog
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLineEdit *loginEdit;
    QLabel *label_2;
    QLineEdit *passwordEdit;
    QPushButton *loginButton;
    QPushButton *registerButton;

    void setupUi(QDialog *AuthDialog)
    {
        if (AuthDialog->objectName().isEmpty())
            AuthDialog->setObjectName("AuthDialog");
        AuthDialog->resize(678, 520);
        AuthDialog->setStyleSheet(QString::fromUtf8(""));
        verticalLayoutWidget = new QWidget(AuthDialog);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(110, 170, 441, 244));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName("label");
        QFont font;
        font.setFamilies({QString::fromUtf8("Futura")});
        font.setBold(true);
        font.setItalic(false);
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("color: white;              \n"
"font: bold 16px \"Futura\";      \n"
"background-color: rgba(0,0,0, 200);  \n"
"border-radius: 4px;    \n"
"padding: 4px 8px; "));

        verticalLayout->addWidget(label);

        loginEdit = new QLineEdit(verticalLayoutWidget);
        loginEdit->setObjectName("loginEdit");
        QFont font1;
        loginEdit->setFont(font1);
        loginEdit->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    min-width: 80px;\n"
"    padding: 6px;\n"
"    font-size: 14px;\n"
"}\n"
""));

        verticalLayout->addWidget(loginEdit);

        label_2 = new QLabel(verticalLayoutWidget);
        label_2->setObjectName("label_2");
        label_2->setFont(font);
        label_2->setStyleSheet(QString::fromUtf8("color: white;                    \n"
"font: bold 16px \"Futura\";      \n"
"background-color: rgba(0,0,0, 200);  \n"
"border-radius: 4px;    \n"
"padding: 4px 8px; "));

        verticalLayout->addWidget(label_2);

        passwordEdit = new QLineEdit(verticalLayoutWidget);
        passwordEdit->setObjectName("passwordEdit");
        passwordEdit->setFont(font1);
        passwordEdit->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    min-width: 10px;\n"
"    padding: 6px;\n"
"    font-size: 14px;\n"
"}\n"
""));

        verticalLayout->addWidget(passwordEdit);

        loginButton = new QPushButton(verticalLayoutWidget);
        loginButton->setObjectName("loginButton");
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Futura")});
        font2.setBold(false);
        font2.setItalic(false);
        loginButton->setFont(font2);
        loginButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	font: \"Futura\";   \n"
"    background-color: #555555;\n"
"    color: white;\n"
"    border-radius: 8px;\n"
"    padding: 6px 12px;\n"
"    border: 2px solid #555555;\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #444444;\n"
"    border-color: #444444;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #333333;\n"
"    border-color: #333333;\n"
"}\n"
""));

        verticalLayout->addWidget(loginButton);

        registerButton = new QPushButton(verticalLayoutWidget);
        registerButton->setObjectName("registerButton");
        registerButton->setFont(font2);
        registerButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	font: \"Futura\";\n"
"    background-color: #555555;\n"
"    color: white;\n"
"    border-radius: 8px;\n"
"    padding: 6px 12px;\n"
"    border: 2px solid #555555;\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #444444;\n"
"    border-color: #444444;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #333333;\n"
"    border-color: #333333;\n"
"}\n"
""));

        verticalLayout->addWidget(registerButton);


        retranslateUi(AuthDialog);

        QMetaObject::connectSlotsByName(AuthDialog);
    } // setupUi

    void retranslateUi(QDialog *AuthDialog)
    {
        AuthDialog->setWindowTitle(QCoreApplication::translate("AuthDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("AuthDialog", "                                 \320\233\320\276\320\263\320\270\320\275", nullptr));
        label_2->setText(QCoreApplication::translate("AuthDialog", "                                \320\237\320\260\321\200\320\276\320\273\321\214", nullptr));
        loginButton->setText(QCoreApplication::translate("AuthDialog", "\320\222\320\276\320\271\321\202\320\270", nullptr));
        registerButton->setText(QCoreApplication::translate("AuthDialog", "\320\227\320\260\321\200\320\265\320\263\320\270\321\201\321\202\321\200\320\270\321\200\320\276\320\262\320\260\321\202\321\214\321\201\321\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AuthDialog: public Ui_AuthDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUTHDIALOG_H
