#ifndef IMG_H
#define IMG_H

#include <QObject>
#include <QWidget>
#include <QtWidgets>

class Img :public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Img(int);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    bool triggered();
    void mDel();
    int type();
    void setPressure();
    void setTrig(bool value);
    void setType(int type);
    int i() const;
    void setI(int i);
    int j() const;
    void setJ(int j);

private:
    bool trig;
    int mType;
    int mI;
    int mJ;

signals:
    void start();
    void help();
};

#endif // IMG_H
