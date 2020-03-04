#include <iostream>
#include "ixwebsocket/IXWebSocketServer.h"
#include "ixwebsocket/IXWebSocket.h"
#include "ixwebsocket/IXConnectionState.h"
#include "json.hpp"
#include "servidor.h"
#include "conexion.h"
#include "planta.h"
#include "usuario.h"
#include "queja.h"
#include "favorito.h"
#include "email.h"
#include "token.h"
#include <QDebug>
#include <QDir>

int main()
{

    /// 1) Abrir conexión con la base de datos
    Conexion con;
    con.open();

    /// 2) Iniciar servidor
    Servidor servidor(9990);
    return servidor.startServidor();

}
