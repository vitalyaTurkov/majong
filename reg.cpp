#include "reg.h"
#include "ui_reg.h"
#include <QFile>
#include <QDebug>
#include <QMessageBox>
#include <QCryptographicHash>

Reg::Reg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Reg)
{
    ui->setupUi(this);
}

Reg::~Reg()
{
    delete ui;
}



void Reg::on_pushButton_clicked()
{
    if(ui->lineEdit_4->text().toInt() <= 0 || ui->lineEdit_4->text().toInt() > 100)
    {
        QMessageBox err;
        err.setText("Incorrect age!");
        err.show();
        err.exec();
        return;
    }
    if (ui->lineEdit->text() == "")
    {
        QMessageBox err;
        err.setText("Enter login!");
        err.show();
        err.exec();
        return;
    }

    if (ui->lineEdit_2->text() == "" || ui->lineEdit_3->text() == "")
    {
        QMessageBox err;
        err.setText("Enter password!");
        err.show();
        err.exec();
        return;
    }

    if (ui->lineEdit_2->text() != ui->lineEdit_3->text())
    {
        QMessageBox err;
        err.setText("Passwords do not match!");
        err.show();
        err.exec();
        return;
    }

    QFile file_1("file.bin");
    if(file_1.open(QIODevice::ReadOnly))
    {
        QString buf_1;
        QDataStream stream_1(&file_1);
        while(!stream_1.atEnd())
        {
            stream_1 >> buf_1;
            if(buf_1 == ui->lineEdit->text())
            {
                QMessageBox err;
                err.setText("This login is already in use!");
                err.show();
                err.exec();
                return;
            }
            stream_1 >> buf_1;
        }
        if(stream_1.status() != QDataStream::Ok)
        {
            qDebug() << "Ошибка чтения";
        }
    }
    file_1.close();

    QCryptographicHash hash_1(QCryptographicHash::Md5);
    hash_1.addData(ui->lineEdit_2->text().toUtf8());
    QString hashStr(hash_1.result().toHex());

    QFile file("file.bin");
    if(file.open(QIODevice::Append))
    {
        QDataStream stream(&file);
        stream << ui->lineEdit->text() << hashStr;
        if(stream.status() != QDataStream::Ok)
        {
            qDebug() << "Ошибка записи";
        }
    }
    file.close();

    mUser.setLogin(ui->lineEdit->text());
    mUser.setPassword(ui->lineEdit_2->text());
    mUser.setYear(ui->lineEdit_4->text().toInt());
    mUser.setExp(ui->comboBox->currentText());

    accept();

}

user Reg::lUser() const
{
    return mUser;
}



