#ifndef BASEDATOS_H
#define BASEDATOS_H

#include <QVariant>
#include <QString>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>

class BaseDatos
{
public:
    BaseDatos();
    virtual bool save();
    virtual bool load(const int id);
    virtual bool update();

};

#endif // BASEDATOS_H
