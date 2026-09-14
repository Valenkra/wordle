#include "lib.h"
#include <array>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<string> cargar_listado(const string & nombre_archivo){
    // Abre el archivo y lo lee completo.
    ifstream archivo(nombre_archivo);
    vector<string> palabras;

    // Si no se pudo abrir el archivo, devuelve un vector vacío.
    if (!archivo.is_open()) {
        return palabras;
    }

    string linea;
    while (getline(archivo, linea)) {
        // Ignora las lineas vacías y agrega las palabras al vector
        if (!linea.empty()) {
            palabras.push_back(linea);
        }
    }

    return palabras;
}

bool intento_valido(const string & intento, const string & palabra_secreta, const vector<string> &listado){
    // Un intento es válido solo si tiene la misma longitud que la palabra secreta
    // y si además se encuentra exactamente en el listado de palabras aceptadas.
    if (intento.size() != palabra_secreta.size()) {
        return false;
    }

    bool encontrado = false;
    int i = 0;
    while (i < listado.size() && !encontrado) {
        if (listado[i] == intento) {
            encontrado = true;
        }
        i++;
    }

    return encontrado;
}

vector<EstadoLetra> evaluar_intento(const string & intento, const string & palabra_secreta){
    // Empiezo asumiendo que todas son NoPresente.
    vector<EstadoLetra> respuesta(intento.size(), EstadoLetra::NoPresente);
    
    // Asumo que las palabras del listado no tienen tildes ni ñ (ASCII a-z minuscula).
    // Cuento cuántas letras "sobran" de la secreta, para los amarillos de mas abajo.
    array<int, 26> letras_restantes{};

    // Marco las letras en posición correcta.
    // También cuento la cantidad de veces que aparece cada letra de la palabra secreta.
    for (int i = 0; i < intento.size(); ++i) {
        if (intento[i] == palabra_secreta[i]) {
            respuesta[i] = EstadoLetra::LugarCorrecto;
        } else {
            int indice = palabra_secreta[i] - 'a';
            if (indice >= 0 && indice < 26) {
                ++letras_restantes[indice];
            }
        }
    }

    // Si una letra no es correcta y todavía quedan apariciones de esa letra
    // lo registro como LugarIncorrecto.
    for (int i = 0; i < intento.size(); ++i) {
        if (respuesta[i] != EstadoLetra::LugarCorrecto) {
            int indice = intento[i] - 'a';
            if (indice >= 0 && indice < 26 && letras_restantes[indice] > 0) {
                respuesta[i] = EstadoLetra::LugarIncorrecto;
                --letras_restantes[indice];
            }
        }
    }

    return respuesta;
}

string respuesta_en_string(const vector<EstadoLetra> & respuesta){
    // Paso cada EstadoLetra a su simbolo: + correcto, - presente en otro lugar, X ausente.
    string salida;

    for (EstadoLetra estado : respuesta) {
        if (estado == EstadoLetra::LugarCorrecto) {
            salida.push_back('+');
        } else if (estado == EstadoLetra::LugarIncorrecto) {
            salida.push_back('-');
        } else {
            salida.push_back('X');
        }
    }

    return salida;
}
