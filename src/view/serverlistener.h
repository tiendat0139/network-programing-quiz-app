#ifndef SERVERLISTENER_H
#define SERVERLISTENER_H

#include <QObject>
#include <QVariant>

#include "../../library/json.hpp"

using json = nlohmann::json;


class ServerListener : public QObject
{
    Q_OBJECT
public:
    explicit ServerListener(QObject *parent = nullptr);

public slots:
    void startListening();

signals:
    void serverResponse(const QString &response, const QVariant &userList = QVariant());
};

#endif // SERVERLISTENER_H
