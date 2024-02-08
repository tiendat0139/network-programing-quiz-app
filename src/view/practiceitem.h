#ifndef PRACTICEITEM_H
#define PRACTICEITEM_H

#include <QWidget>

namespace Ui {
class PracticeItem;
}

class PracticeItem : public QWidget
{
    Q_OBJECT

public:
    explicit PracticeItem(QWidget *parent, int id, const QString& name,
                          const QString& category, int timeLimit, int numberQuestion, int maxScore);
    ~PracticeItem();

private:
    Ui::PracticeItem *ui;
};

#endif // PRACTICEITEM_H
