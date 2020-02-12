#ifndef DB_H
#define DB_H

#include <iostream>
#include <string>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QString>
#include <QSqlError>
#include <QDebug>

class Db
{
public:
    Db();
    bool init();

private:
    QSqlDatabase m_db;

};

#endif // DB_H
