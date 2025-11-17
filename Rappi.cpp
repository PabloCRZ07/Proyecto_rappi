// PROYECTO SISTEMA DE DOMICILIOS 
// Juan Pablo Cardona Rodríguez
// Samuel Felipe García Sanchez
// Edwin Mateo Camacho Tierradentro

#include <iostream>  // Entrada y salida

using namespace std;

int main() {
    // variables van aquí
    string nombre, direccion, telefono;

    // Interfaz 
        cout << "============================================\n";
        cout << "|        BIENVENIDO A RAPPI PROYECT        | \n";
        cout << "============================================\n";
        cout << "| A CONTINUACION INGRESE DATOS DEL CLIENTE |\n";
        cout << "--------------------------------------------\n";

        cout << "|- Telefono  :\n";
        getline(cin, telefono);

        cout << "|- Nombre    :\n";
        getline(cin, nombre); 

        cout << "|- Direccion :\n";
        getline(cin, direccion); 

        cout << telefono << " " << nombre << " " << direccion << "\n";
    return 0;
}