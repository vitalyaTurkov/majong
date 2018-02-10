#ifndef REG_H
#define REG_H

#include <QDialog>
#include "user.h"

namespace Ui {
class Reg;
}

class Reg : public QDialog
{
    Q_OBJECT

public:
    explicit Reg(QWidget *parent = 0);
    ~Reg();

    user lUser() const;

private slots:

    void on_pushButton_clicked();

private:
    Ui::Reg *ui;
    user mUser;
};

#endif // REG_H
