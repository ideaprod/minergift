#ifndef CONF_H
#define CONF_H

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonParseError>
#include <QDebug>

class Conf
{
public:
    Conf(QString fileName);
    QString value(QString key);
private:
    QString fileName;
    QFile confFile;
    QJsonObject minerJson;

    void initConf(QString fileName);
    QString loadFile(QString fileName);
    void loadDefaultConf();
    void readConfFromFile(QString result);
};

#endif // CONF_H
