#ifndef CreateRoomDiaLog_H
#define CreateRoomDiaLog_H

#include <QDialog>
#include <QVariant>
#include <QMessageBox>

namespace Ui {
class CreateRoomDiaLog;
}

class CreateRoomDiaLog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateRoomDiaLog(QWidget *parent = nullptr);
    ~CreateRoomDiaLog();
    bool validate(const QString& field, const QVariant& value);

private slots:
    void on_nextButton_clicked();

    void on_createButton_clicked();

    void on_backButton_clicked();

    void on_privateRadioButton_clicked();

    void on_spinBox_valueChanged(int value);

private:
    Ui::CreateRoomDiaLog *ui;
    int totalScore = 0;
};

#endif // CreateRoomDiaLog_H
