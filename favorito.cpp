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
bool Favorito::save()
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

    if(numeroFilas == 1) return true;
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
            qDebug() << m_id;
        }

    }

    return false;

}

void Favorito::load()
{

    QSqlQuery query;
    query.prepare("");

}



















