#include "practiceitem.h"
#include "ui_practiceitem.h"

#include <QString>

PracticeItem::PracticeItem(QWidget *parent, int id, const QString& name,
                           const QString& category, int timeLimit, int numberQuestion, int maxScore) :
    QWidget(parent),
    ui(new Ui::PracticeItem)
{
    ui->setupUi(this);
    ui->idLabel->setText(QString::number(id));
    ui->nameLabel->setText(name);
    ui->categoryLabel->setText(category);
    ui->timeLimitLabel->setText(QString::number(timeLimit));
    ui->numberQuestionLabel->setText(QString::number(numberQuestion));
    ui->maxScoreLabel->setText(QString::number(maxScore));
}

PracticeItem::~PracticeItem()
{
    delete ui;
}
