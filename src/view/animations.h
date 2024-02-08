#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include <QObject>

class Animations
{
public:
    Animations();
    static void moveBothX(QObject *target, int duration, int distance);
};

#endif // ANIMATIONS_H
