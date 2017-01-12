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
#include "qsnake.h"
#include "snake.h"

#include <QFontDatabase>
#include <QTimer>

QSnake::QSnake(QWidget *parent)
    : QWidget(parent),
      m_finished(false),
      m_paused(true),
      m_speed(9),
      m_score(0),
      m_food(new Food(this)),
      m_snake(new Snake(this)),
      m_timer(new QTimer(this)) {
    setFixedSize(BOARD_WIDTH, BOARD_HEIGHT);
    setMouseTracking(false);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(update()));
    m_food->move(m_snake);
    m_timer->setInterval(FRAME_MSEC);
    m_timer->start();
}

QSnake::~QSnake() {}

/**
 * End the current game.
 */
void QSnake::finish() {
    m_finished = true;
    disconnect(m_timer, SIGNAL(timeout()), this, SLOT(frame()));
}

/**
 * Pause the game.
 */
void QSnake::pause() {
    disconnect(m_timer, SIGNAL(timeout()), this, SLOT(frame()));
    m_paused = true;
}

/**
 * Restart the game.
 */
void QSnake::restart() {
    m_snake->reset();
    m_food->move(m_snake);
    m_finished = false;
    m_paused = true;
    m_score = 0;
}

/**
 * Resume the game.
 */
void QSnake::resume() {
    m_paused = false;
    connect(m_timer, SIGNAL(timeout()), this, SLOT(frame()));
}

/**
 * Qt slot which take care of advancing the game and updating the UI.
 */
void QSnake::frame() {
    if (!m_paused && !m_finished) {
        if (m_snake->collision(m_snake->nextPos())) {
            finish();
        } else {
            m_snake->move();
            if (m_snake->eat(m_food)) {
                m_food->move(m_snake);
                m_score += m_speed;
            }
        }
    }
}

/**
 * Filter intercepted events.
 *
 * @param o The QObject which generated the event.
 * @param e The QEvent generated.
 * @return True if the event has been handled locally, False otherwise.
 */
bool QSnake::eventFilter(QObject *o, QEvent *e) {
    if (e->type() == QEvent::KeyPress) {
        keyPressEvent((QKeyEvent *)e);
        return true;
    }
    return QObject::eventFilter(o, e);
}

/**
 * Executed when a key is pressed.
 *
 * @param e The corresponding QKeyEvent.
 */
void QSnake::keyPressEvent(QKeyEvent *e) {

    if (e->key() == Qt::Key_Space)
        m_paused ? resume() : pause();

    if (!m_paused && !m_finished) {
        switch (e->key()) {
            case Qt::Key_Left:
                m_snake->turnLeft();
                break;
            case Qt::Key_Right:
                m_snake->turnRight();
                break;
            case Qt::Key_Up:
                m_snake->turnUp();
                break;
            case Qt::Key_Down:
                m_snake->turnDown();
                break;
            default:
                break;
        }
    }

}

/**
 * Render the QSnake board together with its components.
 */
void QSnake::paintEvent(QPaintEvent *) {
    QPainter p;
    p.begin(this);
    renderBoard(&p);
    renderFood(&p);
    renderSnake(&p);
    renderPaused(&p);
    p.end();

}

/**
 * Render the board.
 *
 * @param p The active QPainter.
 */
void QSnake::renderBoard(QPainter *p) {
    p->save();
    p->fillRect(rect(), BOARD_BACKGROUND_BRUSH);
    p->restore();
}

/**
 * Render the Food.
 *
 * @param p The active QPainter.
 */
void QSnake::renderFood(QPainter *p) {
    p->save();
    p->fillRect(QSnake::mapToBoard(m_food->pos()), FOOD_FOREGROUND_BRUSH);
    p->restore();
}

/**
 * Render the game paused status.
 *
 * @param p The active QPainter.
 */
void QSnake::renderPaused(QPainter *p) {
    if (m_paused) {
        QFont f = QFontDatabase::systemFont(QFontDatabase::FixedFont);
        f.setPixelSize(TEXT_SIZE);
        p->save();
        p->drawText(rect(), Qt::AlignCenter, TEXT_PAUSED);
        p->restore();
    }
}


/**
 * Render the QSnake food.
 *
 * @param p The active QPainter.
 */
void QSnake::renderSnake(QPainter *p) {
    QPainterPath path;
    for (QPointF point: *m_snake->trail())
        path.addRect(QSnake::mapToBoard(point));
    p->save();
    p->fillPath(path, SNAKE_FOREGROUND_BRUSH);
    p->restore();
}

/**
 * Map the given value to the board.
 *
 * @param v The value to map.
 * @return A 'double' mapped according with the board cell size.
 */
double QSnake::mapToBoard(double v) {
    return v * BOARD_CELL_PIXEL_SIZE;
}

/**
 * Map the given QPointF to the board.
 *
 * @param p The QPointF to map.
 * @return A 'QRectF' representing the QPointF mapped over the board.
 */
QRectF QSnake::mapToBoard(QPointF p) {
    return QRectF(
        QPointF(mapToBoard(p.x()), mapToBoard(p.y())),
        QPointF(mapToBoard(p.x() + 1), mapToBoard(p.y() + 1))
    );
}