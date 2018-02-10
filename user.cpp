#include "user.h"

user::user()
{

}

QString user::getLogin() const
{
    return login;
}

void user::setLogin(const QString &value)
{
    login = value;
}

QString user::getPassword() const
{
    return password;
}

void user::setPassword(const QString &value)
{
    password = value;
}

int user::getYear() const
{
    return year;
}

void user::setYear(int value)
{
    year = value;
}

QString user::getExp() const
{
    return exp;
}

void user::setExp(const QString &value)
{
    exp = value;
}
