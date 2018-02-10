#include "savedialog.h"
#include "ui_savedialog.h"

#include <QtWidgets>

SaveDialog::SaveDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SaveDialog)
{
    ui->setupUi(this);
}

SaveDialog::~SaveDialog()
{
    delete ui;
}

void SaveDialog::on_pushButton_clicked()
{
    QFile file("save.bin");
    if(file.open(QIODevice::WriteOnly))
    {
        QDataStream stream(&file);
        for(int i = 0; i < mVec.size(); i++)
        {
            for(int j = 0; j < mVec[i].size(); j++)
            {
                stream << mVec[i][j];
            }
        }
    }
    this->close();
}

void SaveDialog::setVec(const QVector<QVector<int> > &vec)
{
    mVec = vec;
}

void SaveDialog::on_pushButton_2_clicked()
{
    QFile file("save.bin");
    if(file.open(QIODevice::ReadOnly))
    {
        QDataStream stream(&file);
        for(int i = 0; i < mVec.size(); i++)
        {
            for(int j = 0; j < mVec[i].size(); j++)
            {
                stream >> mVec[i][j];
            }
        }
    }
    accept();
}

QVector<QVector<int> > SaveDialog::vec() const
{
    return mVec;
}
