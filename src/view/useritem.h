#ifndef USERITEM_H
#define USERITEM_H

#include <QWidget>

namespace Ui {
class UserItem;
}

class UserItem : public QWidget
{
    Q_OBJECT

public:
    explicit UserItem(QWidget *parent = nullptr, int index = 0, int user_id = 0,
                      const QString& name = "", const QString& email = "", int status = 1);
    ~UserItem();

private slots:
    void on_deleteButton_clicked();

    void on_unBlockButton_clicked();

    void on_blockButton_clicked();

signals:
    void deleteButton_clicked(int userId);

    void blockButton_clicked(int userId);

    void unBlockButton_clicked(int userId);

private:
    Ui::UserItem *ui;
    int userId = 0;
};

#endif // USERITEM_H
