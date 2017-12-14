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
    Conf();
    QString value(QString key);
private:
    QString fileName;
    QFile confFile;
    QJsonObject minerJson;

    void initConf(QString fileName = 0);
    void loadFile(QString result, QString fileName);
};

#endif // CONF_H
