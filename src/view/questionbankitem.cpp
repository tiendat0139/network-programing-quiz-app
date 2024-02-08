#include "questionbankitem.h"
#include "ui_questionbankitem.h"

#include <QHBoxLayout>
#include <QPixmap>
#include <QLabel>
#include <QIcon>
#include <QWidget>

QuestionBankItem::QuestionBankItem(QWidget *parent, const QuestionClient& question) :
    QWidget(parent),
    ui(new Ui::QuestionBankItem),
    question(question)

{
    ui->setupUi(this);
    ui->optionList->setAlignment(Qt::AlignTop);
    ui->optionList->setSpacing(10);
    QIcon tickIcon(":/img/img/tick.svg");

    ui->questionTextLabel->setText(question.questionText);

    for (const OptionClient& option : question.options) {
        QHBoxLayout *layout = new QHBoxLayout();
        layout->setAlignment(Qt::AlignTop | Qt::AlignLeft);

        QLabel *icon = new QLabel("");
        icon->setMinimumWidth(20);
        if(option.isAnswer) icon->setPixmap(tickIcon.pixmap(20, 20));

        QLabel *text = new QLabel(option.text);
        text->setStyleSheet("font-family: Source Sans 3; ");

        layout->addWidget(icon);
        layout->addWidget(text);

        ui->optionList->addLayout(layout);
    }
}

void QuestionBankItem::on_deleteQuestionButton_clicked()
{
    emit deleteQuestionButton_clicked(question.questionId);
}

QuestionBankItem::~QuestionBankItem()
{
    delete ui;
}


