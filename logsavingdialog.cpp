#include "logsavingdialog.h"
#include "ui_logsavingdialog.h"

LogSavingDialog::LogSavingDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LogSavingDialog)
{
    ui->setupUi(this);
    logListPtr = nullptr;
}

LogSavingDialog::~LogSavingDialog()
{
    delete ui;
    delete logListPtr;
}

void LogSavingDialog::on_pushButton_clicked()
{
    QString path = QFileDialog::getSaveFileName(this, "保存文件", ".\\", "*.log (日志文件)");
    if (path != "")
    {
        ui->lineEdit->setText(path);
    }
}

void LogSavingDialog::getSaveLevel()
{
    saveLevel.setBool(0, ui->isdebug->isChecked());
    saveLevel.setBool(1, ui->isinfo->isChecked());
    saveLevel.setBool(2, ui->iswarning->isChecked());
    saveLevel.setBool(3, ui->iserror->isChecked());
    saveLevel.setBool(4, ui->isfatal->isChecked());
    saveLevel.setBool(5, ui->iscommand->isChecked());
}

void LogSavingDialog::saveLog()
{
    QString path = ui->lineEdit->text();
    QString currentDate = QDateTime::currentDateTime().toString("yyyy-MM-dd");
    path.replace("{date}", currentDate);
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QMessageBox::critical(this, "错误", "无法打开文件，错误信息：" + file.errorString());
        return;
    }
    getSaveLevel();
    QTextStream out(&file);
    int length = (*logListPtr).length();
    ui->progressBar->setMaximum(length);
    for (int i = 0; i < length; i++)
    {
        LogNode *pNode = (*logListPtr)[i];
        if (saveLevel.getBool(pNode->level) == true)
        {
            out << pNode->format() + "\n";
        }
        ui->progressBar->setValue(i);
        QCoreApplication::processEvents();
    }
    file.close();
    QMessageBox::information(this, "文件保存成功", "日志以输出至 " + path);
    return;
}

void LogSavingDialog::on_buttonBox_clicked(QAbstractButton *button)
{
    QDialogButtonBox::StandardButton standardButton = ui->buttonBox->standardButton(button);
    switch (standardButton)
    {
    case QDialogButtonBox::Ok:
        //TODO: save the log
        saveLog();
        break;
    case QDialogButtonBox::Cancel:
        this->destroy();
    }
}

