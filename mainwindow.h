#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QPushButton>

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
    Game* game;
    void initialGame(int row, int col, int mines);

public slots:
    void createNewGame();
    void gameEnd(bool);
};

#endif // MAINWINDOW_H
