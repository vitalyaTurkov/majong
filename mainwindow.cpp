#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "img.h"
#include "reg.h"
#include "savedialog.h"


MainWindow::MainWindow(QString status, QString userName, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mStatus(status),
    mCount(0)
{
    ui->setupUi(this);

    mUserName = userName;

    timer = new QTimer;
    mTime = new QTime(0,0);

    escape = false;

    this->setWindowFlags(Qt::WindowCloseButtonHint);

    ui->lineEdit->setReadOnly(true);


    if(mStatus == QString("User"))
    {
        ui->actionAdd_User->setEnabled(false);
    }
    save = new SaveDialog;
    computerStart = false;

    mVecTypes.resize(10);
    for(int i = 0; i < 10; i++)
    {
        mVecTypes[i].resize(20);
    }

    scene = new QGraphicsScene(0, 0, ui->graphicsView->viewport()->width(), ui->graphicsView->viewport()->height());

    Img *start = new Img(43);
    scene->addItem(start);

    start->setPos(-200, -50);
    ui->graphicsView->setScene(scene);

    connect(timer,SIGNAL(timeout()),this,SLOT(on_timer_timeout()));
    connect(start, SIGNAL(start()), this, SLOT(on_actionStart_triggered()));

    maxSize_1 = 10;
    maxSize_2 = 20;
}

/**
 * @brief MainWindow::newGame
 * Инициализируем сцену и заполняем ее карточками.
 */

void MainWindow::newGame()
{
    mCount = 0;
    int type;
    int x = maxSize_2;
    int y = maxSize_1;
    scene = new QGraphicsScene(0, 0, ui->graphicsView->viewport()->width(), ui->graphicsView->viewport()->height());
    ui->graphicsView->setScene(scene);

    Img *imgHelp = new Img(45);
    scene->addItem(imgHelp);
    imgHelp->setPos(1000, 500);
    connect(imgHelp, SIGNAL(help()), this, SLOT(help()));

    mVec.resize(x);
    for(int i = 0; i < x; i ++)
    {
        mVec[i].resize(y);
        for (int j = 0; j < y; j++)
        {
            type = mVecTypes[j][i];

            Img *a = new Img(type);
            scene->addItem(a);
            a->setPos(350 + i * 609/(x), 42 + j * 537/(y));

            mVec[i][j] = a;
            a->setI(i);
            a->setJ(j);
            if(type != 0)
               mCount++;
        }
    }
    mTime->start();
    timer->start();
    ui->lineEdit->setText(tr("count %1").arg(mCount));
}

/**
 * @brief MainWindow::boolFind
 * Проверка на присутствие в матрице элементов со значением e.
 * @param e
 * @return true если e присутствует.
 */
bool MainWindow::boolFind(int e)
{
    int a = 0;
    for(int i = 0; i < mVecTypes.size(); i++)
        for(int j = 0; j < mVecTypes[i].size(); j++)
        {
            if (mVecTypes[i][j] == e)
            {
                return true;
            }
        }
    return false;
}

/**
 * @brief MainWindow::check
 * @param a Вектор, в котором хранятся данные в какую сторону имеет доступ карточка.
 * @param b Вектор, в котором хранятся данные в какую сторону имеет доступ карточка.
 * @return Возвращает сторону, к которой имеют доступ обе карточки.
 */

int MainWindow::check(QVector<int> a, QVector<int> b)
{
    for(int i = 0; i < a.size(); i++)
    {
        for(int j = 0; j < b.size(); j++)
        {
            if(a[i] == b[j])
            {
                return a[i];
            }
        }
    }
    return -1;
}

/**
 * @brief MainWindow::check_2
 * Проверка на возможность соединения карточки прямой линией.
 * Также происходит создание линий по пути обхода.
 * @param i1 Координаты карточки 1.
 * @param j1
 * @param i2 Координаты карточки 2.
 * @param j2
 * @return Возвращает true, если мы можем соединить две карточки прямой линией.
 */

bool MainWindow::check_2(int i1, int j1, int i2, int j2)
{
    QGraphicsLineItem *line = new QGraphicsLineItem;
    QPen pen(Qt::green);
    pen.setWidth(6);
    line->setPen(pen);

    int i = i1, j = j1;
    if(j1 == j2)
    {
        if(i < i2)
        {
            while(i != i2 && i < i2)
            {
                i++;
                if(mVecTypes[i][j] != 0 && i != i2)
                {
                    return false;
                }
            }

            line->setLine(j1 * 30 + 375, 60 + 54 * i1, j2 * 30 + 375, 60 + 54 * i2);
            scene->addItem(line);
            lines.push_back(line);
            return true;
        }
        if (i > i2)
        {
            while(i != i2 && i > i2)
            {
                i--;
                if(mVecTypes[i][j] != 0 && i != i2)
                {
                    return false;
                }
            }
            line->setLine(j1 * 30 + 375, 60 + 54 * i1, j2 * 30 + 375, 60 + 54 * i2);
            scene->addItem(line);
            lines.push_back(line);
            return true;
        }
    }
    if(i1 == i2)
    {
        if(j < j2)
        {
            while(j != j2 && j < j2)
            {
                j++;
                if(mVecTypes[i1][j] != 0 && j != j2)
                {
                    return false;
                }
            }
            line->setLine(j1 * 30 + 375, 60 + 54 * i1, j2 * 30 + 375, 60 + 54 * i2);
            scene->addItem(line);
            lines.push_back(line);
            return true;
        }
        if (j > j2)
        {
            while(j != j2 && j > j2)
            {
                j--;
                if(mVecTypes[i1][j] != 0 && j != j2)
                {
                    return false;
                }
            }
            line->setLine(j1 * 30 + 375, 60 + 54 * i1, j2 * 30 + 375, 60 + 54 * i2);
            scene->addItem(line);
            lines.push_back(line);
            return true;
        }
    }
    return false;
}

/**
 * @brief MainWindow::setBoard
 * Генирируем матрицу чисел, по которой потом будет заполнять сцену карточками.
 * Выбираем два случайных свободных места, ставим туда два числа и проверям можем ли мы их соединить,
 * если можем, то продолжаем снова.
 * @param size1, size2 Размеры поля
 */

void MainWindow::setBoard(int size1, int size2)
{
    srand ( time(NULL) );

    if(size1 == maxSize_1 + 2)
    {
        return;
    }
    QVector<QVector<int>> vec_1(size1, QVector<int>(size2, 0));
    for(int i = 1, i_1 = 0; i < vec_1.size() - 1; i++, i_1++)
    {
        for(int j = 1, j_1 = 0; j < vec_1[i].size() - 1; j++, j_1++)
        {
            vec_1[i][j] = mVecTypes[i_1][j_1];
        }
    }
    mVecTypes = vec_1;
    int iter = 0;
    int i1, j1, i2, j2, type;
    while(boolFind(0) && iter < 150)
    {
        type = rand() % 42 + 1;
        i1 = rand() % size1;
        j1 = rand() % size2;
        while(mVecTypes[i1][j1] != 0)
        {
            i1 = rand() % size1;
            j1 = rand() % size2;
        }

        mVecTypes[i1][j1] = type;
        i2 = rand() % size1;
        j2 = rand() % size2;
        while(mVecTypes[i2][j2] != 0)
        {
            i2 = rand() % size1;
            j2 = rand() % size2;
        }
         mVecTypes[i2][j2] = type;

         if(check(isExternalRow(i1, j1), isExternalRow(i2, j2)) == -1)
         {
             mVecTypes[i1][j1] = 0;
             mVecTypes[i2][j2] = 0;
         }
         iter++;
    }

    setBoard(size1 + 2, size2 + 2);
}

/**
 * @brief MainWindow::isExternalRow
 * @param i Координаты карточки в матрице.
 * @param j
 * @return Возвращает вектор сторон, к которым карточка имеет доступ, то есть не закрыта другой карточкой.
 */

QVector<int> MainWindow::isExternalRow(int i, int j)
{
    QVector<int> rezult;

    int i1 = i;
    int j1 = j;
    while(i < mVecTypes.size())
    {
        i++;
        if(i == mVecTypes.size())
        {
            rezult.push_back(1);
            break;
        }

        if(mVecTypes[i][j] != 0)
        {
            break;
        }
    }

    i = i1;

    while(i >= 0)
    {
        if(i == 0)
        {
            rezult.push_back(2);
            break;
        }
        i--;

        if(mVecTypes[i][j] != 0)
        {
            break;
        }
    }

    i = i1;

    while(j < mVecTypes[0].size())
    {
        j++;
        if(j == mVecTypes[0].size())
        {
            rezult.push_back(3);
            break;
        }
        if(mVecTypes[i][j] != 0)
        {
            break;
        }
    }

    j = j1;

    while(j >= 0)
    {
        if(j == 0)
        {
            rezult.push_back(4);
            break;
        }
        j--;

        if(mVecTypes[i][j] != 0)
        {
            break;
        }
    }

    return rezult;
}

/**
 * @brief MainWindow::on_actionStart_triggered
 * Слот, который активизируется при нажатии на кнопку старт в меню.
 */

void MainWindow::on_actionStart_triggered()
{
    setBoard(2, 12);
    newGame();
}

/**
 * @brief MainWindow::on_timer_timeout
 * Метод запускается каждую секунду, обновляет отображение статистики
 * и в нем происходит проверка на то есть ли выбранные карточки и верно ли они выбраны.
 */

void MainWindow::on_timer_timeout()
{   
    ui->lineEdit->setText(tr("Осталось карточек: %1       Время игры: %2 секунд").arg(mCount).arg(int(mTime->elapsed() * 0.001)));
    int count = 0;
    QVector<Img*> buf;
    for (int i = 0; i < mVec.size(); i++)
    {
        for(int j = 0; j < mVec[i].size(); j++)
        {
            if(mVec[i][j]->triggered() == true)   //Проверка на нажатие на карточку, если нажата
            {                                     //, то добавляем ее в буферный вектор.
                buf.push_back(mVec[i][j]);
                count++;
            }
        }
    }
    if(count != 0)                  //если одна карточка уже нажата, то ищем вторую и проверяем одинакове ли они.
    {                               //если нет, то отжимаем карточки.
        for (int i = 0; i < mVec.size(); i++)
            for(int j = 0; j < mVec[i].size(); j++)
            {
                if(mVec[i][j]->triggered() == true && mVec[i][j]->type() == buf[0]->type() && mVec[i][j] != buf[0])
                {
                    buf.push_back(mVec[i][j]);
                    count++;
                }
                if(mVec[i][j]->triggered() == true && mVec[i][j]->type() != buf[0]->type())
                {
                    mVec[i][j]->setPressure();
                    buf[0]->setPressure();
                }

            }
    }

    if(count == 3)                                    //Если нашли две одинаковые, нажатые карточки,
    {                                                 //то начинаем проверять можем ли мы соединить их.
        QGraphicsLineItem *line_1, *line_2, *line_3;
        int checkRezult = -1;
        line_1 = new QGraphicsLineItem;
        line_2 = new QGraphicsLineItem;
        line_3 = new QGraphicsLineItem;

        if(check_2(buf[0]->j(), buf[0]->i(), buf[1]->j(), buf[1]->i()))
            checkRezult = 5;
        if (checkRezult == -1)
        {
            checkRezult = check_4(buf[0]->j(), buf[0]->i(), buf[1]->j(), buf[1]->i());
            if(checkRezult == -1)
                checkRezult = 0;
            else
                checkRezult = 6;
        }
        if (checkRezult == 0)
        {
           checkRezult = check(isExternalRow(buf[0]->j(), buf[0]->i()), isExternalRow(buf[1]->j(), buf[1]->i()));
        }
        if(checkRezult != -1 && !isExternalRow(buf[0]->j(), buf[0]->i()).isEmpty()
                && !isExternalRow(buf[1]->j(), buf[1]->i()).isEmpty())
        {
            scene->removeItem(buf[0]);
            scene->removeItem(buf[1]);
            buf[0]->setTrig(false);
            buf[1]->setTrig(false);
            buf[0]->setType(0);
            buf[1]->setType(0);
            mVecTypes[buf[0]->j()][buf[0]->i()] = 0;
            mVecTypes[buf[1]->j()][buf[1]->i()] = 0;
            mCount -= 2;
            QPen pen(Qt::green);
            pen.setWidth(6);

            if(checkRezult == 3)
            {
                //Отрисовка линий
                line_1->setLine(buf[0]->pos().x() + 20, buf[0]->pos().y() + 18, 400 + (20) * 609/(20), buf[0]->pos().y() + 18);
                line_1->setPen(pen);
                scene->addItem(line_1);
                line_2->setLine(buf[1]->pos().x() + 20, buf[1]->pos().y() + 18, 400 + (20) * 609/(20), buf[1]->pos().y() + 18);
                line_2->setPen(pen);
                scene->addItem(line_2);
                line_3->setLine(400 + (20) * 609/(20), buf[0]->pos().y() + 18, 400 + (20) * 609/(20), buf[1]->pos().y() + 18);
                line_3->setPen(pen);
                scene->addItem(line_3);
            }
            if(checkRezult == 1)
            {
                line_1->setLine(buf[0]->pos().x() + 20, buf[0]->pos().y() + 18, buf[0]->pos().x() + 20, 80 + (10) * 537/10);
                line_1->setPen(pen);
                scene->addItem(line_1);
                line_2->setLine(buf[1]->pos().x() + 20, buf[1]->pos().y() + 18, buf[1]->pos().x() + 20, 80 + (10) * 537/10);
                line_2->setPen(pen);
                scene->addItem(line_2);
                line_3->setLine(buf[0]->pos().x() + 20, 80 + (10) * 537/10, buf[1]->pos().x() + 20, 80 + (10) * 537/10);
                line_3->setPen(pen);
                scene->addItem(line_3);
            }
            if(checkRezult == 2)
            {
                line_1->setLine(buf[0]->pos().x() + 20, buf[0]->pos().y() + 18, buf[0]->pos().x() + 20, 80 + (-1) * 537/10);
                line_1->setPen(pen);
                scene->addItem(line_1);
                line_2->setLine(buf[1]->pos().x() + 20, buf[1]->pos().y() + 18, buf[1]->pos().x() + 20, 80 + (-1) * 537/10);
                line_2->setPen(pen);
                scene->addItem(line_2);
                line_3->setLine(buf[0]->pos().x() + 20, 80 + (-1) * 537/10, buf[1]->pos().x() + 20, 80 + (-1) * 537/10);
                line_3->setPen(pen);
                scene->addItem(line_3);
            }
            if(checkRezult == 4)
            {

                line_1->setLine(buf[0]->pos().x() + 20, buf[0]->pos().y() + 18, 400 + (-2) * 609/(20), buf[0]->pos().y() + 18);
                line_1->setPen(pen);
                scene->addItem(line_1);
                line_2->setLine(buf[1]->pos().x() + 20, buf[1]->pos().y() + 18, 400 + (-2) * 609/(20), buf[1]->pos().y() + 18);
                line_2->setPen(pen);
                scene->addItem(line_2);
                line_3->setLine(400 + (-2) * 609/(20), buf[0]->pos().y() + 18, 400 + (-2) * 609/(20), buf[1]->pos().y() + 18);
                line_3->setPen(pen);
                scene->addItem(line_3);
            }
            lines.push_back(line_1);
            lines.push_back(line_2);
            lines.push_back(line_3);
            if(mCount == 0)
            {
                Sleep(200);
                for(int i = 0; i < lines.size(); i++)
                {
                    delete lines[i];
                }
                lines.clear();
                Img *win = new Img(44);
                win->setPos(150, 50);
                scene->addItem(win);
                timer->stop();
                saveLeader();
            }
        }
        else
        {
            buf[0]->setPressure();
            buf[1]->setPressure();
        }

    }
    else if(!lines.isEmpty())
    {
        Sleep(250);
        for(int i = 0; i < lines.size(); i++)
        {
            delete lines[i];
        }
        lines.clear();
    }
    else if(computerStart == true)
    {
        if(!lines.isEmpty())
        {
            Sleep(250);
            for(int i = 0; i < lines.size(); i++)
            {
                delete lines[i];
            }
            lines.clear();
        }
        else
        {
            if(mCount == 2)
            {
                computerStart = false;
            }
            help();
        }
    }
}

/**
 * @brief MainWindow::on_actionAdd_User_triggered
 * Добавление пользователя
 */

void MainWindow::on_actionAdd_User_triggered()
{
    Reg a;
    a.show();
    a.exec();
    mUsers.push_back(a.lUser());
}

/**
 * @brief MainWindow::on_actionSave_triggered
 * Сохранение игры
 */

void MainWindow::on_actionSave_triggered()
{
    save->setVec(mVecTypes);
    save->show();
    if(save->exec() != QDialog::Accepted)
    {
        return;
    }
    mVecTypes = save->vec();
    newGame();
}

/**
 * @brief MainWindow::keyPressEvent
 * @param e Ключ кнопки
 * Метод используется в случае, если пользователь нажмет кнопку ESC.
 * В этом случае стерется поле и сгенерируются кнопки меню.
 */

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Escape && escape == false)
    {
        Img *start = new Img(43);
        scene = new QGraphicsScene(0, 0, ui->graphicsView->viewport()->width(), ui->graphicsView->viewport()->height());
        scene->addItem(start);
        start->setPos(450, 200);
        ui->graphicsView->setScene(scene);
        connect(start, SIGNAL(start()), this, SLOT(on_actionStart_triggered()));
        escape = true;
        return;
    }
    if(e->key() == Qt::Key_Escape && escape == true)
    {
        newGame();
        escape = false;
        return;
    }
}

