#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    std::pair<bool, QVector<QVector<int>>> hitoriSolution =
        HitoriSolver::GetHitoriSolve(5, {{3, 2, 4, 2, 5}, {5, 2, 3, 3, 1}, {2, 5, 5, 1, 1}, {1, 4, 2, 5, 3}, {3, 5, 5, 3, 3}});

    qDebug() << hitoriSolution;
}

MainWindow::~MainWindow()
{
    delete ui;
}
