#include "favorito.h"
#include <QString>
#include <QVariant>
#include <QSqlError>
#include <QDebug>

Favorito::Favorito(int m_idUsuario, int m_idPlanta)
{

    this->m_idUsuario = m_idUsuario;
    this->m_idPlanta = m_idPlanta;

}

/// return 1 si existe
/// return 0 si no existe
bool Favorito::check()
{

    QSqlQuery query;
    query.prepare("SELECT count(*) as numero FROM favorito where idusuario=:idusuario AND idplanta=:idplanta");
    query.bindValue(":idusuario", m_idUsuario);
    query.bindValue(":idplanta", m_idPlanta);
    bool resultado = query.exec();

    int numeroFilas{0};
    if(resultado)
    {
        query.next();
        numeroFilas = query.value("numero").toInt();
    }

    if(numeroFilas == 1)
    {

        query.prepare("DELETE FROM favorito where idusuario=:idusuario AND idplanta=:idplanta");
        query.bindValue(":idusuario", m_idUsuario);
        query.bindValue(":idplanta", m_idPlanta);
        query.exec();

        return true;

    }
    else
    {

        query.prepare("INSERT INTO favorito (idusuario, idplanta) VALUES (:idusuario, :idplanta) RETURNING idfavorito");
        query.bindValue(":idusuario", m_idUsuario);
        query.bindValue(":idplanta", m_idPlanta);
        bool result = query.exec();

        if(result)
        {
            query.next();
            m_id = query.value("idfavorito").toInt();
        }

    }

    return false;

}

bool Favorito::load(int idUsuario, int idPlanta)
{

    QSqlQuery query;
    query.prepare("SELECT count(*) as numero FROM favorito where idusuario=:idusuario AND idplanta=:idplanta");
    query.bindValue(":idusuario", idUsuario);
    query.bindValue(":idplanta", idPlanta);
    bool resultado = query.exec();

    int numeroFilas{0};
    if(resultado)
    {
        query.next();
        numeroFilas = query.value("numero").toInt();
    }

    if(numeroFilas == 1)
    {

        query.prepare("SELECT * from favorito where idusuario=:idusuario AND idplanta=:idplanta");
        query.bindValue(":idusuario", idUsuario);
        query.bindValue(":idplanta", idPlanta);
        bool resultado2 = query.exec();

        if(resultado2 && query.next())
        {

            m_id = query.value("idfavorito").toInt();
            m_idUsuario = query.value("idusuario").toInt();
            m_idPlanta = query.value("idplanta").toInt();

        } // end if

        return true;

    } // end if

    return false;

}

JSON Favorito::toJSON()
{

    JSON favorito;

    favorito["id"] = m_id;
    favorito["idUsuario"] = m_idUsuario;
    favorito["idPlanta"] = m_idPlanta;

    return favorito;

}

std::list<Planta> Favorito::find(int idUsuario)
{

    std::list<Planta> lista{};

    QSqlQuery query;
    query.prepare("SELECT * from favorito where idusuario=:idusuario");
    query.bindValue(":idusuario", idUsuario);
    query.exec();

    QSqlRecord rec = query.record();
    while (query.next())
    {

        int idPlanta = query.value("idplanta").toInt();

        Planta planta("", "", "");
        planta.load(idPlanta);

        lista.push_back(planta);

    } // end while

    return lista;

}

int Favorito::getIdUsuario() { return m_idUsuario; }
int Favorito::getIdPlanta() { return m_idPlanta; }


