/**
 * @brief MainWindow::check_3
 * Метод проверки на то можем ли мы соединить карточки ломаной линией с одним коленом.
 * @param i1, i2, j1, j2 Координаты карточек.
 * @return возвращает 1, 2, 3, 4 в зависимости каким путем мы подошли к карточке
 */

int MainWindow::check_3(int i1, int j1, int i2, int j2)
{
    QPen pen(Qt::green);
    pen.setWidth(6);
    int i = i1, j = j1;
    int rezult = 0;
    if(i1 > i2 && j1 < j2)
    {
        while(j1 != j2)
        {
            j1++;
            if(mVecTypes[i1][j1] != 0)
            {
                rezult = -1;
            }
        }
        while(i1 != i2)
        {
            i1--;
            if(mVecTypes[i1][j1] != 0 && i1 != i2)
            {
                rezult = -1;
            }
        }
        i1 = i;
        j1 = j;
        if(rezult != -1)
        {
            QGraphicsLineItem *line_1 = new QGraphicsLineItem;
            QGraphicsLineItem *line_2 = new QGraphicsLineItem;
            line_1->setLine(j1 * 30 + 375, 60 + 54 * i1, j2 * 30 + 375, 60 + 54 * i1);
            line_1->setPen(pen);
            line_2->setLine(j2 * 30 + 375, 60 + 54 * i2, j2 * 30 + 375, 60 + 54 * i1);
            line_2->setPen(pen);
            scene->addItem(line_2);
            lines.push_back(line_1);
            scene->addItem(line_1);
            lines.push_back(line_2);
            rezult = -1;
            return 1;
        }
        else
        {
            i1 = i;
            j1 = j;
            rezult = 0;
            while(i1 != i2)
            {
                i1--;
                if(mVecTypes[i1][j1] != 0)
                {
                    rezult = -1;
                }
            }
            while(j1 != j2)
            {
                j1++;
                if(mVecTypes[i1][j1] != 0 && j1 != j2)
                {
                    rezult = -1;
                }
            }
            i1 = i;
            j1 = j;
            if (rezult != -1)
            {
                QGraphicsLineItem *line_1 = new QGraphicsLineItem;
                QGraphicsLineItem *line_2 = new QGraphicsLineItem;
                line_1->setLine(j1 * 30 + 375, 60 + 54 * i1, j1 * 30 + 375, 60 + 54 * i2);
                line_1->setPen(pen);
                line_2->setLine(j2 * 30 + 375, 60 + 54 * i2, j1 * 30 + 375, 60 + 54 * i2);
                line_2->setPen(pen);
                scene->addItem(line_2);
                lines.push_back(line_1);
                scene->addItem(line_1);
                lines.push_back(line_2);
                return 3;
            }
        }

    }
    else if(i1 < i2 && j1 < j2 )
    {

        while(i1 != i2)
        {
            i1++;
            if(mVecTypes[i1][j1] != 0)
            {
                rezult = -1;
            }
        }
        while(j1 != j2)
        {
            j1++;
            if(mVecTypes[i1][j1] != 0 && j1 != j2)
            {
                rezult = -1;
            }
        }
        i1 = i;
        j1 = j;
        if(rezult != -1)
        {
            QGraphicsLineItem *line_1 = new QGraphicsLineItem;
            QGraphicsLineItem *line_2 = new QGraphicsLineItem;
            line_1->setLine(j1 * 30 + 375, 60 + 54 * i1, j1 * 30 + 375, 60 + 54 * i2);
            line_1->setPen(pen);
            line_2->setLine(j2 * 30 + 375, 60 + 54 * i2, j1 * 30 + 375, 60 + 54 * i2);
            line_2->setPen(pen);
            scene->addItem(line_2);
            lines.push_back(line_1);
            scene->addItem(line_1);
            lines.push_back(line_2);
            return 2;
        }

        else
        {
            i1 = i;
            j1 = j;
            rezult = 0;
            while(j1 != j2)
            {
                j1++;
                if(mVecTypes[i1][j1] != 0)
                {
                    rezult = -1;
                }
            }
            while(i1 != i2)
            {
                i1++;
                if(mVecTypes[i1][j1] != 0 && i1 != i2)
                {
                    rezult = -1;
                }
            }
            i1 = i;
            j1 = j;
            if(rezult != -1)
            {
                QGraphicsLineItem *line_1 = new QGraphicsLineItem;
                QGraphicsLineItem *line_2 = new QGraphicsLineItem;
                line_1->setLine(j1 * 30 + 375, 60 + 54 * i1, j2 * 30 + 375, 60 + 54 * i1);
                line_1->setPen(pen);
                line_2->setLine(j2 * 30 + 375, 60 + 54 * i2, j2 * 30 + 375, 60 + 54 * i1);
                line_2->setPen(pen);
                scene->addItem(line_2);
                lines.push_back(line_1);
                scene->addItem(line_1);
                lines.push_back(line_2);
                return 4;
            }
        }
        return -1;

    }
    return -1;
}

