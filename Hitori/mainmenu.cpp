#include "mainmenu.h"
#include "ui_mainmenu.h"
#include <QMessageBox>

MainMenu::MainMenu(const QString &username, QWidget *parent) :
    QDialog(parent),
    currentUsername(username),
    ui(new Ui::MainMenu)
{
    ui->setupUi(this);
    setWindowTitle("Hitori — Главное меню");
    setMinimumSize(300, 200);
}

MainMenu::~MainMenu() {
    delete ui;
}

void MainMenu::on_playButton_clicked() {
    int size = ui->sizeComboBox->currentText().split("×")[0].toInt();
    bool useUnique = ui->uniqueCheckBox->isChecked();

    GameWindow *game = new GameWindow(currentUsername, size, useUnique);
    game->show();
    this->close();
}

void MainMenu::on_statsButton_clicked() {
    QMessageBox::information(this, "Статистика", "Раздел в разработке!");
}

void MainMenu::on_exitButton_clicked() {
    close();
}
