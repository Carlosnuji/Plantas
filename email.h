#ifndef EMAIL_H
#define EMAIL_H

#include <string>
#include <map>
#include <QSqlQuery>
#include <QSqlRecord>

class Email
{

public:
    Email();
    void sendEmail(std::string toEmail, std::string subject, std::string texto);
    void insert(int idusuario);

private:
    int m_puerto{0};
    std::string m_server;
    std::string m_user;
    std::string m_password;
    std::map<std::string, std::string> m_propiedades;
    void loadProperties();
    void readFile();
    void processLine(std::string line);

};

#endif // EMAIL_H