/**
 * @brief MainWindow::help
 * Обход поля, чтобы найти карточки, которые можно удалить.
 */

void MainWindow::help()
{
    QVector<int> rez;
    for(int i1 = 0; i1 < mVecTypes.size(); i1++)
    {
        for(int j1 = 0; j1 < mVecTypes[i1].size(); j1++)
        {
            for(int i2 = 0; i2 < mVecTypes.size(); i2++)
            {
                for(int j2 = 0; j2 < mVecTypes[i2].size(); j2++)
                {
                    if(mVecTypes[i1][j1] == mVecTypes[i2][j2] && mVecTypes[i1][j1] != 0)
                    {
                        if(i1 == i2 && j1 == j2)
                        {
                            continue;
                        }
                        int checkRezult = check(isExternalRow(i1, j1), isExternalRow(i2, j2));
                        if(checkRezult != -1)
                        {
                            rez.push_back(i1);
                            rez.push_back(j1);
                            rez.push_back(i2);
                            rez.push_back(j2);
                            goto lbl;
                        }
                    }
                }
            }
        }
    }
    lbl:
    if(!rez.isEmpty())
    {
        if(computerStart)
        {
            mVec[rez[1]][rez[0]]->setTrig(true);
            mVec[rez[3]][rez[2]]->setTrig(true);
        }
        else
        {
            QMessageBox *a = new QMessageBox;
            a->setText(tr("Подсказка : %1 ряд %2 столбец - первая карточка \n %3 ряд %4 столбец - вторая карточка.")
                       .arg(rez[0] + 1).arg(rez[1] + 1).arg(rez[2] + 1).arg(rez[3] + 1));
            a->setWindowTitle("Help");

            a->show();
        }
    }
}

