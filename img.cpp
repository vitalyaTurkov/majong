#include "img.h"
#include "mainwindow.h"
#include <QDebug>

/**
 * @brief Img::Img
 * @param a Код отображаемого элемента.
 */

Img::Img(int a)
{
    mType = a;
    if(a == 0)
        return;
    if(mType != 44)
        setCursor(Qt::PointingHandCursor);
    if(a == 43)
    {
        QPixmap qp;
        qp.load(":/images/play1.png");
        setPixmap(qp);
        trig = false;
        return;
    }
    if(a == 44)
    {
        QPixmap qp;
        qDebug() << qp.load(":/images/win.png");
        setPixmap(qp);
        trig = false;
        return;
    }
    if(a == 45)
    {
        setPixmap(QPixmap(":/images/help.png"));
        trig = false;
        return;
    }
    else
    {
        QString str = QString::number(a);
        str = ":/images/" + str + ".png";
        setPixmap(QPixmap(str));
    }
    trig = false; 
}

void Img::mousePressEvent(QGraphicsSceneMouseEvent *)
{
    if(mType == 43)
    {
        emit start();
        return;
    }
    if(mType == 45)
    {
        emit help();
        return;
    }
    if(mType == 44)
    {
        return;
    }
    setPressure();
}

bool Img::triggered()
{
    return trig;
}

void Img::mDel()
{
    delete this;
}

int Img::type()
{
    return mType;
}

void Img::setPressure()
{
    QString str = QString::number(mType);

    if(trig == false)
    {
        str = ":/images/1." + str + ".png";
        trig = true;
        setPixmap(QPixmap(str));
    }
    else
    {
        str = ":/images/" + str + ".png";
        trig = false;
        setPixmap(QPixmap(str));
    }
}

void Img::setTrig(bool value)
{
    trig = value;
}

void Img::setType(int type)
{
    mType = type;
}

int Img::i() const
{
    return mI;
}

void Img::setI(int i)
{
    mI = i;
}

int Img::j() const
{
    return mJ;
}

void Img::setJ(int j)
{
    mJ = j;
}






