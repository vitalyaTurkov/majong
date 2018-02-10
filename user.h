#ifndef USER_H
#define USER_H

#include <QtWidgets>

class user
{
public:
    user();
    QString getLogin() const;
    void setLogin(const QString &value);

    QString getPassword() const;
    void setPassword(const QString &value);

    int getYear() const;
    void setYear(int value);

    QString getExp() const;
    void setExp(const QString &value);

private:
    QString login;
    QString password;
    QString exp;
    int year;
};

#endif // USER_H
