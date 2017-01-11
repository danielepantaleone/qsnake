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

#include <QGraphicsScene>
#include <QObject>
#include <QTimer>

class Board;

class Food;

class Snake;

class Game : public QObject {

    Q_OBJECT

    public:

        Game(Board &b, QObject *parent = 0);
        ~Game();

        void setFinished(bool f);
        void pause();
        void resume();
        void restart();

    signals:

        void gameOver();
        void score(int);

    protected:

        bool eventFilter(QObject *o, QEvent *e);
        void keyPressEvent(QKeyEvent *e);

    private:

        bool finished;
        bool paused;
        int speed;
        Board &board;
        Food *food;
        Snake *snake;
        QTimer *timer;

    private slots:

        void frame();
};

#endif //QSNAKE_GAME_H
