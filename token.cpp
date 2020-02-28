#include "token.h"
#include <QVariant>
#include <iostream>
#include "usuario.h"


Token::Token()
{

}

QString Token::generateToken()
{

    QUuid u = QUuid::createUuid();
    return u.toString();

}

bool Token::insert(QString uuid, int idusuario)
{

    QSqlQuery query;
    query.prepare("INSERT INTO token (uuid, idusuario) VALUES (:uuid, :idusuario)");

    query.bindValue(":uuid", uuid);
    query.bindValue(":idusuario", QString::number(idusuario));
    query.exec();

    QString error (query.lastError().text());

    if(error == " ") return true;
    else qDebug() << query.lastError().text();

    return false;

}

bool Token::checkToken(std::string token)
{

    QSqlQuery query;
    query.prepare("SELECT * from token WHERE uuid=:token");

    query.bindValue(":token", QString::fromUtf8(token.c_str()));

    bool resultado = query.exec();

    if(resultado && query.size() >= 1)
    {

        query.next();
        int idUsuario = query.value("idusuario").toInt();

        Usuario user("","","");
        user.load(idUsuario);

        user.setStatus(1);
        user.update();

        return true;

    }

    return  false;

}






















