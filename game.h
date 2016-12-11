#ifndef GAME_H
#define GAME_H

#include <QGridLayout>
#include <QSize>

class Pane;

class Game : public QGridLayout
{
    Q_OBJECT
public:
    Game(int row, int col, int mines);
    ~Game();
    QSize getPreferSize();
private:
    int row, col, mines, leftMines;
    Pane** panes;
    bool gameOver;

    void randSort();
    void initialPanes();

    Pane** getNeiborPanes(int id);
    int calNeiborMines(Pane** neibor);
    void revealAll();
    bool isWin();
signals:
    void end(bool);
    void updateMines(int leftMines);
public slots:
    void reveal(int id);
    void mark(int id);
};

#endif // GAME_H
