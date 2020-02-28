#ifndef PLANTA_H
#define PLANTA_H

#include <string>
#include <list>
#include <QSqlQuery>
#include <QSqlRecord>
#include "json.hpp"

using JSON = nlohmann::json;

/**
 * @brief Clase para el manejo de las plantas de la base de datos.
 *
 * Con esta clase se podrá crear, eliminar, cargar, actualizar y buscar plantas en la
 * base de datos. A su vez se podrá crear un JSON de la clase.
 * @code
 * int main()
 * {
 *     Planta planta("Nombre", "Nombre científico", "Descripción");
 *     planta.save();
 *     planta.load(2);
 *     planta.toJSON();
 *     planta.remove();
 *     Planta::find("Nombre planta")
 * }
 * @endcode
 */
class Planta
{

public:
    Planta(std::string nombre, std::string nombreCientifico, std::string descripcion);
    /**
     * @brief Crea JSON de la planta.
     *
     * Usando la libreria nlohmann/json creamos un JSON que es el que se enviará al cliente.
     * @return JSON de la planta.
     */
    JSON toJSON();
    /**
     * @brief Guarda la planta en la base de datos.
     *
     * Hace un insert en la base datos con las propiedades que le hayamos indicado a la planta.
     */
    bool save();
    /**
     * @brief Carga una planta de la base de datos.
     *
     * A partir de un nombre y nombre científico se hace un select de la base de datos
     * de la respectiva planta.
     * @param nombre - Nombre de la planta.
     * @param nombreCientifico - Nombre científico de la planta.
     * @return
     */
    static Planta load(std::string nombre, std::string nombreCientifico);
    /**
     * @brief Carga una planta de la base de datos.
     *
     * A partir del id de la planta se hace un select en la base de datos y se recupera
     * la información de la planta.
     * @param id - Id de la planta de la base de datos.
     */
    bool load(int id);
    /**
     * @brief Elimina una planta de la base de datos.
     *
     * Hace un delete de la base de datos a partir del id del usuario que el pasemos.
     * @param id - Id del usuario de la base de datos.
     */
    void remove(int id);
    /**
     * @brief Busca todas las plantas con el nombre que se le pase.
     *
     * Hace un select en la base de datos de todas las plantas con el nombre o que contengan ese
     * texto en su nombre y devuelve una lista de plantas con el resultado.
     * @param nombre - Nombre de la planta.
     * @return - Lista de plantas que ha encontrado.
     */
    static std::list<Planta> find(std::string nombre);
    ~Planta();
    /**
     * @brief Devuelve el id de la planta;
     * @return Id de la planta.
     */
    int getId();
    /**
     * @brief Obtener el nombre de la planta.
     * @return Nombre de la planta
     */
    std::string getNombre();
    /**
     * @brief Obtener el nombre científico
     * @return Nombre científico
     */
    std::string getNombreCientifico();
    /**
     * @brief Obtener descripción de la planta.
     * @return Descripción de la planta.
     */
    std::string getDescripcion();

private:
    /**
     * @brief Id de la planta.
     */
    int m_id{0};
    /**
     * @brief Nombre de la planta.
     */
    std::string m_nombre{""};
    /**
     * @brief Nombre científico de la planta.
     */
    std::string m_nombreCientifico{""};
    /**
     * @brief Descripción de la planta.
     */
    std::string m_descripcion{""};

};

#endif // PLANTA_H
















