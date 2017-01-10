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

#ifndef QSNAKE_BOARD_H
#define QSNAKE_BOARD_H

#include <QGraphicsScene>

class Board : public QGraphicsScene {

    Q_OBJECT

    public:

        Board(QObject *parent = 0);
        ~Board();

        static double mapToBoard(double v);
        static QRectF mapToBoard(QPointF p);

};

#endif //QSNAKE_BOARD_H