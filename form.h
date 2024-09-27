#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <string>
#include <QTime>
#include <QVector>
#include <QTimer>
#include <QGuiApplication>
#include "logsavingdialog.h"
#include "lognode.h"

#define TIMER_TIMEOUT (50) // mesc

extern QVector<LogNode *> LogList;
extern QVector<QString> cmdHelpList;

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr);
    void dbgPrtf(levels l, std::string s);
    void onCommand(QString s);
    ~Form();
    void (*customCmdEventFunc)(std::string);
    void stopUpdating();
    void startUpdating();
    QTimer *timer;
    QVector<LogNode *> logBuffer;
    bool isLogOutputing;

private slots:
    void on_pushButton_clicked();

    void on_lineEdit_returnPressed();

    void on_Form_destroyed();

    void on_timer_timeout();

private:
    Ui::Form *ui;
    bool isSpeedLimited;
};

#endif // FORM_H
