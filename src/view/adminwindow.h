#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include "questionclient.h"

#include <QMainWindow>
#include <QVector>

namespace Ui {
class AdminWindow;
}

class AdminWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminWindow(QWidget *parent = nullptr);
    ~AdminWindow();
    void getQuestionByCategory();

    void handleDeleteQuestion(int questionId);

    void handleDeleteUser(int userId);

    void handleBlockUser(int userId);

    void handleUnblockUser(int userId);

    void showUserList();

public slots:
    void handleViewButtonClicked(int categoryId);

private slots:
    void on_addQuestionButton_clicked();

    void on_questionPushButton_clicked();

    void on_userPushButton_clicked();

    void on_logoutButton_clicked();

private:
    QVector<QuestionClient> questions;
    Ui::AdminWindow *ui;
    int selectedCategoryId;
};

#endif // ADMINWINDOW_H
