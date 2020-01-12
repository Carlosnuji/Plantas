#include "conexion.h"

Conexion::Conexion()
{
}

void Conexion::loadProperties()
{

    m_hostName = "localhost";
    m_databaseName = "plantas";
    m_port = 5432;
    m_userName = "postgres";
    m_password = "";

}

bool Conexion::open()
{

    /// 1) Cargar propiedades
    loadProperties();
    m_db = QSqlDatabase::addDatabase("QPSQL");
    m_db.setHostName(m_hostName);
    m_db.setDatabaseName(m_databaseName);
    m_db.setPort(5432);
    m_db.setUserName(m_userName);
    m_db.setPassword(m_password);


    /// 2) Abrir conexión
    bool ok = m_db.open();

    return ok;

}

void Conexion::close()
{

    m_db.close();

}
