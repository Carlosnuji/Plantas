#ifndef CONEXION_H
#define CONEXION_H

#include <string>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QString>

class Conexion
{

public:
    Conexion();
    bool open();
    void close();

private:
    QSqlDatabase m_db;
    QString m_hostName;
    QString m_databaseName;
    int m_port;
    QString m_userName;
    QString m_password;
    void loadProperties();

};

#endif // CONEXION_H
