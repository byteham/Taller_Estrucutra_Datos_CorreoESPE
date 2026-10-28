#include "Validaciones.h"
#include <cctype>

using namespace std;

bool cedulaEcuatorianaValida(const string& cedula) {
    // 1. Debe tener exactamente 10 caracteres y todos deben ser digitos
    if (cedula.size() != 10) return false;
    for (size_t i = 0; i < cedula.size(); i++)
        if (!isdigit((unsigned char)cedula[i])) return false;

    // 2. Los dos primeros digitos son la provincia (01-24) o 30 (ecuatorianos en el exterior)
    int provincia = (cedula[0] - '0') * 10 + (cedula[1] - '0');
    if (!((provincia >= 1 && provincia <= 24) || provincia == 30)) return false;

    // 3. El tercer digito debe ser menor a 6 (persona natural)
    int tercero = cedula[2] - '0';
    if (tercero >= 6) return false;

    // 4. Algoritmo modulo 10 con coeficientes 2,1,2,1,2,1,2,1,2
    int suma = 0;
    for (int i = 0; i < 9; i++) {
        int digito = cedula[i] - '0';
        int coeficiente = (i % 2 == 0) ? 2 : 1;
        int producto = digito * coeficiente;
        if (producto >= 10) producto -= 9;
        suma += producto;
    }
    int verificador = (10 - (suma % 10)) % 10;

    return verificador == (cedula[9] - '0');
}

bool soloLetras(const string& texto) {
    if (texto.empty()) return false;
    for (size_t i = 0; i < texto.size(); i++)
        if (!isalpha((unsigned char)texto[i])) return false;
    return true;
}

string aMinusculas(string texto) {
    for (size_t i = 0; i < texto.size(); i++)
        texto[i] = (char)tolower((unsigned char)texto[i]);
    return texto;
}

string recortar(const string& texto) {
    size_t inicio = texto.find_first_not_of(" \t\r\n");
    if (inicio == string::npos) return "";
    size_t fin = texto.find_last_not_of(" \t\r\n");
    return texto.substr(inicio, fin - inicio + 1);
}
