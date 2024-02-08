#ifndef COMPONENT_H
#define COMPONENT_H

#include "adminwindow.h"
#include <QWidget>

class Component
{
public:
    Component();
    static QWidget *userInRoomItem(const QString& name, const QString& email);
    static QWidget *userResultItem(int id = 0, const QString& name = "", const QString& email = "",
                                   int totalQuestion = 0, int correctQuestion = 0, int score = 0);
    static QWidget *categoryItem(AdminWindow *aw);
    static QWidget *historyItem(int id, const QString& examName, const QString& type,
                                const QString& time, int correctNum, int score);
};

#endif // COMPONENT_H