/**
 * @brief MainWindow::check_4
 * Проверяем можем ли мы соеденить карточки ломанными линиями, имеющими два колена.
 * @param i1, i2, j1, j2 Координаы карточек.
 * @return
 */

int MainWindow::check_4(int i1, int j1, int i2, int j2)
{

    QPen pen(Qt::green);
    pen.setWidth(6);
    int i = i1;
    int j = j1;
    while (i1 + 1 != mVecTypes.size())
    {
        {
            if (check_3(i1, j1, i2, j2) != -1)
            {
                QGraphicsLineItem *line = new QGraphicsLineItem;
                line->setPen(pen);
                line->setLine(j1 * 30 + 375, 60 + 54 * i1, j1 * 30 + 375, 60 + 54 * i);
                scene->addItem(line);
                lines.push_back(line);
                return 1;
            }
            if(mVecTypes[i1 + 1][j1] != 0)
            {
                break;
            }
            i1++;
        }
    }
    i1 = i;
    while(i1 - 1 != -1)
    {
        if(check_3(i1, j1, i2, j2) != -1)
        {
            QGraphicsLineItem *line = new QGraphicsLineItem;
            line->setPen(pen);
            line->setLine(j1 * 30 + 375, 60 + 54 * i1, j1 * 30 + 375, 60 + 54 * i);
            scene->addItem(line);
            lines.push_back(line);
            return 2;
        }
        if(mVecTypes[i1 - 1][j1] != 0)
        {
            break;
        }
        i1--;

    }
    i1 = i;
    while (j1 + 1 != mVecTypes[i1].size())
    {


        if (check_3(i1, j1, i2, j2) != -1)
        {
            QGraphicsLineItem *line = new QGraphicsLineItem;
            line->setPen(pen);
            line->setLine(j1 * 30 + 375, 60 + 54 * i1, j * 30 + 375, 60 + 54 * i1);
            scene->addItem(line);
            lines.push_back(line);
            return 3;
        }
        if(mVecTypes[i1][j1 + 1] != 0 )
        {
            break;
        }
        j1++;

    }
    j1 = j;
    while(j1 - 1 != -1)
    {


        if(check_3(i1, j1, i2, j2) != -1)
        {
            QGraphicsLineItem *line = new QGraphicsLineItem;
            line->setPen(pen);
            line->setLine(j1 * 30 + 375, 60 + 54 * i1, j * 30 + 375, 60 + 54 * i1);
            scene->addItem(line);
            lines.push_back(line);
            return 4;
        }
        if(mVecTypes[i1][j1 - 1] != 0)
        {
            break;
        }
        j1--;

    }
    return -1;

}


