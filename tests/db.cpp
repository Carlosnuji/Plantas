#include "db.h"

Db::Db()
{

}

bool Db::init()
{

    bool init = false;

    m_db = QSqlDatabase::addDatabase("QPSQL");
    m_db.setHostName("localhost");
    m_db.setDatabaseName("template1");
    m_db.setPort(5432);
    m_db.setUserName("postgres");
    m_db.setPassword("");
    bool ok = m_db.open();

    if(ok)
    {

        QSqlQuery query("DROP DATABASE IF EXISTS testplantas", m_db);
        if(query.lastError().type() == QSqlError::NoError)
        {

            QSqlQuery query1("CREATE DATABASE testplantas", m_db);
            if(query1.lastError().type() == QSqlError::NoError)
            {

                m_db.close();
                m_db.setDatabaseName("testplantas");
                m_db.open();

                QString create = "CREATE TABLE usuario ( \
                                  idusuario serial PRIMARY KEY, \
                                  nombre VARCHAR (50) UNIQUE NOT NULL, \
                                  password TEXT NOT NULL, \
                                  email VARCHAR (100) UNIQUE NOT NULL)";

                QSqlQuery query1 (create, m_db);

                init = true;
            }

        } // end if

    } // end if

    return init;

}
