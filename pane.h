#ifndef PANE_H
#define PANE_H

#include <QPushButton>
#include <QWidget>
#include <string>
using namespace std;

class Pane : public QPushButton
{
    Q_OBJECT
public:
    Pane(bool isMine);
    void reveal();
    bool isReveal();
    bool isMine();
    bool isMarkMine();
    void markMine();
    void setId(int id);
    void setNum(int num);
    int getId();
private:
    bool revealState;
    bool mine;
    bool mark;
    bool dieHere;
    int id;
    int showNum;
    void render();
    string color[9];
    void initialColor();
signals:
    void clicked(int);
    void rightClicked(int);
protected:
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
};

#endif // PANE_H
