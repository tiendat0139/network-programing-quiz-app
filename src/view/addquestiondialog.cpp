#include "addquestiondialog.h"
#include "ui_addquestiondialog.h"
#include "questionhandler.h"
#include <QRadioButton>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QWidget>
#include <QIcon>
#include <QPushButton>
#include <QDebug>

AddQuestionDiaLog::AddQuestionDiaLog(QWidget *parent, int id) :
    QDialog(parent),
    ui(new Ui::AddQuestionDiaLog)
{
    categoryId = id;
    ui->setupUi(this);
    ui->optionList->layout()->setAlignment(Qt::AlignTop);
    setModal(true);
    setWindowTitle("Add Question");

    buttonGroup = new QButtonGroup(this);
    connect(buttonGroup, SIGNAL(buttonClicked(int)), this, SLOT(handleSelectAnswer(int)));
}

// thêm một option input
void AddQuestionDiaLog::on_addPushButton_clicked()
{
    optionCount++;
    QWidget* container = new QWidget;
    QHBoxLayout *layout = new QHBoxLayout(container);

    // thêm radio button
    QRadioButton *radioButton = new QRadioButton();
    radioButton->setStyleSheet("QRadioButton::indicator {width: 20px; height: 20px;}");
    radioButton->setCursor(Qt::PointingHandCursor);
    radioButton->setProperty("index", optionCount);
    buttonGroup->addButton(radioButton);

    // thêm ô input
    QLineEdit *lineEdit = new QLineEdit();
    optionInputs.append(qMakePair(optionCount, lineEdit));

    // thêm icon xóa item
    QIcon delIcon(":/img/img/delete.svg");
    QPushButton *delButton = new QPushButton();
    delButton->setProperty("index", optionCount);
    delButton->setStyleSheet("border: none; ");
    delButton->setCursor(Qt::PointingHandCursor);
    delButton->setIcon(delIcon);
    connect(delButton, &QPushButton::clicked, this, &AddQuestionDiaLog::handleDeleteOption);

    layout->addWidget(radioButton);
    layout->addWidget(lineEdit);
    layout->addWidget(delButton);
    container->setMinimumHeight(30);
    ui->optionList->layout()->addWidget(container);
}

// xử lý sự kiện chọn đáp án trong các option
void AddQuestionDiaLog::handleSelectAnswer(int id)
{
    QRadioButton *clickedButton = dynamic_cast<QRadioButton*>(buttonGroup->button(id));
    answerId = clickedButton->property("index").toInt();
}

void AddQuestionDiaLog::handleDeleteOption()
{
    QPushButton *deleteButton = qobject_cast<QPushButton*>(sender());
    int deletedItemId = deleteButton->property("index").toInt();
    QWidget *itemWidget = deleteButton->parentWidget();

    // xóa qlineEdit trong optionInputs
    for(int i = 0; i < optionInputs.size(); ++i) {
        const QPair<int, QLineEdit>& pair = optionInputs.at(i);
        if(pair.first == deletedItemId){
            optionInputs.remove(i);
            break;
        }
    }

    // xóa lineEdit phía ui
    ui->optionList->layout()->removeWidget(itemWidget);
    delete itemWidget;
}

// xử lý submit
void AddQuestionDiaLog::on_submitPushButton_clicked()
{
    QString title = ui->titleLineEdit->text();
    int level = ui->levelSpinBox->value();
    QVector<QPair<QString, bool>> options;

    for(int i = 0; i < optionInputs.size(); ++i) {
        const QPair<int, QLineEdit*>& item = optionInputs.at(i);
        bool isAnswer = false;
        if(item.first == answerId) isAnswer = true;
        options.append(qMakePair(item.second->text(), isAnswer));
    }
    qDebug() << title << level << categoryId;
    for(int i = 0; i < options.size(); i++){
        qDebug() << options.at(i).first << options.at(i).second;
    }

    RequestCreateQuestionBody body;
    body.title = title.toStdString();
    body.level = level;
    body.category_id = categoryId;

    std::vector<std::pair<std::string, bool>> optionsReq;
    for(int i = 0; i < options.size(); i++){
        optionsReq.push_back(std::make_pair(options.at(i).first.toStdString(), options.at(i).second));
    }
    body.options = optionsReq;
    QuestionHandler questionHandler;
    questionHandler.requestCreateQuestion(body);
    json res = questionHandler.responseCreateQuestion();
    if(res["status"] == "SUCCESS"){
        accept();
    }
}

AddQuestionDiaLog::~AddQuestionDiaLog()
{
    delete ui;
}
