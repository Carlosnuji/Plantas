#include "queja.h"
#include <QString>
#include <QVariant>
#include <QSqlError>
#include <QDebug>

Queja::Queja(int idUsuario, std::string queja)
{

    m_idUsuario = idUsuario;
    m_queja = queja;

}

void Queja::save()
{

    QSqlQuery query;
    query.prepare("INSERT INTO queja (idusuario, queja) VALUES (:idUser, :queja)");

    query.bindValue(":idUser", QString::number(m_idUsuario));
    query.bindValue(":queja", QString::fromStdString(m_queja));
    query.exec();

    QString error (query.lastError().text());

    if(error == " ")
    {

        query.prepare("SELECT * FROM queja order by idqueja desc limit 1;");
        query.exec();
        QSqlRecord rec = query.record();
        while (query.next())
        {
            int id = query.value("idqueja").toInt();
            this->m_id = id;
        }

    } // end if
    else
    {
        qDebug() << error;
    }

}

void Queja::load(int id)
{

    QSqlQuery query;
    query.prepare("SELECT * FROM queja WHERE idqueja=:id");
    query.bindValue(":id", QString::number(id));
    bool resultado = query.exec();

    if(resultado)
    {
        query.next();
        m_id = query.value("idqueja").toInt();
        m_idUsuario = query.value("idusuario").toInt();
        QString queja = query.value("queja").toString();
        setQueja(queja.toUtf8().constData());
    }

}

void Queja::remove(int id)
{

    QSqlQuery query;
    query.prepare("DELETE FROM queja where idqueja = :id");

    query.bindValue(":id", id);
    query.exec();

}

std::list<Queja> Queja::find(int idUsuario)
{

    std::list<Queja> lista = {};

    QSqlQuery query;
    query.prepare("SELECT * FROM queja where idusuario = :id");

    query.bindValue(":id", idUsuario);
    query.exec();

    QSqlRecord rec = query.record();
    while (query.next())
    {

        int id = query.value("idqueja").toInt();
        int idUsuario = query.value("idusuario").toInt();
        QString quejaValor = query.value("queja").toString();

        Queja queja(idUsuario,quejaValor.toUtf8().constData());
        queja.m_id = id;

        lista.push_back(queja);
        qDebug() << quejaValor;

    } // end while

    return lista;

}

int Queja::getId(){ return m_id; }
int Queja::getIdUsuario(){ return m_idUsuario; }
std::string Queja::getQueja(){ return m_queja; }

void Queja::setQueja(std::string queja){ m_queja = queja; }
























