#include <iostream>
#include "ixwebsocket/IXWebSocketServer.h"
#include "ixwebsocket/IXWebSocket.h"
#include "ixwebsocket/IXConnectionState.h"
#include "json.hpp"
#include "servidor.h"

int main()
{

    Servidor servidor(9990);
    return servidor.startServidor();

}
