#ifndef QUESTIONBANKITEM_H
#define QUESTIONBANKITEM_H

#include <QWidget>
#include <questionclient.h>

namespace Ui {
class QuestionBankItem;
}

class QuestionBankItem : public QWidget
{
    Q_OBJECT

public:
    explicit QuestionBankItem(QWidget *parent = nullptr, const QuestionClient& question = QuestionClient());
    ~QuestionBankItem();

private slots:
    void on_deleteQuestionButton_clicked();

signals:
    void deleteQuestionButton_clicked(int questionId);
private:
    Ui::QuestionBankItem *ui;
    QuestionClient question;
};

#endif // QUESTIONBANKITEM_H
