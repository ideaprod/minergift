#include "conf.h"


Conf::Conf(QString fileName)
{
    this->fileName = fileName;
    this->initConf(this->fileName);
}

void Conf::initConf(QString fileName)
{
    QString result;
    loadFile(result, fileName);
    readConfFromFile(result);
}

void Conf::loadFile(QString result, QString fileName)
{
    this->confFile.setFileName(fileName);
    if(this->confFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        result = this->confFile.readAll();
        this->confFile.close();
    }
    else
    {
        qDebug() << "Could not open file: " << this->fileName;
        this->loadDefaultConf();
    }
}

void Conf::readConfFromFile(QString result)
{
    QJsonDocument confJson = QJsonDocument::fromJson(result.toUtf8());
    if (!confJson.isNull())
    {
        QJsonObject sett2 = confJson.object();
        QJsonValue value = sett2.value(QString("miner"));
        this->minerJson = value.toObject();
    }
    else
    {
        qDebug() << "Could not parse: " << this->fileName;
        this->loadDefaultConf();
    }
}

void Conf::loadDefaultConf()
{
    qDebug() << "ToDo";
}

QString Conf::value(QString key)
{
    QString result;
    QJsonValue jsonValue = this->minerJson[key];
    result = jsonValue.toString();
    return result;
}

