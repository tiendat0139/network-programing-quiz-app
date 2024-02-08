#include "createpracticedialog.h"
#include "ui_createpracticedialog.h"

#include <QScreen>
#include <QWidget>
#include <QGuiApplication>

#include "../app/request/room.h"
#include "roomhandler.h"
#include "categoryhandler.h"
#include "practicehandler.h"

CreatePracticeDiaLog::CreatePracticeDiaLog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreatePracticeDiaLog)
{
    ui->setupUi(this);
    setModal(true);
    setWindowTitle("Practice Information");
    ui->levelRadioButton->setChecked(true);

    connect(ui->level1SpinBox, SIGNAL(valueChanged(int)), this, SLOT(on_spinBox_valueChanged(int)));
    connect(ui->level2SpinBox, SIGNAL(valueChanged(int)), this, SLOT(on_spinBox_valueChanged(int)));
    connect(ui->level3SpinBox, SIGNAL(valueChanged(int)), this, SLOT(on_spinBox_valueChanged(int)));
    connect(ui->level4SpinBox, SIGNAL(valueChanged(int)), this, SLOT(on_spinBox_valueChanged(int)));
    connect(ui->level5SpinBox, SIGNAL(valueChanged(int)), this, SLOT(on_spinBox_valueChanged(int)));

    totalScore = 0;

    QStringList categories;

    CategoryHandler categoryHandler;
    categoryHandler.requestListCategory();
    json res = categoryHandler.responseListCategory();


    json categoriesRes = res["body"]["categories"];
    for (auto category : categoriesRes) {
        categories.append(QString::fromStdString(category["name"]));
    }

    ui->categoryComboBox->addItems(categories);
}

void CreatePracticeDiaLog::on_levelRadioButton_toggled(bool checked)
{
    setFixedHeight(360);
    if(checked) ui->levelGroup->show();
    isRandom = false;
}

void CreatePracticeDiaLog::on_randomLevel_toggled(bool checked)
{
    if(checked) ui->levelGroup->hide();
    setFixedHeight(297);
    isRandom = true;
}

void CreatePracticeDiaLog::on_submitPushButton_clicked()
{
    QString name = ui->nameLineEdit->text();
    int time_limit = ui->timeSpinBox->value();
    int category_id = ui->categoryComboBox->currentIndex() + 1;

    if(isRandom){
        PracticeHandler practiceHandler;
        practiceHandler.requestCreatePractice(category_id, name.toStdString(), time_limit);
        json res = practiceHandler.responseCreatePractice();
        int room_id = res["body"]["room"]["id"];

        practiceHandler.requestStartPractice(room_id);
        json resStart = practiceHandler.responseStartPractice();
        std::string status = resStart["status"];
        if(status == SUCCESS) {
            roomId = room_id;
            accept();
        }
    } else {
        QVector<int> question_config;
        question_config.push_back(ui->level1SpinBox->value());
        question_config.push_back(ui->level2SpinBox->value());
        question_config.push_back(ui->level3SpinBox->value());
        question_config.push_back(ui->level4SpinBox->value());
        question_config.push_back(ui->level5SpinBox->value());

        QuestionsExam questions_exam;
        questions_exam.category_id = category_id;
        questions_exam.question_config = question_config.toStdVector();

        RequestCreateRoomBody body;
        body.name = name.toStdString();
        body.capacity = 10;
        body.time_limit = time_limit;
        body.is_private = false;
        body.password = "";
        body.type = ROOM_PRACTICE_TYPE;

        RoomHandler roomHandler;
        roomHandler.requestCreateRoom(body, questions_exam);
        json res = roomHandler.responseCreateRoom();

        std::string status = res["status"];
        if(status == SUCCESS) {
            accept();
        }
    }

}

// listen spinbox change value
void CreatePracticeDiaLog::on_spinBox_valueChanged(int value)
{
    QSpinBox *senderSpinBox = qobject_cast<QSpinBox*>(sender());
    QString spinBoxName = senderSpinBox->objectName();

    if (spinBoxName == "level1SpinBox") {
        totalScore += value * 1;
    } else if (spinBoxName == "level2SpinBox") {
        totalScore += value * 2;
    } else if (spinBoxName == "level3SpinBox") {
        totalScore += value * 3;
    } else if (spinBoxName == "level4SpinBox") {
        totalScore += value * 4;
    } else if (spinBoxName == "level5SpinBox") {
        totalScore += value * 5;
    }
}

int CreatePracticeDiaLog::getRoomId(){
    return roomId;
}

CreatePracticeDiaLog::~CreatePracticeDiaLog()
{
    delete ui;
}
