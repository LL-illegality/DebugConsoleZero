#include "form.h"
#include "ui_form.h"

QVector<LogNode *> LogList = {};

QVector<QString> cmdHelpList = {
    "clear: clear all the logs on the screen",
    "exit: quit the program",
    "help: show this list",
    "save: save the logs as a .log file",
    "speedswitch: switch the log output speed",
    "User can set more custom commands by using APIs of DebugConsoleZero"
};

Form::Form(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Form)
{
    //customCmdEventFunc = []();
    ui->setupUi(this);
    logBuffer = {};
    isSpeedLimited = false;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(on_timer_timeout()));
    dbgPrtf(info, "DebugConsoleZero developed by LL");
    dbgPrtf(info, "Input \"help\" for help");
    timer->start(TIMER_TIMEOUT);
}

Form::~Form()
{
    if (timer->isActive())
    {
        timer->stop();
    }
    delete timer;
    delete ui;
}

void Form::startUpdating()
{
    this->setUpdatesEnabled(true);
}

void Form::stopUpdating()
{
    this->setUpdatesEnabled(false);
}

void Form::dbgPrtf(levels l, std::string s)
{
    LogNode *pDbg = new LogNode(l, QString::fromStdString(s));
    //LogNode dbg(l, QString::fromStdString(s));
    logBuffer.append(pDbg);
    LogList.append(pDbg);
    return;
}

void Form::onCommand(QString cmd)
{
    if (cmd == "clear")
    {
        ui->plainTextEdit->setPlainText("");
        logBuffer.clear();
        LogList.clear();
    }
    else if (cmd == "exit") {
        exit(0);
    }
    else if (cmd == "help") {
        dbgPrtf(command, "The original commands list:");
        for (int i = 0; i < cmdHelpList.length(); i++)
        {
            dbgPrtf(command, cmdHelpList[i].toStdString());
        }
    }
    else if (cmd == "save") {
        LogSavingDialog logSaving;
        logSaving.logListPtr = &LogList;
        logSaving.show();
        QEventLoop eventLoop;
        QObject::connect(&logSaving, &QDialog::destroyed, &eventLoop, &QEventLoop::quit);
        eventLoop.exec();
    }
    else if (cmd == "speedswitch")
    {
        isSpeedLimited = !isSpeedLimited;
        dbgPrtf(command, "Switched SpeedLimit mode to " + std::to_string(isSpeedLimited));
    }
    else
    {
        if (customCmdEventFunc != nullptr)
        {
            customCmdEventFunc(cmd.toStdString());
        }
        else
        {
            dbgPrtf(command, "Illegal Command: " + cmd.toStdString());
        }
    }
    return;
}

void Form::on_pushButton_clicked()
{
    QString cmdStr = ui->lineEdit->text();
    ui->lineEdit->setText("");
    if (cmdStr.length() != 0)
    {
        dbgPrtf(command, cmdStr.toStdString());
        onCommand(cmdStr);
    }
}


void Form::on_lineEdit_returnPressed()
{
    on_pushButton_clicked();
}


void Form::on_Form_destroyed()
{
    for (LogNode *pNode : LogList)
    {
        delete pNode;
    }
    exit(0);
}


void Form::on_timer_timeout()
{
    if (logBuffer.length() > 0)
    {
        if (isSpeedLimited == false)
        {
            for (int i = 0; i < logBuffer.length(); i++)
            {
                LogNode *pNode = logBuffer[i];
                ui->plainTextEdit->appendPlainText(pNode->format());
            }
            logBuffer.clear();
        }
        else
        {
            int i = 100;
            while (logBuffer.length() > 0 && i > 0)
            {
                LogNode *pNode = logBuffer[0];
                logBuffer.pop_front();
                ui->plainTextEdit->appendPlainText(pNode->format());
                i--;
            }
        }
    }
    startUpdating();
}

