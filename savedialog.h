#ifndef SAVEDIALOG_H
#define SAVEDIALOG_H

#include <QDialog>

namespace Ui {
class SaveDialog;
}

class SaveDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SaveDialog(QWidget *parent = 0);
    ~SaveDialog();

    void setVec(const QVector<QVector<int> > &vec);

    QVector<QVector<int> > vec() const;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::SaveDialog *ui;
    QVector<QVector<int>> mVec;
};

#endif // SAVEDIALOG_H
