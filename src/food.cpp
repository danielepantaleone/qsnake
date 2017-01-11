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

Food::Food(Game *g) : game(g) {
    setZValue(0.0);
}

Food::~Food() {}

/**
 * Returns the Snake bounding rectangle as QRectF.
 *
 * @return QRectF
 */
QRectF Food::boundingRect() const {
    return Board::mapToBoard(m_gridPos);
}

/**
 * Returns the Food grid position.
 *
 * @return QPointF
 */
QPointF Food::gridPos() {
    return m_gridPos;
}

/**
 * Move the food grid position according with the trail of the given Snake.
 *
 * @param s A pointer to the active Snake.
 */
void Food::move(Snake *s) {
    QPointF p;
    do {
        p.setX(qrand() % (BOARD_CELL_COUNT_X - BOARD_ORIGIN_X) + BOARD_ORIGIN_X);
        p.setY(qrand() % (BOARD_CELL_COUNT_X - BOARD_ORIGIN_X) + BOARD_ORIGIN_X);
    } while(s->trail()->contains(p));
    setGridPos(p);
}

/**
 * Set the Food position on the grid.
 *
 * @param p QPointF
 */
void Food::setGridPos(QPointF p) {
    m_gridPos = p;
    prepareGeometryChange();
}

/**
 * Returns the 'shape' of the Snake as QPainterPath (used for collision detection).
 *
 * @return QPainterPath
 */
QPainterPath Food::shape() const {
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);
    path.addRect(Board::mapToBoard(m_gridPos));
    return path;
}

/**
 * Renders the Snake shape.
 *
 * @param painter The painter to be used for the rendering.
 */
void Food::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    painter->save();
    painter->fillPath(shape(), FOOD_FOREGROUND_BRUSH);
    painter->restore();
}