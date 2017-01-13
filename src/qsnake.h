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

#ifndef QSNAKE_QSNAKE_H
#define QSNAKE_QSNAKE_H

#include <QPaintEvent>
#include <QPainter>
#include <QSettings>
#include <QWidget>

class Food;

class Snake;

class QSnake : public QWidget {

    Q_OBJECT

    public:

        QSnake(QWidget *parent = 0);
        ~QSnake();

        void finish();
        void pause();
        void restart();
        void resume();

        static double mapToBoard(double v);
        static QRectF mapToBoard(QPointF p);

    protected:

        bool eventFilter(QObject *o, QEvent *e);
        void keyPressEvent(QKeyEvent *e);
        void paintEvent(QPaintEvent *);

    private:

        bool m_finished;
        bool m_paused;
        int m_handicap;
        int m_score;
        int m_record;
        int m_speed;
        Food *m_food;
        Snake *m_snake;
        QTimer *m_timer;
        QFont m_font1;
        QFont m_font2;
        QSettings m_settings;

        void renderBaseline(QPainter *p);
        void renderBoard(QPainter *p);
        void renderFood(QPainter *p);
        void renderGameOver(QPainter *p);
        void renderPaused(QPainter *p);
        void renderSnake(QPainter *p);

    private slots:

        void frame();

};

#endif //QSNAKE_QSNAKE_H