#include "createroom.h"
#include "ui_createroom.h"

#include <QString>
#include <QStringList>
#include <QDebug>

CreateRoom::CreateRoom(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CreateRoom)
{
    ui->setupUi(this);
    ui->passwordInput->hide();
    QStringList categories = QStringList() << "caterogy 1" << "category 2" << "category 3";
    ui->categoryComboBox->addItems(categories);
}

CreateRoom::~CreateRoom()
{
    delete ui;
}

void CreateRoom::on_nextButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

// handle tạo phòng thi
void CreateRoom::on_createButton_clicked()
{
    QString name = ui->nameLineEdit->text();
    int time_limit = ui->timeSpinBox->value();
    int capacity = ui->capacitySpinBox->value();
    bool is_private = false;
    if(ui->privateRadioButton->isChecked()) is_private = true;
    QString password = ui->passwordLineEdit->text();
    int category_id = ui->categoryComboBox->currentIndex();
    QVector<int> question_config;
    question_config.push_back(ui->level1SpinBox->value());
    question_config.push_back(ui->level2SpinBox->value());
    question_config.push_back(ui->level3SpinBox->value());
    question_config.push_back(ui->level4SpinBox->value());
    question_config.push_back(ui->level5SpinBox->value());


}

// handle back button clicked
void CreateRoom::on_backButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

// show / hide passwordInput khi check private radiobutton
void CreateRoom::on_privateRadioButton_clicked()
{
    if(ui->privateRadioButton->isChecked()){
        ui->passwordInput->show();
    } else {
        ui->passwordInput->hide();
    }
}

// handle close modal
void CreateRoom::on_closeModalPushButton_clicked()
{
    this->hide();
}
