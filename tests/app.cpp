#include "app.h"
#include "doctest.h"
#include "db.h"
#include "../usuario.h"
#include "../planta.h"
#include "../token.h"
#include "../queja.h"
#include "../favorito.h"
#include "../json.hpp"
#include <QDebug>

using JSON = nlohmann::json;

App::App()
{

}

TEST_CASE("01 Test base datos")
{

    /// Iniciar base datos
    Db database;
    CHECK(database.init() == true);

}

TEST_CASE("02 Usuario")
{

    Usuario usuario("test", "test123", "test@gmail.com");

    CHECK(usuario.save() == true);

    CHECK(usuario.load(1) == true);

    CHECK(usuario.getId() == 1);

    CHECK(usuario.getNombre() == "test");

    CHECK(usuario.getEmail() == "test@gmail.com");

    CHECK(usuario.getStatus() == 0);

}

TEST_CASE("03 Planta")
{

    Planta planta("Nombre", "Nombre científico", "Descripción");

    CHECK(planta.save() == true);

    CHECK(planta.load(1) == true);

    CHECK(planta.getId() == 1);

    CHECK(planta.getNombre() == "Nombre");

    CHECK(planta.getNombreCientifico() == "Nombre científico");

    CHECK(planta.getDescripcion() == "Descripción");

}

TEST_CASE("04 Token")
{

    Token token;
    QString tokenString{token.generateToken()};
    int idUsuario{1};

    CHECK(token.insert(tokenString, idUsuario) == true);

    CHECK(token.checkToken(tokenString.toUtf8().constData()) == true);

}

TEST_CASE("05 Queja")
{

    int idUsuario{1};
    Queja queja(idUsuario, "Esto es una queja");

    CHECK(queja.save() == true);

    CHECK(queja.load(idUsuario) == true);

    CHECK(queja.getId() == 1);

    CHECK(queja.getIdUsuario() == 1);

}

TEST_CASE("06 Favorito")
{

    int idUsuario{1};
    int idPlanta{1};
    Favorito favorito(idUsuario, idPlanta);

    CHECK(favorito.check() == false);

    CHECK(favorito.load(idUsuario, idPlanta) == true);

    CHECK(favorito.getIdUsuario() == idUsuario);

    CHECK(favorito.getIdPlanta() == idPlanta);

    CHECK(favorito.check() == true);

}





















