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
#include "mainwindow.h"

#include <QApplication>
#include <QTime>

int main(int argc, char *argv[]) {
    qsrand((uint)QTime::currentTime().msec());
    QApplication::setApplicationName(QSNAKE_TITLE);
    QApplication::setOrganizationName(QSNAKE_ORGANIZATION);
    QApplication a(argc, argv);
    MainWindow m;
    m.show();
    return a.exec();
}