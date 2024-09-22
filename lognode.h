#ifndef LOGNODE_H
#define LOGNODE_H

#include <QObject>

extern QVector<QString> levelList;

enum levels {
    debug,
    info,
    warning,
    error,
    fatal,
    command
};

class LogNode
{
public:
    LogNode(levels l, QString s);
    ~LogNode();
    QString format();
    QString logTime;
    levels level;
    QString information;
};

class BoolStorage
{
public:
    BoolStorage();
    ~BoolStorage();
    void setBool(int index, bool value);
    bool getBool(int index);
private:
    int storage;
};

#endif // LOGNODE_H
