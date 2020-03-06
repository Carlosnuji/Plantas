#ifndef USUARIO_H
#define USUARIO_H

#include <string>
#include <list>
#include "basedatos.h"
#include "json.hpp"

using JSON = nlohmann::json;

/**
 * @brief Clase para el manejo de los usuarios de la base de datos.
 *
 * Con esta clase se podrá crear, eliminar, cargar, actualizar y buscar usuarios en la
 * base de datos. A su vez se podrá crear un JSON de la clase.
 * @code
 * int main()
 * {
 *     Usuario usuario("name", "pass", "email");
 *     usuario.save();
 *     usuario.load(1);
 *     usuario.update("nombre", "email", 1);
 *     usuario.toJSON();
 *     Usuario::remove(1);
 * }
 * @endcode
 */

class Usuario : public BaseDatos
{

public:
    Usuario(std::string nombre, std::string password, std::string email);
    /**
     * @brief Crea JSON del usuario.
     *
     * Usando la libreria nlohmann/json creamos un JSON que es el que se enviará al cliente.
     * @return JSON del usuario.
     */
    JSON toJSON();
    /**
     * @brief Guarda el usuario en la base de datos.
     *
     * Hace un insert en la base datos con las propiedades que le hayamos indicado al usuario.
     * @return True si se ha guardado con éxito sino devolverá false.
     */
    bool save();
    /**
     * @brief Carga un usuario de la base de datos.
     *
     * A partir de un email y contraseña se hace un select de la base de datos
     * del respectivo usuario.
     * @param email - Email del usuario.
     * @param password - Contraseña del usuario.
     * @return
     */
    static Usuario load(std::string email, std::string password);
    /**
     * @brief Elimina un usuario de la base de datos.
     *
     * Hace un delete de la base de datos a partir del id del usuario que el pasemos.
     * @param id
     */
    static void remove(int id);
    /**
     * @brief Carga un usuario de la base de datos.
     *
     * A partir del id del usuario hace un select de la base de datos
     * del respectivo usuario.
     * @param id - Id del usuario.
     */
    bool load(const int id);
    /**
     * @brief Actualiza las propiedades del usuario en la base de datos.
     *
     * Hace un update del usuario y actualiza el nombre, email y estatus del usuario
     * por el que se le indica.
     * @param nombre - Nombre del usuario.
     * @param email - Email del usuario.
     * @param status - Estado del usuario.
     */
    bool update();
    /**
     * @brief Buscar todos los usuario de la base de datos.
     * @return Lista usuarios.
     */
    static std::list<Usuario> find();
    /**
     * @brief Obtener el id del usuario.
     * @return Id del usuario.
     */
    int getId();
    /**
     * @brief Obtiene el nombre del usuario.
     * @return Nombre del usuario.
     */
    std::string getNombre();
    /**
     * @brief Obtiene la contraseña del usuario.
     * @return Contraseña del usuario.
     */
    std::string getPassword();
    /**
     * @brief Obtiene el email de usuario.
     * @return Email del usuario.
     */
    std::string getEmail();
    /**
     * @brief Obtiene el status del usuario.
     * @return Status del usuario.
     */
    int getStatus();
    void setNombre(std::string nombre);
    void setEmail(std::string email);
    void setStatus(int status);
    void setAdmin(int admin);

private:
    /**
     * @brief Id del usuario.
     */
    int m_id{0};
    /**
     * @brief Nombre del usuario.
     */
    std::string m_nombre{""};
    /**
     * @brief Contraseña del usuario.
     */
    std::string m_password{""};
    /**
     * @brief Email del usuario.
     */
    std::string m_email{""};
    /**
     * @brief Status del usuario.
     */
    int m_status{0};
    /**
     * @brief Saber si el usuario es administardor;
     */
    int m_admin{0};

};

#endif // USUARIO_H


















