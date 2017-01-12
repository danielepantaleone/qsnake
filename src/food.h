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

#ifndef QSNAKE_FOOD_H
#define QSNAKE_FOOD_H

#include "constants.h"

#include <QObject>
#include <QRectF>

class Snake;

class Food : public QObject {

    Q_OBJECT

    public:

        Food(QObject *parent = 0);
        ~Food();

        void move(Snake *s);
        QPointF pos();
        void setPos(QPointF p);

    private:

        QPointF m_pos;

};

#endif //QSNAKE_FOOD_H
