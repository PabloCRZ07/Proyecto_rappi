// PROYECTO SISTEMA DE DOMICILIOS 
// Juan Pablo Cardona Rodríguez
// Samuel Felipe García Sanchez
// Edwin Mateo Camacho Tierradentro

#include <iostream>
#include <limits>

using namespace std;

int main() {
    string nombre, direccion, telefono;
    string repetir = "s";

    cout << "============================================\n";
    cout << "|        BIENVENIDO A RAPPI PROYECT        | \n";
    cout << "============================================\n";
    cout << "| A CONTINUACION INGRESE DATOS DEL CLIENTE |\n";
    cout << "--------------------------------------------\n";

    while (repetir == "s" || repetir == "S") {

        cout << "|- Telefono  : ";
        getline(cin, telefono);

        cout << "|- Nombre    : ";
        getline(cin, nombre);

        cout << "|- Direccion : ";
        getline(cin, direccion);

        cout << "\nDesea ingresar otro domicilio? (s/n): ";
        cin >> repetir;

        // limpiar ENTER pendiente antes de usar getline otra vez
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "\nUltimo domicilio ingresado:\n";
    cout << telefono << " " << nombre << " " << direccion << "\n";

    return 0;
}
