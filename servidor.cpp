#include "servidor.h"

Servidor::Servidor(int puerto)
{

    this->m_puerto = puerto;

}

int Servidor::startServidor()
{

    //Crea un servidor
    ix::WebSocketServer server(this->m_puerto, "0.0.0.0");

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
                    this->nuevoMensajeJSON(receivedObject);

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

void Servidor::nuevoMensajeJSON(const JSON &mensaje)
{

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

            } // end if

        }

    } // end if

}

bool Servidor::exists(const JSON& json, const std::string& key)
{
    return json.find(key) != json.end();
}



















