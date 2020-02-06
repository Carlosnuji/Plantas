#ifndef FAVORITO_H
#define FAVORITO_H

#include <iostream>
#include <string>
#include <list>
#include <QSqlQuery>
#include <QSqlRecord>
#include "json.hpp"
#include "planta.h"

using JSON = nlohmann::json;

class Favorito
{

public:
    Favorito(int m_idUsuario, int m_idPlanta);
    JSON toJSON();
    void load(int idUsuario, int idPlanta);
    bool check();
    static std::list<Planta> find(int idUsuario);
    int getIdUsuario();
    int getIdPlanta();

private:
    int m_id{0};
    int m_idUsuario{0};
    int m_idPlanta{0};

};

#endif // FAVORITO_H
