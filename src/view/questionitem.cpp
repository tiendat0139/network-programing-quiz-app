#include "questionitem.h"

#include <QDebug>

QuestionItem::QuestionItem(const QStringList& answerOptions, QWidget *parent)
    : QWidget(parent) {

    // tạo layout chứa danh sách answer
    layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignTop);
    layout->setSpacing(16);

    // Tạo danh sách các câu trả lời gồm radiobutton và text
    for (int i = 0; i < answerOptions.size(); i++) {
        QRadioButton *radioButton = new QRadioButton(answerOptions.at(i), this);
        // style cho radiobutton
        radioButton->setStyleSheet("QRadioButton::indicator {width: 24px; height: 24px;}");
        radioButton->setCursor(Qt::PointingHandCursor);

        // set property index cho radiobutton
        radioButton->setProperty("index", i);

        // kết nối event radiobutton clicked với hàm handle clicked event
        connect(radioButton, &QRadioButton::clicked, this, &QuestionItem::on_answerRadioButton_clicked);

        // add radiobutton vào vector answerRadioButtons
        answerRadioButtons.push_back(radioButton);
        layout->addWidget(radioButton);
    }
}

// handle click vào mỗi answer
void QuestionItem::on_answerRadioButton_clicked() {
    QRadioButton *clickedButton = qobject_cast<QRadioButton*>(sender());
    if(clickedButton) {
        qDebug() << clickedButton->property("index").toInt();
    }
}
