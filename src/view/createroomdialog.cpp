#include "createroomdialog.h"
#include "ui_createroomdialog.h"

#include <iostream>
#include "createroomdialog.h"
#include "ui_createroomdialog.h"
#include "../app/request/room.h"
#include "roomhandler.h"
#include "categoryhandler.h"

#include <QDebug>

CreateRoomDiaLog::CreateRoomDiaLog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateRoomDiaLog)
{
    ui->setupUi(this);
    setModal(true);
    setWindowTitle("Create Room");

    ui->passwordInput->hide();
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
    qDebug() << categories;
    ui->categoryComboBox->addItems(categories);
}

void CreateRoomDiaLog::on_nextButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void CreateRoomDiaLog::on_createButton_clicked()
{
    bool valid = true;
    QString name = ui->nameLineEdit->text();
    valid = validate("name", name);

    int time_limit = ui->timeSpinBox->value();
    valid = validate("time_limit", time_limit);

    int capacity = ui->capacitySpinBox->value() + 1;
    valid = validate("capacity", capacity);

    bool is_private = false;
    if(ui->privateRadioButton->isChecked()) is_private = true;

    QString password = ui->passwordLineEdit->text();
    if(is_private){
        valid = validate("password", password);
    }
    int category_id = ui->categoryComboBox->currentIndex();

    QVector<int> question_config;
    question_config.push_back(ui->level1SpinBox->value());
    question_config.push_back(ui->level2SpinBox->value());
    question_config.push_back(ui->level3SpinBox->value());
    question_config.push_back(ui->level4SpinBox->value());
    question_config.push_back(ui->level5SpinBox->value());

    QuestionsExam questions_exam;
    questions_exam.category_id = category_id + 1;
    questions_exam.question_config = question_config.toStdVector();

    RequestCreateRoomBody body;
    body.name = name.toStdString();
    body.capacity = capacity;
    body.time_limit = time_limit;
    body.is_private = is_private;
    body.password = password.toStdString();
    body.type = ROOM_EXAM_TYPE;

    RoomHandler roomHandler;
    roomHandler.requestCreateRoom(body, questions_exam);
    json res = roomHandler.responseCreateRoom();

    std::string status = res["status"];
    if(status == SUCCESS) {
        accept();
    }

}

void CreateRoomDiaLog::on_backButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void CreateRoomDiaLog::on_privateRadioButton_clicked()
{
    if(ui->privateRadioButton->isChecked()){
        ui->passwordInput->show();
    } else {
        ui->passwordInput->hide();
    }
}

// listen spinbox change value
void CreateRoomDiaLog::on_spinBox_valueChanged(int value)
{
    QSpinBox *senderSpinBox = qobject_cast<QSpinBox*>(sender());
    QString spinBoxName = senderSpinBox->objectName();

    qDebug() << spinBoxName << " " << value << " " << totalScore;
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
    qDebug() << totalScore;
    ui->totalScoreLabel->setText(QString::number(totalScore));
}

bool CreateRoomDiaLog::validate(const QString& field, const QVariant& value)
{
    if(value.type() == QVariant::Int) {
        int intValue = value.toInt();
        if(field == "level" && (intValue < 0 || intValue > 5)) {
            QMessageBox::critical(nullptr, "Error", "Level only ranges from 1 to 5");
            return false;
        }
        if(field == "time_limit" && intValue < 0) {
            QMessageBox::critical(nullptr, "Error", "Time limit must be greater than 0");
            return false;
        }
        if(field == "capacity" && intValue < 0) {
            QMessageBox::critical(nullptr, "Error", "Capacity must be greater than 0");
            return false;
        }
    }

    if(value.type() == QVariant::String) {
        QString stringValue = value.toString();
        if(field == "name" && stringValue == "") {
            QMessageBox::critical(nullptr, "Error", "Name cannot be blank");
            return false;
        }
        if(field == "password" && stringValue == "") {
            QMessageBox::critical(nullptr, "Error", "Password cannot be blank");
            return false;
        }
    }
    return true;
}

CreateRoomDiaLog::~CreateRoomDiaLog()
{
    delete ui;
}
