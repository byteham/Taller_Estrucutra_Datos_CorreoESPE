#include "ListaDoble.h"
#include "Validaciones.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

static const string DOMINIO = "@espe.edu.ec";
static const string ARCHIVO = "registros.txt";

ListaDoble::ListaDoble() : cabeza(nullptr), cola(nullptr) {}

ListaDoble::~ListaDoble() {
    Nodo* actual = cabeza;
    while (actual != nullptr) {
        Nodo* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }
}

void ListaDoble::agregarNodo(Nodo* nuevo) {
    if (cabeza == nullptr) {
        cabeza = cola = nuevo;
    } else {
        cola->siguiente = nuevo;
        nuevo->anterior = cola;
        cola = nuevo;
    }
}

bool ListaDoble::correoExiste(const string& correo) const {
    for (Nodo* p = cabeza; p != nullptr; p = p->siguiente)
        if (p->correo == correo) return true;
    return false;
}

// Correo = 1a letra nombre1 + 1a letra nombre2 (o "_") + apellido1 + [numero] + dominio
// Si el correo ya existe se agrega 1, 2, 3, ... al final del apellido.
string ListaDoble::generarCorreo(const string& nombre1, const string& nombre2,
                                 const string& apellido1) const {
    string base;
    base += nombre1[0];
    base += nombre2.empty() ? '_' : nombre2[0];
    base += apellido1;
    base = aMinusculas(base);

    string correo = base + DOMINIO;
    int contador = 0;
    while (correoExiste(correo)) {
        contador++;
        correo = base + to_string(contador) + DOMINIO;
    }
    return correo;
}

Nodo* ListaDoble::insertar(const string& cedula, const string& nombre1,
                           const string& nombre2, const string& apellido1,
                           const string& apellido2) {
    string correo = generarCorreo(nombre1, nombre2, apellido1);
    Nodo* nuevo = new Nodo(cedula, nombre1, nombre2, apellido1, apellido2, correo);
    agregarNodo(nuevo);
    return nuevo;
}

void ListaDoble::guardarEnArchivo(const Nodo* nodo) const {
    ofstream archivo(ARCHIVO, ios::app);
    if (!archivo) {
        cout << "No se pudo abrir el archivo para guardar.\n";
        return;
    }
    archivo << nodo->cedula << ";" << nodo->nombre1 << ";" << nodo->nombre2 << ";"
            << nodo->apellido1 << ";" << nodo->apellido2 << ";" << nodo->correo << "\n";
}

// Carga los registros guardados para que la numeracion de correos repetidos continue
void ListaDoble::cargarDesdeArchivo() {
    ifstream archivo(ARCHIVO);
    if (!archivo) return;

    string linea;
    while (getline(archivo, linea)) {
        if (linea.empty()) continue;

        stringstream ss(linea);
        string cedula, n1, n2, a1, a2, correo;
        getline(ss, cedula, ';');
        getline(ss, n1, ';');
        getline(ss, n2, ';');
        getline(ss, a1, ';');
        getline(ss, a2, ';');
        getline(ss, correo, ';');

        agregarNodo(new Nodo(cedula, n1, n2, a1, a2, correo));
    }
}

void ListaDoble::mostrarAdelante() const {
    if (cabeza == nullptr) {
        cout << "\nLa lista esta vacia.\n";
        return;
    }
    cout << "\n--- LISTA (inicio -> fin) ---\n";
    for (Nodo* p = cabeza; p != nullptr; p = p->siguiente) {
        cout << p->cedula << " | " << p->nombre1 << " " << p->nombre2 << " "
             << p->apellido1 << " " << p->apellido2 << " | " << p->correo << "\n";
    }
}

void ListaDoble::mostrarAtras() const {
    if (cola == nullptr) {
        cout << "\nLa lista esta vacia.\n";
        return;
    }
    cout << "\n--- LISTA (fin -> inicio) ---\n";
    for (Nodo* p = cola; p != nullptr; p = p->anterior) {
        cout << p->cedula << " | " << p->nombre1 << " " << p->nombre2 << " "
             << p->apellido1 << " " << p->apellido2 << " | " << p->correo << "\n";
    }
}
