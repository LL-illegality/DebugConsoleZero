#ifndef LOGSAVINGDIALOG_H
#define LOGSAVINGDIALOG_H

#include <QDialog>
#include <QFileDialog>
#include <QAbstractButton>
#include <QVector>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QApplication>
#include "lognode.h"
#include "form.h"

namespace Ui {
class LogSavingDialog;
}

class LogSavingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LogSavingDialog(QWidget *parent = nullptr);
    ~LogSavingDialog();
    void saveLog();
    void getSaveLevel();
    BoolStorage saveLevel;
    QVector<LogNode> *logListPtr;

private slots:
    void on_pushButton_clicked();

    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::LogSavingDialog *ui;
};

#endif // LOGSAVINGDIALOG_H
