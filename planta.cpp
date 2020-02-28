#include "planta.h"

Planta::Planta(std::string nombre, std::string nombreCientifico, std::string descripcion)
{

    this->m_nombre = nombre;
    this->m_nombreCientifico = nombreCientifico;
    this->m_descripcion = descripcion;

}

bool Planta::save()
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

    QString error (query.lastError().text());

    if(error == " ") return true;
    else qDebug() << query.lastError().text();

    return false;

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

bool Planta::load(const int id)
{

    QSqlQuery query;
    query.prepare("SELECT * FROM planta where idplanta=:idplanta");

    query.bindValue(":idplanta", id);
    query.exec();

    if(query.next())
    {

        QString nombre = query.value("nombre").toString();
        QString nombreCientifico = query.value("nombreCientifico").toString();
        QString descripcion = query.value("descripcion").toString();

        m_id = query.value("idplanta").toInt();
        m_nombre = nombre.toUtf8().constData();
        m_nombreCientifico = nombreCientifico.toUtf8().constData();
        m_descripcion = descripcion.toUtf8().constData();

        return true;

    }

    return false;

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

int Planta::getId(){ return m_id; }

std::string Planta::getNombre(){ return m_nombre; }

std::string Planta::getNombreCientifico(){ return m_nombreCientifico; }

std::string Planta::getDescripcion() { return m_descripcion; }














