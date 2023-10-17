/*
 * Copyright 2023 Snap One, LLC. All Rights Reserved.
*/
#ifndef FPSCOUNTER_HPP
#define FPSCOUNTER_HPP

#include <QQuickPaintedItem>
#include <QPainter>
#include <QTimer>

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

private slots:
    void onSecond();

private:
    void recalculateFPS();
    unsigned _fps;
    unsigned _tempFps;
    QVector<unsigned> _history;

    QTimer _timer;
};

#endif // FPSCOUNTER_HPP
