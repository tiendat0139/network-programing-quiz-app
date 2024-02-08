#include "questionclient.h"

#include <QString>
#include <QStringList>
#include <QVector>
#include <QPushButton>

QuestionClient::QuestionClient(int id, const QString& questionText, const QVector<OptionClient> &options, int selectedOptionId) :
    questionId(id),
    questionText(questionText),
    options(options),
    selectedOptionId(selectedOptionId)
{

}


// constructor mặc định
QuestionClient::QuestionClient() :
    questionId(0),
    questionText(""),
    options(QVector<OptionClient>()),
    selectedOptionId(-1)
{

}