void MainWindow::on_actionComputer_triggered()
{
    if(computerStart == false)
        computerStart = true;
    else
        computerStart = false;
}

/**
 * @brief MainWindow::saveLeader
 * Сохраняем результат игры в файл.
 */

void MainWindow::saveLeader()
{
    QString name;
    int time;
    QFile file("leaders.bin");
    if(file.open(QIODevice::Append))
    {

        QDataStream stream_1(&file);
        while(!stream_1.atEnd())
        {
            stream_1 >> name;
            stream_1 >> time;
        }
        stream_1 << mUserName << mTime->elapsed();
        if(stream_1.status() != QDataStream::Ok)
        {
            qDebug() << "Ошибка чтения";
        }
    }
    file.close();
}

struct lead
{
    int time;
    QString name;
};

/**
 * @brief prefLessThan
 * Метод необходимый для сортировки лидеров.
 */

bool prefLessThan(const lead &p1, const lead &p2)
{
    return p1.time < p2.time;
}

/**
 * @brief MainWindow::on_actionLeaders_triggered
 * Метод считывает из файла и показывает нам список лидеров.
 */

void MainWindow::on_actionLeaders_triggered()
{

    QVector<lead> vec;
    QFile file("leaders.bin");
    if(file.open(QIODevice::ReadOnly))
    {
        QDataStream stream(&file);
        while(!stream.atEnd())
        {
            lead buf;
            stream >> buf.name >> buf.time;
            vec.push_back(buf);
        }
    }
    qSort(vec.begin(), vec.end(), prefLessThan);
    QTextEdit *text = new QTextEdit;
    text->setWindowTitle("Список лидеров");
    for(int i = 0; i < vec.size(); i++)
    {
        text->append(tr("%1: %2 секунд\n").arg(vec[i].name).arg(int(vec[i].time * 0.001)));
    }
    text->show();
    text->setEnabled(false);
}

