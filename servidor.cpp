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

    std::cout << "Iniciando servidor en el puerto " << this->m_puerto << std::endl;

    /*
    ix::SocketTLSOptions webSocketTLS;
    webSocketTLS.tls = true;
    webSocketTLS.keyFile = "./cert/localhost/localhost.key";
    webSocketTLS.certFile = "./cert/localhost/localhost.crt";
    webSocketTLS.caFile = "NONE";

    server.setTLSOptions(webSocketTLS);
    */

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

                return ultimasBusquedas(mensaje);

            } // end if

            /// Devolver búsqueda del usuario
            if(mensaje["action"] == "buscar")
            {

                return busquedaUsuario(mensaje);

            } // end if

            /// Crear nuevo usuario
            if(mensaje["action"] == "crearUsuario")
            {

                /// 1. Insert Tabla usuario
                std::cout << "Crear usuario" << std::endl;
                resultado["id"] = mensaje["id"];

                std::string nombre = mensaje["nombre"];
                std::string pass = mensaje["pass"];
                std::string email = mensaje["email"];

                Usuario usuario(nombre, pass, email);
                usuario.save();

                /// 2. Generar Token e insert Tabla token
                Token token;
                QString tokenString = token.generateToken();
                token.insert(tokenString, usuario.getId());

                /// 3. Enviar email e insert Tabla envio_email
                Email e;

                std::string tokn = tokenString.toUtf8().constData();
                QString path = QDir::currentPath();
                QString indexPath = "file://" + path + "/WebUsuario/index.html?token=" + QString::fromUtf8(tokn.c_str());

                e.sendEmail(usuario.getEmail(),"Verificar email", indexPath.toUtf8().constData());
                e.insert(usuario.getId());

                /// 4. Enviar JSON
                JSON usuarioJSON = usuario.toJSON();
                resultado["resultado"][0] = usuarioJSON;

                return resultado;

            } // end if

            /// Cargar usuario
            if(mensaje["action"] == "cargarUsuario")
            {

                return cargarUsuario(mensaje);

            } // end if

            /// Cargar planta
            if(mensaje["action"] == "cargarPlanta")
            {

                return cargarPlanta(mensaje);

            } // end if

            /// Queja
            if(mensaje["action"] == "queja")
            {

                return queja(mensaje);

            } // end if

            /// Check favorito
            if(mensaje["action"] == "checkLike")
            {

                return checkFavorito(mensaje);

            } // end if

            /// Cargar favorito
            if(mensaje["action"] == "cargarFavorito")
            {

                return cargarFavorito(mensaje);

            } // end if

            /// Cargar lista favoritos
            if(mensaje["action"] == "listaFavoritos")
            {

                return listaFavortitos(mensaje);

            } // end if

            /// Cargar perfil
            if(mensaje["action"] == "perfil")
            {

                return cargarPerfil(mensaje);

            } // end if

            /// Modificar perfil
            if(mensaje["action"] == "modificarUser")
            {

                return modificarPerfil(mensaje);

            }

            /// Check token
            if(mensaje["action"] == "checkToken")
            {

                return checkToken(mensaje);

            }

            /// Lista usuarios
            if(mensaje["action"] == "listaUsuarios")
            {

                return listaUsuarios(mensaje);

            }

        } // end if

    } // end if

    return resultado;

}

bool Servidor::exists(const JSON& json, const std::string& key)
{
    return json.find(key) != json.end();
}

JSON Servidor::ultimasBusquedas(const JSON& mensaje)
{

    JSON resultado;

    std::cout << "Devolver ultimas búsquedas" << std::endl;
    resultado["id"] = mensaje["id"];

    std::list<Planta> lista = Planta::find("p");
    unsigned long contador = 0;
    for(Planta planta : lista)
    {

        JSON plantaJSON = planta.toJSON();
        resultado["resultado"][contador] = plantaJSON;

        contador++;
    }

    return resultado;

}

JSON Servidor::busquedaUsuario(const JSON& mensaje)
{

    JSON resultado;

    std::cout << "Devolver búsqueda" << std::endl;
    resultado["id"] = mensaje["id"];
    std::string buscar = mensaje["busqueda"];

    std::list<Planta> lista = Planta::find(buscar);
    unsigned long contador = 0;
    for(Planta planta : lista)
    {

        JSON plantaJSON = planta.toJSON();
        resultado["resultado"][contador] = plantaJSON;

        contador++;

    }

    return resultado;

}

