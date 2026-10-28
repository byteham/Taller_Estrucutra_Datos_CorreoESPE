#pragma once
#include <string>
#include "Nodo.h"

class ListaDoble {
private:
    Nodo* cabeza;
    Nodo* cola;

    void agregarNodo(Nodo* nuevo);

public:
    ListaDoble();
    ~ListaDoble();

    bool correoExiste(const std::string& correo) const;
    std::string generarCorreo(const std::string& nombre1, const std::string& nombre2,
                              const std::string& apellido1) const;

    Nodo* insertar(const std::string& cedula, const std::string& nombre1,
                   const std::string& nombre2, const std::string& apellido1,
                   const std::string& apellido2);

    void guardarEnArchivo(const Nodo* nodo) const;
    void cargarDesdeArchivo();

    void mostrarAdelante() const;
    void mostrarAtras() const;
};
