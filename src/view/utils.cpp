#include "utils.h"

#include <QString>
#include <QTextStream>

Utils::Utils()
{

}

QString Utils::formatTime(int seconds)
{
    int hour = seconds / 3600;
    int minute = (seconds % 3600) / 60;
    int second = seconds % 60;

    QString formatted;
    QTextStream stream(&formatted);

    stream.setFieldWidth(2);
    stream.setPadChar('0');
    stream << hour;

    stream.setFieldWidth(1);
    stream << ":";

    stream.setFieldWidth(2);
    stream.setPadChar('0');
    stream << minute;

    stream.setFieldWidth(1);
    stream << ":";

    stream.setFieldWidth(2);
    stream.setPadChar('0');
    stream << second;
    return formatted;
}






