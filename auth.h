#ifndef AUTH_H
#define AUTH_H

#include <QDialog>

namespace Ui {
class Auth;
}

class Auth : public QDialog
{
    Q_OBJECT

public:
    explicit Auth(QWidget *parent = 0);
    ~Auth();

    QString getStatus() const;

    QString getUserName() const;

private slots:
    void on_pushButton_clicked();

    void on_lineEdit_editingFinished();

    void on_lineEdit_2_editingFinished();

private:
    Ui::Auth *ui;
    QString status;
    QString userName;
};

#endif // AUTH_H
