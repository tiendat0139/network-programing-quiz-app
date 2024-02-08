#include "component.h"
#include "styles.h"
#include "adminwindow.h"

#include <QHBoxLayout>
#include <QWidget>
#include <QSizePolicy>
#include <QIcon>
#include <QPushButton>

Component::Component()
{

}

QWidget* Component::userInRoomItem(const QString& name, const QString& email)
{
    QWidget* container = new QWidget;

    QHBoxLayout* userLayout = new QHBoxLayout(container);
    QLabel* idLabel = new QLabel("1");
    Styles::tableHead(idLabel, 1);

    QLabel* nameLabel = new QLabel(name);
    Styles::tableHead(nameLabel, 4);

    QLabel* emailLabel = new QLabel(email);
    Styles::tableHead(emailLabel, 7);

    userLayout->addWidget(idLabel);
    userLayout->addWidget(nameLabel);
    userLayout->addWidget(emailLabel);

    container->setLayout(userLayout);
    container->setStyleSheet("background-color: #fff; "
                             "border-radius: 4px; ");
    return container;
}

// tạo useritem trong danh sách user của màn thống kê kết quả
QWidget* Component::userResultItem(int id, const QString& name, const QString& email, int totalQuestion, int correctQuestion, int score)
{
    QWidget* container = new QWidget;

    QHBoxLayout* resultLayout = new QHBoxLayout(container);
    QLabel* idLabel = new QLabel(QString::number(id));
    Styles::tableHead(idLabel, 1);

    QLabel* nameLabel = new QLabel(name);
    Styles::tableHead(nameLabel, 3);

    QLabel* emailLabel = new QLabel(email);
    Styles::tableHead(emailLabel, 3);

    QLabel* totalLabel = new QLabel(QString::number(totalQuestion));
    Styles::tableHead(totalLabel, 2);

    QLabel* correctLabel = new QLabel(QString::number(correctQuestion));
    Styles::tableHead(correctLabel, 2);

    QLabel* scoreLabel = new QLabel(QString::number(score));
    Styles::tableHead(scoreLabel, 2);

    resultLayout->addWidget(idLabel);
    resultLayout->addWidget(nameLabel);
    resultLayout->addWidget(emailLabel);
    resultLayout->addWidget(totalLabel);
    resultLayout->addWidget(correctLabel);
    resultLayout->addWidget(scoreLabel);

    container->setLayout(resultLayout);

    container->setStyleSheet("background-color: #fff; "
                             "border-radius: 4px; ");
    return container;
}

QWidget* Component::historyItem(int id, const QString& examName, const QString& type,
                                const QString& time, int correctNum, int score)
{
    QWidget* container = new QWidget;

    QHBoxLayout* resultLayout = new QHBoxLayout(container);
    QLabel* idLabel = new QLabel(QString::number(id));
    Styles::tableHead(idLabel, 1);

    QLabel* examNameLabel = new QLabel(examName);
    Styles::tableHead(examNameLabel, 3);

    QLabel* typeLabel = new QLabel(type);
    Styles::tableHead(typeLabel, 2);

    QLabel* timeLabel = new QLabel(time);
    Styles::tableHead(timeLabel, 3);

    QLabel* correctLabel = new QLabel(QString::number(correctNum));
    Styles::tableHead(correctLabel, 2);

    QLabel* scoreLabel = new QLabel(QString::number(score));
    Styles::tableHead(scoreLabel, 2);

    resultLayout->addWidget(idLabel);
    resultLayout->addWidget(examNameLabel);
    resultLayout->addWidget(typeLabel);
    resultLayout->addWidget(timeLabel);
    resultLayout->addWidget(correctLabel);
    resultLayout->addWidget(scoreLabel);

    container->setLayout(resultLayout);

    container->setStyleSheet("background-color: #fff; "
                             "border-radius: 4px; ");
    return container;
}


