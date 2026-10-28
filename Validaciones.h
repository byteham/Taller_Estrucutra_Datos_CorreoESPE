#pragma once
#include <string>

// Valida una cedula ecuatoriana (10 digitos, provincia, tercer digito y modulo 10)
bool cedulaEcuatorianaValida(const std::string& cedula);

// Devuelve true si el texto tiene al menos una letra y solo contiene letras (A-Z, a-z)
bool soloLetras(const std::string& texto);

// Convierte a minusculas
std::string aMinusculas(std::string texto);

// Elimina espacios al inicio y al final
std::string recortar(const std::string& texto);
