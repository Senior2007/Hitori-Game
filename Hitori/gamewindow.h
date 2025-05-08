#pragma once
#include <QMainWindow>
#include <QTimer>
#include <QPushButton>

namespace Ui {
class GameWindow;
}

class GameWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit GameWindow(const QString& username, int size, bool useUnique, QWidget *parent = nullptr);
    ~GameWindow();

private slots:
    void onCellClicked();
    void updateTimer();
    void onSurrenderClicked();

private:
    Ui::GameWindow *ui;
    QString username;
    int boardSize;
    int cellSize;
    bool useUniqueBoards;
    QVector<QVector<int>> board;
    QVector<QVector<int>> solution;
    QTimer *timer;
    int secondsElapsed;
    QPushButton *selectedCell;

    bool loadBoard();
    void initBoardUI();
    void checkSolution();
    void showSolution();
};
