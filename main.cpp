#include <iostream>
#include "ixwebsocket/IXWebSocketServer.h"
#include "ixwebsocket/IXWebSocket.h"
#include "ixwebsocket/IXConnectionState.h"
#include "json.hpp"
#include "servidor.h"
#include "conexion.h"
#include "planta.h"

int main()
{

    Conexion con;
    con.open();

    /*
    QSqlQuery q;
    bool result = q.exec("SELECT * FROM planta");

    if(result)
    {
        QSqlRecord rec = q.record();
        while (q.next())
        {
            qDebug() << q.value("nombre").toString() << q.value("nombreCientifico").toString();
        } // end while
    } // end if
    */

    Servidor servidor(9990);
    return servidor.startServidor();

}
