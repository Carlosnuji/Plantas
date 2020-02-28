#ifndef SERVIDOR_H
#define SERVIDOR_H

#include<iostream>
#include "ixwebsocket/IXWebSocketServer.h"
#include "ixwebsocket/IXWebSocket.h"
#include "ixwebsocket/IXConnectionState.h"
#include "json.hpp"
#include "planta.h"
#include "usuario.h"
#include "queja.h"
#include "favorito.h"
#include "token.h"
#include "email.h"


using JSON = nlohmann::json;

/**
 * @brief Clase para crear y manejar el servidor.
 *
 * Con esta clase se podrá crear un servidor websocket y enviar y recibir
 * mesnajes con los clinetes.
 * @code
 * int main()
 * {
 *     Servidor server(9999);
 *     server.startServidor();
 * }
 * @endcode
 */

class Servidor
{

public:
    Servidor(int);
    /**
     * @brief Se enciende el servidor.
     *
     * Se crea un servidor websocket en el puerto que se le ha indicado
     * y atenderá a los mensajes recibidos por el cliente.
     */
    int startServidor();

private:
    /**
     * @brief El puerto que utilizará el servidor, por defecto el 9990.
     */
    int m_puerto{9990};
    /**
     * @brief Comprueba si el JSON que se envia existe o no.
     * @return True si existe, false si no existe.
     */
    static bool exists(const JSON&, const std::string&);
    /**
     * @brief Maneja los mensajes JSON que recibe el servidor.
     *
     * Cuando llega un mensaje primero comprueba si existe, sino existe lo descarta,
     * si existe comprueba el action y dependiendo el action crea el mensaje de
     * respuesta que tiene que recibir el cliente.
     * @return JSON que tiene que recibir el cliente.
     */
    JSON nuevoMensajeJSON(const JSON&);
    JSON ultimasBusquedas(const JSON& mensaje);
    JSON busquedaUsuario(const JSON& mensaje);
    JSON cargarUsuario(const JSON& mensaje);
    JSON cargarPlanta(const JSON& mensaje);
    JSON queja(const JSON& mensaje);
    JSON checkFavorito(const JSON& mensaje);
    JSON cargarFavorito(const JSON& mensaje);
    JSON listaFavortitos(const JSON& mensaje);
    JSON cargarPerfil(const JSON& mensaje);
    JSON modificarPerfil(const JSON& mensaje);
    JSON checkToken(const JSON& mensaje);

};

#endif // SERVIDOR_H















