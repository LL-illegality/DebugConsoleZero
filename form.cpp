#include "form.h"
#include "ui_form.h"

QVector<LogNode> LogList = {};

QVector<QString> cmdHelpList = {
    "clear: clear all the logs on the screen",
    "exit: quit the program",
    "help: show this list",
    "save: save the logs as a .log file",
    "User can set more custom commands by using APIs of DebugConsoleZero"
};

Form::Form(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Form)
{
    //customCmdEventFunc = []();
    ui->setupUi(this);
    logBuffer = {};
    isLogOutputing = false;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(on_timer_timeout()));
    dbgPrtf(info, "DebugConsoleZero developed by LL");
    dbgPrtf(info, "Input \"help\" for help");
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
    isLogOutputing = false;
    this->setUpdatesEnabled(true);
}

void Form::stopUpdating()
{
    isLogOutputing = true;
    this->setUpdatesEnabled(false);
}

void Form::dbgPrtf(levels l, std::string s)
{
    LogNode dbg(l, QString::fromStdString(s));
    logBuffer.append(dbg);
    stopUpdating();
    if (timer->isActive() == false)
    {
        timer->start(TIMER_TIMEOUT);
    }
    return;
}

void Form::onCommand(QString cmd)
{
    if (cmd == "clear")
    {
        ui->plainTextEdit->setPlainText("");
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
    exit(0);
}


void Form::on_timer_timeout()
{
    if (isLogOutputing == true)
    {
        for (int i = 0; i < logBuffer.length(); i++)
        {
            LogNode log = logBuffer[i];
            LogList.append(log);
            ui->plainTextEdit->appendPlainText(log.format());
        }
        ui->plainTextEdit->moveCursor(QTextCursor::End);
        logBuffer.clear();
        //QGuiApplication::processEvents();
        startUpdating();
        this->repaint();
        QCoreApplication::processEvents();
        return;
    }
    // if (timer->isActive())
    // {
    //     timer->stop();
    // }
}

