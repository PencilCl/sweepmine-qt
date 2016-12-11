#include <QtWidgets>

#include "mainwindow.h"
#include <iostream>
using namespace std;

#include "game.h"

MainWindow::MainWindow()
{
    centerWindow = new QWidget;
    this->setCentralWidget(centerWindow);

    newGame = new QPushButton(":)");
    showBomb = new QLabel("Bomb:20");

    connect(newGame, SIGNAL(clicked(bool)), this, SLOT(createNewGame()));

    initialGame(16 ,16, 20);
}

void MainWindow::initialGame(int row, int col, int mines) {
    game = new Game(row, col, mines);

    layout = new QGridLayout();
    layout->addWidget(newGame, 0, (col - 4) / 2, 1, 1);
    layout->addWidget(showBomb, 0, col - 4, 1, 4);
    layout->addLayout(game, 1, 0, row, col);

    delete centerWindow->layout();
    centerWindow->setLayout(layout);
    this->setFixedSize(game->getPreferSize());

    connect(game, SIGNAL(end(bool)), this, SLOT(gameEnd(bool)));
    connect(game, SIGNAL(updateMines(int)), this, SLOT(updateMines(int)));
}

void MainWindow::createNewGame() {
    newGame->setText(":)");
    bool ok;
    int row, col, mines;
    row = QInputDialog::getInt(this, "input game row number", "input game row number", 16, 5, 30, 1, &ok);
    if (!ok) {
        return ;
    }
    col = QInputDialog::getInt(this, "input game col number", "input game col number", 16, 5, 30, 1, &ok);
    if (!ok) {
        return ;
    }
    if (row * col < 2) {
        QMessageBox::critical(this, "error!", "col and row error!", QMessageBox::Ok, 0);
        return ;
    }
    mines = QInputDialog::getInt(this, "input game mines number", "input game mines number", 16, 1, row * col - 1, 1, &ok);
    if (!ok) {
        return ;
    }
    showBomb->setText("Bomb:" + QString::number(mines));
    initialGame(row, col, mines);
}

void MainWindow::gameEnd(bool result) {
    if (result) {
        QMessageBox::information(this, "Win!", "Win!", QMessageBox::Ok, 0);
    } else {
        QMessageBox::information(this, "Fali!", "Fali!", QMessageBox::Ok, 0);
        newGame->setText(":(");
    }
}

void MainWindow::updateMines(int mines) {
    showBomb->setText("Bomb:" + QString::number(mines));
}
