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

#ifndef QSNAKE_SNAKE_H
#define QSNAKE_SNAKE_H

#include "constants.h"

#include <QGraphicsItem>
#include <QRectF>


class Snake : public QGraphicsItem {

    public:

        Snake();
        ~Snake();

        Direction direction();
        void move();
        void setDirection(Direction direction);

        QRectF boundingRect() const;
        QPainterPath shape() const;
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

    private:

        Direction m_direction;
        QList<QPointF> m_trail;

};

#endif //QSNAKE_SNAKE_H
