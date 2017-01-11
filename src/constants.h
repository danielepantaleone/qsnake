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

#ifndef QSNAKE_CONSTANTS_H
#define QSNAKE_CONSTANTS_H

#include <QBrush>
#include <QColor>

const QBrush    BOARD_BACKGROUND_BRUSH  = QBrush(QColor(177, 216, 123, 255));
const int       BOARD_CELL_PIXEL_SIZE   = 12;
const int       BOARD_CELL_COUNT_X      = 32;
const int       BOARD_CELL_COUNT_Y      = 32;
const int       BOARD_FONT_PIZEL_SIZE   = 14;
const int       BOARD_ORIGIN_X          = 0;
const int       BOARD_ORIGIN_Y          = 0;
const int       BOARD_HEIGHT            = BOARD_CELL_PIXEL_SIZE * BOARD_CELL_COUNT_Y;
const int       BOARD_WIDTH             = BOARD_CELL_PIXEL_SIZE * BOARD_CELL_COUNT_X;
const QBrush    FOOD_FOREGROUND_BRUSH   = QBrush(QColor(121, 123, 89, 255));
const int       FRAME_MSEC              = 50;
const QBrush    SNAKE_FOREGROUND_BRUSH  = QBrush(QColor(0, 25, 0, 255));
const int       SNAKE_INITIAL_LENGTH    = 4;
const int       SNAKE_INITIAL_X         = BOARD_CELL_COUNT_X / 2 - 4;
const int       SNAKE_INITIAL_Y         = BOARD_CELL_COUNT_Y / 2 - 2;

enum Direction {
    DirectionLeft,
    DirectionUp,
    DirectionRight,
    DirectionDown,
};

#endif //QSNAKE_CONSTANTS_H