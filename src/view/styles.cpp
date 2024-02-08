#include "styles.h"

#include <QSizePolicy>

Styles::Styles()
{

}

void Styles::questionButtonActive(QPushButton *button)
{
    button->setStyleSheet("border: none; "
                          "min-height: 46px; "
                          "max-width: 46px; "
                          "min-width: 46px; "
                          "border-radius: 6px; "
                          "font-family: Source Sans 3; "
                          "font-weight: bold; "
                          "color: rgba(255,255,255,0.9)");
}

void Styles::questionButtonDisable(QPushButton *button)
{
    button->setStyleSheet("background-color: #DEE5EF; "
                          "border: none; "
                          "min-height: 46px; "
                          "max-width: 46px; "
                          "min-width: 46px; "
                          "border-radius: 6px; "
                          "font-family: Source Sans 3; "
                          "font-weight: bold; "
                          "color: #67758D; ");
}

void Styles::questionButtonStyle(QPushButton *button)
{
    button->setStyleSheet("background-color: #DEE5EF; "
                          "border: none; "
                          "min-height: 46px; "
                          "max-width: 46px; "
                          "min-width: 46px; "
                          "border-radius: 6px; "
                          "font-family: Source Sans 3; "
                          "font-weight: bold; "
                          "color: #67758D; ");
}

void Styles::activeSidebarItem(QPushButton *button)
{
    button->setStyleSheet("background-color: rgb(0, 191, 154); "
                          "border-radius: 8px; "
                          "border: none; "
                          "color: #fff;"
                          "text-align: left; "
                          "padding-left: 20px; ");
}

void Styles::disableSidebarItem(QPushButton *button)
{
    button->setStyleSheet("background: none; "
                          "border-radius: 8px; "
                          "color: #fff; "
                          "text-align: left; "
                          "padding-left: 20px; ");
}

void Styles::unReadyButton(QPushButton *button)
{
    button->setStyleSheet("background-color: rgb(225, 193, 7); "
                          "border: none; "
                          "color: #000; "
                          "border-radius: 25px;" );
}

void Styles::readyButton(QPushButton *button)
{
    button->setStyleSheet("background-color: rgb(9, 44, 76); "
                          "border: none; "
                          "color: #fff; "
                          "border-radius: 25px; ");
}


void Styles::tableHead(QLabel *thead, int hStretch)
{
    thead->setStyleSheet("font-family: Source Sans 3; ");
    QSizePolicy policy = thead->sizePolicy();
    policy.setHorizontalStretch(hStretch);
    thead->setSizePolicy(policy);
}

void Styles::tableHeadButton(QWidget *thead, int hStretch)
{
    QSizePolicy policy = thead->sizePolicy();
    policy.setHorizontalStretch(hStretch);
    thead->setSizePolicy(policy);
}

void Styles::activeStatus(QLabel *label)
{
    label->setStyleSheet("color: #00bf9a");
}

void Styles::blockStatus(QLabel *label)
{
    label->setStyleSheet("color: #ff0000");
}

void Styles::checkBoxStyles(QCheckBox *checkbox)
{
    QString styleSheet = "QCheckBox {"
                         "    font-family: Source Sans 3;"
                         "    border: none;"
                         "}"
                         "QCheckBox::indicator {"
                         "    width: 20px;"
                         "    height: 20px;"
                         "}";
    checkbox->setStyleSheet(styleSheet);
}
