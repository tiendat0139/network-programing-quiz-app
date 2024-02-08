#ifndef CREATEPRACTICEDIALOG_H
#define CREATEPRACTICEDIALOG_H

#include <QDialog>

namespace Ui {
class CreatePracticeDiaLog;
}

class CreatePracticeDiaLog : public QDialog
{
    Q_OBJECT

public:
    explicit CreatePracticeDiaLog(QWidget *parent = nullptr);
    ~CreatePracticeDiaLog();
    int getRoomId();
private slots:
    void on_levelRadioButton_toggled(bool checked);

    void on_randomLevel_toggled(bool checked);

    void on_submitPushButton_clicked();

    void on_spinBox_valueChanged(int value);

private:
    Ui::CreatePracticeDiaLog *ui;
    int totalScore = 0;
    bool isRandom;
    int roomId;

};

#endif // CREATEPRACTICEDIALOG_H
