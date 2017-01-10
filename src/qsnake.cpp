/**
 * This file is part of QSnake.
 *
 * Copyright (C) 2017 Daniele Pantaleone <danielepantaleone@me.com>
 *
 * QSnake is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * QSnake is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Foobar. If not, see <http://www.gnu.org/licenses/>.
 */

#include "board.h"
#include "constants.h"
#include "game.h"
#include "qsnake.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QMenu>
#include <QMenuBar>

QSnake::QSnake(QWidget *parent)
    : QMainWindow(parent),
      board(new Board(this)),
      view(new QGraphicsView(board, this)) {
    setupActions();
    setupMenus();
    setupUI();
}

QSnake::~QSnake() {}

/**
 * Initialize QSnake main actions.
 */
void QSnake::setupActions() {
    newGameAction = new QAction(tr("&New Game"), this);
    newGameAction->setShortcut(QKeySequence::New);
    newGameAction->setStatusTip(tr("Launch a new game"));
    connect(newGameAction, &QAction::triggered, this, &QSnake::newGame);
    quitAction = new QAction(tr("&Quit"), this);
    quitAction->setShortcut(QKeySequence::Quit);
    quitAction->setStatusTip(tr("Quit QSnake"));
    connect(quitAction, &QAction::triggered, this, &QSnake::close);
}

/**
 * Initialize QSnake menus.
 */
void QSnake::setupMenus() {
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newGameAction);
    fileMenu->addSeparator();
    fileMenu->addAction(quitAction);
}

/**
 * Setup QSnake user interface.
 */
void QSnake::setupUI() {
    board->setBackgroundBrush(BOARD_BACKGROUND_BRUSH);
    board->setSceneRect(BOARD_ORIGIN_X, BOARD_ORIGIN_Y, BOARD_WIDTH, BOARD_HEIGHT);
    board->setItemIndexMethod(Board::BspTreeIndex);
    view->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    setAttribute(Qt::WA_QuitOnClose);
    setCentralWidget(view);
    setFixedSize(BOARD_WIDTH, BOARD_HEIGHT);
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
    move(QApplication::desktop()->screen()->rect().center() - rect().center());
}

/**
 * Qt slot which triggers the start of a new game.
 */
void QSnake::newGame() {
    game = new Game(*board, this);
}