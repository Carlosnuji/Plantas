#ifndef FAVORITO_H
#define FAVORITO_H

#include <string>
#include <list>
#include <QSqlQuery>
#include <QSqlRecord>
#include "json.hpp"

using JSON = nlohmann::json;

class Favorito
{

public:
    Favorito(int m_idUsuario, int m_idPlanta);
    bool save();
    void load();

private:
    int m_id{0};
    int m_idUsuario{0};
    int m_idPlanta{0};

};

#endif // FAVORITO_H
