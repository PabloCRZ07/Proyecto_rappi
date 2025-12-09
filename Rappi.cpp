// PROYECTO SISTEMA DE DOMICILIOS 
// Juan Pablo Cardona Rodríguez
// Samuel Felipe García Sanchez
// Edwin Mateo Camacho Tierradentro

#include <iostream>
#include <limits>
#include <ctime>
#include <windows.h>

using namespace std;

// ===== Structs =====
struct datosPersonales {
    string nombre[100], direccion[100], telefono[100];
};

struct datosPedido {
    string producto[100][20];  
    float precio[100][20];
    int cantidad[100][20];
    int numProductos[100];

    string horaReg[100], fechaReg[100];
    int estado[100]; // 0=Pendiente, 1=Preparando, 2=En camino, 3=Entregado
};

// ===== Variables globales =====
datosPersonales cliente;
datosPedido pedido;
int totalRegistros = 0;

// ======= FUNCIONES =======
void registrarPedidos();
void mostrarPedidos();
void cambiarEstado();
void filtrarPorEstado();
void filtrarNombreNumero();  
void historialEstadisticas();

// Funcion de colores ASCII
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}


// ============================ MENU PRINCIPAL =================================
int main() {

    int opcion;

    do {
        system("cls");

        cout << "1. Registrar pedidos\n";
        cout << "2. Mostrar pedidos\n";
        cout << "3. Cambiar estado del pedido\n";
        cout << "4. Filtrar por estado\n";
        cout << "5. Filtrar por nombre o telefono\n";
        cout << "6. Historial y Estadisticas\n"; // nueva opción
        cout << "7. Salir\n"; // salida como última
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch(opcion) {
        case 1: registrarPedidos(); break;
        case 2: mostrarPedidos(); break;
        case 3: cambiarEstado(); break;
        case 4: filtrarPorEstado(); break;
        case 5: filtrarNombreNumero(); break;
        case 6: historialEstadisticas(); break; // nueva opción
        case 7: cout << "Saliendo del sistema...\n"; break;
        default: cout << "Opcion no valida.\n";

        }

    } while (opcion != 7);

    return 0;
}

// =========================== REGISTRAR PEDIDOS ===============================
void registrarPedidos() {

     // Variables de repeticion
    string repetir = "s", repetirDomicilio = "s";

    // sistema de repeticion de PRODUCTO 
    while (repetir == "s" || repetir == "S") {

        repetirDomicilio = "s";
        pedido.numProductos[totalRegistros] = 0;

        // Para que no se salte la función 
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "|- Telefono  : ";
        getline(cin, cliente.telefono[totalRegistros]);

        cout << "|- Nombre    : ";
        getline(cin, cliente.nombre[totalRegistros]);

        cout << "|- Direccion : ";
        getline(cin, cliente.direccion[totalRegistros]);


// =================== SACAR HORA DEL PC =====================
        time_t now = time(0);
        tm* localTime = localtime(&now);

        char bufferFecha[11];
        sprintf(bufferFecha, "%02d/%02d/%d",
            localTime->tm_mday,
            localTime->tm_mon + 1,
            localTime->tm_year + 1900);
        pedido.fechaReg[totalRegistros] = bufferFecha;

        char bufferHora[6];
        sprintf(bufferHora, "%02d:%02d",
            localTime->tm_hour,
            localTime->tm_min);
        pedido.horaReg[totalRegistros] = bufferHora;
// ===========================================================

        pedido.estado[totalRegistros] = 0;

// Sistema de repeticion de domicilio
        while (repetirDomicilio == "s" || repetirDomicilio == "S") {

            int pos = pedido.numProductos[totalRegistros];

            cout << "|- Ingrese nombre del producto : ";
            getline(cin, pedido.producto[totalRegistros][pos]);

            cout << "|- Ingrese cantidad : ";
            cin >> pedido.cantidad[totalRegistros][pos];

            cout << "|- Ingrese precio : ";
            cin >> pedido.precio[totalRegistros][pos];

            pedido.numProductos[totalRegistros]++;

            cout << "Desea ingresar otro producto? (s/n): ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, repetirDomicilio);
        }

        // Para que se guarden individualmente
        totalRegistros++;

        cout << "\nDesea ingresar otro domicilio? (s/n): ";
        cin >> repetir;
    }
}

