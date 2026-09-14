#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>
#include "lib.h"

using namespace std;

int main(){
    // Carga el listado de palabras disponible para jugar.
    vector<string> listado = cargar_listado("listado.txt");

    if (listado.empty()) {
        cout << "ERROR: No se pudo cargar el listado de palabras. Chequea el path del archivo." << endl;
        return 1;
    }

    
    // Genera una semilla distinta para que la palabra secreta cambie en cada ejecución.
    srand(time(nullptr));
    // Elige una palabra secreta al azar del listado.
    string secret_word = listado[rand() % listado.size()];

    const int MAX_INTENTOS = 6;
    int intentos_restantes = MAX_INTENTOS;

    cout << R"( 
     __   __  ___     ______     _______   ________   ___       _______  
    |"  |/  \|  "|   /    " \   /"      \ |"      "\ |"  |     /"     "| 
    |'  /    \:  |  // ____  \ |:        |(.  ___  :)||  |    (: ______) 
    |: /'        | /  /    ) :)|_____/   )|: \   ) |||:  |     \/    |   
     \//  /\'    |(: (____/ //  //      / (| (___\ || \  |___  // ___)_  
    /   /  \\   | \        /  |:  __   \ |:       :)( \_|:  \(:      "| 
    |___/    \___|  "_____/   |__|  \___)(________/  \_______)\_______) 
    )" << endl;

    cout << "Adiviná la palabra secreta de 5 letras. Tenes " << MAX_INTENTOS << " intentos." << endl;

    while (intentos_restantes > 0) {
        cout << "Intento " << (MAX_INTENTOS - intentos_restantes + 1) << "/" << MAX_INTENTOS << ": ";
        string intento;
        cin >> intento;

        // Paso todo a minuscula para que coincida con el listado
        for (int i = 0; i < intento.length(); i++) {
            intento[i] = tolower(intento[i]);
        }

        if (!intento_valido(intento, secret_word, listado)) {
            cout << "Intento no válido. Asegurate de que tu palabra tenga la longitud correcta y que esté dentro del listado. \n" << endl;
        } else {
            if (intento == secret_word) {
                cout << R"(
                _     _  ___   __    _  __    _  _______  ______             
                | | _ | ||   | |  |  | ||  |  | ||       ||    _ |            
                | || || ||   | |   |_| ||   |_| ||    ___||   | ||            
                |       ||   | |       ||       ||   |___ |   |_||_           
                |       ||   | |  _    ||  _    ||    ___||    __  |          
                |   _   ||   | | | |   || | |   ||   |___ |   |  | |          
                |__| |__||___| |_|  |__||_|  |__||_______||___|  |_|          
                _     _  ___   __    _  __    _  _______  ______             
                | | _ | ||   | |  |  | ||  |  | ||       ||    _ |            
                | || || ||   | |   |_| ||   |_| ||    ___||   | ||            
                |       ||   | |       ||       ||   |___ |   |_||_           
                |       ||   | |  _    ||  _    ||    ___||    __  |          
                |   _   ||   | | | |   || | |   ||   |___ |   |  | |          
                |__| |__||___| |_|  |__||_|  |__||_______||___|  |_|          
                _______  __   __  ___   _______  ___   _  _______  __    _   
                |       ||  | |  ||   | |       ||   | | ||       ||  |  | |  
                |       ||  |_|  ||   | |       ||   |_| ||    ___||   |_| |  
                |       ||       ||   | |       ||      _||   |___ |       |  
                |      _||       ||   | |      _||     |_ |    ___||  _    |  
                |     |_ |   _   ||   | |     |_ |    _  ||   |___ | | |   |  
                |_______||__| |__||___| |_______||___| |_||_______||_|  |__|  
                ______   ___   __    _  __    _  _______  ______             
                |      | |   | |  |  | ||  |  | ||       ||    _ |            
                |  _    ||   | |   |_| ||   |_| ||    ___||   | ||            
                | | |   ||   | |       ||       ||   |___ |   |_||_           
                | |_|   ||   | |  _    ||  _    ||    ___||    __  |          
                |       ||   | | | |   || | |   ||   |___ |   |  | |          
                |______| |___| |_|  |__||_|  |__||_______||___|  |_|     
                )" << endl;
                cout << "¡Adivinaste la palabra secreta!" << endl;
                return 0;
            }

            vector<EstadoLetra> respuesta = evaluar_intento(intento, secret_word);
            cout << "Respuesta: " << respuesta_en_string(respuesta) << "\n" << endl;

            --intentos_restantes;

            if (intentos_restantes == 0) {
                cout << "No te quedan más intentos :( La palabra era: " << secret_word << endl;
                return 0;
            }

            if (intentos_restantes == 1) {
                cout << "¡Cuidado! Te queda solo un intento." << endl;
            }
        }
    }

    return 0;
}