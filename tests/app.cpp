#include "app.h"
#include "doctest.h"
#include "db.h"

App::App()
{

}

int App::suma(int num1, int num2)
{

   return num1 + num2;

}

TEST_CASE("database")
{

    Db database;
    CHECK(database.init() == true);

}
