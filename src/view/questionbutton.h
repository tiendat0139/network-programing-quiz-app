#ifndef QUESTIONBUTTON_H
#define QUESTIONBUTTON_H

#include <QPushButton>

namespace Ui {
class QuestionButton;
}

class QuestionButton : public QPushButton
{
    Q_OBJECT

public:
    explicit QuestionButton(int questionId, int index, QWidget *parent = nullptr);
    int questionId;
    int index;
    bool answered = false;
    void active();
    void disable();

signals:
    void override_clicked(int index);

private slots:
    void on_override_clicked();
};

#endif // QUESTIONBUTTON_H
