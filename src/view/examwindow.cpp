#include "examwindow.h"
#include "ui_examwindow.h"
#include "questionbutton.h"
#include "questionclient.h"
#include "utils.h"
#include "mainwindow.h"

#include "createroomdialog.h"
#include "ui_createroomdialog.h"
#include "../app/request/room.h"

#include "clientmanager.h"
#include "answerhandler.h"
#include "questionhandler.h"

#include <iostream>
#include <math.h>
#include <QPushButton>
#include <QRadioButton>
#include <QTimer>
#include <QTextStream>
#include <QDebug>

using json = nlohmann::json;

ExamWindow::ExamWindow(QWidget *parent, int roomId) :
    QMainWindow(parent),
    roomId(roomId),
    ui(new Ui::ExamWindow)
{
    // load danh sách question
    loadQuestions();

    ui->setupUi(this);
    setWindowTitle("Exam");

    // setup layout cho danh sách Options
    ui->optionList->setSpacing(20);
    ui->optionList->setAlignment(Qt::AlignTop);

    // tạo danh sách question button
    QGridLayout *questionList = ui->gridLayout;
    questionList->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    questionList->setSpacing(30);

    for(int i = 0; i < questions.size(); ++i){
        QuestionButton *button = new QuestionButton(questions[i].questionId, i);
        connect(button, &QuestionButton::override_clicked, this, &ExamWindow::on_questionButton_clicked);
        questionButtons.append(button);
        questionList->addWidget(button, i / 5, i % 5);
    }

    // Hiển thị question đầu tiên trong danh sách
    setupQuestion(questions[0]);

    // khởi tạo đồng hồ đếm ngược
    ui->countdownLabel->setText(Utils::formatTime(remainingTime));
    countdownTimer = new QTimer(this);
    connect(countdownTimer, &QTimer::timeout, this, &ExamWindow::updateCountdown);
    countdownTimer->start(1000);
}

/*
 * Thiết lập / cập nhật giao diện
*/
// handle event click vào mỗi question button trong question button list
void ExamWindow::on_questionButton_clicked(int index){
    currentIndex = index;

    // update ui option list của selected question
    QuestionClient currentQuestion = questions[currentIndex];
    setupQuestion(currentQuestion); /* hiển thị question text và danh sách Options */
    ui->questionNumber->setText(QString::number(index + 1));
}

// Hiển thị question text và danh sách anwser
void ExamWindow::setupQuestion(QuestionClient question){

    // reset ui danh sách option
    QLayoutItem *item;
    while((item = ui->optionList->takeAt(0))){
        if(item->widget()) {
            delete item->widget();
        }
        delete item;
    }

    // Tạo danh sách các câu trả lời gồm OptionsText và RadioButton
    for (const OptionClient& option : question.options) {
        QRadioButton *radioButton = new QRadioButton(option.text, this);
        // style cho radiobutton
        radioButton->setStyleSheet("QRadioButton::indicator {width: 20px; height: 20px;}");
        radioButton->setCursor(Qt::PointingHandCursor);

        // set property index cho radiobutton
        radioButton->setProperty("index", option.optionId);

        if(option.optionId == question.selectedOptionId) {
            radioButton->setChecked(true);
        }

        // connect radiobutton với hàm xử lý click
        connect(radioButton, &QRadioButton::clicked, this, &ExamWindow::handleSelectOption);
        ui->optionList->addWidget(radioButton);
    }

    // Hiển thị nội dung câu hỏi
    ui->questionText->setText(question.questionText);
}

// cập nhật đồng hồ đếm ngược
void ExamWindow::updateCountdown(){
    if(remainingTime > 0) remainingTime--;
    ui->countdownLabel->setText(Utils::formatTime(remainingTime));
    if(remainingTime == 0 && !isReturned) {
        countdownTimer->stop();
        MainWindow *mainWindow = new MainWindow(this);
        mainWindow->show();
    }
}

/*
 * Xử lý các sự kiện
*/
// active question button khi select option
void ExamWindow::handleSelectOption(){
    QRadioButton *clickedRadioButton = qobject_cast<QRadioButton*>(sender());
    QuestionButton *currentQuestionButton = questionButtons[currentIndex];
    QuestionClient question = questions[currentIndex];

    currentQuestionButton->active();
    int optionId = clickedRadioButton->property("index").toInt();
    questions[currentIndex].selectedOptionId = optionId;

    // xử lý gửi lên server
    AnswerHandler answerHandler;
    answerHandler.requestSubmitAnswer(roomId, question.questionId, optionId);
    answerHandler.responseSubmitAnswer();
}

// handle sự kiện xóa câu trả lời đã chọn
void ExamWindow::on_clearButton_clicked()
{
    QuestionClient currentQuestion = questions[currentIndex];
    currentQuestion.selectedOptionId = -1;
    setupQuestion(currentQuestion);
}

// handle sự kiện next question button click
void ExamWindow::on_nextButton_clicked()
{
    QuestionClient nextQuestion;
    if(currentIndex == questions.size() - 1){
        currentIndex = 0;
    } else {
        currentIndex++;
    }
    nextQuestion = questions[currentIndex];
    setupQuestion(nextQuestion);
    ui->questionNumber->setText(QString::number(currentIndex + 1));
}

// handle prev question button
void ExamWindow::on_gobackButton_clicked()
{
    QuestionClient prevQuestion;
    if(currentIndex == 0){
        currentIndex = questions.size() - 1;
    } else {
        currentIndex--;
    }
    prevQuestion = questions[currentIndex];
    setupQuestion(prevQuestion);
    ui->questionNumber->setText(QString::number(currentIndex + 1));
}


/*
 * Xử lý dữ liệu
*/
// load danh sách câu hỏi nhận từ server
void ExamWindow::loadQuestions()
{
//    QuestionClient myQuestion(10, "What is your favorite color?", QVector<OptionClient>{
//                            OptionClient(1, "Red"),
//                            OptionClient(2, "Blue"),
//                            OptionClient(3, "Green")
//                        });
//    QuestionClient myQuestion2(20, "What is your favorite animal?", QVector<OptionClient>{
//                            OptionClient(1, "Dog"),
//                            OptionClient(2, "Cat"),
//                            OptionClient(3, "Bird")
//                        });
//    QuestionClient myQuestion3(30, "What is your favorite subject?", QVector<OptionClient>{
//                            OptionClient(1, "Math"),
//                            OptionClient(2, "Physic"),
//                            OptionClient(3, "Chemistry")
//                        });
//    questions.append(myQuestion);
//    questions.append(myQuestion2);
//    questions.append(myQuestion3);

    QuestionHandler questionHandler;
    questionHandler.requestGetQuestionByRoom(roomId);
    json res = questionHandler.responseGetQuestionByRoom();
    json questionList = res["body"]["questions"];
    for(auto question : questionList) {
        QString title = QString::fromStdString(question["question"]["title"]);
        int questionId = question["question"]["id"];

        json options = question["options"];
        QVector<OptionClient> optionList;
        for(auto option : options) {
            int id = option["id"];
            QString text = QString::fromStdString(option["content"]);
            OptionClient opt = OptionClient(id, text);
                optionList.push_back(opt);
        }
        QuestionClient questionItem(questionId, title, optionList);
        questions.append(questionItem);
    }
}

void ExamWindow::on_submitButton_clicked(){
    isReturned = true;
    emit submitButton_clicked();
}


ExamWindow::~ExamWindow()
{
    delete ui;
}



