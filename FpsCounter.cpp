/*
 *
 * Copyright 2023 Snap One, LLC. All Rights Reserved.
*/
#include "FpsCounter.hpp"
#include <QDateTime>

const int SECOND = 1000;

FpsCounter::FpsCounter(): QQuickPaintedItem(), _currentFPS(0), _cacheCount(0)
{
    _times.clear();
    setFlag(QQuickItem::ItemHasContents);
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
    qint64 currentTime = QDateTime::currentDateTime().toMSecsSinceEpoch();
    _times.push_back(currentTime);

    while (_times[0] < currentTime - SECOND)
    {
        _times.pop_front();
    }

    int currentCount = _times.length();
    _currentFPS = (currentCount + _cacheCount) / 2;

    if (currentCount != _cacheCount)
    {
        _history.push_back(_currentFPS);
        Q_EMIT fpsChanged();
    }

    _cacheCount = currentCount;

    QBrush brush(Qt::black);

    painter->setBrush(brush);
    painter->setPen(Qt::NoPen);
    painter->setRenderHint(QPainter::Antialiasing);
    painter->drawRoundedRect(0, 0, boundingRect().width(), boundingRect().height(), 0, 0);
    update();
}

int FpsCounter::fps() const
{
    return _currentFPS;
}
