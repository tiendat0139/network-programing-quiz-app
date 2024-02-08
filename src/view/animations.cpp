#include "animations.h"

#include <QObject>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QRect>
#include <QParallelAnimationGroup>

Animations::Animations()
{

}
void Animations::moveBothX(QObject *target, int duration, int distance)
{
    QRect currentRect = target->property("geometry").toRect();

    QRect leftRect = currentRect.translated(-distance, 0);
    QRect rightRect = currentRect.translated(distance, 0);

    QPropertyAnimation *leftAnimation = new QPropertyAnimation(target, "geometry");
    leftAnimation->setDuration(duration);
    leftAnimation->setStartValue(currentRect);
    leftAnimation->setEndValue(leftRect);

    QPropertyAnimation *rightAnimation = new QPropertyAnimation(target, "geometry");
    rightAnimation->setDuration(duration);
    rightAnimation->setStartValue(currentRect);
    rightAnimation->setEndValue(rightRect);

    QPropertyAnimation *returnFromLeftAnimation = new QPropertyAnimation(target, "geometry");
    returnFromLeftAnimation->setDuration(duration);
    returnFromLeftAnimation->setStartValue(leftRect);
    returnFromLeftAnimation->setEndValue(currentRect);

    QPropertyAnimation *returnFromRightAnimation = new QPropertyAnimation(target, "geometry");
    returnFromRightAnimation->setDuration(duration);
    returnFromRightAnimation->setStartValue(rightRect);
    returnFromRightAnimation->setEndValue(currentRect);


    QSequentialAnimationGroup *oscillationGroup = new QSequentialAnimationGroup;
    oscillationGroup->addAnimation(leftAnimation);
    oscillationGroup->addAnimation(returnFromLeftAnimation);
    oscillationGroup->addAnimation(rightAnimation);
    oscillationGroup->addAnimation(returnFromRightAnimation);
    oscillationGroup->addAnimation(leftAnimation);
    oscillationGroup->addAnimation(returnFromLeftAnimation);
    oscillationGroup->addAnimation(rightAnimation);
    oscillationGroup->addAnimation(returnFromRightAnimation);

    oscillationGroup->start();
}
