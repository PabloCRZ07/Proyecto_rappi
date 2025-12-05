// PROYECTO SISTEMA DE DOMICILIOS 
// Juan Pablo Cardona Rodríguez
// Samuel Felipe García Sanchez
// Edwin Mateo Camacho Tierradentro

#include <iostream>
#include <limits>

using namespace std;

int main() {
    
    // DEFINIENDO VARIABLES
    string nombre[100], direccion[100], telefono[100], producto[100];
    float precio[100];
    string repetir = "s", repetirDomicilio = "s";
    int n = 0, cantidad[100];
    
    // DEFINIENDO FUNCIONES
    int suma();
    
    cout << "============================================\n";
    cout << "|        BIENVENIDO A RAPPI PROYECT        | \n";
    cout << "============================================\n";
    cout << "| A CONTINUACION INGRESE DATOS DEL CLIENTE |\n";
    cout << "--------------------------------------------\n";
    
    while (repetir == "s" || repetir == "S") { 
          
        repetirDomicilio = "s"; 
    
        cout << "|- Telefono  : ";
        getline(cin, telefono[n]);

        cout << "|- Nombre    : ";
        getline(cin, nombre[n]);

        cout << "|- Direccion : ";
        getline(cin, direccion[n]);
        
        while(repetirDomicilio == "s" || repetirDomicilio == "S") {
        
        cout << "|- Ingrese nombre del producto : \n";
        getline(cin, producto[n]);
        cout << "|- Ingrese cantidad : \n";
        cin >>  cantidad[n];
        
        cout << "|- Ingrese precio : \n";
        cin >> precio[n];
        
        cout << "Desea ingresar otro producto? (s/n): ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // para que no se salte el getline
        getline(cin, repetirDomicilio);
        }
        
        n++;

        cout << "\nDesea ingresar otro domicilio? (s/n): ";
        cin >> repetir;

        // limpiar ENTER pendiente antes de usar getline otra vez
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "\n============================================\n";
    cout << "        DOMICILIOS REGISTRADOS\n";
    cout << "============================================\n";

    for(int i = 0; i < n; i++){
        cout << "\nDomicilio #" << i + 1 << "\n";
        cout << "---------------------------------\n";
        cout << "Telefono : " << telefono[i] << "\n";
        cout << "Nombre   : " << nombre[i]   << "\n";
        cout << "Direccion: " << direccion[i] << "\n";
        cout << "Producto : " << producto[i] << "\n";
        cout << "Cantidad : " << cantidad[i] << "\n";
        cout << "Precio   : " << precio[i] << "\n";
    }
    cout << "\nUltimo domicilio ingresado:\n";
    cout << telefono << " " << nombre << " " << direccion << "\n";
    
    system("pause");
    return 0;
}
