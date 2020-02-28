#ifndef EMAIL_H
#define EMAIL_H

/**
 * @brief Clase para poder crear Emails.
 *
 * Sirve para poder enviar emails via smpt gracias a la libreria SimpleMail
 * descargada desde GitHub.
 * @code
 * int main()
 * {
 *     Email email();
 *     email.sendEmail("toTest@gmail.com", "Subject", "Text");
 *     email.insert(1);
 * }
 * @endcode
 */

#include <string>
#include <map>
#include <QSqlQuery>
#include <QSqlRecord>

class Email
{

public:
    Email();
    /**
     * @brief Poder enviar un email via smtp.
     *
     * Se crea un objeto Sender de la libreria SimpleMail y se cargar las propiedades necesarias como,
     * el usuario, la contraseña, el servidor y el envio mediante SSL.
     * Se añaden la dirección, el asunto y el texto y se envia el email.
     * @param toEmail - Dirección a la que se va a enviar el email.
     * @param subject - El asunto del email.
     * @param texto - Texto que se enviará en el email.
     */
    void sendEmail(std::string toEmail, std::string subject, std::string texto);
    /**
     * @brief Insertar en la tabla envio_email el email que hayamos enviado.
     * @param idusuario - Id del usuario al que se le envia el email.
     */
    void insert(int idusuario);

private:
    /**
     * @brief Puerto que utiliza.
     */
    int m_puerto{0};
    /**
     * @brief Servidor al que se conecta para enviar el email.
     */
    std::string m_server;
    /**
     * @brief Dirección de correo con la que se envia el email.
     */
    std::string m_user;
    /**
     * @brief Contraseña del usuario.
     */
    std::string m_password;
    /**
     * @brief Mapa donde se guardan las propiedades de la conexión con el servidor de email.
     */
    std::map<std::string, std::string> m_propiedades;
    /**
     * @brief Carga las propiedades del email.
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

#endif // EMAIL_H














