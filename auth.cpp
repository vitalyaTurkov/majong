#include "auth.h"
#include "ui_auth.h"
#include "reg.h"
#include "mainwindow.h"

#include <QDialog>
#include <QFile>
#include <QDataStream>
#include <QMessageBox>
#include <QDebug>

Auth::Auth(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Auth)
{
    ui->setupUi(this);
    setWindowTitle("Login");
    QFile file("file.bin");

    ui->lineEdit->setText("Enter login");
    ui->lineEdit_2->setText("Enter password");
    this->setFocus();

    QCryptographicHash hash(QCryptographicHash::Md5);
    hash.addData("Admin");
    QString hashStr(hash.result().toHex());

    if(file.open(QIODevice::Append))
    {
        QDataStream stream(&file);
        file.seek(0);
        stream.setVersion (QDataStream::Qt_4_2) ;
        if(stream.atEnd())
        {
            stream << QString("admin") << hashStr;
        }
    }
    file.close();
}

Auth::~Auth()
{
    delete ui;
}

void Auth::on_pushButton_clicked()
{
    QFile file("file.bin");
    if(file.open(QIODevice::ReadOnly))
    {
        QDataStream stream(&file);
        stream.setVersion (QDataStream::Qt_4_2) ;
        while(!stream.atEnd())
        {
            QString buf_1, buf_2;
            stream >> buf_1 >> buf_2;

            QCryptographicHash hash(QCryptographicHash::Md5);
            hash.addData("Admin");
            QString hashStr(hash.result().toHex());

            if(buf_1 == QString("admin") && buf_2 == hashStr && buf_1 == ui->lineEdit->text())
            {
                QMessageBox::about(this, "Authorization is successful.", "Hello Administrator!");
                status = QString("admin");
                userName = "Administrator";
                accept();
                return;
            }
            QString buf_3 = ui->lineEdit_2->text();
            QCryptographicHash hash_2(QCryptographicHash::Md5);
            hash_2.addData(buf_3.toUtf8());
            hashStr = hash_2.result().toHex();

            if(buf_1 == ui->lineEdit->text() && hashStr == buf_2)
            {
                QMessageBox::about(this, "Authorization is successful.", tr("Hello %1!").arg(buf_1));
                status = QString("User");
                userName = ui->lineEdit->text();
                accept();
                return;
            }
        }
        if(stream.status() != QDataStream::Ok)
        {
            qDebug() << "Ошибка чтения файла";
        }
    file.close();
    }

    QMessageBox err;
    err.setText("Not a valid username and password!");
    err.show();
    err.exec();
}

QString Auth::getStatus() const
{
    return status;
}

void QLineEdit::mousePressEvent(QMouseEvent *event)
{
    if(this->text() == "Enter password")
    {
        setEchoMode(Password);
    }
    if(this->text() == "Enter password" || this->text() == "Enter login")
    {
        this->clear();
    }
}


void Auth::on_lineEdit_editingFinished()
{
    if(ui->lineEdit->text() == "")
    {
        ui->lineEdit->setText("Enter login");
    }
}

void Auth::on_lineEdit_2_editingFinished()
{
    if(ui->lineEdit_2->text() == "")
    {
        ui->lineEdit_2->setText("Enter password");
        ui->lineEdit_2->setEchoMode(QLineEdit::Normal);
    }
}

QString Auth::getUserName() const
{
    return userName;
}
