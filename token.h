#ifndef TOKEN_H
#define TOKEN_H

#include <QString>
#include <QUuid>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QString>
#include <QSqlError>
#include <QDebug>

/**
 * @brief Clase para el manejo y generación de tokens.
 *
 * Con esta clase se podrá crear, insertar en la base de datos o comprobar si
 * un token existe en la base de datos.
 * @code
 * int main()
 * {
 *     Token token();
 *     QString tokenString = token.generateToken();
 *     token.insert(tokenString, 1);
 *     Token::checkToken(tokenString);
 * }
 * @endcode
 */

class Token
{

public:
    Token();
    /**
     * @brief Genera un token aleatorio.
     *
     * A partir del Quuid de Qt genera un token aleatorio y devolvemos
     * dicho token.
     * @return Token generado.
     */
    QString generateToken();
    /**
     * @brief insert
     *
     * Guarda el token generado y el usuario que lo ha pedido en la
     * base de datos.
     * @param uuid - Token generado.
     * @param idusuario - Id del usuario.
     */
    bool insert(QString uuid, int idusuario);
    /**
     * @brief Comprueba si el token que se le pasa existe.
     *
     * Hace una select en la base de datos mirando si existe el token
     * que se le ha pasado y si existe se actualiza el estado del usuario.
     * @param Token que se evalua.
     * @return True si existe el token, False si no existe.
     */
    static bool checkToken(std::string token);

private:


};

#endif // TOKEN_H


















