#include <iostream>
#include <string>
#include "ListaDoble.h"
#include "Validaciones.h"

using namespace std;

// Pide una cedula hasta que sea una cedula ecuatoriana valida
string leerCedula() {
    string cedula;
    while (true) {
        cout << "Cedula (10 digitos): ";
        getline(cin, cedula);
        cedula = recortar(cedula);

        if (cedulaEcuatorianaValida(cedula)) return cedula;
        cout << "Cedula invalida. Ingrese una cedula ecuatoriana valida.\n";
    }
}

// Pide un texto que solo tenga letras. Si es opcional, permite dejarlo vacio.
string leerTexto(const string& mensaje, bool opcional) {
    string texto;
    while (true) {
        cout << mensaje;
        getline(cin, texto);
        texto = recortar(texto);

        if (texto.empty()) {
            if (opcional) return "";
            cout << "Este campo es obligatorio.\n";
            continue;
        }
        if (soloLetras(texto)) return aMinusculas(texto);
        cout << "Solo se permiten letras (sin espacios, numeros ni simbolos).\n";
    }
}

void ingresarPersona(ListaDoble& lista) {
    cout << "\n--- NUEVO REGISTRO ---\n";
    string cedula    = leerCedula();
    string nombre1   = leerTexto("Primer nombre: ", false);
    string nombre2   = leerTexto("Segundo nombre (Enter si no tiene): ", true);
    string apellido1 = leerTexto("Primer apellido: ", false);
    string apellido2 = leerTexto("Segundo apellido (Enter si no tiene): ", true);

    Nodo* nuevo = lista.insertar(cedula, nombre1, nombre2, apellido1, apellido2);
    lista.guardarEnArchivo(nuevo);

    cout << "\nCorreo generado: " << nuevo->correo << "\n";
}

int main() {
    ListaDoble lista;
    lista.cargarDesdeArchivo();

    int opcion = 0;
    do {
        cout << "\n===== GENERADOR DE CORREOS ESPE =====\n";
        cout << "1. Ingresar persona\n";
        cout << "2. Mostrar lista (inicio -> fin)\n";
        cout << "3. Mostrar lista (fin -> inicio)\n";
        cout << "4. Salir\n";
        cout << "Opcion: ";

        string linea;
        getline(cin, linea);
        try {
            opcion = stoi(linea);
        } catch (...) {
            opcion = 0;
        }

        switch (opcion) {
            case 1: ingresarPersona(lista); break;
            case 2: lista.mostrarAdelante(); break;
            case 3: lista.mostrarAtras(); break;
            case 4: cout << "Hasta luego.\n"; break;
            default: cout << "Opcion invalida.\n";
        }
    } while (opcion != 4);

    return 0;
}
