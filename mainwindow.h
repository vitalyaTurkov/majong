#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QCryptographicHash>

#include "img.h"
#include "savedialog.h"
#include "user.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QString status, QString userName, QWidget *parent = 0);
    void newGame();
    void keyPressEvent(QKeyEvent *e);
    void setBoard(int size1, int size2);
    QVector<int> isExternalRow(int i, int j);
    bool boolFind(int e);

    int check(QVector<int> a, QVector<int> b);
    bool check_2(int i1, int j1, int i2, int j2);
    int check_3(int i1, int j1, int i2, int j2);
    int check_4(int i1, int j1, int i2, int j2);

    void saveLeader();

    ~MainWindow();

private slots:
    void on_actionStart_triggered();
    void on_timer_timeout();
    void on_actionAdd_User_triggered();
    void on_actionSave_triggered();
    void help();
    void on_actionComputer_triggered();


    void on_actionLeaders_triggered();

    void on_actionGame_rools_triggered();

    void on_actionNew_users_triggered();

    void on_actionHard_triggered();

    void on_actionNormal_triggered();

    void on_actionEasy_triggered();

private:
    Ui::MainWindow *ui;
    QVector<QVector<Img*>> mVec;
    QGraphicsScene *scene;
    QTimer * timer;
    QTime * mTime;
    QString mStatus;
    QVector<QVector<int>> mVecTypes;
    SaveDialog *save;
    QVector<QGraphicsLineItem*> lines;
    bool escape;
    int mCount;
    bool computerStart;
    QString mUserName;
    QList<user> mUsers;
    int countVariants;
    int maxSize_1;
    int maxSize_2;
};

#endif // MAINWINDOW_H
