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

Food::Food(QObject *parent) : QObject(parent) {}

Food::~Food() {}

/**
 * Returns the Food position.
 *
 * @return QPointF
 */
QPointF Food::pos() {
    return m_pos;
}

/**
 * Move the food position according with the trail of the given Snake.
 *
 * @param s A pointer to the active Snake.
 */
void Food::move(Snake *s) {
    QList<QPointF> board;
    for (int i = 0; i < BOARD_CELL_LENGTH_X; i++)
        for (int j = 0; j < BOARD_CELL_LENGTH_Y; j++)
            if (!s->trail()->contains(QPointF(i, j)))
                board.append(QPointF(i, j));
    setPos(board.at(qrand() % board.size()));
}

/**
 * Set the Food position.
 *
 * @param p QPointF
 */
void Food::setPos(QPointF p) {
    m_pos = p;
}