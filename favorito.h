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

/**
 * @brief Clase para el manejo de los favoritos de los usuarios.
 *
 * Se podrá crear e insertar un nuevo favorito en la base de datos y eliminarlo,
 * comprobar si esa planta la tiene el usuario en favorito o no y buscar
 * todas las plantas que tiene en favoritos un usuario.
 * @code
 * int main()
 * {
 *     Favorito favorito(1, 1);
 *     favorito.load();
 *     bool b = favorito.check();
 *     favorito.find(1);
 * }
 * @endcode
 */
class Favorito
{

public:
    Favorito(int m_idUsuario, int m_idPlanta);
    /**
     * @brief Crea un JSON de la clase.
     *
     * A partir de las propiedades de la clase se genera un JSON usando la libreria nlohmann/json descargada en GitHub.
     * @return El JSON generado.
     */
    JSON toJSON();
    /**
     * @brief Carga un favorito de la base de datos a partir de un usuario  y una planta.
     *
     * Hace una select en la base de datos cogiendo el idusuario y el idplanta y lo carga en la clase.
     * @param idUsuario - El id del ususario
     * @param idPlanta - El id de la planta
     */
    bool load(int idUsuario, int idPlanta);
    /**
     * @brief Comprueba si esa planta la tiene en favoritos el usuario.
     *
     * Hace un select haciendo un count y si devuelve 1 o más la tiene en favorito.
     * Si la tiene en favorito lo eliminamos y si no la tiene la añadimos a favorito.
     * @return True si la tiene en favorito y false si no la tiene en favorito.
     */
    bool check();
    /**
     * @brief Busca todas las plantas que tiene en favoritos un usuario
     *
     * Hace un select en la base de datos filtrando por el usuario que se quiera y devuelve
     * una lista de plantas, que son las que tiene el usuario en favoritos.
     * @param IdUsuario - El usuario del cual se quiere filtrar.
     * @return Lista de plantas a las que tiene en favorito el usuario.
     */
    static std::list<Planta> find(int idUsuario);
    /**
     * @brief Saber el id del usuario.
     * @return Id del usuario.
     */
    int getIdUsuario();
    /**
     * @brief Saber el id de la planta.
     * @return Id de la planta.
     */
    int getIdPlanta();

private:
    /**
     * @brief Id favorito de la base de datos.
     */
    int m_id{0};
    /**
     * @brief Id del usuario.
     */
    int m_idUsuario{0};
    /**
     * @brief Id de la planta.
     */
    int m_idPlanta{0};

};

#endif // FAVORITO_H











