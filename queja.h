#ifndef QUEJA_H
#define QUEJA_H

#include <string>
#include <list>
#include <QSqlQuery>
#include <QSqlRecord>
#include "json.hpp"

using JSON = nlohmann::json;

class Queja
{

public:
    Queja(int idUsuario, std::string queja);
    JSON toJSON();
    void save();
    void load(int id);
    static void remove(int id);
    static std::list<Queja> find(int idUsuario);
    int getId();
    int getIdUsuario();
    std::string getQueja();
    void setQueja(std::string queja);

private:
    int m_id{0};
    int m_idUsuario{0};
    std::string m_queja{""};

};

#endif // QUEJA_H
