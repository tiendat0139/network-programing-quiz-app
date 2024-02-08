#ifndef EXAMWINDOW_H
#define EXAMWINDOW_H

#include "questionclient.h"
#include "questionbutton.h"

#include <QMainWindow>
#include <QVector>
#include <QPair>

namespace Ui {
class ExamWindow;
}

class ExamWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ExamWindow(QWidget *parent = nullptr, int roomId = 0);
    ~ExamWindow();
    void loadQuestions();
    void setupQuestion(QuestionClient question);
    void handleSelectOption();
    void countdown();
    void on_questionButton_clicked(int index);

private slots:

    void updateCountdown();

    void on_clearButton_clicked();

    void on_nextButton_clicked();

    void on_gobackButton_clicked();

    void on_submitButton_clicked();

signals:
    void submitButton_clicked();

private:
    QVector<QuestionClient> questions;
    QVector<QuestionButton*> questionButtons;
    int currentIndex = 0;
    int remainingTime = 60;
    int roomId;
    bool isReturned = false;
    QTimer *countdownTimer;
    Ui::ExamWindow *ui;
};

#endif // EXAMWINDOW_H