JSON Servidor::cargarUsuario(const JSON& mensaje)
{

    JSON resultado;

    std::cout << "Cargar usuario" << std::endl;
    resultado["id"] = mensaje["id"];

    Usuario usuario = Usuario::load(mensaje["email"], mensaje["pass"]);
    JSON usuarioJSON = usuario.toJSON();
    resultado["resultado"][0] = usuarioJSON;

    return resultado;

}

JSON Servidor::cargarPlanta(const JSON& mensaje)
{

    JSON resultado;

    std::cout << "Cargar planta" <<std::endl;
    resultado["id"] = mensaje["id"];

    Planta planta = Planta::load(mensaje["nombre"], mensaje["nombreCientifico"]);
    JSON plantaJSON = planta.toJSON();
    resultado["resultado"][0] = plantaJSON;

    return resultado;

}

JSON Servidor::queja(const JSON& mensaje)
{

    JSON resultado;

    std::cout << "Responder queja" <<std::endl;
    resultado["id"] = mensaje["id"];

    int idUsuario = mensaje["idUsuario"];
    std::string quejaValor = mensaje["queja"];
    Queja queja(idUsuario, quejaValor);
    queja.save();

    return resultado;

}

JSON Servidor::checkFavorito(const JSON& mensaje)
{

    JSON resultado;

    std::cout << "Check like" << std::endl;
    resultado["id"] = mensaje["id"];

    Planta planta = Planta::load(mensaje["nombrePlanta"], mensaje["nombreCientifico"]);
    Favorito favorito(mensaje["idUsuario"], planta.getId());

    bool check = favorito.check();
    JSON favoritoJSON = favorito.toJSON();
    favoritoJSON["check"] = check;
    resultado["resultado"][0] = favoritoJSON;

    return resultado;

}

JSON Servidor::cargarFavorito(const JSON& mensaje)
{

    JSON resultado;

    std::cout << "Cargar favorito" << std::endl;
    resultado["id"] = mensaje["id"];

    Planta planta = Planta::load(mensaje["nombre"], mensaje["nombreCientifico"]);
    Favorito favorito(0, 0);
    favorito.load(mensaje["idUsuario"], planta.getId());

    resultado["resultado"][0] = favorito.toJSON();

    return resultado;

}

JSON Servidor::listaFavortitos(const JSON& mensaje)
{

    JSON resultado;

    std::cout << "Lista favoritos" << std::endl;
    resultado["id"] = mensaje["id"];

    std::list<Planta> lista = Favorito::find(mensaje["idUsuario"]);
    unsigned long contador = 0;
    for(Planta planta : lista)
    {

        JSON plantaJSON = planta.toJSON();
        resultado["resultado"][contador] = plantaJSON;

        contador++;

    }

    return resultado;

}

JSON Servidor::cargarPerfil(const JSON& mensaje)
{

    JSON resultado;

    std::cout << "Perfil" << std::endl;
    resultado["id"] = mensaje["id"];

    Usuario usuario("", "", "");
    usuario.load(mensaje["idUsuario"]);

    resultado["resultado"][0] = usuario.toJSON();

    return resultado;

}

JSON Servidor::modificarPerfil(const JSON& mensaje)
{

    JSON resultado;

    std::cout << "Modificar perfil" << std::endl;
    resultado["id"] = mensaje["id"];

    Usuario usuario("", "", "");
    usuario.load(mensaje["idUsuario"]);

    if(usuario.getNombre() != mensaje["nombre"]) usuario.update();

    resultado["resultado"][0] = usuario.toJSON();

    return resultado;

}

JSON Servidor::checkToken(const JSON& mensaje)
{

    JSON resultado;

    std::cout << "Comprobar token" <<std::endl;
    resultado["id"] = mensaje["id"];

    bool correct = Token::checkToken(mensaje["token"]);

    JSON respuesta;
    respuesta["tokenCorrect"] = correct;

    resultado["resultado"][0] = respuesta;

    return resultado;

}

JSON Servidor::listaUsuarios(const JSON& mensaje)
{

    JSON resultado;

    std::cout << "Lista usuarios" << std::endl;
    resultado["id"] = mensaje["id"];

    std::list<Usuario> usuarios = Usuario::find();
    unsigned long contador = 0;
    for(Usuario usuario : usuarios)
    {

        JSON usuarioJSON = usuario.toJSON();
        resultado["resultado"][contador] = usuarioJSON;

        contador++;

    }

    return resultado;

}










