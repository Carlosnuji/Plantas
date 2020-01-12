#include <iostream>
#include "ixwebsocket/IXWebSocketServer.h"
#include "ixwebsocket/IXWebSocket.h"
#include "ixwebsocket/IXConnectionState.h"
#include "json.hpp"
#include "servidor.h"
#include "conexion.h"
#include "planta.h"
#include "usuario.h"

int main()
{

    Conexion con;
    con.open();

    Servidor servidor(9990);
    return servidor.startServidor();

}
