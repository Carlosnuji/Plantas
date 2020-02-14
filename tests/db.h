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
    bool isNumber(const std::string& s);
    bool init();
    bool insert(const std::string nombreTabla, const std::vector<std::string>& campos, const std::vector<std::string>& valores);

private:
    QSqlDatabase m_db;

};

#endif // DB_H
