#pragma once
#include <QDialog>
#include "gamewindow.h"

namespace Ui {
class MainMenu;
}

class MainMenu : public QDialog {
    Q_OBJECT

public:
    explicit MainMenu(const QString &username, QWidget *parent = nullptr);
    ~MainMenu();

private slots:
    void on_playButton_clicked();
    void on_statsButton_clicked();
    void on_exitButton_clicked();

private:
    QString currentUsername;
    Ui::MainMenu *ui;
};
