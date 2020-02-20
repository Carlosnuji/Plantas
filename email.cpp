#include "email.h"
#include <sender.h>
#include <mimemessage.h>
#include <emailaddress.h>
#include <mimetext.h>
#include <QString>
#include <QFile>
#include <iostream>

Email::Email()
{

    loadProperties();

}

void Email::insert(int idusuario)
{

    QSqlQuery query;
    query.prepare("INSERT INTO envio_email (idusuario) VALUES (:idusuario)");

    query.bindValue(":idusuario", QString::number(idusuario));
    query.exec();

}

void Email::sendEmail(std::string toEmail, std::string subject, std::string texto)
{

    SimpleMail::Sender sender(QString::fromUtf8(m_server.c_str()), m_puerto, SimpleMail::Sender::SslConnection);

    sender.setUser(QString::fromUtf8(m_user.c_str()));
    sender.setPassword(QString::fromUtf8(m_password.c_str()));

    SimpleMail::MimeMessage message;
    message.setSender(SimpleMail::EmailAddress("carlosnuji97@gmail.com", "Carlos"));
    message.addTo(SimpleMail::EmailAddress(QString::fromUtf8(toEmail.c_str())));
    message.setSubject(QString::fromUtf8(subject.c_str()));

    SimpleMail::MimeText text;

    text.setText(QString::fromUtf8(texto.c_str()));

    message.addPart(&text);

    sender.sendMail(message);

}

void Email::loadProperties()
{

    readFile();

    m_puerto = std::atoi(m_propiedades["puerto"].c_str());
    m_server = m_propiedades["server"];
    m_user = m_propiedades["user"];
    m_password = m_propiedades["password"];

}

void Email::processLine(std::string line)
{

    std::string newLine = line.substr(0, line.rfind("\n"));

    std::string clave = newLine.substr(0, newLine.rfind("="));
    std::string valor = newLine.substr(newLine.rfind("=") + 1, newLine.size());

    m_propiedades[clave] = valor;

}

void Email::readFile()
{

    QString nombreArchivo = "/home/usuario/ProyectoPlantas/ServerPlantas/SimpleMail/mail.conf";

    if(QFile::exists(nombreArchivo) ){

        QFile file(nombreArchivo);


        if(file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            while(!file.atEnd())
            {
                std::string line = QString(file.readLine()).toUtf8().constData();
                processLine(line);

            }
        } // end if

    }
    else
    {
        qDebug() << "No se encuentra el archivo " + nombreArchivo;
        exit(0);
    } // end if

}






















