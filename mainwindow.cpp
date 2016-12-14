#include <QtWidgets>

#include "mainwindow.h"
#include <iostream>
using namespace std;

#include "game.h"

MainWindow::MainWindow()
{
    centerWindow = new QWidget;
    this->setCentralWidget(centerWindow);
    p = this;

    newGame = new QPushButton("🙂");
    newGame->setStyleSheet("font-size: 22px;");
    showBomb = new QLabel("Bomb:20");
    showTime = new QLabel("time:0");


    connect(newGame, SIGNAL(clicked(bool)), this, SLOT(createNewGame()));

    initialGame(16 ,16, 20);
}

void MainWindow::initialGame(int row, int col, int mines) {
    newGame->setText("🙂");
    showBomb->setText("Bomb:" + QString::number(mines));

    game = new Game(row, col, mines);

    layout = new QGridLayout();
    layout->addWidget(showTime, 0, 0, 1, 3);
    layout->addWidget(newGame, 0, col / 2, 1, 1);
    layout->addWidget(showBomb, 0, col - 4, 1, 4);
    layout->addLayout(game, 1, 0, row, col);

    delete centerWindow->layout();
    centerWindow->setLayout(layout);
    this->setFixedSize(game->getPreferSize());

    connect(game, SIGNAL(end(bool)), this, SLOT(gameEnd(bool)));
    connect(game, SIGNAL(updateMines(int)), this, SLOT(updateMines(int)));

    timeConsuming = 0;
    pthread_cancel(tid);
    pthread_create(&tid, NULL, thread_t, (void*)this);
}

void MainWindow::createNewGame() {
    bool ok;
    int row, col, mines;
    row = QInputDialog::getInt(this, "input game row number", "input game row number", 16, 6, 30, 1, &ok);
    if (!ok) {
        return ;
    }
    col = QInputDialog::getInt(this, "input game col number", "input game col number", 16, 8, 30, 1, &ok);
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
    initialGame(row, col, mines);
}

void MainWindow::gameEnd(bool result) {
    pthread_cancel(tid);
    if (result) {
        QMessageBox::information(this, "Win!", "Win!", QMessageBox::Ok, 0);
        newGame->setText("😀");
    } else {
        QMessageBox::information(this, "Fali!", "Fali!", QMessageBox::Ok, 0);
        newGame->setText("☹️");
    }
}

void MainWindow::updateMines(int mines) {
    showBomb->setText("Bomb:" + QString::number(mines));
}
