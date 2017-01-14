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
#include <QMap>

const QBrush          BORDER_BACKGROUND_BRUSH = QBrush(QColor(0, 0, 0, 255));
const QBrush          BORDER_FOREGROUND_BRUSH = QBrush(QColor(177, 216, 123, 255));
const int             BORDER_SIZE             = 18;
const QBrush          BOARD_BACKGROUND_BRUSH  = QBrush(QColor(177, 216, 123, 255));
const int             BOARD_CELL_SIZE         = 12;
const int             BOARD_CELL_LENGTH_X     = 28;
const int             BOARD_CELL_LENGTH_Y     = 28;
const int             BOARD_ORIGIN_X          = 0;
const int             BOARD_ORIGIN_Y          = 0;
const int             BOARD_HEIGHT            = BOARD_CELL_SIZE * BOARD_CELL_LENGTH_Y;
const int             BOARD_WIDTH             = BOARD_CELL_SIZE * BOARD_CELL_LENGTH_X;
const QBrush          FOOD_FOREGROUND_BRUSH   = QBrush(QColor(121, 123, 89, 255));
const QMap<int, int>  FRAME_LEVEL_MSEC        {{1, 240}, {2, 210}, {3, 180}, {4, 150}, {5, 130}, {6, 110}, {7, 90}, {8, 70}, {9, 50}};
const int             FRAME_LEVEL_DEFAULT     = 6;
const int             FRAME_HANDICAP_COUNT    = 2;
const QBrush          SNAKE_FOREGROUND_BRUSH  = QBrush(QColor(0, 25, 0, 255));
const int             SNAKE_INITIAL_LENGTH    = 4;
const int             SNAKE_INITIAL_X         = BOARD_CELL_LENGTH_X / 2 - 4;
const int             SNAKE_INITIAL_Y         = BOARD_CELL_LENGTH_Y / 2 - 2;
const QString         TEXT_GAME_OVER          = QString("GAME OVER");
const QString         TEXT_LEVEL              = QString("LEVEL");
const QString         TEXT_PAUSED             = QString("PAUSED");
const QString         TEXT_RECORD             = QString("RECORD");
const int             TEXT_SIZE_1             = 10;
const int             TEXT_SIZE_2             = 14;
const int             QSNAKE_HEIGHT           = BOARD_HEIGHT + 2 * BORDER_SIZE;
const QString         QSNAKE_ORGANIZATION     = QString(APP_AUTHOR);
const QString         QSNAKE_TITLE            = QString(APP_NAME);
const int             QSNAKE_WIDTH            = BOARD_WIDTH + 2 * BORDER_SIZE;
const QString         QSNAKE_VERSION          = QString(APP_VERSION);

enum Direction {
    DirectionLeft,
    DirectionUp,
    DirectionRight,
    DirectionDown,
};

#endif //QSNAKE_CONSTANTS_H