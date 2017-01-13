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
      m_handicap(0),
      m_food(new Food(this)),
      m_snake(new Snake(this)),
      m_timer(new QTimer(this)) {
    setFixedSize(QSNAKE_WIDTH, QSNAKE_HEIGHT);
    setMouseTracking(false);
    m_speed = m_settings.value("options/level", FRAME_LEVEL_DEFAULT).toInt();
    m_record = m_settings.value("score/record", 0).toInt(),
    m_font1 = QFontDatabase::systemFont(QFontDatabase::FixedFont);
    m_font1.setPixelSize(TEXT_SIZE_1);
    m_font2 = QFontDatabase::systemFont(QFontDatabase::FixedFont);
    m_font2.setPixelSize(TEXT_SIZE_2);
    m_food->move(m_snake);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(update()));
    m_timer->setInterval(FRAME_LEVEL_MSEC.value(m_speed));
    m_timer->start();
}

QSnake::~QSnake() {}

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
 * End the current game.
 */
void QSnake::finish() {
    m_finished = true;
    disconnect(m_timer, SIGNAL(timeout()), this, SLOT(frame()));
    if (m_record > m_settings.value("score/record", 0).toInt())
        m_settings.setValue("score/record", m_record);
}

/**
 * Qt slot which take care of advancing the game and updating the UI.
 */
void QSnake::frame() {
    if (!m_paused && !m_finished) {
        if (m_snake->collision(m_snake->nextPos())) {
            if (m_handicap < FRAME_HANDICAP_COUNT) {
                m_handicap++;
            } else {
                finish();
            }
        } else {
            m_handicap = 0;
            m_snake->move();
            if (m_snake->eat(m_food)) {
                m_food->move(m_snake);
                m_score += m_speed;
                m_record = qMax(m_record, m_score);
            }
        }
    }
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
 * Map the given value to the board.
 *
 * @param v The value to map.
 * @return A 'double' mapped according with the board cell size.
 */
double QSnake::mapToBoard(double v) {
    return v * BOARD_CELL_SIZE + BORDER_SIZE;
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

/**
 * Render the QSnake board together with its components.
 */
void QSnake::paintEvent(QPaintEvent *) {
    QPainter p;
    p.begin(this);
    renderBaseline(&p);
    renderBoard(&p);
    renderFood(&p);
    renderSnake(&p);
    renderPaused(&p);
    renderGameOver(&p);
    p.end();
}

/**
 * Pause the game.
 */
void QSnake::pause() {
    disconnect(m_timer, SIGNAL(timeout()), this, SLOT(frame()));
    m_paused = true;
}

/**
 * Render the board.
 *
 * @param p The active QPainter.
 */
void QSnake::renderBoard(QPainter *p) {
    QPointF p1(QSnake::mapToBoard(BOARD_ORIGIN_X), QSnake::mapToBoard(BOARD_ORIGIN_Y));
    QPointF p2(QSnake::mapToBoard(BOARD_CELL_LENGTH_X), QSnake::mapToBoard(BOARD_CELL_LENGTH_Y));
    p->save();
    p->fillRect(QRectF(p1, p2), BOARD_BACKGROUND_BRUSH);
    p->restore();
}

/**
 * Render the baseline.
 *
 * @param p The active QPainter.
 */
void QSnake::renderBaseline(QPainter *p) {
    QPointF p1(BORDER_SIZE, 0);
    QPointF p2(BORDER_SIZE + BOARD_WIDTH, BORDER_SIZE);
    QPointF p3(BORDER_SIZE, BORDER_SIZE + BOARD_HEIGHT);
    QPointF p4(BORDER_SIZE + BOARD_WIDTH, 2 * BORDER_SIZE + BOARD_HEIGHT);
    QRectF topBar = QRectF(p1, p2);
    QRectF bottomBar = QRectF(p3, p4);
    p->save();
    p->fillRect(rect(), BORDER_BACKGROUND_BRUSH);
    p->setFont(m_font1);
    p->setPen(QPen(BORDER_FOREGROUND_BRUSH.color()));
    p->drawText(topBar, Qt::AlignLeft|Qt::AlignVCenter, QSNAKE_TITLE + " v" + QSNAKE_VERSION);
    p->drawText(topBar, Qt::AlignRight|Qt::AlignVCenter, QString::number(m_score));
    p->drawText(bottomBar, Qt::AlignLeft|Qt::AlignVCenter, TEXT_LEVEL + ": " + QString::number(m_speed));
    p->drawText(bottomBar, Qt::AlignRight|Qt::AlignVCenter, TEXT_RECORD + ": " + QString::number(m_record));
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
 * Render the game over status.
 *
 * @param p The active QPainter.
 */
void QSnake::renderGameOver(QPainter *p) {
    if (m_finished) {
        p->save();
        p->setFont(m_font2);
        p->drawText(rect(), Qt::AlignCenter, TEXT_GAME_OVER);
        p->restore();
    }
}

/**
 * Render the game paused status.
 *
 * @param p The active QPainter.
 */
void QSnake::renderPaused(QPainter *p) {
    if (m_paused && !m_finished) {
        p->save();
        p->setFont(m_font2);
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
 * Restart the game.
 */
void QSnake::restart() {
    m_snake->reset();
    m_food->move(m_snake);
    m_finished = false;
    m_paused = true;
    m_score = 0;
    m_handicap = 0;
    m_timer->setInterval(FRAME_LEVEL_MSEC.value(m_speed));
}

/**
 * Resume the game.
 */
void QSnake::resume() {
    m_paused = false;
    connect(m_timer, SIGNAL(timeout()), this, SLOT(frame()));
}

/**
 * Set the game speed.
 *
 * @param speed The speed level.
 */
void QSnake::setLevel(int speed) {
    m_speed = speed;
    m_settings.setValue("options/level", m_speed);
    restart();
}