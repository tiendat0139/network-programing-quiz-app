#ifndef RoomItem_H
#define RoomItem_H

#include <QWidget>

namespace Ui {
class RoomItem;
}

class RoomItem : public QWidget
{
    Q_OBJECT

public:
    explicit RoomItem(QWidget *parent, int roomId = 0,
                      const QString& name = "",
                      int capacity = 0,
                      int time_limit = 0,
                      const QString& start_time = "",
                      bool isPrivate = false);
    ~RoomItem();

signals:
    void joinPushButton_clicked(int room_id, bool isPrivate);

private slots:
    void on_joinPushButton_clicked();

private:
    Ui::RoomItem *ui;
    int roomId;
    bool isPrivate;
    QString password;
};

#endif // RoomItem_H
