#include <QObject>

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
#include "game.h"

#include <QEvent>
#include <QKeyEvent>

Game::Game(Board &b, QObject *parent)
    : QObject(parent),
      paused(true),
      speed(1),
      board(b),
      food(new Food()),
      snake(new Snake()),
      timer(new QTimer(this)) {
    board.addItem(snake);
    board.addItem(food);
    board.installEventFilter(this);
    food->move(snake->trail());
    connect(timer, SIGNAL(timeout()), this, SLOT(frame()));
    timer->setInterval(FRAME_MSEC);
    timer->start();
}

Game::~Game() {}

/**
 * Tells whether the game is paused.
 *
 * @return True if the Game is paused, False otherwise.
 */
bool Game::isPaused() {
    return paused;
}

/**
 * Set the Game paused status.
 *
 * @param p bool
 */
void Game::setPaused(bool p) {
    paused = p;
}


/**
 * Filter intercepted events.
 *
 * @param o The QObject which generated the event.
 * @param e The QEvent generated.
 * @return True if the event has been handled locally, False otherwise
 */
bool Game::eventFilter(QObject *o, QEvent *e) {
    if (e->type() == QEvent::KeyPress) {
        keyPressEvent((QKeyEvent *)e);
        return true;
    }
    return QObject::eventFilter(o, e);
}

/**
 * Executed when a key is pressed.
 *
 * @param e The corresponding QKeyEvent.
 */
void Game::keyPressEvent(QKeyEvent *e) {
    switch (e->key()) {
        case Qt::Key_Left:
            snake->setDirection(DirectionLeft);
            break;
        case Qt::Key_Right:
            snake->setDirection(DirectionRight);
            break;
        case Qt::Key_Up:
            snake->setDirection(DirectionUp);
            break;
        case Qt::Key_Down:
            snake->setDirection(DirectionDown);
            break;
        case Qt::Key_Space:
            setPaused(!paused);
        default:
            break;
    }
}

/**
 * Qt slot which is executed every FRAME_MSEC.
 * This slots take care of advancing the game and updating the game UI.
 */
void Game::frame() {
    if (!paused) {
        snake->move();
        if (snake->eat(food)) {
            snake->grow();
            food->move(snake->trail());
        }
    }
}