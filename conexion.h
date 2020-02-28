#ifndef CONEXION_H
#define CONEXION_H

/**
 * @brief Clase para el manejo de la conexión con la base de datos.
 *
 * Se podrá abrir la conexión con la base de datos a partir de la lectura
 * de un archivo de configuración y guardara sus propiedades.
 * Se necesita los includes de qtsql para poder hacer la conexión.
 * @code
 * int main()
 * {
 *     Conexion conexion();
 *     conexion.open();
 *     conexion.close();
 * }
 * @endcode
 */

#include <iostream>
#include <string>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QString>
#include <map>

class Conexion
{

public:
    Conexion();
    /**
     * @brief Abre conexión con la base de datos.
     * @return true si hay conexión, false si no hay conexión.
     */
    bool open();
    /**
     * @brief Cierra la conexión con la base de datos.
     */
    void close();

private:
    /**
     * @brief Base de datos que se usuará.
     */
    QSqlDatabase m_db;
    /**
     * @brief Nombre del host o ip.
     */
    QString m_hostName;
    /**
     * @brief Nombre de la base de datos
     */
    QString m_databaseName;
    /**
     * @brief Puerto que utiliza la base de datos
     */
    int m_port;
    /**
     * @brief Nombre del usuario de la base de datos
     */
    QString m_userName;
    /**
     * @brief Contraseña del usuario de la base de datos
     */
    QString m_password;
    /**
     * @brief Mapa donde se guardarán las propiedades de la base de datos
     */
    std::map<std::string, std::string> m_propiedades;
    /**
     * @brief Carga las propiedades de la base de datos.
     *
     * Llama al método readFile para leer el archivo de configuración y
     * guarda las propiedas que están en el map m_propiedades.
     * @see readFile()
     */
    void loadProperties();
    /**
     * @brief Lee el archivo de configuración de la base de datos.
     *
     * A partir de la ruta del archivo, abre el archivo y lo lee
     * linea por linea y se llama al metodo precessLine para guardar
     * las propiedades.
     * @see processLine();
     */
    void readFile();
    /**
     * @brief Procesa cada linea del archivo de configuración.
     *
     * Se le pasa una linea del archivo de configuración y añade al map
     * m_popiedades su clave y valor.
     * @param Linea del archivo de configuración.
     */
    void processLine(std::string line);

};

#endif // CONEXION_H


















