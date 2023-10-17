/*
 *
 * Copyright 2023 Snap One, LLC. All Rights Reserved.
*/
#include "FpsCounter.hpp"
#include <QDateTime>
#include <QFile>

const int SECOND = 1000;

FpsCounter::FpsCounter(): QQuickPaintedItem(), _fps(0), _tempFps(0)
{
    setFlag(QQuickItem::ItemHasContents);
    connect(&_timer, &QTimer::timeout, this, &FpsCounter::onSecond);

    _timer.setInterval(SECOND);
    _timer.setSingleShot(false);
    _timer.start();
}

FpsCounter::~FpsCounter()
{
    QFile file("fps_result.csv");
    if (file.open(QFile::WriteOnly | QFile::Text))
    {
        QTextStream out(&file);
        out << "second, fps\n";

        for (unsigned i = 0; i < _history.size(); i++)
        {
            out << i << "," << _history[i]<<"\n";
        }
    }
}

void FpsCounter::paint(QPainter *painter)
{
    _tempFps++;

    QBrush brush(Qt::black);

    painter->setBrush(brush);
    painter->setPen(Qt::NoPen);
    painter->setRenderHint(QPainter::Antialiasing);
    painter->drawRoundedRect(0, 0, boundingRect().width(), boundingRect().height(), 0, 0);
    update();
}

int FpsCounter::fps() const
{
    return _fps;
}

void FpsCounter::onSecond()
{
    _fps = _tempFps;

    _history.push_back(_fps);

    Q_EMIT fpsChanged();

    _tempFps = 0;
}
