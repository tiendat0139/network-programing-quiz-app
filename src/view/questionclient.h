#ifndef QUESTIONCLIENT_H
#define QUESTIONCLIENT_H

#include<QString>
#include<QStringList>
#include<QVector>

struct OptionClient {
    int optionId;
    QString text;
    bool isAnswer = false;

    OptionClient() : optionId(0), text("") {}
    OptionClient(int id, const QString& t) : optionId(id), text(t) {}
    OptionClient(int id, const QString &t, bool isAnswer) : optionId(id), text(t), isAnswer(isAnswer) {}
};

class QuestionClient
{
public:
    explicit QuestionClient(int id, const QString& questionText, const QVector<OptionClient>& options, int selectedOption = -1);
    QuestionClient();

    int questionId;
    QString questionText;
    QVector<OptionClient> options;
    int selectedOptionId;
};

#endif // QUESTIONCLIENT_H




