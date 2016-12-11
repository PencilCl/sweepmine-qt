#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <pthread.h>
#include <unistd.h>

class Game;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    QLabel* showTime;
    int timeConsuming;
    static void* thread_t(void* param) {
        MainWindow* main = (MainWindow*)param;
        while (true) {
            main->showTime->setText("time:" + QString::number(main->timeConsuming));
            ++main->timeConsuming;
            sleep(1);
        }
    }

private:
    QWidget* centerWindow;
    QGridLayout* layout;
    QPushButton* newGame;
    QMainWindow* p;
    pthread_t tid;
    QLabel* showBomb;
    Game* game;
    void initialGame(int row, int col, int mines);
public slots:
    void createNewGame();
    void gameEnd(bool);
    void updateMines(int);
};

#endif // MAINWINDOW_H
