#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QThread>
#include <QVector>
#include <QPair>
#include "serverlistener.h"

//QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
//QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QWidget* createUserItem();

    QWidget* createResultItem();

    void createBarChart(QVector<QPair<QString, double>> results);

    void getRoomList(QVector<int> categoryIds = QVector<int>(), const QString& searchText = "");

    void redirectToMain();

    void handleCheckboxChangeState(int state);

    void handleOwnerRoomChange(int index);

    void getCategoryList();

    void createSpectrumChart(QVector<QPair<int, int>> results);

public slots:
    void redirectToWaittingRoom();

    void checkRoomAcceptPms(int room_id, bool isPrivate);

    void handleServerResponse(const QString &response, const QVariant &data);

private slots:
    void on_createExamButton_clicked();

    void on_leaveButton_clicked();

    void on_examPushButton_clicked();

    void on_practicePushButton_clicked();

    void on_historyPushButton_clicked();

    void on_readyButton_clicked();

    void on_createPracticeButton_clicked();

    void on_statisticButton_clicked();

    void on_logoutButton_clicked();

private:
    Ui::MainWindow *ui;
    int roomId = 0;
    bool isRoomOwner = false;
    QThread *serverListenerThread;
    ServerListener *serverListener;
    QVector<int> *roomListOwnerIds = new QVector<int>();
    QVector<int> *selectedCategoryIds = new QVector<int>();

};
#endif // MAINWINDOW_H
