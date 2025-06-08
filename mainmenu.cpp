#include "mainmenu.h"
#include "ui_mainmenu.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QTextBrowser>

MainMenu::MainMenu(const QString &username, QWidget *parent) :
    QDialog(parent),
    currentUsername(username),
    ui(new Ui::MainMenu)
{
    ui->setupUi(this);
    setWindowTitle("Главное меню");
    setMinimumSize(300, 200);

    QPixmap bkgnd("/Users/senior/Desktop/BSUIR/ОАиП/Курсач/Картинки/Главное меню 3.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);
    this->setAutoFillBackground(true);
    ui->uniqueCheckBox->setChecked(1);

    this->resize(700, 600);
}

MainMenu::~MainMenu() {
    delete ui;
}

void MainMenu::resizeEvent(QResizeEvent *event) {
    QPixmap bkgnd("/Users/senior/Desktop/BSUIR/ОАиП/Курсач/Картинки/Главное меню 3.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);
    this->setAutoFillBackground(true);
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

void MainMenu::on_globalStatsButton_clicked()
{
    QFile usersFile("/Users/senior/Desktop/BSUIR/ОАиП/Курсач/Hitori/build/Desktop_arm_darwin_generic_mach_o_64bit-Debug/users.txt");
    if (!usersFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл пользователей!");
        return;
    }

    struct PlayerStats {
        QString login;
        int total;
        int solved5;
        int solved10;
        int solved15;
        int solved20;
        int bestTime5;
        int bestTime10;
        int bestTime15;
        int bestTime20;
    };

    QVector<PlayerStats> allStats;

    QTextStream usersStream(&usersFile);
    while (!usersStream.atEnd()) {
        QString login = usersStream.readLine().split(':')[0];
        QString statsPath = "/Users/senior/Desktop/BSUIR/ОАиП/Курсач/Hitori/build/Desktop_arm_darwin_generic_mach_o_64bit-Debug/statistics/" + login + ".txt";

        QFile statsFile(statsPath);
        if (statsFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&statsFile);
            PlayerStats stats;
            stats.login = login;
            stats.total = in.readLine().toInt();
            stats.solved5 = in.readLine().toInt();
            stats.bestTime5 = in.readLine().toInt();
            stats.solved10 = in.readLine().toInt();
            stats.bestTime10 = in.readLine().toInt();
            stats.solved15 = in.readLine().toInt();
            stats.bestTime15 = in.readLine().toInt();
            stats.solved20 = in.readLine().toInt();
            stats.bestTime20 = in.readLine().toInt();

            allStats.append(stats);
            statsFile.close();
        }
    }
    usersFile.close();

    if (allStats.isEmpty()) {
        QMessageBox::information(this, "Статистика", "Нет данных о игроках!");
        return;
    }

    std::sort(allStats.begin(), allStats.end(),
              [](const PlayerStats &a, const PlayerStats &b) { return a.total > b.total; });

    QString statsText = "<h3>Топ-5 игроков по количеству решений:</h3><ol>";

    for (int i = 0; i < qMin(5, allStats.size()); ++i) {
        const auto &s = allStats[i];
        statsText += QString("<li><b>%1</b> (%2 реш.) - %3, %4, %5, %6</li>")
                         .arg(s.login)
                         .arg(s.total)
                         .arg(s.solved5)
                         .arg(s.solved10)
                         .arg(s.solved15)
                         .arg(s.solved20);
    }

    statsText += "</ol><h3>Рекордсмены по времени:</h3><ul>";

    auto findBestTime = [&allStats](int PlayerStats::*timeField) {
        return *std::min_element(allStats.begin(), allStats.end(),
                                 [timeField](const PlayerStats &a, const PlayerStats &b) {
                                     int aTime = a.*timeField;
                                     int bTime = b.*timeField;
                                     return (aTime > 0 && (bTime == 0 || aTime < bTime));
                                 });
    };

    auto formatTime = [](int seconds) {
        return seconds > 0 ? QString("%1:%2")
        .arg(seconds/60, 2, 10, QLatin1Char('0'))
            .arg(seconds%60, 2, 10, QLatin1Char('0')) : "N/A";
    };

    if (auto best = findBestTime(&PlayerStats::bestTime5); best.bestTime5 > 0) {
        statsText += QString("<li>5x5: <b>%1</b> (%2)</li>")
        .arg(best.login).arg(formatTime(best.bestTime5));
    }

    if (auto best = findBestTime(&PlayerStats::bestTime10); best.bestTime10 > 0) {
        statsText += QString("<li>10x10: <b>%1</b> (%2)</li>")
        .arg(best.login).arg(formatTime(best.bestTime10));
    }

    if (auto best = findBestTime(&PlayerStats::bestTime15); best.bestTime15 > 0) {
        statsText += QString("<li>15x15: <b>%1</b> (%2)</li>")
        .arg(best.login).arg(formatTime(best.bestTime15));
    }

    if (auto best = findBestTime(&PlayerStats::bestTime20); best.bestTime20 > 0) {
        statsText += QString("<li>20x20: <b>%1</b> (%2)</li>")
        .arg(best.login).arg(formatTime(best.bestTime20));
    }

    statsText += "</ul>";

    QDialog statsDialog(this);
    statsDialog.setWindowTitle("Глобальная статистика");
    statsDialog.resize(500, 400);

    QTextBrowser *textBrowser = new QTextBrowser(&statsDialog);
    textBrowser->setHtml(statsText);
    textBrowser->setOpenExternalLinks(true);

    QVBoxLayout *layout = new QVBoxLayout(&statsDialog);
    layout->addWidget(textBrowser);

    QPushButton *closeButton = new QPushButton("Закрыть", &statsDialog);
    connect(closeButton, &QPushButton::clicked, &statsDialog, &QDialog::accept);
    layout->addWidget(closeButton);

    statsDialog.exec();
}

