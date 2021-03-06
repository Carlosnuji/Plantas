#include "usuario.h"

Usuario::Usuario(std::string nombre, std::string password, std::string email)
{

    this->m_nombre = nombre;
    this->m_password = password;
    this->m_email = email;

}

bool Usuario::save()
{

    QSqlQuery query;
    query.prepare("INSERT INTO usuario (nombre, password, email) VALUES (:nombre, crypt(:pass, gen_salt('bf')), :email);");

    QVariant nombre = QString::fromStdString(m_nombre);
    QVariant pass = QString::fromStdString(m_password);
    QVariant email = QString::fromStdString(m_email);
    query.bindValue(":nombre", nombre);
    query.bindValue(":pass", pass);
    query.bindValue(":email", email);
    query.exec();

    QString error (query.lastError().text());

    if(error == " ")
    {
        query.prepare("select * from usuario order by idusuario desc limit 1;");
        query.exec();
        QSqlRecord rec = query.record();
        while (query.next())
        {
            int id = query.value("idusuario").toInt();
            this->m_id = id;
        }

        return true;
    }
    else
    {
        qDebug() << error;
        return false;
    }

}

Usuario Usuario::load(std::string email, std::string password)
{

    Usuario usuario("", "", "");

    QSqlQuery query;
    query.prepare("SELECT (password = crypt(:password, password)) AS pwd_match  FROM usuario where email = :email;");

    QVariant eml = QString::fromStdString(email);
    QVariant pas = QString::fromStdString(password);
    query.bindValue(":email", eml);
    query.bindValue(":password", pas);
    query.exec();

    bool passCorrect = false;
    QSqlRecord rec = query.record();
    while (query.next())
    {
        passCorrect = QVariant(query.value("pwd_match")).toBool();
    } // end while

    if(passCorrect)
    {

        query.prepare("SELECT * from usuario where email = :email");
        query.bindValue(":email", eml);
        query.exec();

        QSqlRecord rec = query.record();
        while (query.next())
        {
            QString nombre = query.value("nombre").toString();
            QString pass = query.value("password").toString();
            QString email = query.value("email").toString();
            int status = query.value("status").toInt();
            int admin = query.value("administrador").toInt();

            Usuario user(nombre.toUtf8().constData(), pass.toUtf8().constData(), email.toUtf8().constData());
            user.m_id = query.value("idusuario").toInt();
            user.m_status = status;
            user.m_admin = admin;
            return user;
        }

    } // end if


    return usuario;

}

bool Usuario::load(const int id)
{

    QSqlQuery query;
    query.prepare("SELECT * FROM usuario where idusuario=:idusuario");

    query.bindValue(":idusuario", id);
    query.exec();

    if(query.next())
    {

        QString nombre = query.value("nombre").toString();
        QString pass = query.value("password").toString();
        QString email = query.value("email").toString();
        int status = query.value("status").toInt();
        int admin = query.value("administrador").toInt();

        m_id = query.value("idusuario").toInt();
        m_nombre = nombre.toUtf8().constData();
        m_password = pass.toUtf8().constData();
        m_email = email.toUtf8().constData();
        m_status = status;
        m_admin = admin;

        return true;

    }

    return false;

}

void Usuario::remove(int id)
{

    QSqlQuery query;
    query.prepare("DELETE FROM usuario where idusuario = :id");

    query.bindValue(":id", id);
    query.exec();

}

bool Usuario::update()
{

    QSqlQuery query;
    query.prepare("UPDATE usuario set nombre=:nombre, email=:email, status=:status where idusuario=:idusuario");

    query.bindValue(":nombre", QString::fromStdString(m_nombre));
    query.bindValue(":email", QString::fromStdString(m_email));
    query.bindValue(":idusuario", m_id);
    query.bindValue(":status", m_status);
    query.exec();

    return true;

}

std::list<Usuario> Usuario::find()
{

    std::list<Usuario> usuarios{};

    QSqlQuery query;
    query.prepare("SELECT * FROM usuario");
    query.exec();

    while (query.next())
    {

        QString nombre = query.value("nombre").toString();
        QString pass = query.value("password").toString();
        QString email = query.value("email").toString();
        int status = query.value("status").toInt();
        int admin = query.value("administrador").toInt();

        Usuario user(nombre.toUtf8().constData(), pass.toUtf8().constData(), email.toUtf8().constData());
        user.m_id = query.value("idusuario").toInt();
        user.m_status = status;
        user.m_admin = admin;

        usuarios.push_back(user);

    }

    return usuarios;

}

JSON Usuario::toJSON()
{

    JSON usuario;
    usuario["id"] = m_id;
    usuario["nombre"] = m_nombre;
    usuario["pass"] = m_password;
    usuario["email"] = m_email;
    usuario["status"] = m_status;
    usuario["admin"] = m_admin;

    return usuario;

}

int Usuario::getId(){ return m_id; }
std::string Usuario::getNombre(){ return m_nombre; }
std::string Usuario::getPassword(){ return m_password; }
std::string Usuario::getEmail(){ return m_email; }
int Usuario::getStatus(){ return m_status; }

void Usuario::setNombre(std::string nombre){ m_nombre = nombre; }
void Usuario::setEmail(std::string email){ m_email = email; }
void Usuario::setStatus(int status){ m_status = status; }
void Usuario::setAdmin(int admin){m_admin = admin; }






















