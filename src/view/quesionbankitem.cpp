#include "quesionbankitem.h"
#include "ui_quesionbankitem.h"

QuesionBankItem::QuesionBankItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QuesionBankItem)
{
    ui->setupUi(this);
}

QuesionBankItem::~QuesionBankItem()
{
    delete ui;
}
