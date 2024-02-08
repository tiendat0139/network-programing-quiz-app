#ifndef QUESIONBANKITEM_H
#define QUESIONBANKITEM_H

#include <QWidget>

namespace Ui {
class QuesionBankItem;
}

class QuesionBankItem : public QWidget
{
    Q_OBJECT

public:
    explicit QuesionBankItem(QWidget *parent = nullptr);
    ~QuesionBankItem();

private:
    Ui::QuesionBankItem *ui;
};

#endif // QUESIONBANKITEM_H
