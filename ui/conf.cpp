#include "conf.h"


Conf::Conf()
{
    this->fileName= "./miner.json";
    this->initConf(this->fileName);
}

void Conf::initConf(QString fileName)
{
    QString result;
    this->confFile.setFileName(fileName);
    this->confFile.open(QIODevice::ReadOnly | QIODevice::Text);
    result = this->confFile.readAll();
    this->confFile.close();
    QJsonDocument confJson = QJsonDocument::fromJson(result.toUtf8());
    QJsonObject sett2 = confJson.object();
    QJsonValue value = sett2.value(QString("miner"));
    this->minerJson = value.toObject();
}

QString Conf::value(QString key)
{
    QString result;
    QJsonValue jsonValue = this->minerJson[key];
    result = jsonValue.toString();
    return result;
}

/*
  {
   "miner": {
      "description": "SomeDescription",
      "message": "SomeMessage"
   }
}
*/

