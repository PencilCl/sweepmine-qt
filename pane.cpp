#include <QtWidgets>
#include "pane.h"

#include <iostream>
using namespace std;

Pane::Pane(bool isMine) : QPushButton()
{
    this->mine = isMine;
    this->dieHere = false;
    this->revealState = false;
    this->mark = false;
    this->showNum = 0;

    QFont font ( "Microsoft YaHei",  15,   75);
    this->setFont(font);
    initialColor();
    render();
}

void Pane::initialColor() {
    color[0] = "rgb(130, 130, 130)";
    color[1] = "blue";
    color[2] = "green";
    color[3] = "red";
    color[4] = "darkblue";
    color[5] = "brown";
    color[6] = "crimson";
    color[7] = "darkviolet";
    color[8] = "deeppink";
}

bool Pane::isReveal() {
    return this->revealState;
}

bool Pane::isMine() {
    return this->mine;
}

bool Pane::isMarkMine() {
    return this->mark;
}

void Pane::markMine() {
    this->mark = this->mark ? false : true;
    render();
}

void Pane::setId(int id) {
    this->id = id;
}

int Pane::getId() {
    return this->id;
}

void Pane::setNum(int num) {
    this->showNum = num;
    render();
}

void Pane::reveal() {
    this->revealState = true;
    render();
}

void Pane::render() {
    this->setText("");
    if (this->revealState) {
        this->setText(QString::number(this->showNum));
        if (this->mine) {
            this->setText(this->dieHere ? "💥" : "💣");
            this->setStyleSheet("background-color: rgb(130, 130, 130);");
        } else {
            this->setStyleSheet(QString::fromStdString("background-color: rgb(130, 130, 130); color: " + color[this->showNum]));
        }
    } else {
        if (this->mark) {
            this->setText("1");
            this->setStyleSheet("background-color: darkgray; color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 rgb(255, 0, 0) stop:1 rgb(0, 0, 255))");
        } else {
            this->setStyleSheet("background-color: darkgray");
        }
    }
}

void Pane::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        this->dieHere = this->mine;
        emit clicked(this->id);
    } else if (event->button() == Qt::RightButton) {
        emit rightClicked(this->id);
    }
}
