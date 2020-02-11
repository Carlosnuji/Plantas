#include "servidor.h"
#include "ixwebsocket/IXSocketTLSOptions.h"
#include <QDebug>

Servidor::Servidor(int puerto)
{

    this->m_puerto = puerto;

}

int Servidor::startServidor()
{

    //Crea un servidor
    ix::WebSocketServer server(this->m_puerto, "0.0.0.0");

    ix::SocketTLSOptions webSocketTLS;
    webSocketTLS.tls = true;
    webSocketTLS.keyFile = "/home/usuario/cert/localhost/localhost.key";
    webSocketTLS.certFile = "/home/usuario/cert/localhost/localhost.crt";
    webSocketTLS.caFile = "NONE";

    server.setTLSOptions(webSocketTLS);

    server.setOnConnectionCallback(
                [this](std::shared_ptr<ix::WebSocket> webSocket,
                          std::shared_ptr<ix::ConnectionState> connectionState)
    {

        webSocket->setOnMessageCallback(
            [webSocket, connectionState, this](const ix::WebSocketMessagePtr msg)
            {

                if (msg->type == ix::WebSocketMessageType::Open)
                {

                    std::cout << "New connection" << std::endl;

                }
                else if (msg->type == ix::WebSocketMessageType::Close)
                {
                    std::cout << "Bye bye connection" << std::endl;
                }
                else if (msg->type == ix::WebSocketMessageType::Message)
                {
                    if(!msg->binary)
                    {
                        std::cout << msg->str << std::endl;
                    }

                    /// 1) Decodificar JSON
                    JSON receivedObject = JSON::parse(msg->str, nullptr, false);

                    /// 2) Trabajar con el mensaje JSON
                    JSON respuesta = this->nuevoMensajeJSON(receivedObject);

                    /// 3) Enviar respuesta al cliente
                    std::string respuestaCliente = respuesta.dump();
                    webSocket->send(respuestaCliente);

                }
                else if (msg->type == ix::WebSocketMessageType::Error)
                {
                    std::cout << "Error: " << msg->errorInfo.reason << std::endl;
                }

            }
        );

    }
    );

    auto res = server.listen();

    if(!res.first)
    {
        return 1;
    }

    server.start();
    server.wait();
    server.stop();

    return 0;

}

