#include <QtWidgets>
#include "game.h"
#include <time.h>

#include <iostream>
using namespace std;

#include "pane.h"

Game::~Game() {
    for (int i = 0; i < row * col; ++i) {
        delete panes[i];
    }
}

Game::Game(int row, int col, int mines) : QGridLayout() {
    this->row =row;
    this->col = col;
    this->mines = mines;
    this->gameOver = false;

    // 置随机数种子
    srand((int)time(0));
    initialPanes();
}

void Game::initialPanes() {
    int i;
    panes = new Pane*[row * col];
    // 生成雷
    for (i = 0; i < mines; ++i) {
        panes[i] = new Pane(true);
    }
    //生成非雷
    for (i = mines; i < row * col; ++i) {
        panes[i] = new Pane(false);
    }
    // random sort;
    randSort();
    // 加入layout, 分配id并connect
    for (i = 0; i < row * col; ++i) {
        this->addWidget(panes[i], i / col, i % col, 1, 1);
        panes[i]->setMaximumSize(25, 25);
        panes[i]->setId(i);
        connect(panes[i], SIGNAL(clicked(int)), this, SLOT(reveal(int)));
        connect(panes[i], SIGNAL(rightClicked(int)), this, SLOT(mark(int)));
    }
}

void Game::randSort() {
    int i, j, totle = col * row;
    for (i = 0; i < totle; ++i) {
        j = rand() % totle;
        Pane* tmp = panes[i];
        panes[i] = panes[j];
        panes[j] = tmp;
    }
}

QSize Game::getPreferSize() {
    return QSize(this->col * 25 + 20, this->row * 25 + 50);
}

void Game::reveal(int id) {
    if (this->gameOver || this->panes[id]->isReveal() || this->panes[id]->isMarkMine()) {
        return ;
    }
    Pane* current = this->panes[id];
    current->reveal();
    if (current->isMine()) {
        revealAll();
        this->gameOver = true;
        // 通知游戏结束
        emit end(false);
        return ;
    }
    Pane** neibor = getNeiborPanes(id);
    int minesNum = calNeiborMines(neibor);
    if (minesNum > 0) {
        current->setNum(minesNum);
    } else {
        for (int i = 0; i < 8; ++i) {
            if (neibor[i]) {
                reveal(neibor[i]->getId());
            }
        }
    }
    // 判断是否赢
    if (!this->gameOver && isWin()) {
        this->gameOver = true;
        emit end(true);
        revealAll();
    }

}

void Game::revealAll() {
    for (int i = 0; i < row * col; ++i) {
        if (this->panes[i]->isReveal() == false) {
            Pane** neibor = getNeiborPanes(this->panes[i]->getId());
            int minesNum = calNeiborMines(neibor);
            this->panes[i]->setNum(minesNum);
            this->panes[i]->reveal();
        }
    }
}

Pane** Game::getNeiborPanes(int id) {
    Pane** panes = new Pane*[8];
    int row = id / this->col;
    int col = id % this->col;
    panes[0] = row > 0 && col > 0 ? this->panes[id - this->col - 1] : NULL;
    panes[1] = row > 0 ? this->panes[id - this->col] : NULL;
    panes[2] = row > 0 && col < this->col - 1 ? this->panes[id - this->col + 1] : NULL;
    panes[3] = col > 0 ? this->panes[id - 1]:NULL;
    panes[4] = col < this->col - 1 ? this->panes[id + 1]:NULL;
    panes[5] = row < this->row - 1 && col > 0 ? this->panes[id + this->col - 1] : NULL;
    panes[6] = row < this->row - 1 ? this->panes[id + this->col] : NULL;
    panes[7] = row < this->row - 1 && col < this->col - 1 ? this->panes[id + this->col + 1] : NULL;
    return panes;
}

int Game::calNeiborMines(Pane** neibor) {
    int result = 0;
    for (int i = 0; i < 8; ++i) {
        if (neibor[i] && neibor[i]->isMine()) {
            ++result;
        }
    }
    return result;
}

void Game::mark(int id) {
    if (panes[id]->isReveal()) {
        return ;
    }
    panes[id]->markMine();
}

bool Game::isWin() {
    for (int i = 0; i < col * row; ++i) {
        if (!panes[i]->isReveal() && !panes[i]->isMine()) {
            return false;
        }
    }
    return true;
}
