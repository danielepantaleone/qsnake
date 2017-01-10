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

#ifndef QSNAKE_QSNAKE_H
#define QSNAKE_QSNAKE_H

#include "board.h"
#include "game.h"

#include <QAction>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMainWindow>


class QSnake : public QMainWindow {

    Q_OBJECT

    public:

        QSnake(QWidget *parent = 0);
        ~QSnake();

    private:

        Board *board;
        Game *game;

        QAction *newGameAction;
        QAction *quitAction;
        QGraphicsView *view;

        void setupActions();
        void setupMenus();
        void setupUI();

    private slots:

        void newGame();

};


#endif //QSNAKE_QSNAKE_H