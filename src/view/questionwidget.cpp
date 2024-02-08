// questionwidget.cpp
#include "questionwidget.h"

QuestionWidget::QuestionWidget(const QString& question, const QStringList& answerOptions, QWidget *parent)
    : QWidget(parent) {

    layout = new QVBoxLayout(this);

    questionLabel = new QLabel(question, this);
    layout->addWidget(questionLabel);

    for (const QString& answer : answerOptions) {
        QRadioButton *radioButton = new QRadioButton(answer, this);
        answerRadioButtons.push_back(radioButton);
        layout->addWidget(radioButton);
    }
}