// ========================= MOSTRAR PEDIDOS ===================================
void mostrarPedidos() {

    cout << "\n============================================\n";
    cout << "        DOMICILIOS PENDIENTES\n";
    cout << "============================================\n";

    bool hayPendientes = false;

    for (int i = 0; i < totalRegistros; i++) {

        if (pedido.estado[i] != 0) continue;

        hayPendientes = true;

        cout << "\nDomicilio #" << i + 1 << "\n";
        cout << "---------------------------------\n";
        cout << "Telefono : " << cliente.telefono[i] << "\n";
        cout << "Nombre   : " << cliente.nombre[i] << "\n";
        cout << "Direccion: " << cliente.direccion[i] << "\n";
        cout << "Fecha    : " << pedido.fechaReg[i] << "\n";
        cout << "Hora     : " << pedido.horaReg[i] << "\n";

        cout << "Estado   : ";
        setColor(14); cout << "Pendiente\n"; setColor(7);

        cout << "\n--- PRODUCTOS ---\n";

        for (int p = 0; p < pedido.numProductos[i]; p++) {
            cout << "Producto : " << pedido.producto[i][p] << "\n";
            cout << "Cantidad : " << pedido.cantidad[i][p] << "\n";
            cout << "Precio   : " << pedido.precio[i][p] << "\n";
            cout << "-------------------------\n";
        }
    }

    if (!hayPendientes)
        cout << "\nNo hay pedidos pendientes.\n";

    cout << "\nPresione ENTER para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}
// =============================================================================

// ============================== CAMBIAR ESTADO ===============================
void cambiarEstado() {
     // VALIDACION SI NO HAY PEDIDOS
    if (totalRegistros == 0) {
        cout << "\nNo hay pedidos registrados.\n";
        system("pause");
        return;
    }

    int id;
    cout << "\nIngrese el ID del pedido que desea modificar (1 - " << totalRegistros << "): ";
    cin >> id;

    // VALIDACION POR SI NO EXISTE EL ID
    if (id < 1 || id > totalRegistros) {
        cout << "ID invalido.\n";
        return;
    }

    int indice = id - 1;

    int nuevoEstado;
    cout << "\nSeleccione nuevo estado:\n";
    cout << "0. Pendiente\n";
    cout << "1. Preparando\n";
    cout << "2. En camino\n";
    cout << "3. Entregado\n";
    cout << "Opcion: ";
    cin >> nuevoEstado;

    // VALIDACION que el nuevo valor sea valido
    while (nuevoEstado < 0 || nuevoEstado > 3) {
        cout << "Valor invalido. Debe ser 0, 1, 2 o 3.\n";
        cout << "Ingrese nuevamente: ";
        cin >> nuevoEstado;
    }

    pedido.estado[indice] = nuevoEstado;

    cout << "\nEstado actualizado correctamente.\n";
}

// ======================= FILTRAR POR ESTADO ==================================
void filtrarPorEstado() {

     // VALIDA QUE HAYAN PEDIDOS
    if (totalRegistros == 0) {
        cout << "\nNo hay pedidos registrados.\n";
        cout << "\nPresione ENTER para continuar...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        return;
    }

    int estadoBuscado;
    cout << "\nFiltrar por estado:\n";
    cout << "0 = Pendiente\n";
    cout << "1 = Preparando\n";
    cout << "2 = En camino\n";
    cout << "3 = Entregado\n";
    cout << "Seleccione: ";
    cin >> estadoBuscado;

    // VALIDA que estadoBuscado este entre el rango
    while (estadoBuscado < 0 || estadoBuscado > 3) {
        cout << "Valor invalido. Debe ser 0, 1, 2 o 3.\n";
        cout << "Seleccione nuevamente: ";
        cin >> estadoBuscado;
    }

    cout << "\n========== PEDIDOS FILTRADOS ==========\n";

    bool encontrado = false;

    for (int i = 0; i < totalRegistros; i++) {

        if (pedido.estado[i] == estadoBuscado) {

            encontrado = true;

            cout << "\nDomicilio #" << i + 1 << "\n";
            cout << "---------------------------------\n";
            cout << "Telefono : " << cliente.telefono[i] << "\n";
            cout << "Nombre   : " << cliente.nombre[i] << "\n";
            cout << "Direccion: " << cliente.direccion[i] << "\n";
            cout << "Fecha    : " << pedido.fechaReg[i] << "\n";
            cout << "Hora     : " << pedido.horaReg[i] << "\n";

            cout << "\n--- PRODUCTOS ---\n";

            for (int p = 0; p < pedido.numProductos[i]; p++) {
                cout << "Producto : " << pedido.producto[i][p] << "\n";
                cout << "Cantidad : " << pedido.cantidad[i][p] << "\n";
                cout << "Precio   : " << pedido.precio[i][p] << "\n";
                cout << "-------------------------\n";
            }
        }
    }

//  VALIDACION 
    if (!encontrado)
        cout << "\nNo existen pedidos con ese estado.\n";

//  Para que no se salte directamente a menu
    cout << "\nPresione ENTER para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

// ======================= FILTRAR POR NOMBRE O TELEFONO =======================


void filtrarNombreNumero() {

//  VALIDA que hayan pedidos
    if (totalRegistros == 0) {
        cout << "\nNo hay pedidos registrados.\n";
        cout << "\nPresione ENTER para continuar...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        return;
    }
    
    // prompt
    int tipo;
    cout << "\n¿Desea buscar por?:\n";
    cout << "1. Telefono\n";
    cout << "2. Nombre del cliente\n";
    cout << "Seleccione: ";
    cin >> tipo;

    // VALIDACION
    while (cin.fail() || (tipo != 1 && tipo != 2)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Opcion invalida. Seleccione 1 o 2: ";
        cin >> tipo;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // limpiar buffer

    if (tipo == 1) {
        string telBuscar;
        cout << "Ingrese el numero de telefono: ";
        getline(cin, telBuscar);

        bool encontrado = false;                         
        for (int i = 0; i < totalRegistros; i++) {
            if (cliente.telefono[i] == telBuscar) {
                encontrado = true;
                cout << "\n===== RESULTADO =====\n";     // DESPLIEGUE DE DATOS
                cout << "Pedido #" << i + 1 << "\n";
                cout << "Nombre   : " << cliente.nombre[i] << "\n";
                cout << "Telefono : " << cliente.telefono[i] << "\n";
                cout << "Direccion: " << cliente.direccion[i] << "\n";
            }
        }

        // Mensaje de salida
        if (!encontrado)
            cout << "\nNo hay pedidos con ese telefono.\n";
    }

    else {
        string nombreBuscar;
        cout << "Ingrese el nombre del cliente: ";
        getline(cin, nombreBuscar);

        bool encontrado = false;

        for (int i = 0; i < totalRegistros; i++) {
            if (cliente.nombre[i] == nombreBuscar) {
                encontrado = true;
                cout << "\n===== RESULTADO =====\n";
                cout << "Pedido #" << i + 1 << "\n";
                cout << "Nombre   : " << cliente.nombre[i] << "\n";
                cout << "Telefono : " << cliente.telefono[i] << "\n";
                cout << "Direccion: " << cliente.direccion[i] << "\n";
            }
        }
        // Mensaje de salida
        if (!encontrado)
            cout << "\nNo hay pedidos a nombre de esa persona.\n";
    }

    cout << "\nPresione ENTER para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}
// ====================== HISTORIAL Y ESTADISTICAS =============================

void historialEstadisticas() {
    if (totalRegistros == 0) {
        cout << "\nNo hay pedidos registrados.\n";
        cout << "\nPresione ENTER para continuar...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        return;
    }

    int totalPendientes = 0, totalPreparando = 0, totalEnCamino = 0, totalEntregado = 0;
    double tiempoTotalMinutos = 0;
    int entregadosCont = 0;

    cout << "\n================ HISTORIAL DE PEDIDOS ================\n";

    for (int i = 0; i < totalRegistros; i++) {
        cout << "\nDomicilio #" << i + 1 << "\n";
        cout << "---------------------------------\n";
        cout << "Telefono : " << cliente.telefono[i] << "\n";
        cout << "Nombre   : " << cliente.nombre[i] << "\n";
        cout << "Direccion: " << cliente.direccion[i] << "\n";
        cout << "Fecha    : " << pedido.fechaReg[i] << "\n";
        cout << "Hora     : " << pedido.horaReg[i] << "\n";

        cout << "Estado   : ";
        switch(pedido.estado[i]) {
            case 0: setColor(14); cout << "Pendiente"; totalPendientes++; break;
            case 1: setColor(6); cout << "Preparando"; totalPreparando++; break;
            case 2: setColor(9); cout << "En camino"; totalEnCamino++; break;
            case 3: setColor(10); cout << "Entregado"; totalEntregado++;
                    // calcular tiempo aproximado desde registro hasta ahora
                    {
                        tm t = {};
                        int h, m;
                        sscanf(pedido.horaReg[i].c_str(), "%d:%d", &h, &m);
                        t.tm_hour = h;
                        t.tm_min = m;
                        tiempoTotalMinutos += (difftime(time(0), mktime(&t)) / 60.0);
                        entregadosCont++;
                    }
                    break;
        }
        setColor(7);
        cout << "\n--- PRODUCTOS ---\n";
        for (int p = 0; p < pedido.numProductos[i]; p++) {
            cout << "Producto : " << pedido.producto[i][p] << "\n";
            cout << "Cantidad : " << pedido.cantidad[i][p] << "\n";
            cout << "Precio   : " << pedido.precio[i][p] << "\n";
            cout << "-------------------------\n";
        }
    }

    cout << "\n================ ESTADISTICAS =================\n";
    cout << "Total Pendientes  : " << totalPendientes << "\n";
    cout << "Total Preparando  : " << totalPreparando << "\n";    
    cout << "Total En camino  : " << totalEnCamino << "\n";
    cout << "Total Entregados  : " << totalEntregado << "\n";

    if (entregadosCont > 0)
        cout << "Tiempo promedio de entrega (minutos): " << tiempoTotalMinutos / entregadosCont << "\n";
    else
        cout << "Tiempo promedio de entrega (minutos): N/A\n";

    cout << "\nPresione ENTER para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}
