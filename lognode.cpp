#include "lognode.h"
#include <QVector>
#include <QDateTime>

QVector<QString> levelList = {
    "Debug",
    "Info",
    "Warning",
    "Error",
    "Fatal",
    "Command"
};

LogNode::LogNode(levels l, QString s)
{
    level = l;
    information = s;
    QString qstrTime = QDateTime::currentDateTime().toString("hh:mm:ss:zzz");
    logTime = qstrTime;
}

LogNode::~LogNode()
{

}

QString LogNode::format()
{
    QString temp = "[" + logTime + "] [" + levelList[level] + "] " + information;
    return temp;
}

BoolStorage::BoolStorage() : storage(0)
{

}

BoolStorage::~BoolStorage()
{

}

void BoolStorage::setBool(int index, bool value)
{
    if (value) {
        storage |= (1 << index);  // 设置指定位置为 1
    } else {
        storage &= ~(1 << index); // 设置指定位置为 0
    }
}

bool BoolStorage::getBool(int index)
{
    return (storage >> index) & 1;
}
