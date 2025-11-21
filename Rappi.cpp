// PROYECTO SISTEMA DE DOMICILIOS 
// Juan Pablo Cardona Rodríguez
// Samuel Felipe García Sanchez
// Edwin Mateo Camacho Tierradentro

#include <iostream>
#include <limits>

using namespace std;

int main() {
    string nombre[100], direccion[100], telefono[100];
    string repetir = "s";
    int n = 0;

    cout << "============================================\n";
    cout << "|        BIENVENIDO A RAPPI PROYECT        | \n";
    cout << "============================================\n";
    cout << "| A CONTINUACION INGRESE DATOS DEL CLIENTE |\n";
    cout << "--------------------------------------------\n";
    
    while (repetir == "s" || repetir == "S") {

        cout << "|- Telefono  : ";
        getline(cin, telefono[n]);

        cout << "|- Nombre    : ";
        getline(cin, nombre[n]);

        cout << "|- Direccion : ";
        getline(cin, direccion[n]);
        
        n++;

        cout << "\nDesea ingresar otro domicilio? (s/n): ";
        cin >> repetir;

        // limpiar ENTER pendiente antes de usar getline otra vez
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

	for(int i = 0; i <= n; i++){
		cout << i + 1 << ". " 
        << telefono[i] << " | "
        << nombre[i]   << " | "
        << direccion[i] << "\n";
	}
    cout << "\nUltimo domicilio ingresado:\n";
    cout << telefono << " " << nombre << " " << direccion << "\n";

    return 0;
}
