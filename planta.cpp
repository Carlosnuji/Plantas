#include "planta.h"
#include <QVariant>
#include <QString>

Planta::Planta(std::string nombre, std::string nombreCientifico, std::string descripcion)
{

    this->m_nombre = nombre;
    this->m_nombreCientifico = nombreCientifico;
    this->m_descripcion = descripcion;

}

Planta::~Planta(){}

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

Planta Planta::load(std::string nombre, std::string nombreCientifico)
{

    QSqlQuery query;
    query.prepare("SELECT * FROM planta where nombre = :nombre AND nombrecientifico = :nomcien");

    query.bindValue(":nombre", QString::fromStdString(nombre));
    query.bindValue(":nomcien", QString::fromStdString(nombreCientifico));
    query.exec();

    QSqlRecord rec = query.record();
    while (query.next())
    {
        QString nombre = query.value("nombre").toString();
        QString nombreCientifico = query.value("nombreCientifico").toString();
        QString descripcion = query.value("descripcion").toString();

        Planta planta(nombre.toUtf8().constData(), nombreCientifico.toUtf8().constData(), descripcion.toUtf8().constData());
        planta.m_id = query.value("idplanta").toInt();
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

std::list<Planta> Planta::find(std::string nombre)
{

    std::list<Planta> listaPlantas = {};

    QSqlQuery query;
    query.prepare("SELECT * FROM planta WHERE nombre LIKE :nombre");

    QString  nom = QString::fromStdString(nombre);
    query.bindValue(":nombre", QString("%%1%").arg(nom));

    query.exec();

    QSqlRecord rec = query.record();
    while (query.next())
    {

        QString nombre = query.value("nombre").toString();
        QString nombreCientifico = query.value("nombreCientifico").toString();
        QString descripcion = query.value("descripcion").toString();

        Planta planta(nombre.toUtf8().constData(), nombreCientifico.toUtf8().constData(), descripcion.toUtf8().constData());
        planta.m_id = query.value("idplanta").toInt();

        listaPlantas.push_back(planta);

    }

    return listaPlantas;

}

JSON Planta::toJSON()
{

    JSON planta;
    planta["id"] = m_id;
    planta["nombre"] = m_nombre;
    planta["nombreCientifico"] = m_nombreCientifico;
    planta["descripcion"] = m_descripcion;

    return planta;

}

std::string Planta::getNombre(){ return m_nombre; }

std::string Planta::getNombreCientifico(){ return m_nombreCientifico; }

std::string Planta::getDescripcion() { return m_descripcion; }














