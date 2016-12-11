#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>

class Game;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

private:
    QWidget* centerWindow;
    QGridLayout* layout;
    QPushButton* newGame;
    QLabel* showBomb;
    Game* game;
    void initialGame(int row, int col, int mines);

public slots:
    void createNewGame();
    void gameEnd(bool);
    void updateMines(int);
};

#endif // MAINWINDOW_H
