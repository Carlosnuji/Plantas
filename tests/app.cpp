#include "app.h"
#include "doctest.h"
#include "db.h"
#include <QDebug>

App::App()
{

}

TEST_CASE("Test base datos")
{

    /// Iniciar base datos
    Db database;
    CHECK(database.init() == true);

    /// Insert planta
    std::vector<std::string> campos{"nombre", "nombreCientifico", "descripcion"};
    std::vector<std::string> valores{"planta", "plantibiris", "descripcion planta"};
    CHECK(database.insert("planta", campos, valores) == true);

    /// Insert usuario
    std::vector<std::string> campos1{"nombre", "password", "email"};
    std::vector<std::string> valores1{"carlos", "carlos123", "carlos@gmail.com"};
    CHECK(database.insert("usuario", campos1, valores1) == true);

}


