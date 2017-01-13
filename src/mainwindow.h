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

#ifndef QSNAKE_MAINWINDOW_H
#define QSNAKE_MAINWINDOW_H

#include "qsnake.h"

#include <QAction>
#include <QActionGroup>
#include <QMainWindow>

class MainWindow : public QMainWindow {

    Q_OBJECT

    public:

        MainWindow(QWidget *parent = 0);
        ~MainWindow();

    private:

        QSettings m_settings;
        QSnake *m_qsnake;

        QAction *newGameAction;
        QAction *quitAction;
        QActionGroup *levelActions;

        void setupActions();
        void setupControls();
        void setupMenus();
        void setupUI();

    private slots:

        void newGame();
        void setGameLevel();

};

#endif //QSNAKE_MAINWINDOW_H
