#ifndef LOBBYWINDOW_H
#define LOBBYWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QWidget>

namespace Ui {
class LobbyWindow;
}

class LobbyWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LobbyWindow(QWidget *parent = nullptr, const QString &room_id = nullptr);
    ~LobbyWindow();
    QWidget* createUserItem();

private:
    Ui::LobbyWindow *ui;
};

#endif // LOBBYWINDOW_H
