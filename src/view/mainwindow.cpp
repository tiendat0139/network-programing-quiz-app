#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "roomitem.h"
#include "examwindow.h"
#include "createroomdialog.h"
#include "passworddialog.h"
#include "styles.h"
#include "component.h"
#include "loginwindow.h"
#include "createpracticedialog.h"
#include "practiceitem.h"
#include "clientmanager.h"
#include "../app/comunicate/client.h"
#include "resulthandler.h"
#include "practicehandler.h"
#include "categoryhandler.h"
#include "createroomdialog.h"
#include "ui_createroomdialog.h"
#include "../app/request/room.h"
#include "roomhandler.h"
#include "serverlistener.h"
#include "resulthandler.h"
#include "../app/request/logout.h"
#include <iostream>
#include <pthread.h>
#include <QWidget>
#include <QDebug>
#include <QString>
#include <QtCharts>
#include <QThread>
#include <QVariant>
#include <QLayoutItem>
#include <QCheckBox>

using json = nlohmann::json;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->waitingLabel->hide();
    ui->userList->setAlignment(Qt::AlignTop);
    ui->roomResultList->layout()->setAlignment(Qt::AlignTop);
    ui->roomResultList->layout()->setSpacing(12);
    ui->historyList->layout()->setAlignment(Qt::AlignTop);
    ui->historyList->layout()->setSpacing(12);
    ui->historyChart->layout()->setAlignment(Qt::AlignHCenter);
    ui->roomList->layout()->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    ui->roomList->layout()->setSpacing(20);
    ui->praticeList->layout()->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    ui->praticeList->layout()->setSpacing(12);
    ui->categoryFilterList->setAlignment(Qt::AlignTop);
    ui->categoryFilterList->setSpacing(12);
    ui->cannotFoundLabel->hide();

    getCategoryList();
    getRoomList();

    json currentUser = ClientManager::authUser;
    ui->nameInfoLabel->setText(QString::fromStdString(currentUser["name"]));
    ui->emailInfoLabel->setText(QString::fromStdString(currentUser["email"]));

    RoomHandler roomHandler;
    roomHandler.requestDetailRoom(roomId);
    roomHandler.responseDetailRoom();

    // lấy room list mà user làm owner
    roomHandler.requestListRoomOwner();
    json res = roomHandler.responseListRoomOwner();
    json rooms = res["body"]["rooms"];

    for(auto room : rooms){
        QString roomName = QString::fromStdString(room["name"]);
        int roomOwnerId = room["id"];
        roomListOwnerIds->append(roomOwnerId);
        ui->roomOwnerComboBox->addItem(roomName);
    }
    connect(ui->roomOwnerComboBox , QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::handleOwnerRoomChange);
}

void MainWindow::handleServerResponse(const QString &response, const QVariant &data) {
    // Xử lý phản hồi từ server
    if (response.toLower() == "start") {
        serverListenerThread->terminate();

        while(!serverListenerThread->isFinished()){}

        if(!serverListenerThread->isRunning())
            qDebug() << "thread is stopped";

        if(!isRoomOwner) {
            ui->sidebar->hide();
            ExamWindow *examWindow = new ExamWindow(this, roomId);
            connect(examWindow, &ExamWindow::submitButton_clicked, this, &MainWindow::redirectToMain);
            ui->stackedWidget->addWidget(examWindow);
            ui->stackedWidget->setCurrentWidget(examWindow);
        }
    }

    if(response.toLower() == "userready" || response.toLower() == "userunready") {
        // empty list
        QLayoutItem *item;
        while((item = ui->userList->takeAt(0)) != nullptr){
            delete item;
        }

        if(!data.isNull() && data.canConvert<QVector<QPair<QString, QString>>>()) {
             QVector<QPair<QString, QString>> userList = data.value<QVector<QPair<QString, QString>>>();
             for (int i = 0; i < userList.size(); i++) {
                 QPair<QString, QString> user = userList.at(i);
                 QWidget *userWidget = Component::userInRoomItem(user.first, user.second);
                 ui->userList->addWidget(userWidget);
             }
        }
    }
}

// kiểm tra mật khẩu của room
void MainWindow::checkRoomAcceptPms(int room_id, bool isPrivate)
{
    if(!isPrivate){
        RoomHandler roomHandler;
        roomHandler.requestJoinRoom(roomId, isPrivate, "");

        json joinRes = roomHandler.responseJoinRoom();
        if(joinRes == SUCCESS) {
            roomId = room_id;
            redirectToWaittingRoom();
        }
    } else {
        PasswordDialog *pd = new PasswordDialog(this, room_id, isPrivate);
        pd->show();
        if(pd->exec() == QDialog::Accepted) {
            roomId = room_id;
            redirectToWaittingRoom();
        }
    }
}

