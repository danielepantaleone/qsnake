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
#include "food.h"
#include "snake.h"

#include <QPainter>

Snake::Snake(QObject *parent) : QObject(parent) {
    m_direction = DirectionRight;
    for (int i = 0; i < SNAKE_INITIAL_LENGTH; i++)
        m_trail.append(QPointF(SNAKE_INITIAL_X - i, SNAKE_INITIAL_Y));

}

Snake::~Snake() {}


/**
 * Detect possible Snake collision on the given point.
 *
 * @return True if the Snake will collide with itself or the Board limits, False otherwise;
 */
bool Snake::collision(QPointF p) {
    if (p.x() < BOARD_ORIGIN_X || p.x() >= BOARD_CELL_LENGTH_X)
        return true;
    if (p.y() < BOARD_ORIGIN_Y || p.y() >= BOARD_CELL_LENGTH_Y)
        return true;
    return m_trail.contains(p);
}

/**
 * Let the current Snake eat the given food (and grow in its size).
 *
 * @param f A pointer to the Food instance.
 * @return True if the Snake ate the Foof, False otherwise.
 */
bool Snake::eat(Food *f) {
    if (pos() == f->pos()) {
        m_trail.append(QPointF(m_trail.back()));
        return true;
    }
    return false;
}

/**
 * Advance the Snake in the board by one cell.
 */
void Snake::move() {
    m_trail.removeLast();
    m_trail.prepend(nextPos());
}

/**
 * Returns the Snake next (head) position.
 *
 * @return QPointF
 */
QPointF Snake::nextPos() {
    return nextPos(m_direction);
}

/**
 * Returns the Snake next (head) position according with the given direction.
 *
 * @param direction The direction to use to calculate the next (head) position.
 * @return QPointF
 */
QPointF Snake::nextPos(Direction direction) {
    switch (direction) {
        case DirectionLeft:
            return QPointF(m_trail.front()) + QPointF(-1, 0);
        case DirectionUp:
            return QPointF(m_trail.front()) + QPointF(0, -1);
        case DirectionRight:
            return QPointF(m_trail.front()) + QPointF(+1, 0);
        case DirectionDown:
            return QPointF(m_trail.front()) + QPointF(0, +1);
    }
    return QPointF(m_trail.front());
}

/**
 * Returns a QPointF which is the position (head) of the Snake in the board.
 *
 * @return QPointF
 */
QPointF Snake::pos() {
    return m_trail.front();
}


/**
 * Reset the Snake to its initial state.
 */
void Snake::reset() {
    m_direction = DirectionRight;
    m_trail.clear();
    for (int i = 0; i < SNAKE_INITIAL_LENGTH; i++)
        m_trail.append(QPointF(SNAKE_INITIAL_X - i, SNAKE_INITIAL_Y));
}

/**
 * Returns a pointer to the Snake trail.
 *
 * @return QList<QPointF> *
 */
QList<QPointF> *Snake::trail() {
    return &m_trail;
}

/**
 * Turn the Snake down.
 */
void Snake::turnDown() {
    if (m_direction != DirectionUp)
        if (m_trail.front().y() != BOARD_CELL_LENGTH_Y - 1)
            if (nextPos(DirectionDown) != m_trail.at(1))
                m_direction = DirectionDown;
}

/**
 * Turn the Snake left.
 */
void Snake::turnLeft() {
    if (m_direction != DirectionRight)
        if (m_trail.front().x() != BOARD_ORIGIN_X)
            if (nextPos(DirectionLeft) != m_trail.at(1))
                m_direction = DirectionLeft;
}

/**
 * Turn the Snake right.
 */
void Snake::turnRight() {
    if (m_direction != DirectionLeft)
        if (m_trail.front().x() != BOARD_CELL_LENGTH_X - 1)
            if (nextPos(DirectionRight) != m_trail.at(1))
                m_direction = DirectionRight;
}

/**
 * Turn the Snake up.
 */
void Snake::turnUp() {
    if (m_direction != DirectionDown)
        if (m_trail.front().y() != BOARD_ORIGIN_Y)
            if (nextPos(DirectionUp) != m_trail.at(1))
                m_direction = DirectionUp;
}