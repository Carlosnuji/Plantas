#include "db.h"

Db::Db()
{

    m_db = QSqlDatabase::addDatabase("QPSQL");
    m_db.setHostName("localhost");
    m_db.setDatabaseName("template1");
    m_db.setPort(5432);
    m_db.setUserName("postgres");
    m_db.setPassword("");

}

bool Db::isNumber(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

bool Db::init()
{

    bool init = false;
    bool ok = m_db.open();

    if(ok)
    {

        qDebug() << "Eliminando base datos";
        QSqlQuery query("DROP DATABASE IF EXISTS testplantas", m_db);
        if(query.lastError().type() == QSqlError::NoError)
        {

            qDebug() << "Creando base datos";
            QSqlQuery query1("CREATE DATABASE testplantas", m_db);
            if(query1.lastError().type() == QSqlError::NoError)
            {

                m_db.close();
                m_db.setDatabaseName("testplantas");
                m_db.open();

                QSqlQuery extension("CREATE EXTENSION pgcrypto;", m_db);

                QString createUser = "CREATE TABLE usuario ( \
                                  idusuario serial PRIMARY KEY, \
                                  nombre VARCHAR (50) UNIQUE NOT NULL, \
                                  password TEXT NOT NULL, \
                                  email VARCHAR (100) UNIQUE NOT NULL, \
                                  status INTEGER )";

                QSqlQuery query1 (createUser, m_db);

                QString createPlanta = "CREATE TABLE planta ( \
                                  idplanta serial PRIMARY KEY, \
                                  nombre VARCHAR (50) NOT NULL, \
                                  nombrecientifico VARCHAR (50) NOT NULL, \
                                  descripcion VARCHAR (50) NOT NULL, \
                                  imagen BYTEA )";

                QSqlQuery query2 (createPlanta, m_db);

                QString createToken = "CREATE TABLE token ( \
                                    idtoken serial PRIMARY KEY, \
                                    uuid TEXT, \
                                    idusuario INTEGER, \
                                    date date default CURRENT_DATE )";

                QSqlQuery query3 (createToken, m_db);

                QString createQueja = "CREATE TABLE queja ( \
                                    idqueja serial PRIMARY KEY, \
                                    idusuario INTEGER, \
                                    queja TEXT )";

                QSqlQuery query4 (createQueja, m_db);

                QString createFavorito = "CREATE TABLE favorito ( \
                                        idfavorito serial PRIMARY KEY, \
                                        idusuario INTEGER, \
                                        idplanta INTEGER )";

                QSqlQuery query5 (createFavorito, m_db);

                init = true;
            }

        } // end if

    } // end if

    return init;

}

bool Db::insert(const std::string nombreTabla, const std::vector<std::string>& campos, const std::vector<std::string>& valores)
{

    /// 1. Crear insert
    std::string strQuery = "INSERT INTO " + nombreTabla + " (";

    for (ulong x = 0; x < campos.size(); x++)
    {

        if(x < campos.size() -1) strQuery += campos.at(x) + ",";
        else strQuery += campos.at(x);

    }
    strQuery += ") VALUES (";

    for (ulong y = 0; y < valores.size(); y++)
    {

        if (!isNumber(valores.at(y)) && y < valores.size() - 1) strQuery += "'" + valores.at(y) + "'" + ",";
        else if (isNumber(valores.at(y)) &&  y < valores.size() - 1) strQuery += valores.at(y) + ",";
        else if (!isNumber(valores.at(y)) && y == valores.size() - 1) strQuery += "'" + valores.at(y) + "'";

    }
    strQuery += ")";

    //std::cout << strQuery << std::endl;

    /// 2. Ejecutar insert
    QSqlQuery query;
    query.prepare(QString::fromUtf8(strQuery.c_str()));
    bool ok = query.exec();

    return ok;

}
























