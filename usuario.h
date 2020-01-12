#ifndef USUARIO_H
#define USUARIO_H

#include <string>
#include <list>
#include <QSqlQuery>
#include <QSqlRecord>
#include "json.hpp"

using JSON = nlohmann::json;

class Usuario
{

public:
    Usuario(std::string, std::string, std::string);
    JSON toJSON();
    void save();
    static Usuario load(int);
    static void remove(int);
    std::string getNombre();
    std::string getPassword();
    std::string getEmail();

private:
    int m_id{0};
    std::string m_nombre{""};
    std::string m_password{""};
    std::string m_email{""};

};

#endif // USUARIO_H
