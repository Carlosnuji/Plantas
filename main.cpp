#include <iostream>
#include "ixwebsocket/IXWebSocketServer.h"
#include "ixwebsocket/IXWebSocket.h"
#include "ixwebsocket/IXConnectionState.h"
#include "json.hpp"

int main()
{

    //Crea un servidor
    ix::WebSocketServer server(9990, "0.0.0.0");

    server.setOnConnectionCallback(
                [&server](std::shared_ptr<ix::WebSocket> webSocket,
                          std::shared_ptr<ix::ConnectionState> connectionState)
    {

        webSocket->setOnMessageCallback(
            [webSocket, connectionState, &server](const ix::WebSocketMessagePtr msg)
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

}
