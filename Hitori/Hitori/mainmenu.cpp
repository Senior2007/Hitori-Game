#include "mainmenu.h"
#include "ui_mainmenu.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

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
    QString statsFilePath =
        "/Users/senior/Desktop/BSUIR/ОАиП/Курсач/Hitori/build/Desktop_arm_darwin_generic_mach_o_64bit-Debug/statistics/"
                            + currentUsername + ".txt";
    QFile statsFile(statsFilePath);

    if (!statsFile.exists()) {
        QMessageBox::information(this, "Статистика", "Статистика не найдена!");
        return;
    }

    if (!statsFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл статистики!");
        return;
    }

    QTextStream in(&statsFile);
    QStringList stats;

    for (int i = 0; i < 9; ++i) {
        stats << in.readLine();
    }
    statsFile.close();

    QString statsMessage =
        "Общая статистика для " + currentUsername + ":\n\n"
                                                    "• Всего решено: " + stats[0] + "\n\n"
                     "────── По размерам ──────\n"
                                 "5×5:\n"
                                 "  - Решено: " + stats[1] + "\n"
                     "  - Лучшее время: " + formatTime(stats[2]) + "\n\n"
                                 "10×10:\n"
                                 "  - Решено: " + stats[3] + "\n"
                     "  - Лучшее время: " + formatTime(stats[4]) + "\n\n"
                                 "15×15:\n"
                                 "  - Решено: " + stats[5] + "\n"
                     "  - Лучшее время: " + formatTime(stats[6]) + "\n\n"
                                 "20×20:\n"
                                 "  - Решено: " + stats[7] + "\n"
                     "  - Лучшее время: " + formatTime(stats[8]);

    QMessageBox::information(this, "Статистика", statsMessage);
}

QString MainMenu::formatTime(const QString &seconds) {
    bool ok;
    int totalSeconds = seconds.toInt(&ok);
    if (!ok || totalSeconds < 0) return "N/A";

    int minutes = totalSeconds / 60;
    int secs = totalSeconds % 60;
    return QString("%1:%2")
        .arg(minutes, 2, 10, QLatin1Char('0'))
        .arg(secs, 2, 10, QLatin1Char('0'));
}

void MainMenu::on_exitButton_clicked() {
    close();
}

int MainMenu::getSelectedSize() {
    int size = ui->sizeComboBox->currentText().split("×")[0].toInt();
    return size;
}

bool MainMenu::useUniqueBoards() {
    bool useUnique = ui->uniqueCheckBox->isChecked();
    return useUnique;
}
