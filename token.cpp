#include "token.h"
#include <QVariant>


Token::Token()
{

}

QString Token::generateToken()
{

    QUuid u = QUuid::createUuid();
    return u.toString();

}

void Token::insert(QString uuid, int idusuario)
{

    QSqlQuery query;
    query.prepare("INSERT INTO token (uuid, idusuario) VALUES (:uuid, :idusuario)");

    query.bindValue(":uuid", uuid);
    query.bindValue(":idusuario", QString::number(idusuario));
    query.exec();

}
