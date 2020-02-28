#ifndef QUEJA_H
#define QUEJA_H

#include <string>
#include <list>
#include "basedatos.h"
#include "json.hpp"

using JSON = nlohmann::json;

/**
 * @brief Clase para el manejo de las quejas en la base de datos.
 *
 * Con esta clase de podrá crear y elminar una queja, cargar una queja de un usuario,
 * obtener una lista de todas las quejas de un usuario y crear un JSON de la clase para
 * enviar al cliente.
 * @code
 * int main()
 * {
 *     Queja queja(1, "Queja");
 *     queja.save();
 *     queja.load(1);
 *     Queja::remove(1);
 *     Queja::find(1);
 * }
 * @endcode
 */

class Queja : public BaseDatos
{

public:
    Queja(int idUsuario, std::string queja);
    /**
     * @brief Crea un JSON de la queja.
     *
     * Usando la libreria nlohmann/json se crea un JSON de la queja que es el que se enviará al cliente.
     * @return JSON de la queja.
     */
    JSON toJSON();
    /**
     * @brief Guarda la queja en la base de datos.
     *
     * Hace un insert en la base datos con las propiedades que le hayamos indicado de la queja.
     */
    bool save();
    /**
     * @brief Carga una queja de la base de datos.
     *
     * A partir del id de la queja se hace un select de la queja filtrando por su id y cargar
     * las propiedades de la queja.
     * @param id - Id de la queja en la base de datos.
     */
    bool load(const int id);
    /**
     * @brief Elimina una queja de la base de datos.
     *
     * Hace un delete de la queja a partir del id de la queja que se le pase.
     * @param id - Id de la queja
     */
    static void remove(int id);
    /**
     * @brief Busca todas las quejas del usuario indicado.
     *
     * Hace una select en la base de datos de todas las quejas
     * filtrando por el usuario que se indique y devuelve una lista de dichas quejas.
     * @param idUsuario - Id del usuario.
     * @return Lista de quejas del usuario.
     */
    static std::list<Queja> find(int idUsuario);
    /**
     * @brief Obtener el id de la queja.
     * @return Id de la queja.
     */
    int getId();
    /**
     * @brief Obtener id del usuario de la queja.
     * @return Id del usuario.
     */
    int getIdUsuario();
    /**
     * @brief Obtener el tetxo de la queja.
     * @return Texto de la queja.
     */
    std::string getQueja();
    void setQueja(std::string queja);

private:
    /**
     * @brief Id de la queja.
     */
    int m_id{0};
    /**
     * @brief Id del usuario.
     */
    int m_idUsuario{0};
    /**
     * @brief Texto de la queja.
     */
    std::string m_queja{""};

};

#endif // QUEJA_H



















