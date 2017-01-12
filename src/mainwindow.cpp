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

#include "constants.h"
#include "mainwindow.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QMenu>
#include <QMenuBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      m_qsnake(new QSnake(this)) {
    setupActions();
    setupControls();
    setupMenus();
    setupUI();
}

MainWindow::~MainWindow() {}

/**
 * Initialize QSnake main actions.
 */
void MainWindow::setupActions() {
    newGameAction = new QAction(tr("&New Game"), this);
    newGameAction->setShortcut(QKeySequence::New);
    newGameAction->setStatusTip(tr("Launch a new game"));
    connect(newGameAction, &QAction::triggered, this, &MainWindow::newGame);
    quitAction = new QAction(tr("&Quit"), this);
    quitAction->setShortcut(QKeySequence::Quit);
    quitAction->setStatusTip(tr("Quit QSnake"));
    connect(quitAction, &QAction::triggered, this, &MainWindow::close);
}

/**
 * Initialize QSnake controls listeners.
 */
void MainWindow::setupControls() {
    installEventFilter(m_qsnake);
}


/**
 * Initialize QSnake menus.
 */
void MainWindow::setupMenus() {
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newGameAction);
    fileMenu->addSeparator();
    fileMenu->addAction(quitAction);
}

/**
 * Setup QSnake user interface.
 */
void MainWindow::setupUI() {
    setAttribute(Qt::WA_QuitOnClose);
    setCentralWidget(m_qsnake);
    setFixedSize(QSNAKE_WIDTH, QSNAKE_HEIGHT);
    setWindowTitle(QString(QSNAKE_TITLE + " v" + QSNAKE_VERSION));
    move(QApplication::desktop()->screen()->rect().center() - rect().center());
}

/**
 * Qt slot which triggers the start of a new game.
 */
void MainWindow::newGame() {
    m_qsnake->restart();
}