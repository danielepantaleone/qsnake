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

#include <QFontDatabase>
#include <QPainter>
#include <QGraphicsView>

Board::Board(QObject *parent) : QGraphicsScene(parent) {
    ff = QFontDatabase::systemFont(QFontDatabase::FixedFont);
    ff.setPointSize(14);
}

Board::~Board() {}


/**
 * Returns the reference to the current QString set as board foreground.
 *
 * @return QString*
 */
QString & Board::foreground() {
    return fg;
}

/**
 * Set the QString to be drawn as foreground.
 *
 * @param s The QString to draw.
 */
void Board::setForeground(QString s) {
    fg = s;
    update();
}

/**
 * Draw the board foreground.
 *
 * @param painter The active QPainter.
 * @param rect
 */
void Board::drawForeground(QPainter *painter, const QRectF &rect) {
    if (!fg.isNull() && !fg.isEmpty()) {
        painter->save();
        painter->setFont(ff);
        painter->drawText(rect, Qt::AlignCenter, fg);
        painter->restore();
    }
}

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