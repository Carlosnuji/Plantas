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

class Servidor
{

public:
    Servidor(int);
    int startServidor();

private:
    int m_puerto{9990};
    static bool exists(const JSON&, const std::string&);
    JSON nuevoMensajeJSON(const JSON&);

};

#endif // SERVIDOR_H
