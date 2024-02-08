#include "adminwindow.h"
#include "ui_adminwindow.h"
#include "categoryitem.h"
#include "questionbankitem.h"
#include "addquestiondialog.h"
#include "useritem.h"
#include "styles.h"
#include "categoryhandler.h"
#include "questionhandler.h"
#include "userhandler.h"

#include <iostream>
#include <QWidget>
#include <QDebug>
#include <QMessageBox>

AdminWindow::AdminWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdminWindow)
{
    ui->setupUi(this);
    ui->categoryList->layout()->setAlignment(Qt::AlignTop);
    ui->questionList->layout()->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    ui->questionList->layout()->setSpacing(12);
    ui->userList->layout()->setAlignment(Qt::AlignTop);
    ui->userList->layout()->setSpacing(12);

    CategoryHandler categoryHandler;
    categoryHandler.requestListCategory();
    json res = categoryHandler.responseListCategory();

    json categories = res["body"]["categories"];
    for(auto category : categories){
        int id = category["id"];
        QString name = QString::fromStdString(category["name"]);
        QString slug = QString::fromStdString(category["slug"]);
        CategoryItem *item = new CategoryItem(this, id, name, slug);
        connect(item, &CategoryItem::viewButton_clicked, this, &AdminWindow::handleViewButtonClicked);
        ui->categoryList->layout()->addWidget(item);
    }

    showUserList();
}

void AdminWindow::handleViewButtonClicked(int categoryId)
{
    // thiết lập id của câu hỏi đang xem vào selectedCategoryId
    selectedCategoryId = categoryId;

    ui->stackedWidget->setCurrentIndex(1);

    getQuestionByCategory();
}

void AdminWindow::on_addQuestionButton_clicked()
{
    AddQuestionDiaLog *aqd = new AddQuestionDiaLog(this, selectedCategoryId);
    aqd->show();
    if(aqd->exec() == QDialog::Accepted) {
        getQuestionByCategory();
    }

}

void AdminWindow::handleDeleteQuestion(int questionId)
{
    qDebug() << "delete question: " << questionId;
    QuestionHandler questionHandler;
    questionHandler.requestDeleteQuestion(questionId);
    json res = questionHandler.responseDeleteQuestion();
}

void AdminWindow::handleDeleteUser(int userId)
{
    QMessageBox::StandardButton confirm;
    confirm = QMessageBox::question(
                this,
                "Confirm user deletion",
                "Are you sure you want to delete this user?",
                QMessageBox::Yes | QMessageBox::No
              );

    if(confirm == QMessageBox::Yes){
        UserHandler userHandler;
        userHandler.requestDeleteUser(userId);
        qDebug() << "delete user: " << userId;
        json res = userHandler.responseDeleteUser();
        if(res["status"] == "SUCCESS"){
            showUserList();
        }
    }
}

void AdminWindow::handleBlockUser(int userId)
{
    QMessageBox::StandardButton confirm;
    confirm = QMessageBox::question(
                this,
                "Confirm user blocking",
                "Are you sure you want to blok this user?",
                QMessageBox::Yes | QMessageBox::No
              );

    if(confirm == QMessageBox::Yes){
        UserHandler userHandler;
        userHandler.requestActiveUser(userId, false);
        qDebug() << "block user: " << userId;
        json res = userHandler.responseActiveUser();
        if(res["status"] == "SUCCESS"){
            showUserList();
        }
    }
}

void AdminWindow::handleUnblockUser(int userId)
{
    UserHandler userHandler;
    userHandler.requestActiveUser(userId, true);
    qDebug() << "block user: " << userId;
    json res = userHandler.responseActiveUser();
    if(res["status"] == "SUCCESS"){
        showUserList();
    }
}

void AdminWindow::showUserList()
{
    // reset user list
    QLayoutItem *item;
    while((item = ui->userList->layout()->takeAt(0))){
        if(item->widget()) {
            delete item->widget();
        }
        delete item;
    }

    UserHandler userHandler;
    userHandler.requestListUser();
    json resUser = userHandler.responseListUser();
    json users = resUser["body"]["users"];
    int index = 1;
    for(auto user : users){
        int id = user["id"];
        QString name = QString::fromStdString(user["name"]);
        QString email = QString::fromStdString(user["email"]);
        int status = user["status"];
        UserItem *item = new UserItem(this, index, id, name, email, status);
        connect(item, &UserItem::deleteButton_clicked, this, &AdminWindow::handleDeleteUser);
        connect(item, &UserItem::blockButton_clicked, this, &AdminWindow::handleBlockUser);
        connect(item, &UserItem::unBlockButton_clicked, this, &AdminWindow::handleUnblockUser);
        ui->userList->layout()->addWidget(item);
        index++;
    }
}


void AdminWindow::getQuestionByCategory()
{
    // get question list from server
    QuestionHandler questionHandler;
    questionHandler.requestGetQuestionByCategory(selectedCategoryId);
    json res = questionHandler.responseGetQuestionByCategory();
    json questionList = res["body"]["questions"];

    for(auto question : questionList) {
        QString title = QString::fromStdString(question["question"]["title"]);
        int questionId = question["question"]["id"];

        json options = question["options"];
        QVector<OptionClient> optionList;
        for(auto option : options) {
            int id = option["id"];
            QString text = QString::fromStdString(option["content"]);
            bool isAnswer = option["correct"];
            OptionClient opt = OptionClient(id, text, isAnswer);
            optionList.push_back(opt);
        }
        QuestionClient questionItem(questionId, title, optionList);
        questions.append(questionItem);
    }

    // display question list
    for (QuestionClient& question : questions) {
        QuestionBankItem *questionBankItem = new QuestionBankItem(this, question);
        connect(questionBankItem, &QuestionBankItem::deleteQuestionButton_clicked, this, &AdminWindow::handleDeleteQuestion);
        ui->questionList->layout()->addWidget(questionBankItem);
    }

//    QuestionClient myQuestion(1, "What is your favorite color?", QVector<OptionClient>{
//                            OptionClient(1, "Red", true),
//                            OptionClient(2, "Blue"),
//                            OptionClient(3, "Green")
//                        });
//    QuestionClient myQuestion2(2, "What is your favorite animal?", QVector<OptionClient>{
//                            OptionClient(1, "Dog", true),
//                            OptionClient(2, "Cat"),
//                            OptionClient(3, "Bird")
//                        });
//    QuestionClient myQuestion3(3, "What is your favorite subject?", QVector<OptionClient>{
//                            OptionClient(1, "Math", true),
//                            OptionClient(2, "Physic"),
//                            OptionClient(3, "Chemistry")
//                        });
//    questions.append(myQuestion);
//    questions.append(myQuestion2);
//    questions.append(myQuestion3);

}
void AdminWindow::on_logoutButton_clicked()
{

}

void AdminWindow::on_questionPushButton_clicked()
{
    Styles::activeSidebarItem(ui->questionPushButton);
    Styles::disableSidebarItem(ui->userPushButton);
    ui->stackedWidget->setCurrentIndex(0);
}

void AdminWindow::on_userPushButton_clicked()
{
    Styles::activeSidebarItem(ui->userPushButton);
    Styles::disableSidebarItem(ui->questionPushButton);
    ui->stackedWidget->setCurrentIndex(2);
}

AdminWindow::~AdminWindow()
{
    delete ui;
}


