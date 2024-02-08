#ifndef ADDQUESTIONDIALOG_H
#define ADDQUESTIONDIALOG_H

#include <QDialog>
#include <QButtonGroup>
#include <QVector>
#include <QPair>
#include <QLineEdit>

namespace Ui {
class AddQuestionDiaLog;
}

class AddQuestionDiaLog : public QDialog
{
    Q_OBJECT

public:
    explicit AddQuestionDiaLog(QWidget *parent = nullptr, int id = 0);
    ~AddQuestionDiaLog();
    void handleDeleteOption();

private slots:
    void on_addPushButton_clicked();

    void handleSelectAnswer(int id);

    void on_submitPushButton_clicked();

private:
    Ui::AddQuestionDiaLog *ui;
    QButtonGroup *buttonGroup;
    int categoryId;
    int optionCount = 0;
    int answerId = 0;
    QVector<QPair<int, QLineEdit*>> optionInputs;

};

#endif // ADDQUESTIONDIALOG_H
