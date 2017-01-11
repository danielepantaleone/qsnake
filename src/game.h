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
 * along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef QSNAKE_GAME_H
#define QSNAKE_GAME_H

#include "board.h"
#include "food.h"
#include "snake.h"

#include <QGraphicsScene>
#include <QObject>
#include <QTimer>

class Game : public QObject {

    Q_OBJECT

    public:

        Game(Board &b, QObject *parent = 0);
        ~Game();

        bool isPaused();
        void setPaused(bool p);

    public slots:

        void frame();

    protected:

        bool eventFilter(QObject *o, QEvent *e);
        void keyPressEvent(QKeyEvent *e);

    private:

        bool paused;
        int speed;
        Board &board;
        Food *food;
        Snake *snake;
        QTimer *timer;
};

#endif //QSNAKE_GAME_H
