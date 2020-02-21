#ifndef TOKEN_H
#define TOKEN_H


#include <QString>
#include <QUuid>
#include <QSqlQuery>
#include <QSqlRecord>

class Token
{

public:
    Token();
    QString generateToken();
    void insert(QString uuid, int idusuario);
    static bool checkToken(std::string token);

private:


};

#endif // TOKEN_H
