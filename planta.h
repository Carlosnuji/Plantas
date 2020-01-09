#ifndef PLANTA_H
#define PLANTA_H

#include <string>
#include "json.hpp"

using JSON = nlohmann::json;

class Planta
{

public:
    Planta(int, std::string, std::string, std::string);
    JSON toJSON();
    Planta fromJSON(JSON);

private:
    int id;
    std::string nombre;
    std::string nombreCientifico;
    std::string descripcion;

};

#endif // PLANTA_H