// Di chuyển tới màn hình waitting room (signals)
void MainWindow::redirectToWaittingRoom() {
    ui->stackedWidget->setCurrentIndex(1);

    RoomHandler roomHandler;
    roomHandler.requestDetailRoom(roomId);
    json res = roomHandler.responseDetailRoom();
    isRoomOwner = res["body"]["is_owner"];
    if(isRoomOwner) {
            ui->readyButton->setText("START");
    }

    if(isRoomOwner) {
        serverListenerThread = new QThread(this);
        serverListener = new ServerListener();
        serverListener->moveToThread(serverListenerThread);

        connect(serverListenerThread, &QThread::started, serverListener, &ServerListener::startListening);
        connect(serverListenerThread, &QThread::finished, serverListenerThread, &QThread::deleteLater);
        connect(serverListener, &ServerListener::serverResponse, this, &MainWindow::handleServerResponse);

        serverListenerThread->start();
    }
    json room = res["body"]["room"];
    std::string status = room["status"];
    if(status == ROOM_CLOSE_STATUS) ui->readyButton->setText("VIEW RESULT");
}

void MainWindow::redirectToMain(){
    PracticeHandler practiceHandler;
    practiceHandler.requestEndPractice(roomId);
    json res = practiceHandler.responseEndPractice();
    ui->stackedWidget->setCurrentIndex(0);
    ui->sidebar->show();
}

// open model tạo exam
void MainWindow::on_createExamButton_clicked()
{
    CreateRoomDiaLog *crd = new CreateRoomDiaLog(this);
    crd->show();
    if(crd->exec() == QDialog::Accepted) {
        getRoomList();
    }
}

