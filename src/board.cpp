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
#include "board.h"

Board::Board(QObject *parent) : QGraphicsScene(parent) {}

Board::~Board() {}

/**
 * Map the given value according with the board cell size.
 *
 * @param v The value to map.
 * @return A 'double' mapped according with the board cell size.
 */
double Board::mapToBoard(double v) {
    return v * BOARD_CELL_PIXEL_SIZE;
}

/**
 * Map the given value according with the board cell size.
 *
 * @param p The QPointF to map.
 * @return A 'QRectF' representing the QPointF mapped over the board.
 */
QRectF Board::mapToBoard(QPointF p) {
    return QRectF(
        QPointF(mapToBoard(p.x()), mapToBoard(p.y())),
        QPointF(mapToBoard(p.x() + 1), mapToBoard(p.y() + 1))
    );
}