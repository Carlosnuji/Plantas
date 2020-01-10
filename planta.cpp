#include "planta.h"
#include <QVariant>
#include <QString>
#include <QDebug>

Planta::Planta(std::string nombre, std::string nombreCientifico, std::string descripcion)
{

    this->m_nombre = nombre;
    this->m_nombreCientifico = nombreCientifico;
    this->m_descripcion = descripcion;

}

Planta::~Planta()
{
}

void Planta::save()
{

    QSqlQuery query;
    query.prepare("INSERT INTO planta (nombre, nombreCientifico, descripcion) VALUES (:nombre, :nomCien, :desc);");

    QVariant nombre = QString::fromStdString(m_nombre);
    QVariant nombreCientifico = QString::fromStdString(m_nombreCientifico);
    QVariant descripcion = QString::fromStdString(m_descripcion);
    query.bindValue(":nombre", nombre);
    query.bindValue(":nomCien", nombreCientifico);
    query.bindValue(":desc", descripcion);
    query.exec();

}

Planta Planta::load(int id)
{

    QSqlQuery query;
    query.prepare("SELECT * FROM planta where idplanta = :id");

    query.bindValue(":id", id);
    query.exec();

    QSqlRecord rec = query.record();
    while (query.next())
    {
        QString nombre = query.value("nombre").toString();
        QString nombreCientifico = query.value("nombreCientifico").toString();
        QString descripcion = query.value("descripcion").toString();

        Planta planta(nombre.toUtf8().constData(), nombreCientifico.toUtf8().constData(), descripcion.toUtf8().constData());
        return planta;
    }

}

void Planta::remove(int id)
{

    QSqlQuery query;
    query.prepare("DELETE FROM planta where idplanta = :id");

    query.bindValue(":id", id);
    query.exec();

}