// handle leave room
void MainWindow::on_leaveButton_clicked()
{
    // chuyển về page room list
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_readyButton_clicked()
{
    QString buttonText = ui->readyButton->text();
    if(buttonText == "READY"){
        ui->readyButton->setText("UNREADY");
        ui->waitingLabel->show();
        Styles::unReadyButton(ui->readyButton);

        RoomHandler roomHandler;
        roomHandler.requestReadyRoom(roomId);     // get room id run owner before
        roomHandler.responseReadyRoom();

        serverListenerThread = new QThread(this);
        serverListener = new ServerListener();
        serverListener->moveToThread(serverListenerThread);

        connect(serverListenerThread, &QThread::started, serverListener, &ServerListener::startListening);
        connect(serverListenerThread, &QThread::finished, serverListenerThread, &QThread::deleteLater);
        connect(serverListener, &ServerListener::serverResponse, this, &MainWindow::handleServerResponse);

        serverListenerThread->start();

    } else if(buttonText == "UNREADY"){
        ui->readyButton->setText("READY");
        ui->waitingLabel->hide();

        RoomHandler roomHandler;
        roomHandler.requestUnReadyRoom(roomId);
        roomHandler.responseUnReadyRoom();
    } else if(buttonText == "START") {
        RoomHandler roomHandler;
        roomHandler.requestStartRoom(roomId);
    }
}

void MainWindow::on_createPracticeButton_clicked()
{
    CreatePracticeDiaLog *cpd = new CreatePracticeDiaLog(this);
    cpd->show();
    if(cpd->exec() == QDialog::Accepted) {
        roomId = cpd->getRoomId();
        ui->sidebar->hide();
        ExamWindow *examWindow = new ExamWindow(this, roomId);
        connect(examWindow, &ExamWindow::submitButton_clicked, this, &MainWindow::redirectToMain);
        ui->stackedWidget->addWidget(examWindow);
        ui->stackedWidget->setCurrentWidget(examWindow);
    }
}

void MainWindow::getRoomList(QVector<int> categoryIds, const QString& searchText)
{
    QLayoutItem *item;
    while((item = ui->roomList->layout()->takeAt(0)) != nullptr){
        delete item->widget();
        delete item;
    }

    RoomHandler roomHandler;
    roomHandler.requestListRoom(categoryIds.toStdVector(), "");
    json res = roomHandler.responseListRoom();
    json roomsRes = res["body"]["rooms"];

    if(res["status"] == FAILURE){
        ui->cannotFoundLabel->show();
    } else {
        ui->cannotFoundLabel->hide();
        for(auto roomItem : roomsRes) {
            QString name = QString::fromStdString(roomItem["name"]);
            qDebug() << name;
            int capacity = roomItem["capacity"];
            QString start_time = QString::fromStdString(roomItem["start_time"]);
            int time_limit = roomItem["time_limit"];
            bool is_private = roomItem["is_private"];
            int roomId = roomItem["id"];
            RoomItem *item = new RoomItem(this, roomId, name, capacity, time_limit, start_time, is_private);

            // Kết nối tới signal joinPushButton_clicked của room item
            connect(item, &RoomItem::joinPushButton_clicked, this, &MainWindow::checkRoomAcceptPms);
            ui->roomList->layout()->addWidget(item);
        }
    };
}

void MainWindow::getCategoryList()
{
    CategoryHandler categoryHandler;
    categoryHandler.requestListCategory();
    json res = categoryHandler.responseListCategory();

    json categories = res["body"]["categories"];
    int i = 0;
    for(auto category : categories){
        int id = category["id"];
        QString name = QString::fromStdString(category["name"]);
        QCheckBox *checkbox = new QCheckBox(name);
        checkbox->setProperty("categoryId", id);
        checkbox->setCursor(Qt::PointingHandCursor);
        Styles::checkBoxStyles(checkbox);
        connect(checkbox, &QCheckBox::stateChanged, this, &MainWindow::handleCheckboxChangeState);
        ui->categoryFilterList->addWidget(checkbox);
        i++;
    }
}


void MainWindow::handleCheckboxChangeState(int state)
{
    QCheckBox *checkbox = qobject_cast<QCheckBox*>(sender());
    int categoryId = checkbox->property("categoryId").toInt();
    if(state == Qt::Checked){
        selectedCategoryIds->append(categoryId);
        getRoomList(*selectedCategoryIds, ui->searchLineEdit->text());
    } else {
        selectedCategoryIds->removeAll(categoryId);
        getRoomList(*selectedCategoryIds, ui->searchLineEdit->text());
    }
}

void MainWindow::handleOwnerRoomChange(int index)
{
    qDebug() << "Owner Room: " << index;
}

// xử lý click vào sidebar item
void MainWindow::on_examPushButton_clicked()
{
    Styles::activeSidebarItem(ui->examPushButton);
    Styles::disableSidebarItem(ui->practicePushButton);
    Styles::disableSidebarItem(ui->historyPushButton);
    Styles::disableSidebarItem(ui->statisticButton);
    ui->stackedWidget->setCurrentIndex(0);
    getRoomList();
}

void MainWindow::on_practicePushButton_clicked()
{
    Styles::activeSidebarItem(ui->practicePushButton);
    Styles::disableSidebarItem(ui->examPushButton);
    Styles::disableSidebarItem(ui->historyPushButton);
    Styles::disableSidebarItem(ui->statisticButton);
    ui->stackedWidget->setCurrentIndex(2);

    QWidget *item = new PracticeItem(this, 1, "Test Practice", "Math", 20, 50, 100);
    ui->praticeList->layout()->addWidget(item);
}

void MainWindow::on_logoutButton_clicked()
{
    char buff[BUFF_SIZE];
    json authUser = ClientManager::authUser;
    RequestLogout reqLogout;
    reqLogout.header = authUser;
    sendToServer(reqLogout.toJson().dump().c_str());
    recvFromServer(buff);
    json resLogout = json::parse(buff);
    if(resLogout["status"] == "SUCCESS") {
        ClientManager::authUser = json{};
        hide();
        LoginWindow *lw = new LoginWindow(this);
        lw->show();
    }
}

void MainWindow::on_historyPushButton_clicked()
{
    QLayoutItem *item;
    while((item = ui->historyChart->layout()->takeAt(0)) != nullptr){
        delete item;
    }
    while((item = ui->historyList->layout()->takeAt(0)) != nullptr){
        delete item;
    }

    Styles::activeSidebarItem(ui->historyPushButton);
    Styles::disableSidebarItem(ui->examPushButton);
    Styles::disableSidebarItem(ui->practicePushButton);
    Styles::disableSidebarItem(ui->statisticButton);
    ui->stackedWidget->setCurrentIndex(4);

    ResultHandler resultHandler;
    resultHandler.requestHistoryResult();
    json res = resultHandler.responseHistoryResult();
    json results = res["body"]["historyResults"];

    std::cout << results.dump(4);
    int i = 1;
    QVector<QPair<QString, double>> userResult;
    for(auto result : results) {
        QString examName = QString::fromStdString(result["exam_name"]);
        QString type = QString::fromStdString(result["type"]);
        QString time = QString::fromStdString(result["start_time"]);
        int correctNum = result["number_question_correct"];
        int score = result["score"];
        double average_score = result["average_score"];

        QWidget *item = Component::historyItem(i, examName, type, time, correctNum, score);
        ui->historyList->layout()->addWidget(item);
        userResult.append(qMakePair(time, average_score));
        i++;
    }
    std::reverse(userResult.begin(), userResult.end());
    createBarChart(userResult);
}

void MainWindow::on_statisticButton_clicked()
{
    QLayoutItem *item;
    while((item = ui->roomResultList->layout()->takeAt(0)) != nullptr){
        delete item;
    }
    while((item = ui->spectrumChart->layout()->takeAt(0)) != nullptr){
        delete item;
    }

    Styles::activeSidebarItem(ui->statisticButton);
    Styles::disableSidebarItem(ui->examPushButton);
    Styles::disableSidebarItem(ui->practicePushButton);
    Styles::disableSidebarItem(ui->historyPushButton);
    ui->stackedWidget->setCurrentIndex(5);

    if(!roomListOwnerIds->isEmpty()){
        ResultHandler resultHandler;
        resultHandler.requestRoomResult(roomListOwnerIds->at(0));
        json roomResultRes = resultHandler.responseRoomResult();
        json userOfRoom = roomResultRes["body"]["roomResults"];
        int totalQuestion = roomResultRes["body"]["total_question"];
        json spectrum_scores = roomResultRes["body"]["spectrum_score"];

        int i = 1;
        for(auto user : userOfRoom){
            QString username = QString::fromStdString(user["username"]);
            qDebug() << username;
            QString email = QString::fromStdString(user["email"]);
            int correctQuestion = user["number_question_correct"];
            double finalScore = user["score_scale10"];
            QWidget *userItem = Component::userResultItem(i, username, email, totalQuestion, correctQuestion, finalScore);
            ui->roomResultList->layout()->addWidget(userItem);
            i++;
        }
        QVector<QPair<int, int>> spectrumScore;
        for(auto spectrum_score : spectrum_scores) {
            int score_range = spectrum_score["score_range"];
            int frequency = spectrum_score["frequency"];
            spectrumScore.append(qMakePair(score_range, frequency));
        }
        createSpectrumChart(spectrumScore);
    }
}

void MainWindow::createBarChart(QVector<QPair<QString, double>> results) {
    QtCharts::QBarSeries *series = new QtCharts::QBarSeries();
    QtCharts::QBarSet *set = new QtCharts::QBarSet("Score");

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    for(const auto& result : results) {
        *set << result.second;
        axisX->append(result.first.left(10));
        set->setColor("#00bf9a");
    }
    series->append(set);
    // Tạo biểu đồ cột
    QtCharts::QChart *chart = new QtCharts::QChart();
    chart->addSeries(series);

    QValueAxis *axisY = new QValueAxis();
    axisY->setLabelFormat("%d");
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);

    series->setBarWidth(0.1);
    series->attachAxis(axisX);
    series->attachAxis(axisY);

    // Tạo QChartView và thiết lập biểu đồ
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    chart->setMargins(QMargins(0, 0, 0, 0));
    chart->setBackgroundRoundness(0);
    ui->historyChart->layout()->addWidget(chartView);
}

void MainWindow::createSpectrumChart(QVector<QPair<int, int>> results) {
    QtCharts::QBarSeries *series = new QtCharts::QBarSeries();
    QtCharts::QBarSet *set = new QtCharts::QBarSet("Spectrum score");

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    for(const auto& result : results) {
        *set << result.second;
        axisX->append(QString::number(result.first));
    }
    set->setColor("#00bf9a");
    series->append(set);
    // Tạo biểu đồ cột
    QtCharts::QChart *chart = new QtCharts::QChart();
    chart->addSeries(series);

    QValueAxis *axisY = new QValueAxis();
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);

    series->setBarWidth(0.5);
    series->attachAxis(axisX);
    series->attachAxis(axisY);

    // Tạo QChartView và thiết lập biểu đồ
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    chart->setMargins(QMargins(0, 0, 0, 0));
    chart->setBackgroundRoundness(0);
    ui->spectrumChart->layout()->addWidget(chartView);
}

MainWindow::~MainWindow()
{
    delete ui;
}

