/*
 * Copyright 2023 Snap One, LLC. All Rights Reserved.
*/
#ifndef FPSCOUNTER_HPP
#define FPSCOUNTER_HPP

#include <QQuickPaintedItem>
#include <QPainter>

class FpsCounter : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(int fps READ fps NOTIFY fpsChanged)

public:
    FpsCounter();

    ~FpsCounter();

    void paint(QPainter *);
    int fps()const;

signals:
    void fpsChanged();

private:
    void recalculateFPS();
    int _currentFPS;
    int _cacheCount;
    QVector<qint64> _times;
    QVector<unsigned> _history;
};

#endif // FPSCOUNTER_HPP
