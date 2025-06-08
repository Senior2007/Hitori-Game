/********************************************************************************
** Form generated from reading UI file 'mainmenu.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINMENU_H
#define UI_MAINMENU_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_MainMenu
{
public:
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QComboBox *sizeComboBox;
    QPushButton *playButton;
    QCheckBox *uniqueCheckBox;
    QSpacerItem *horizontalSpacer;
    QPushButton *statsButton;
    QSpacerItem *verticalSpacer_2;
    QPushButton *exitButton;

    void setupUi(QDialog *MainMenu)
    {
        if (MainMenu->objectName().isEmpty())
            MainMenu->setObjectName("MainMenu");
        MainMenu->resize(676, 481);
        verticalLayout = new QVBoxLayout(MainMenu);
        verticalLayout->setObjectName("verticalLayout");
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        sizeComboBox = new QComboBox(MainMenu);
        sizeComboBox->addItem(QString());
        sizeComboBox->addItem(QString());
        sizeComboBox->addItem(QString());
        sizeComboBox->addItem(QString());
        sizeComboBox->setObjectName("sizeComboBox");

        verticalLayout->addWidget(sizeComboBox);

        playButton = new QPushButton(MainMenu);
        playButton->setObjectName("playButton");
        playButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
"    background-color: #376130;\n"
"    border-color: #376130;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #333333;\n"
"    border-color: #333333;\n"
"}\n"
""));

        verticalLayout->addWidget(playButton);

        uniqueCheckBox = new QCheckBox(MainMenu);
        uniqueCheckBox->setObjectName("uniqueCheckBox");
        uniqueCheckBox->setStyleSheet(QString::fromUtf8("font: \"Futura\";"));

        verticalLayout->addWidget(uniqueCheckBox);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        verticalLayout->addItem(horizontalSpacer);

        statsButton = new QPushButton(MainMenu);
        statsButton->setObjectName("statsButton");
        statsButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	font: \"Futura\";   \n"
"    background-color: #555555;\n"
"    color: white;\n"
"    border-radius: 8px;\n"
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

        verticalLayout->addWidget(statsButton);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        exitButton = new QPushButton(MainMenu);
        exitButton->setObjectName("exitButton");
        exitButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	font: \"Futura\";   \n"
"    background-color: #555555;\n"
"    color: white;\n"
"    border-radius: 8px;\n"
"    border: 2px solid #555555;\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #fc0330;\n"
"    border-color: #fc0330;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #333333;\n"
"    border-color: #333333;\n"
"}\n"
""));

        verticalLayout->addWidget(exitButton);


        retranslateUi(MainMenu);

        QMetaObject::connectSlotsByName(MainMenu);
    } // setupUi

    void retranslateUi(QDialog *MainMenu)
    {
        MainMenu->setWindowTitle(QCoreApplication::translate("MainMenu", "Dialog", nullptr));
        sizeComboBox->setItemText(0, QCoreApplication::translate("MainMenu", "5\303\2275", nullptr));
        sizeComboBox->setItemText(1, QCoreApplication::translate("MainMenu", "10\303\22710", nullptr));
        sizeComboBox->setItemText(2, QCoreApplication::translate("MainMenu", "15\303\22715", nullptr));
        sizeComboBox->setItemText(3, QCoreApplication::translate("MainMenu", "20\303\22720", nullptr));

        playButton->setText(QCoreApplication::translate("MainMenu", "\320\230\320\263\321\200\320\260\321\202\321\214", nullptr));
        uniqueCheckBox->setText(QCoreApplication::translate("MainMenu", "\320\242\320\276\320\273\321\214\320\272\320\276 \321\203\320\275\320\270\320\272\320\260\320\273\321\214\320\275\321\213\320\265", nullptr));
        statsButton->setText(QCoreApplication::translate("MainMenu", "\320\241\321\202\320\260\321\202\320\270\321\201\321\202\320\270\320\272\320\260", nullptr));
        exitButton->setText(QCoreApplication::translate("MainMenu", "\320\222\321\213\321\205\320\276\320\264", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainMenu: public Ui_MainMenu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINMENU_H
