#ifndef PLANTA_H
#define PLANTA_H

#include <string>
#include <list>
#include <QSqlQuery>
#include <QSqlRecord>
#include "json.hpp"

using JSON = nlohmann::json;

class Planta
{

public:
    Planta(std::string nombre, std::string nombreCientifico, std::string descripcion);
    JSON toJSON();
    Planta fromJSON(JSON);
    void save();
    static Planta load(int);
    void remove(int);
    static std::list<Planta> find(std::string);
    ~Planta();
    std::string getNombre();
    std::string getNombreCientifico();
    std::string getDescripcion();

private:
    int m_id{0};
    std::string m_nombre{""};
    std::string m_nombreCientifico{""};
    std::string m_descripcion{""};

};

#endif // PLANTA_H