JSON Servidor::nuevoMensajeJSON(const JSON &mensaje)
{

    JSON resultado;

    /// 1) Saber si es un JSON válido
    if(mensaje.is_discarded())
    {
        std::cout << "Error, no es un JSON válido" << std::endl;
    }
    else
    {

        /// 2) Saber si existe action en el JSON
        if(exists(mensaje, "action"))
        {

            /// Devolver Ultimas Busquedas
            if(mensaje["action"] == "ultimasBusquedas")
            {

                std::cout << "Devolver ultimas búsquedas" << std::endl;
                resultado["id"] = mensaje["id"];

                std::list<Planta> lista = Planta::find("p");
                int contador = 0;
                for(Planta planta : lista)
                {

                    JSON plantaJSON = planta.toJSON();
                    resultado["resultado"][contador] = plantaJSON;

                    contador++;

                }

                return resultado;

            } // end if

            /// Devolver búsqueda del usuario
            if(mensaje["action"] == "buscar")
            {

                std::cout << "Devolver búsqueda" << std::endl;
                resultado["id"] = mensaje["id"];
                std::string buscar = mensaje["busqueda"];

                std::list<Planta> lista = Planta::find(buscar);
                int contador = 0;
                for(Planta planta : lista)
                {

                    JSON plantaJSON = planta.toJSON();
                    resultado["resultado"][contador] = plantaJSON;

                    contador++;

                }

                return resultado;

            } // end if

            /// Crear nuevo usuario
            if(mensaje["action"] == "crearUsuario")
            {

                std::cout << "Crear usuario" << std::endl;
                resultado["id"] = mensaje["id"];

                std::string nombre = mensaje["nombre"];
                std::string pass = mensaje["pass"];
                std::string email = mensaje["email"];

                Usuario usuario(nombre, pass, email);
                usuario.save();

                JSON usuarioJSON = usuario.toJSON();
                resultado["resultado"][0] = usuarioJSON;

                return resultado;

            } // end if

            /// Cargar usuario
            if(mensaje["action"] == "cargarUsuario")
            {

                std::cout << "Cargar usuario" << std::endl;
                resultado["id"] = mensaje["id"];

                Usuario usuario = Usuario::load(mensaje["email"], mensaje["pass"]);
                JSON usuarioJSON = usuario.toJSON();
                resultado["resultado"][0] = usuarioJSON;

                return resultado;

            } // end if

            /// Cargar planta
            if(mensaje["action"] == "cargarPlanta")
            {

                std::cout << "Cargar planta" <<std::endl;
                resultado["id"] = mensaje["id"];

                Planta planta = Planta::load(mensaje["nombre"], mensaje["nombreCientifico"]);
                JSON plantaJSON = planta.toJSON();
                resultado["resultado"][0] = plantaJSON;

                return resultado;

            } // end if

            /// Queja
            if(mensaje["action"] == "queja")
            {

                std::cout << "Responder queja" <<std::endl;
                resultado["id"] = mensaje["id"];

                int idUsuario = mensaje["idUsuario"];
                std::string quejaValor = mensaje["queja"];
                Queja queja(idUsuario, quejaValor);
                queja.save();

                return resultado;

            } // end if

            /// Check favorito
            if(mensaje["action"] == "checkLike")
            {

                std::cout << "Check like" << std::endl;
                resultado["id"] = mensaje["id"];

                Planta planta = Planta::load(mensaje["nombrePlanta"], mensaje["nombreCientifico"]);
                Favorito favorito(mensaje["idUsuario"], planta.getId());

                bool check = favorito.check();
                JSON favoritoJSON = favorito.toJSON();
                favoritoJSON["check"] = check;
                resultado["resultado"][0] = favoritoJSON;

            } // end if

            /// Cargar favorito
            if(mensaje["action"] == "cargarFavorito")
            {

                std::cout << "Cargar favorito" << std::endl;
                resultado["id"] = mensaje["id"];

                Planta planta = Planta::load(mensaje["nombre"], mensaje["nombreCientifico"]);
                Favorito favorito(0, 0);
                favorito.load(mensaje["idUsuario"], planta.getId());

                resultado["resultado"][0] = favorito.toJSON();

            } // end if

            /// Cargar lista favoritos
            if(mensaje["action"] == "listaFavoritos")
            {

                std::cout << "Lista favoritos" << std::endl;
                resultado["id"] = mensaje["id"];

                std::list<Planta> lista = Favorito::find(mensaje["idUsuario"]);
                int contador = 0;
                for(Planta planta : lista)
                {

                    JSON plantaJSON = planta.toJSON();
                    resultado["resultado"][contador] = plantaJSON;

                    contador++;

                }

            } // end if

            /// Cargar perfil
            if(mensaje["action"] == "perfil")
            {

                std::cout << "Perfil" << std::endl;
                resultado["id"] = mensaje["id"];

                Usuario usuario("", "", "");
                usuario.load(mensaje["idUsuario"]);

                resultado["resultado"][0] = usuario.toJSON();

            } // end if

            /// Modificar perfil
            if(mensaje["action"] == "modificarUser")
            {

                std::cout << "Modificar perfil" << std::endl;
                resultado["id"] = mensaje["id"];

                Usuario usuario("", "", "");
                usuario.load(mensaje["idUsuario"]);

                if(usuario.getNombre() != mensaje["nombre"]) usuario.update(mensaje["nombre"], mensaje["email"]);

                resultado["resultado"][0] = usuario.toJSON();

            }

        } // end if

    } // end if

    return resultado;

}

bool Servidor::exists(const JSON& json, const std::string& key)
{
    return json.find(key) != json.end();
}



















