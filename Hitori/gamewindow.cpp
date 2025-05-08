#include "gamewindow.h"
#include "hitorisolver.h"
#include "ui_gamewindow.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QRandomGenerator>
#include <QGridLayout>
#include <QDebug>

GameWindow::GameWindow(const QString& username, int size, bool useUnique, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow),
    username(username),
    boardSize(size),
    useUniqueBoards(useUnique),
    timer(nullptr),
    secondsElapsed(0),
    selectedCell(nullptr)
{
    ui->setupUi(this);
    setWindowTitle("Hitori — Игра");

    if (boardSize != 5 && boardSize != 10 && boardSize != 15 && boardSize != 20) {
        QMessageBox::critical(this, "Ошибка", "Недопустимый размер доски!");
        close();
        return;
    }


    try {
        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &GameWindow::updateTimer);

        if (!loadBoard()) {
            close();
            return;
        }

        initBoardUI();
        timer->start(1000);
        this->resize(200, 300);

        connect(ui->surrenderButton, &QPushButton::clicked, this, &GameWindow::onSurrenderClicked);
    }
    catch (const std::exception& e) {
        QMessageBox::critical(this, "Ошибка", QString("Исключение при инициализации: %1").arg(e.what()));
        close();
    }
    catch (...) {
        QMessageBox::critical(this, "Ошибка", "Неизвестная ошибка инициализации!");
        close();
    }
}

GameWindow::~GameWindow()
{
    if (timer) {
        delete timer;
    }
    delete ui;
}

bool GameWindow::loadBoard()
{
    QString filename = useUniqueBoards ?
                           QString("%1x%1_unique.txt").arg(boardSize) :
                           QString("%1x%1.txt").arg(boardSize);
    filename = "/Users/senior/Desktop/BSUIR/ОАиП/Курсач/Hitori/build/Desktop_arm_darwin_generic_mach_o_64bit-Debug/boards/" + filename;

    QFile file(filename);
    if (!file.exists()) {
        QMessageBox::critical(this, "Ошибка", QString("Файл %1 не существует").arg(filename));
        return false;
    }

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Ошибка", QString("Не удалось открыть файл %1").arg(filename));
        return false;
    }

    try {
        QTextStream in(&file);
        QStringList allBoards = in.readAll().split("\n\n", Qt::SkipEmptyParts);

        if (allBoards.isEmpty()) {
            QMessageBox::critical(this, "Ошибка", "Файл с полями пуст!");
            return false;
        }

        int randomBoard = QRandomGenerator::global()->bounded(allBoards.size());
        QString boardData = allBoards[randomBoard].trimmed();
        QStringList rows = boardData.split('\n', Qt::SkipEmptyParts);

        if (rows.size() != boardSize) {
            QMessageBox::critical(this, "Ошибка",
                                  QString("Неверное количество строк в поле. Ожидалось %1, получено %2")
                                      .arg(boardSize).arg(rows.size()));
            return false;
        }

        board.resize(boardSize);
        for (int row = 0; row < boardSize; ++row) {
            QStringList numbers = rows[row].split(' ', Qt::SkipEmptyParts);
            if (numbers.size() != boardSize) {
                QMessageBox::critical(this, "Ошибка",
                                      QString("Неверное количество чисел в строке %1").arg(row+1));
                return false;
            }

            board[row].clear();
            for (int col = 0; col < boardSize; ++col) {
                bool ok;
                int num = numbers[col].toInt(&ok);
                if (!ok || num < 1 || num > boardSize) {
                    QMessageBox::critical(this, "Ошибка",
                                          QString("Недопустимое число в строке %1, столбец %2").arg(row+1).arg(col+1));
                    return false;
                }
                board[row].append(num);
            }
        }
        return true;
    }
    catch (const std::exception& e) {
        QMessageBox::critical(this, "Ошибка", QString("Исключение при чтении файла: %1").arg(e.what()));
        return false;
    }
    catch (...) {
        QMessageBox::critical(this, "Ошибка", "Неизвестное исключение при чтении файла!");
        return false;
    }
}

