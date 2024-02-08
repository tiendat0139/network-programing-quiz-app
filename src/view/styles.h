#ifndef STYLES_H
#define STYLES_H


#include <QPushButton>
#include <QLabel>
#include <QWidget>
#include <QCheckBox>

class Styles
{
public:
    Styles();
    static void questionButtonActive(QPushButton *button);
    static void questionButtonDisable(QPushButton *button);
    static void questionButtonStyle(QPushButton *button);
    static void activeSidebarItem(QPushButton *button);
    static void disableSidebarItem(QPushButton *button);
    static void unReadyButton(QPushButton *button);
    static void readyButton(QPushButton *button);
    static void tableHead(QLabel *thead, int hStretch);
    static void tableHeadButton(QWidget *thead, int hStretch);
    static void activeStatus(QLabel *label);
    static void blockStatus(QLabel *label);
    static void checkBoxStyles(QCheckBox *checkbox);
};

#endif // STYLES_H