/**
 * @brief MainWindow::on_actionGame_rools_triggered
 * Вывод правил игры.
 */

void MainWindow::on_actionGame_rools_triggered()
{
    QMessageBox *a = new QMessageBox;
    a->setText("На поле 10*20 позиций карточки с картинками.\n "
               "Карточки удаляются с поля парами только из внешних рядов с одинаковыми картинками. Картинки при удалении  соединяются  ломаной  линией,  имеющей  не  более  трех  колен.\n "
               "Играющий стремится удалить как можно больше карточек.");
    a->setWindowTitle("Game rools");

    a->show();
}

/**
 * @brief MainWindow::on_actionNew_users_triggered
 * Вывод новых пользователей.
 */

void MainWindow::on_actionNew_users_triggered()
{
    QTextEdit *text = new QTextEdit;
    text->setWindowTitle("Список новых пользователей");
    for(int i = 0; i < mUsers.size(); i++)
    {
        text->append(tr("Логин: %1\n Пароль: %2\n Возраст: "
                        "%3 Уровень игры: %4\n\n\n")
                     .arg(mUsers[i].getLogin())
                     .arg(mUsers[i].getPassword())
                     .arg(mUsers[i].getYear())
                     .arg(mUsers[i].getExp()));
    }
    text->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionHard_triggered()
{
    maxSize_1 = 10;
    maxSize_2 = 20;
    setBoard(2, 12);
    newGame();
}

void MainWindow::on_actionNormal_triggered()
{
    maxSize_1 = 6;
    maxSize_2 = 16;
    setBoard(2, 12);
    newGame();
}

void MainWindow::on_actionEasy_triggered()
{
    maxSize_1 = 2;
    maxSize_2 = 12;
    setBoard(2, 12);
    newGame();
}