void GameWindow::initBoardUI()
{
    if (board.size() != boardSize || (boardSize > 0 && board[0].size() != boardSize)) {
        QMessageBox::critical(this, "Ошибка", "Некорректные размеры доски!");
        close();
        return;
    }

    QWidget *container = new QWidget(this);
    QGridLayout *layout = new QGridLayout(container);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);

    for (int row = 0; row < boardSize; ++row) {
        for (int col = 0; col < boardSize; ++col) {
            QPushButton *cell = new QPushButton(QString::number(board[row][col]), container);
            cell->setFixedSize(40, 40);
            cell->setProperty("row", row);
            cell->setProperty("col", col);
            cell->setProperty("state", "white");

            QString style = "QPushButton {"
                            "  background-color: white;"
                            "  color: black;"
                            "  border: 1px solid #d0d0d0;"
                            "  font-size: 16px;"
                            "  font-weight: bold;"
                            "  margin: 0px;"
                            "}";
            cell->setStyleSheet(style);

            connect(cell, &QPushButton::clicked, this, &GameWindow::onCellClicked);
            layout->addWidget(cell, row, col);
        }
    }

    if (ui->boardWidget->layout()) {
        ui->boardWidget->layout()->deleteLater();
    }
    ui->boardWidget->setLayout(layout);
}

void GameWindow::onCellClicked()
{
    QPushButton *cell = qobject_cast<QPushButton*>(sender());
    if (!cell) {
        qDebug() << "Sender is not a QPushButton!";
        return;
    }

    QString state = cell->property("state").toString();
    QString newState;
    QString newStyle;

    if (state == "white") {
        newState = "gray";
        newStyle = "background-color: #aaaaaa; color: black;";
    }
    else if (state == "gray") {
        newState = "black";
        newStyle = "background-color: black; color: white;";
    }
    else {
        newState = "white";
        newStyle = "background-color: white; color: black;";
    }

    cell->setProperty("state", newState);
    cell->setStyleSheet("QPushButton { " + newStyle +
                        " border: 1px solid #d0d0d0;"
                        " font-size: 16px;"
                        " font-weight: bold;"
                        " margin: 0px; }");

    checkSolution();
}

void GameWindow::updateTimer()
{
    secondsElapsed++;
    int minutes = secondsElapsed / 60;
    int seconds = secondsElapsed % 60;
    ui->timeLabel->setText(QString("%1:%2")
                               .arg(minutes, 2, 10, QLatin1Char('0'))
                               .arg(seconds, 2, 10, QLatin1Char('0')));
}

void GameWindow::onSurrenderClicked()
{
    if (timer) {
        timer->stop();
    }
    showSolution();
    QMessageBox::information(this, "Игра окончена", "Вы сдались! Вот правильное решение.");
    close();
}

void GameWindow::checkSolution()
{
    solution.resize(boardSize);
    for (int row = 0; row < boardSize; ++row) {
        solution[row].resize(boardSize);
    }

    QList<QPushButton*> buttons = ui->boardWidget->findChildren<QPushButton*>();

    for (QPushButton* cell : buttons) {
        int row = cell->property("row").toInt();
        int col = cell->property("col").toInt();

        if (row >= 0 && row < boardSize && col >= 0 && col < boardSize) {
            QString state = cell->property("state").toString();
            solution[row][col] = (state == "black") ? 1 : 0;
        }
    }

    qDebug() << "Текущее решение игрока:";
    for (const auto &row : solution) {
        qDebug() << row;
    }

    bool isSolved = HitoriSolver::SolveHitori(board, solution);

    if (isSolved) {
        if (timer) {
            timer->stop();
        }
        QMessageBox::information(this, "Победа!", "Вы решили головоломку!");
        close();
    }
}

void GameWindow::showSolution()
{
    // Заглушка - здесь будет отображение решения
    QMessageBox::information(this, "Решение", "Здесь будет правильное решение");
}
