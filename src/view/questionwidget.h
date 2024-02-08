// questionwidget.h
#ifndef QUESTIONWIDGET_H
#define QUESTIONWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QRadioButton>

class QuestionWidget : public QWidget {
    Q_OBJECT

public:
    explicit QuestionWidget(const QString& question, const QStringList& answerOptions, QWidget *parent = nullptr);

private:
    QVBoxLayout *layout;
    QLabel *questionLabel;
    QVector<QRadioButton*> answerRadioButtons;
};

#endif // QUESTIONWIDGET_H
