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
#include "food.h"
#include "snake.h"

#include <QPainter>

Snake::Snake(Game *g) : game(g) {
    reset();
    setZValue(1.0);
}

Snake::~Snake() {}

/**
 * Returns the Snake current direction.
 *
 * @return Direction
 */
Direction Snake::direction() {
    return m_direction;
}

/**
 * Detect possible Snake collision on the given point.
 *
 * @return True if the Snake will collide with itself or the Board limits, False otherwise;
 */
bool Snake::collision(QPointF p) {
    if (p.x() < BOARD_ORIGIN_X || p.x() >= BOARD_CELL_COUNT_X)
        return true;
    if (p.y() < BOARD_ORIGIN_Y || p.y() >= BOARD_CELL_COUNT_Y)
        return true;
    for (int i = 1; i < m_trail.size(); i++)
        if (p == m_trail.at(i))
            return true;
    return false;
}

/**
 * Let the current Snake eat the given food if necessary.
 *
 * @param f
 * @return
 */
bool Snake::eat(Food *f) {
    return head() == f->gridPos();
}

/**
 * Returns a QPointF which is the head of the Snake in the board.
 *
 * @return QPointF
 */
QPointF Snake::head() {
    return m_trail.front();
}

/**
 * Increase the size of the Snake.
 */
void Snake::grow() {
    m_trail.append(QPointF(m_trail.back()));
}

/**
 * Move the snake in the board by one cell.
 */
void Snake::move() {
    prepareGeometryChange();
    m_trail.removeLast();
    m_trail.prepend(nextPos());
}

/**
 * Returns the Snake next position.
 *
 * @return QPointF
 */
QPointF Snake::nextPos() {
    switch (m_direction) {
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
 * Reset the Snake to its initial state.
 */
void Snake::reset() {
    m_direction = DirectionRight;
    m_trail.clear();
    for (int i = 0; i < SNAKE_INITIAL_LENGTH; i++)
        m_trail.append(QPointF(SNAKE_INITIAL_X - i, SNAKE_INITIAL_Y));
}


/**
 * Set the Snake direction.
 *
 * @param d Direction
 */
void Snake::setDirection(Direction direction) {
    if (direction == DirectionRight) {
        if (m_direction == DirectionLeft)
            return;
        if (m_trail.front().x() == BOARD_CELL_COUNT_X - 1)
            return;
    }
    if (direction == DirectionLeft) {
        if (m_direction == DirectionRight)
            return;
        if (m_trail.front().x() == BOARD_ORIGIN_X)
            return;
    }
    if (direction == DirectionDown) {
        if (m_direction == DirectionUp)
            return;
        if (m_trail.front().y() == BOARD_CELL_COUNT_Y - 1)
            return;
    }
    if (direction == DirectionUp) {
        if (m_direction == DirectionDown)
            return;
        if (m_trail.front().y() == BOARD_ORIGIN_Y)
            return;
    }
    m_direction = direction;
}

/**
 * Returns a pointer to the Snake trail QList.
 *
 * @return QList<QPointF> *
 */
QList<QPointF> * Snake::trail() {
    return &m_trail;
}

/**
 * Returns the Snake bounding rectangle as QRectF.
 *
 * @return QRectF
 */
QRectF Snake::boundingRect() const {
    double minX = 0;
    double minY = 0;
    double maxX = 0;
    double maxY = 0;
    for (QPointF p : m_trail) {
        minX = qMin(minX, p.x());
        minY = qMin(minY, p.y());
        maxX = qMax(maxX, p.x());
        maxY = qMax(maxY, p.y());
    }
    minX = Board::mapToBoard(minX);
    minY = Board::mapToBoard(minY);
    maxX = Board::mapToBoard(maxX + 1);
    maxY = Board::mapToBoard(maxY + 1);
    return QRectF(QPointF(minX, minY), QPointF(maxX, maxY));
}

/**
 * Returns the 'shape' of the Snake as QPainterPath (used for collision detection).
 *
 * @return QPainterPath
 */
QPainterPath Snake::shape() const {
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);
    for (QPointF p : m_trail)
        path.addRect(Board::mapToBoard(p));
    return path;
}

/**
 * Renders the Snake shape.
 *
 * @param painter The painter to be used for the rendering.
 */
void Snake::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    painter->save();
    painter->fillPath(shape(), SNAKE_FOREGROUND_BRUSH);
    painter->restore();
}