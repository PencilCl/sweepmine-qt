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

    connect(newGame, SIGNAL(clicked(bool)), this, SLOT(createNewGame()));

    initialGame(16 ,16, 20);
}

void MainWindow::initialGame(int row, int col, int mines) {
    game = new Game(row, col, mines);

    layout = new QGridLayout();
    layout->addWidget(newGame, 0, col / 2, 1, 1);
    layout->addLayout(game, 1, 0, row, col);

    delete centerWindow->layout();
    centerWindow->setLayout(layout);
    this->setFixedSize(game->getPreferSize());

    connect(game, SIGNAL(end(bool)), this, SLOT(gameEnd(bool)));
}

void MainWindow::createNewGame() {
    newGame->setText(":)");
    initialGame(8, 8, 1);
}

void MainWindow::gameEnd(bool result) {
    if (result) {
        cout<<"win"<<endl;
    } else {
        cout<<"Fail"<<endl;
        newGame->setText(":(");
    }
}
