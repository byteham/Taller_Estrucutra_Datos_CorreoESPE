#pragma once
#include <string>

struct Nodo {
    std::string cedula;
    std::string nombre1;
    std::string nombre2;
    std::string apellido1;
    std::string apellido2;
    std::string correo;
    Nodo* anterior;
    Nodo* siguiente;

    Nodo(const std::string& ced, const std::string& n1, const std::string& n2,
         const std::string& a1, const std::string& a2, const std::string& mail)
        : cedula(ced), nombre1(n1), nombre2(n2), apellido1(a1), apellido2(a2),
          correo(mail), anterior(nullptr), siguiente(nullptr) {}
};
