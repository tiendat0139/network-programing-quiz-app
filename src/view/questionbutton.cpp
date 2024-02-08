#include "questionbutton.h"

#include<QPushButton>

QuestionButton::QuestionButton(int id, int index, QWidget *parent) :
    QPushButton(parent),
    questionId(id),
    index(index)
{
    setStyleSheet("background-color: #DEE5EF; "
                  "border: none; "
                  "min-height: 46px; "
                  "max-width: 46px; "
                  "min-width: 46px; "
                  "border-radius: 6px; "
                  "font-family: Source Sans 3; "
                  "font-weight: bold; "
                  "color: #67758D; ");
    setCursor(Qt::PointingHandCursor);
    setText(QString::number(index + 1));
    if(answered) active();
    connect(this, &QuestionButton::clicked, this, &QuestionButton::on_override_clicked);
}

void QuestionButton::on_override_clicked()
{
    emit override_clicked(index);
}

void QuestionButton::active()
{
    setStyleSheet("background-color: #009E7F; "
                  "border: none; "
                  "min-height: 46px; "
                  "max-width: 46px; "
                  "min-width: 46px; "
                  "border-radius: 6px; "
                  "font-family: Source Sans 3; "
                  "font-weight: bold; "
                  "color: rgba(255,255,255,0.9)");
}

void QuestionButton::disable()
{
    setStyleSheet("background-color: #DEE5EF; "
                  "border: none; "
                  "min-height: 46px; "
                  "max-width: 46px; "
                  "min-width: 46px; "
                  "border-radius: 6px; "
                  "font-family: Source Sans 3; "
                  "font-weight: bold; "
                  "color: #67758D; ");
}

