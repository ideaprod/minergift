#ifndef CONF_H
#define CONF_H

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
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
    void loadFile(QString result, QString fileName);
    void loadDefaultConf();
    void readConfFromFile(QString result);
};

#endif // CONF_H
