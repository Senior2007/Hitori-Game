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
    int getSelectedSize();
    bool useUniqueBoards();

private slots:
    void on_playButton_clicked();
    void on_statsButton_clicked();
    void on_exitButton_clicked();

private:
    void resizeEvent(QResizeEvent *event) override;

    QString currentUsername;
    QString formatTime(const QString &seconds);
    Ui::MainMenu *ui;
};
