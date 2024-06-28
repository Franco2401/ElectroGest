#pragma once
#include "general_variables.h"
#include "client_class.h"
#include "product_manager_class.h"
#include "product_management_functions.h"
#include "supplier_manager_class.h"
#include "inventory_management_class.h"
#include "client_manager_class.h"
#include "ordering_system_class.h"
#include "shopping_cart_class.h"
#include "promotion_management_class.h" 
#include "Graph.h"
#include <iostream>
#include <fstream>
#include <conio.h>
#include <windows.h>
#include <algorithm>
#include <sstream>
#include <cstdlib>
#include <regex>

using namespace std;

//#####################################################################//
//################## MEN�S DE LA APLICACI�N ###########################//
//#####################################################################//

// Men� general
void generalMenu();

// Men�s de vendedores
void sellerLoginMenu(); // Men� de inicio de sesi�n para vendedor
void sellerMenu(string usuario, GestionarProveedores& supplierManager); // Men� de vendedor

// Cliente
void clientRegisterMenu(); // Men� de registro para cliente
void clientLoginMenu(); // Men� de inicio de sesi�n para cliente
void clientMenu(); // Men� de cliente
void homeClientMenu(); // Men� de inicio para cliente
void savePassword(const string& email, const string& password); // Guardar la contrase�a cifrada
void saveClientInfo(const CLIENTE& client); // Guardar la informaci�n del cliente en un archivo   

// Productos
void productCatalogMenu(); // Men� de cat�logo de productos
void productManagementMenu(); // Men� de gesti�n de productos 
void filtrarProductosPorCategoria(); // Filtrar productos por categor�a

// Inventario
void inventoryManagementMenu(); // Men� de gesti�n de inventario

// Proveedores
void supplierManagementMenu(); // Men� de gesti�n de proveedores

// Pedido
void orderingMenu(); // Men� de pedidos
void orderManagementMenu(); // Men� de gesti�n de pedidos

// Gesti�n de clientes
void customerManagementMenu(); // Men� de gesti�n de clientes

void sortProductsPrice(); // Ordenar productos por precio

// Promociones
void promotionsManagementMenu();

//#####################################################################//
//################## IMPLEMENTACI�N DE LOS MEN�S #####################//
//#####################################################################//

// Funci�n para mostrar el men� general
void generalMenu() {
    int opcion = 0; // Opci�n elegida por el usuario

    do {
        system("cls");

        cout << CYAN_COLOR;
        cout << "=====================================" << endl;
        cout << "     �Bienvenido a ElectroGest!      " << endl;
        cout << "=====================================" << endl;
        cout << DOUBLE_SPACE << RESET_COLOR;
        cout << "<1> Iniciar sesi�n como vendedor" << endl;
        cout << "<2> Iniciar sesi�n como cliente" << endl;
        cout << "<3> Salir" << endl;
        ShowConsoleCursor(true); // Mostar cursor
        cout << DOUBLE_SPACE << YELLOW_COLOR << "Ingrese una opci�n: " << RESET_COLOR; // Ingrese una opci�n
        cin >> opcion;

        // Verifica si la entrada fall�
        if (cin.fail()) { // Verifica si la entrada fall�
            cin.clear(); // Limpia el estado de cin
            cin.ignore((numeric_limits<streamsize>::max)(), '\n'); // Ignora la entrada incorrecta
            ShowConsoleCursor(false); // Oculta el cursor
            cout << DOUBLE_SPACE << MAGENTA_COLOR << "Entrada no v�lida, por favor, ingrese un n�mero."; // Entrada no v�lida
            Sleep(1500); // Espera 1.5 segundos
            continue; // Contin�a al siguiente ciclo del bucle do-while
        }

        // Evaluador del men� de opciones
        switch (opcion) {
        case 1:
            sellerLoginMenu(); // Men� de inicio de sesi�n para vendedor
            break;
        case 2:
            clientMenu(); // Men� de cliente
            break;
        case 3:
            exit(0); // Salir del programa
            break;
        }
    } while (opcion != 3); // Continuar hasta que el usuario elija salir
}

// Men�s de vendedores

// Funci�n para mostrar el men� de vendedor
void sellerLoginMenu() {
    ShowConsoleCursor(true); // Muestra el cursor en la consola

    system("cls"); // Limpia la consola

    // Definir variables
    string usuario, contrasena;
    string usuarioArchivo, contrasenaArchivo;

    // Crear el objeto ProductManager
    GestionarProveedores supplierManager;

    // Solicita al usuario que ingrese sus datos
    cout << CYAN_COLOR << "=== �BIENVENIDO, VENDEDOR! ===" << DOUBLE_SPACE;
    cout << GRAY_COLOR << "Ingrese sus datos para iniciar sesi�n." << DOUBLE_SPACE; // Ingrese sus credenciales
    cout << YELLOW_COLOR << "Usuario: " << RESET_COLOR;
    cin >> usuario; // Lee el nombre de usuario
    cout << YELLOW_COLOR << "Contrase�a: " << RESET_COLOR;

    // Oculta la contrase�a mientras se escribe
    char caracter;
    contrasena = ""; // Inicializa la cadena de la contrase�a
    // Bucle para leer la contrase�a
    while (true) {
        caracter = _getch(); // Lee un car�cter sin mostrarlo
        if (caracter == 13) // 13 es el c�digo ASCII para la tecla Enter
            break; // Si es Enter, termina el bucle
        else if (caracter == 8) { // 8 es el c�digo ASCII para la tecla Backspace
            if (contrasena.length() > 0) {
                cout << "\b \b"; // Retrocede y borra el �ltimo car�cter
                contrasena.pop_back(); // Elimina el �ltimo car�cter de la cadena
            }
        }
        else {
            cout << "*"; // Muestra un asterisco en lugar del car�cter
            contrasena.push_back(caracter); // Agrega el car�cter a la contrase�a
        }
    }

    ifstream archivo("seller_data.txt"); // Abre el archivo de vendedores

    bool encontrado = false;

    // Verifica si el archivo se abri� correctamente
    if (!archivo.is_open()) {
        cout << DOUBLE_SPACE << MAGENTA_COLOR << "Error al abrir el archivo." << endl; // Error al abrir el archivo
        return;
    }

    // Lee los datos del archivo l�nea por l�nea y compara con los ingresados por el usuario
    while (archivo >> usuarioArchivo >> contrasenaArchivo) {
        // Compara los datos del archivo con los ingresados por el usuario
        if (usuario == usuarioArchivo && contrasena == contrasenaArchivo) {
            encontrado = true;
            break; // Se encontr� la coincidencia, no es necesario continuar buscando
        }
    }

    // Cierra el archivo
    archivo.close();

    // Si se encontr� el usuario
    if (encontrado) {
        sellerMenu(usuario, supplierManager); // Muestra el men� de vendedor
    }
    else {
        ShowConsoleCursor(false); // Oculta el cursor
        cout << DOUBLE_SPACE << RED_COLOR << "Usuario o contrase�a incorrectos. Por favor, int�ntelo de nuevo." << endl; // Usuario o contrase�a incorrectos
        Sleep(1500); // Espera 1.5 segundos
        system("cls"); // Limpia la consola
        ShowConsoleCursor(true); // Muestra el cursor
        sellerLoginMenu(); // Intenta nuevamente
    }
}

// Funci�n para mostrar el men� de vendedor
void sellerMenu(string usuario, GestionarProveedores& supplierManager) {

    // Crear los objetos de las clases
    GESTION_INVENTARIO inventoryManager; // Crear el objeto GestionInventarios
    GESTION_PRODUCTOS productManager; // Crear el objeto GESTION_PRODUCTOS

    int opcion; // Opci�n elegida por el usuario

    string usuarioTP = usuario; // Nombre de usuario
    transform(usuarioTP.begin(), usuarioTP.end(), usuarioTP.begin(), [](unsigned char c) {
        return toupper(c);
    });

    // Bucle para mostrar el men� y obtener la opci�n del usuario
    do {

        system("cls"); // Limpia la consola

        cout << CYAN_COLOR << "=== �BIENVENIDO, " << usuarioTP << "! " << "===" << DOUBLE_SPACE << RESET_COLOR; // Bienvenido
        cout << "<1> " << "Gestionar productos" << endl; // Gesti�n de productos
        cout << "<2> " << "Gestionar inventario" << endl; // Gesti�n de inventario
        cout << "<3> " << "Gestionar proveedores" << endl; // Gesti�n de proveedores
        cout << "<4> " << "Gestionar pedidos" << endl; // Gesti�n de pedidos
        cout << "<5> " << "Gestionar clientes" << endl; // Gesti�n de cliente
        cout << "<6> " << "Gestionar promociones" << endl; // Gesti�n de cliente
        cout << "<7> " << "Salir"; // Salir
        ShowConsoleCursor(true); // Muestra el cursor
        cout << DOUBLE_SPACE << YELLOW_COLOR << "Ingrese una opc��n: " << RESET_COLOR; cin >> opcion; // Ingrese una opci�n

        // Verifica si la entrada fall�
        if (cin.fail()) { // Verifica si la entrada fall�
            cin.clear(); // Limpia el estado de cin
            cin.ignore((numeric_limits<streamsize>::max)(), '\n'); // Ignora la entrada incorrecta
            ShowConsoleCursor(false); // Oculta el cursor
            cout << DOUBLE_SPACE << MAGENTA_COLOR << "Entrada no v�lida, por favor ingrese un n�mero."; // Entrada no v�lida
            Sleep(1500); // Espera 1.5 segundos
            continue; // Contin�a al siguiente ciclo del bucle do-while
        }

        // Evaluador de opciones
        switch (opcion) {
        case 1:
            productManagementMenu(); // Men� de gesti�n de productos
            break;
        case 2:
            inventoryManagementMenu(); // Men� de gesti�n de inventario
            break;
        case 3:
            supplierManagementMenu(); // Men� de gesti�n de proveedores
            break;
        case 4:
            orderManagementMenu(); // Men� de gesti�n de pedidos
            break;
        case 5:
            customerManagementMenu(); // Men� de gesti�n de clientes
            break;
        case 6:
            promotionsManagementMenu(); // Men� de gesti�n de clientes
            break;
        case 7:
			break;
        }
    } while (opcion != 7); // El bucle contin�a hasta que se elige la opci�n de salir
}

// Men�s de clientes 

// Funci�n para mostrar el men� de registro para cliente
void clientRegisterMenu() {
    // Crear un objeto CLIENTE
    unordered_set<string> existingIds = loadExistingIds();

    // Create a CLIENTE object with unique ID generation
    CLIENTE cliente(existingIds);    
    GESTION_CLIENTE clienteManager;

    // Definir variables
    string input;

    system("cls"); // Limpia la consola

    cout << CYAN_COLOR << "=== BIENVENIDO, CLIENTE ===" << DOUBLE_SPACE; // Registro de cliente
    cout << GRAY_COLOR << "Por favor, complete el siguiente formulario para registrarse" << DOUBLE_SPACE; // Ingrese sus datos
    cin.ignore(); // Limpia el buffer del teclado

    // Solicitar al usuario que ingrese un nombre
    cout << YELLOW_COLOR << "Nombre: " << RESET_COLOR; // Nombre
    string input_nombre;
    getline(cin, input_nombre);

    while (!contieneSoloLetras(input_nombre)) {
        cout << MAGENTA_COLOR << endl << "Nombre no permitido.";

        cout << DOUBLE_SPACE << YELLOW_COLOR << "Ingrese un nombre v�lido: " << RESET_COLOR;
        getline(cin, input_nombre);
    }

    // Obtener el primer nombre
    string primer_nombre;
    size_t pos = input_nombre.find(' ');
    if (pos != string::npos) {
        primer_nombre = input_nombre.substr(0, pos);
    }
    else {
        primer_nombre = input_nombre;
    }

    cliente.setNombre(primer_nombre);

    // Solicitar al usuario que ingrese un apellido
    cout << YELLOW_COLOR << "Apellido: " << RESET_COLOR; // Apellido
    string input_apellido;
    getline(cin, input_apellido);

    while (!contieneSoloLetrasApellido(input_apellido)) {
        cout << MAGENTA_COLOR << endl << "Apellido no permitido.";

        cout << DOUBLE_SPACE << YELLOW_COLOR << "Ingrese un apellido v�lido: " << RESET_COLOR;
        getline(cin, input_apellido);
    }

    // Obtener el primer apellido
    string primer_apellido;
    size_t posA = input_apellido.find(' ');
    if (posA != string::npos) {
        primer_apellido = input_apellido.substr(0, posA);
    }
    else {
        primer_apellido = input_apellido;
    }

    cliente.setApellido(primer_apellido);

    string input_correo;
    regex correoRegex(R"([a-zA-Z0-9._%+-]+@(gmail|yahoo|outlook|email)\.(com|net|org|edu))");

    do {
        // Solicitar al usuario que ingrese un correo electr�nico
        cout << YELLOW_COLOR << "Correo electr�nico: " << RESET_COLOR; // Correo electr�nico
        getline(cin, input_correo);

        // Verificar si la direcci�n de correo electr�nico cumple con la expresi�n regular
        if (!regex_match(input_correo, correoRegex)) {
            // La direcci�n de correo electr�nico no es v�lida
            cout << endl << MAGENTA_COLOR << "Direcci�n de correo electr�nico no v�lida." << DOUBLE_SPACE;
        }
    } while (!regex_match(input_correo, correoRegex));
    cliente.setCorreoElectronico(input_correo);

    // Solicitar al usuario que ingrese una contrase�a
    cout << YELLOW_COLOR << "Contrase�a: " << RESET_COLOR; // Contrase�a
    string input_contrasenia;
    getline(cin, input_contrasenia);
    cliente.setContrasenia(input_contrasenia);

    // Validar que se haya ingresado una contrase�a
    while (input_contrasenia.empty()) {
        cout << endl << MAGENTA_COLOR << "Debe ingresar una contrase�a. Por favor, int�ntelo de nuevo." << RESET_COLOR << endl;
        cout << YELLOW_COLOR << "Contrase�a: " << RESET_COLOR; // Contrase�a
        getline(cin, input_contrasenia);
        cliente.setContrasenia(input_contrasenia);
    }

    // Solicitar al usuario que confirme la contrase�a
    cout << YELLOW_COLOR << "Confirmar contrase�a: " << RESET_COLOR; // Confirmar Contrase�a
    string input_confirmar_contrasenia;
    getline(cin, input_confirmar_contrasenia);

    // Verificar si las contrase�as coinciden
    while (input_contrasenia != input_confirmar_contrasenia) {
        cout << MAGENTA_COLOR << endl << "Las contrase�as no coinciden. Por favor, int�ntelo de nuevo." << RESET_COLOR << DOUBLE_SPACE;

        // Solicitar al usuario que ingrese la contrase�a nuevamente
        cout << YELLOW_COLOR << "Contrase�a: " << RESET_COLOR; // Contrase�a
        getline(cin, input_contrasenia);
        cliente.setContrasenia(input_contrasenia);

        // Solicitar al usuario que confirme la contrase�a nuevamente
        cout << YELLOW_COLOR << "Confirmar contrase�a: " << RESET_COLOR; // Confirmar Contrase�a
        getline(cin, input_confirmar_contrasenia);
    }

    // Solicitar al usuario que ingrese la direcci�n
    cout << YELLOW_COLOR << "Direcci�n: " << RESET_COLOR; // Direcci�n
    string input_direccion;
    getline(cin, input_direccion);
    cliente.setDireccion(input_direccion);

    string input_telefono;
    do {
        // Solicitar al usuario que ingrese el tel�fono
        cout << YELLOW_COLOR << "Tel�fono: " << RESET_COLOR; // Tel�fono
        getline(cin, input_telefono);
        // Verificar si la entrada es un n�mero de 9 d�gitos y no existe en el archivo
        if (input_telefono.length() != 9 || !all_of(input_telefono.begin(), input_telefono.end(), ::isdigit)) {
            cout << endl << MAGENTA_COLOR << "El tel�fono debe tener exactamente 9 d�gitos. Intente de nuevo." << DOUBLE_SPACE; // N�mero de tel�fono no v�lido
        }
        else if(clienteManager.numeroExistente(input_telefono))
		{
			cout << endl << MAGENTA_COLOR << "N�mero de tel�fono ya registrado." << DOUBLE_SPACE; // N�mero de tel�fono ya registrado
		}
    } while (input_telefono.length() != 9 || !all_of(input_telefono.begin(), input_telefono.end(), ::isdigit) || clienteManager.numeroExistente(input_telefono));
    cliente.setTelefono(input_telefono);

    string input_nacimiento;
    do {
        // Solicitar al usuario que ingrese la fecha de nacimiento
        cout << YELLOW_COLOR << "Fecha de nacimiento: (DD/MM/AAAA): " << RESET_COLOR; // Fecha de nacimiento
        getline(cin, input_nacimiento);

        // Definir un stringstream para separar la entrada en d�a, mes y a�o
        istringstream iss(input_nacimiento);
        int dia, mes, anio;
        char slash1, slash2;
        iss >> dia >> slash1 >> mes >> slash2 >> anio;

        // Validar el formato de la fecha y los rangos de d�a, mes y a�o
        if (iss.fail() || slash1 != '/' || slash2 != '/' || dia < 1 || dia > 31 || mes < 1 || mes > 12 || anio < 1944 || anio > 2006) {
            cout << endl << MAGENTA_COLOR << "Fecha de nacimiento no v�lida." << DOUBLE_SPACE; // Fecha de nacimiento no v�lida
        }
        else {
            // La fecha de nacimiento es v�lida
            // Asignar la fecha de nacimiento al cliente
            string fechaNacimiento = to_string(dia) + "/" + to_string(mes) + "/" + to_string(anio);
            cliente.setFechaNacimiento(fechaNacimiento);
            break;
        }
    } while (true); // Repetir hasta que se ingrese una fecha de nacimiento v�lida

    string input_genero;
    do {
        // Solicitar al usuario que ingrese el g�nero
        cout << YELLOW_COLOR << "Sexo (M, F): " << RESET_COLOR; // Sexo
        getline(cin, input_genero);
        if (input_genero != "M" && input_genero != "F") {
            cout << endl << MAGENTA_COLOR << "Ingrese un sexo v�lido (M, F). Intente de nuevo." << DOUBLE_SPACE; // G�nero no v�lido
        }
    } while (input_genero != "M" && input_genero != "F");
    cliente.setGenero(input_genero);

    // Guardar la informaci�n del cliente en un archivo
    saveClientInfo(cliente);
    savePassword(input_correo, input_contrasenia); // Guardar la contrase�a cifrada

    ShowConsoleCursor(false); // Oculta el cursor

    Sleep(1500); // Espera 1.5 segundos
    homeClientMenu(); // Muestra el men� del vendedor
}

// Funci�n para mostrar el men� de inicio de sesi�n para cliente
void clientLoginMenu() {

    ShowConsoleCursor(true); // Muestra el cursor

    string email, password;
    bool loggedIn = false;

    cout << CYAN_COLOR << "=== �BIENVENIDO, CLIENTE! ===" << DOUBLE_SPACE;
    cout << GRAY_COLOR << "Ingrese sus datos para iniciar sesi�n." << DOUBLE_SPACE;

    cout << YELLOW_COLOR << "Correo electr�nico: " << RESET_COLOR;
    cin >> ws; // Elimina los espacios en blanco iniciales  
    getline(cin, email);
    cout << YELLOW_COLOR << "Contrase�a: " << RESET_COLOR;

    // Oculta la contrase�a mientras se escribe
    password = "";
    char caracter;
    while (true) {
        caracter = _getch(); // Lee un car�cter sin mostrarlo
        if (caracter == 13) // 13 es el c�digo ASCII para la tecla Enter
            break; // Si es Enter, termina el bucle
        else if (caracter == 8) { // 8 es el c�digo ASCII para la tecla Backspace
            if (password.length() > 0) {
                cout << "\b \b"; // Retrocede y borra el �ltimo car�cter
                password.pop_back(); // Elimina el �ltimo car�cter de la cadena
            }
        }
        else {
            cout << "*"; // Muestra un asterisco en lugar del car�cter
            password.push_back(caracter); // Agrega el car�cter a la contrase�a
        }
    }

    // Abrir el archivo de registro de clientees
    ifstream file("passwords.txt");
    if (file.is_open()) {
        string line;
        // Leer el archivo l�nea por l�nea
        while (getline(file, line)) {
            // Dividir la l�nea en tokens usando el espacio como delimitador
            istringstream iss(line);
            string emailFromFile, passwordFromFile;
            iss >> emailFromFile >> passwordFromFile;
            // Comparar el correo electr�nico y la contrase�a ingresados con los almacenados en el archivo
            if (email == emailFromFile && password == passwordFromFile) {
                loggedIn = true;
                ShowConsoleCursor(false);
                cout << DOUBLE_SPACE << GREEN_COLOR << "Inicio de sesi�n exitoso." << DOUBLE_SPACE;
                Sleep(1500);
                system("cls");

                // Guardar el email en la instancia de CLIENTE_ACTUAL
                CLIENTE_ACTUAL* cliente = CLIENTE_ACTUAL::obtenerInstancia();
                cliente->setClienteID(email);

                homeClientMenu(); // Mostrar el men� del cliente
                break;
            }
        }
        file.close();
    }
    else {
        cout << DOUBLE_SPACE << MAGENTA_COLOR << "Error: No se pudo abrir el archivo de registro." << DOUBLE_SPACE;
        return;
    }

    if (loggedIn) {
        clientMenu();
    }
    else {
        ShowConsoleCursor(false);
        cout << DOUBLE_SPACE << MAGENTA_COLOR << "Correo electr�nico o contrase�a incorrectos. Por favor, int�ntelo de nuevo." << DOUBLE_SPACE;
        Sleep(1500);
        system("cls");
    }
}

// Funci�n para mostrar el men� de cliente
void clientMenu() {

    int opcion = 0; // Opci�n elegida por el usuario

    do
    {
        system("cls");

        cout << CYAN_COLOR << "=== �BIENVENIDO! ===" << DOUBLE_SPACE << RESET_COLOR;
        cout << "<1> Crear una cuenta" << endl;
        cout << "<2> Iniciar sesi�n" << endl;
        cout << "<3> Salir";
        cout << DOUBLE_SPACE << YELLOW_COLOR;
        ShowConsoleCursor(true); // Mostrar el cursor
        cout << "Ingrese una opci�n: " << RESET_COLOR;
        cin >> opcion;

        // Verifica si la entrada fall�
        if (cin.fail()) { // Verifica si la entrada fall�
            cin.clear(); // Limpia el estado de cin
            cin.ignore((numeric_limits<streamsize>::max)(), '\n'); // Ignora la entrada incorrecta
            ShowConsoleCursor(false); // Oculta el cursor
            cout << DOUBLE_SPACE << MAGENTA_COLOR << "Entrada no v�lida, por favor ingrese un n�mero."; // Entrada no v�lida
            Sleep(1500); // Espera 1.5 segundos
            continue; // Contin�a al siguiente ciclo del bucle do-while
        }

        switch (opcion)
        {
        case 1:
            system("cls");
            clientRegisterMenu(); // Men� de registro para cliente
            break;
        case 2:
            system("cls");
            clientLoginMenu(); // Men� de inicio de sesi�n para cliente
            break;
        case 3:
            break;
        }
    } while (opcion != 3);

}

// Funci�n para mostrar el men� de inicio para cliente
void homeClientMenu() {
    SISTEMA_PEDIDOS sistemaPedidos;

    CLIENTE_ACTUAL* cliente = CLIENTE_ACTUAL::obtenerInstancia();

    cout << GRAY_COLOR << "Verificando el c�digo del usuario";
    // Animaci�n de los puntos
    for (int i = 0; i < 3; ++i) {
        cout << "." << flush;
        Sleep(500); // Espera 500 ms
    }

    for (int i = 0; i < 3; ++i) {
        cout << "\b \b" << flush;
        Sleep(500); // Espera 500 ms
    }

    for (int i = 0; i < 3; ++i) {
        cout << "." << flush;
        Sleep(500); // Espera 500 ms
    }

    if (cliente->cargarClienteIDDesdeArchivo("client_registration.txt", cliente->getClienteID())) {
        cout << DOUBLE_SPACE << GREEN_COLOR << "C�digo del cliente cargado exitosamente: " << RESET_COLOR << cliente->getClienteID() << endl;
        Sleep(1500);
    }
    else {
        cout << DOUBLE_SPACE << RED_COLOR << "No se pudo cargar el c�digo del cliente." << DOUBLE_SPACE;
        Sleep(1500);
        return;
    }

    int opcion = 0;

    do {
        system("cls");
        cout << CYAN_COLOR << "=== �BIENVENIDO, CLIENTE! ===" << DOUBLE_SPACE << RESET_COLOR;
        cout << "<1> Ver cat�logo de productos" << endl;
        cout << "<2> Realizar pedido" << endl;
        cout << "<3> Ver estado de pedidos" << endl;
        cout << "<4> Salir" << endl;
        cout << DOUBLE_SPACE << YELLOW_COLOR;
        ShowConsoleCursor(true); // Mostrar el cursor
        cout << "Ingrese una opci�n: " << RESET_COLOR;
        cin >> opcion;

        // Verifica si la entrada fall�
        if (cin.fail()) {
            cin.clear();
            cin.ignore((numeric_limits<streamsize>::max)(), '\n');
            ShowConsoleCursor(false);
            cout << DOUBLE_SPACE << MAGENTA_COLOR << "Entrada no v�lida, por favor ingrese un n�mero.";
            Sleep(1500);
            continue;
        }

        switch (opcion)
        {
        case 1:
            system("cls");
            productCatalogMenu();
            break;
        case 2:
            orderingMenu();
            break;
        case 3:
            sistemaPedidos.verHistorialPedidosCliente(cliente->getClienteID());
            break;
        case 4:
            break;
        }
    } while (opcion != 4);
}

// Funci�n para guardar la informaci�n del cliente en el archivo
void saveClientInfo(const CLIENTE& client) {
    ofstream file("client_registration.txt", ios::app); // Abre el archivo en modo append
    if (file.is_open()) {
        file << client.getIdCliente() << ","
            << client.getNombre() << ","
            << client.getApellido() << ","
            << client.getCorreoElectronico() << ","
            << client.getContrasenia() << ","
            << client.getDireccion() << ","
            << client.getTelefono() << ","
            << client.getFechaNacimiento() << ","
            << client.getGenero() << "\n";
        file.close();

        cout << DOUBLE_SPACE << GREEN_COLOR << "�Registro completado exitosamente!" << endl; // Mostrar un mensaje de confirmaci�n
    }
    else {
        cout << "No se pudo abrir el archivo para guardar la informaci�n." << endl;
    }

}

// Funci�n para guardar la contrase�a cifrada
void savePassword(const string& email, const string& password) {
    ofstream passwordFile("passwords.txt", ios::app); // Abre el archivo en modo append
    if (passwordFile.is_open()) {
        passwordFile << email << " " << password << "\n"; // Escribir el correo electr�nico y la contrase�a en el archivo
        passwordFile.close();
    }
    else {
        cout << "No se pudo abrir el archivo para guardar la contrase�a." << endl;
    }
}

// Funciones de gesti�n de productos    

// Funci�n para mostrar el men� de cat�logo de productos
void productCatalogMenu() {

    int opcion;
    string nombre;

    GESTION_PRODUCTOS productManager;

    do
    {

        system("cls");

        cout << CYAN_COLOR << "=== C�TALOGO DE PRODUCTOS ===" << RESET_COLOR << DOUBLE_SPACE;
        cout << "<1> Ver productos" << endl;
        cout << "<2> Filtrar productos" << endl;
        cout << "<3> Buscar productos por nombre" << endl;
        cout << "<4> Volver";
        ShowConsoleCursor(true); // Mostrar el cursor
        cout << DOUBLE_SPACE << YELLOW_COLOR << "Ingrese una opci�n: " << RESET_COLOR;
        cin >> opcion;

        // Verifica si la entrada fall�
        if (cin.fail()) { // Verifica si la entrada fall�
            cin.clear(); // Limpia el estado de cin
            cin.ignore((numeric_limits<streamsize>::max)(), '\n'); // Ignora la entrada incorrecta
            ShowConsoleCursor(false); // Oculta el cursor
            cout << DOUBLE_SPACE << MAGENTA_COLOR << "Entrada no v�lida, por favor ingrese un n�mero."; // Entrada no v�lida
            Sleep(1500); // Espera 1.5 segundos
            continue; // Contin�a al siguiente ciclo del bucle do-while
        }

        switch (opcion)
        {
        case 1: 

            // Verifica si el cat�logo est� vac�o
            if (productManager.getCantidadProductos() == 0) {
                cout << DOUBLE_SPACE << MAGENTA_COLOR << "No hay productos en el cat�logo." << endl; // No hay productos en el cat�logo 
                break;
            }

            system("cls");
            productManager.mostrarTodosLosProductos();
            ShowConsoleCursor(false); // Oculta el cursor
            cout << DOUBLE_SPACE << GRAY_COLOR << "Presiona cualquier tecla para continuar...";
            _getch();
            system("cls");
            break;
        case 2:
            filtrarProductosPorCategoria();
            break;
        case 3:
            system("cls");
            cout << YELLOW_COLOR << "Ingresa el nombre del producto a buscar: " << RESET_COLOR;
            cin.ignore();
            getline(cin, nombre);
            cout << endl;
            productManager.buscarProductoPorNombre(nombre);
			break;
        case 4:
            break;
        }

    } while (opcion != 4);

}

// Funci�n para filtrar productos por categor�a
void filtrarProductosPorCategoria() {
    int opcion;

    GESTION_PRODUCTOS productManager;

    do {

        system("cls");

        cout << CYAN_COLOR << "=== FILTRAR PRODUCTOS POR CATEGOR�A ===" << RESET_COLOR << DOUBLE_SPACE;
        cout << "<1> Filtrar por precio" << endl;
        cout << "<2> Filtrar por color" << endl;
        cout << "<3> Filtrar por marca" << endl;
        cout << "<4> Volver";
        ShowConsoleCursor(true); // Mostrar el cursor
        cout << DOUBLE_SPACE << YELLOW_COLOR << "Ingrese una opci�n: " << RESET_COLOR;
        cin >> opcion;

        // Verifica si la entrada fall�
        if (cin.fail()) { // Verifica si la entrada fall�
            cin.clear(); // Limpia el estado de cin
            cin.ignore((numeric_limits<streamsize>::max)(), '\n'); // Ignora la entrada incorrecta
            ShowConsoleCursor(false); // Oculta el cursor
            cout << DOUBLE_SPACE << MAGENTA_COLOR << "Entrada no v�lida, por favor ingrese un n�mero."; // Entrada no v�lida
            Sleep(1500); // Espera 1.5 segundos
            continue; // Contin�a al siguiente ciclo del bucle do-while
        }

        switch (opcion) {
        case 1:
            system("cls");
            productManager.filtrarPorPrecio(productManager); 
            break;
        case 2:
            system("cls");
            productManager.filtrarPorColor(productManager);
            break;
        case 3:
            system("cls");
            productManager.filtrarPorMarca(productManager);
            break;
        case 4:
            break;
        }
    } while (opcion != 4);
}

// Funci�n para mostrar el men� y manejar la interacci�n con el usuario
void productManagementMenu() {
    GESTION_PRODUCTOS manager; // Crear el gestor de productos con el archivo
    int opcion; // Opci�n elegida por el usuario
    int opcion_ordenar; // Opci�n para ordenar los productos

    do{

        system("cls"); // Limpiar la pantalla en sistemas Windows

        cout << CYAN_COLOR << "=== GESTI�N DE PRODUCTOS ===" << DOUBLE_SPACE << RESET_COLOR;
        cout << "<1> Cat�logo de productos" << endl;
        cout << "<2> Agregar nuevo producto" << endl;
        cout << "<3> Actualizar producto" << endl;
        cout << "<4> Eliminar producto" << endl;
        cout << "<5> Buscar producto" << endl;
        cout << "<6> Salir";
        ShowConsoleCursor(true); // Mostrar el cursor
        cout << DOUBLE_SPACE << YELLOW_COLOR << "Ingrese una opci�n: " << RESET_COLOR;
        cin >> opcion;

        // Verifica si la entrada fall�
        if (cin.fail()) { // Verifica si la entrada fall�
            cin.clear(); // Limpia el estado de cin
            cin.ignore((numeric_limits<streamsize>::max)(), '\n'); // Ignora la entrada incorrecta
            ShowConsoleCursor(false); // Oculta el cursor
            cout << DOUBLE_SPACE << MAGENTA_COLOR << "Entrada no v�lida, por favor ingrese un n�mero."; // Entrada no v�lida
            Sleep(1500); // Espera 1.5 segundos
            continue; // Contin�a al siguiente ciclo del bucle do-while
        }

        switch (opcion) {
        case 1:
            manager.mostrarTodosLosProductos(); // Muestra todos los productos

            // Verifica si el cat�logo est� vac�o
            if (manager.getCantidadProductos() == 0) {
                break;
            }

            // Pregunta al usuario si desea ordenar los productos por precio
            do
            {

                cout << endl << YELLOW_COLOR << "�Desea ordenar los productos por precio?" << DOUBLE_SPACE << RESET_COLOR;
                cout << "<1> S�" << endl;
                cout << "<2> No";
                ShowConsoleCursor(true); // Muestra el cursor
                cout << YELLOW_COLOR << DOUBLE_SPACE << "Ingrese una opci�n: " << RESET_COLOR;
                cin >> opcion_ordenar;

                if (opcion_ordenar == 1) {
                    sortProductsPrice();
                }
				else if (opcion_ordenar == 2) {
					break;
				}
                else {
                    ShowConsoleCursor(false); // Oculta el cursor
                    cout << endl << MAGENTA_COLOR << "Opci�n no v�lida. Por favor, intente de nuevo." << endl;
                    _sleep(1500);
                }

            } while (opcion_ordenar != 2);
            break;
        case 2:
            system("cls");
            addNewProduct(manager); // Agregar un nuevo producto
            break;
        case 3:
            system("cls");
            updateProductProcedure(manager); // Actualizar un producto
            break;
        case 4:
            system("cls");
            removeProductProcedure(manager); // Eliminar un producto
            break;
        case 5:
            system("cls");
            searchProduct(manager); // Buscar un producto
            break;
        case 6:
            break;
        }
    } while (opcion != 6);
}

// Funci�n para mostrar el men� de gesti�n de inventario
void inventoryManagementMenu() {
    int opcion;
    string codigoProducto;
    int cantidad;

    NODO_PRODUCTO* producto = nullptr; // Declara producto fuera del switch
    GESTION_PRODUCTOS gestorProductos;
    GESTION_INVENTARIO gestionInventarios;

    gestionInventarios.cargarInventarioDesdeArchivo(); // Cargar el inventario desde el archivo al iniciar el programa
    gestionInventarios.cargarMovimientosDesdeArchivo(); // Cargar el historial de movimientos desde el archivo al iniciar el programa

    do {
        system("cls");
        cout << CYAN_COLOR << "=== Men� de Gesti�n de Inventarios ===" << endl << RESET_COLOR << endl;
        cout << "<1> Ver Inventario" << endl;
        cout << "<2> A�adir Stock" << endl;
        cout << "<3> Retirar Stock" << endl;
        cout << "<4> Historial de Movimientos" << endl;
        cout << "<5> Salir" << endl;
        ShowConsoleCursor(true); // Muestra el cursor
        cout << endl << YELLOW_COLOR << "Ingrese la opci�n deseada: " << RESET_COLOR;
        cin >> opcion;

        // Verifica si la entrada fall�
        if (cin.fail()) { // Verifica si la entrada fall�
            cin.clear(); // Limpia el estado de cin
            cin.ignore((numeric_limits<streamsize>::max)(), '\n'); // Ignora la entrada incorrecta
            ShowConsoleCursor(false); // Oculta el cursor
            cout << DOUBLE_SPACE << MAGENTA_COLOR << "Entrada no v�lida, por favor ingrese un n�mero."; // Entrada no v�lida
            Sleep(1500); // Espera 1.5 segundos
            continue; // Contin�a al siguiente ciclo del bucle do-while
        }

        switch (opcion) {
        case 1:
            gestionInventarios.verInventario();
            break;
        case 2:
            system("cls");
            cout << YELLOW_COLOR << "Ingrese el c�digo del producto que desea agregar al inventario: " << RESET_COLOR;
            cin >> codigoProducto;
            producto = gestorProductos.buscarProducto(codigoProducto); // Obtiene un puntero al producto
            if (producto != nullptr) {
                int cantidad;
                cout << YELLOW_COLOR << "Ingrese la cantidad de stock a a�adir: " << RESET_COLOR;
                while (!(cin >> cantidad) || cantidad <= 0) {
                    if (cin.fail()) {
                        // Limpiar el estado de error y descartar la entrada inv�lida
                        cin.clear();
                        cin.ignore((numeric_limits<streamsize>::max)(), '\n'); // Ignora la entrada incorrecta
                        cout << endl << MAGENTA_COLOR << "Debe ingresar un n�mero v�lido para la cantidad de stock." << RESET_COLOR << DOUBLE_SPACE;
                    }
                    else {
                        cout << MAGENTA_COLOR << "La cantidad de stock debe ser un n�mero positivo." << RESET_COLOR << DOUBLE_SPACE;
                    }
                    cout << YELLOW_COLOR << "Ingrese nuevamente la cantidad de stock: " << RESET_COLOR;
                }
                gestionInventarios.a�adirStock(producto->producto.getCodigo(), cantidad); // Utiliza el c�digo del producto

                ShowConsoleCursor(false); // Oculta el cursor
                cout << DOUBLE_SPACE << GREEN_COLOR << "Stock a�adido exitosamente." << RESET_COLOR;
                Sleep(1500);
            }
            else {
                ShowConsoleCursor(false); // Oculta el cursor
                cout << endl << MAGENTA_COLOR << "El producto no se encuentra en la lista de productos." << endl;
                Sleep(1500);
            }
            break;
        case 3:
            system("cls");
            cout << YELLOW_COLOR << "Ingrese el c�digo del producto del cual desea retirar stock: " << RESET_COLOR;
            cin >> codigoProducto;
            producto = gestorProductos.buscarProducto(codigoProducto); // Asigna valor a producto
            if (producto != nullptr) {
                cout << YELLOW_COLOR << "Ingrese la cantidad de stock a retirar: " << RESET_COLOR;
                while (!(cin >> cantidad) || cantidad <= 0) {
                    if (cin.fail()) {
                        // Limpiar el estado de error y descartar la entrada inv�lida
                        cin.clear();
                        cin.ignore((numeric_limits<streamsize>::max)(), '\n'); // Ignora la entrada incorrecta
                        cout << MAGENTA_COLOR << "Debe ingresar un n�mero v�lido para la cantidad de stock." << RESET_COLOR << DOUBLE_SPACE;
                    }
                    else {
                        cout << MAGENTA_COLOR << "La cantidad de stock debe ser un n�mero positivo." << RESET_COLOR << DOUBLE_SPACE;
                    }
                    cout << YELLOW_COLOR << "Ingrese nuevamente la cantidad de stock: " << RESET_COLOR;
                }

                gestionInventarios.retirarStock(producto->producto.getCodigo(), cantidad);

                ShowConsoleCursor(false); // Oculta el cursor
                cout << DOUBLE_SPACE << GREEN_COLOR << "Stock retirado exitosamente." << RESET_COLOR;
                Sleep(1500);
            }
            else {
                ShowConsoleCursor(false); // Oculta el cursor
                cout << DOUBLE_SPACE << MAGENTA_COLOR << "El producto no se encuentra en la lista de productos." << endl;
                Sleep(1500);
            }
            break;
        case 4:
            system("cls");
            // Mostrar historial de movimientos
            gestionInventarios.mostrarHistorialMovimientos();
            ShowConsoleCursor(false); // Oculta el cursor
            cout << DOUBLE_SPACE << GRAY_COLOR << "Presione cualquier tecla para continuar...";
            _getch();
            break;
        case 5:
            break;
        }
    } while (opcion != 5);
}

// Funci�n para mostrar el men� y obtener la opci�n del usuario
void supplierManagementMenu() {
    int opcion;
    string nombreBuscar;
    const string archivoProveedores = "supplier_data.txt";

    GestionarProveedores supplierManager; // Crear un objeto de la clase GestionarProveedores

    supplierManager.cargarListaDesdeArchivo();
    
    do {
        system("cls");
        cout << CYAN_COLOR << "=== GESTI�N DE PROVEEDORES ===" << RESET_COLOR << DOUBLE_SPACE;
        cout << "<1> Ver lista de proveedores" << endl;
        cout << "<2> Agregar nuevo proveedor" << endl;
        cout << "<3> Actualizar informaci�n de proveedor" << endl;
        cout << "<4> Eliminar proveedor" << endl;
        cout << "<5> Buscar proveedor" << endl;
        cout << "<6> Volver" << DOUBLE_SPACE;
        ShowConsoleCursor(true); // Muestra el cursor
        cout << YELLOW_COLOR << "Seleccione una opcion: " << RESET_COLOR;
        cin >> opcion;

        if (cin.fail()) { // Verifica si la entrada fall�
            cin.clear(); // Limpia el estado de cin
            cin.ignore((numeric_limits<streamsize>::max)(), '\n'); // Ignora la entrada incorrecta
            ShowConsoleCursor(false);
            cout << DOUBLE_SPACE << MAGENTA_COLOR << "Entrada no v�lida, por favor ingrese un n�mero." << endl;
            Sleep(1000);
            ShowConsoleCursor(true);
            continue; // Contin�a al siguiente ciclo del bucle do-while
        }

        switch (opcion) {
        case 1:
            // Verificar si la lista de proveedores est� vac�a
            if (supplierManager.listaProveedoresVacia()) {
                ShowConsoleCursor(false); // Oculta el cursor
				cout << DOUBLE_SPACE << MAGENTA_COLOR << "No se cuenta con proveedores por el momento." << RESET_COLOR;
				Sleep(1500);
				break;
			}
            system("cls");
            supplierManager.verListaProveedores();
            ShowConsoleCursor(false); // Oculta el cursor
            cout << DOUBLE_SPACE << GRAY_COLOR << "Presione cualquier tecla para salir";
            _getch();
            system("cls");
            break;
        case 2:
            system("cls");
            supplierManager.agregarProveedor(archivoProveedores);
            Sleep(1000);
            system("cls");
            break;
        case 3:
            // Verificar si la lista de proveedores est� vac�a
            if (supplierManager.listaProveedoresVacia()) {
                ShowConsoleCursor(false); // Oculta el cursor
                cout << DOUBLE_SPACE << MAGENTA_COLOR << "No se cuenta con proveedores por el momento." << RESET_COLOR;
                Sleep(1500);
                break;
            }
            system("cls");
            supplierManager.actualizarProveedor(archivoProveedores);
            Sleep(1000);
            system("cls");
            break;
        case 4:
            // Verificar si la lista de proveedores est� vac�a
            if (supplierManager.listaProveedoresVacia()) {
                ShowConsoleCursor(false); // Oculta el cursor
                cout << DOUBLE_SPACE << MAGENTA_COLOR << "No se cuenta con proveedores por el momento." << RESET_COLOR;
                Sleep(1500);
                break;
            }
            system("cls");
            supplierManager.eliminarProveedor(archivoProveedores);
            Sleep(1000);
            system("cls");
            break;
        case 5:
            // Verificar si la lista de proveedores est� vac�a
            if (supplierManager.listaProveedoresVacia()) {
                ShowConsoleCursor(false); // Oculta el cursor
                cout << DOUBLE_SPACE << MAGENTA_COLOR << "No se cuenta con proveedores por el momento." << RESET_COLOR;
                Sleep(1500);
                break;
            }
            system("cls");
            cout << YELLOW_COLOR << "Ingrese el nombre del proveedor que desea buscar: " << RESET_COLOR;
            cin.ignore();
            getline(cin, nombreBuscar);
            supplierManager.buscarProveedor(nombreBuscar);
            cout << DOUBLE_SPACE << GRAY_COLOR << "Presionar cualquier tecla para continuar";
            _getch();
            system("cls");
            break;
        case 6:
            break;
        }
    } while (opcion != 6);
}

// Funci�n para mostrar el men� de realizar pedido para cliente
void orderingMenu() {
    GESTION_INVENTARIO inventario;
    CARRO_COMPRAS carrito;
    SISTEMA_PEDIDOS sistemaPedidos;
    GESTION_PROMOCIONES gestionPromociones;

    inventario.cargarInventarioDesdeArchivo(); // Cargar el inventario desde el archivo al iniciar el programa

    int opcion;
    bool running = true;
    string codigoProducto;
    int cantidad;

    string clienteID = CLIENTE_ACTUAL::obtenerInstancia()->getClienteID();

    while (running) {
        system("cls");
        cout << CYAN_COLOR << "=== REALIZAR PEDIDO ===" << RESET_COLOR << DOUBLE_SPACE;
        cout << "<1> Agregar Producto al Carrito" << endl;
        cout << "<2> Ver Carrito" << endl;
        cout << "<3> Confirmar Pedido" << endl;
        cout << "<4> Cancelar Pedido" << endl;
        cout << "<5> Salir";
        ShowConsoleCursor(true); // Muestra el cursor
        cout << YELLOW_COLOR << DOUBLE_SPACE << "Seleccione una opci�n: " << RESET_COLOR;
        cin >> opcion;

        if (cin.fail()) {
            cin.clear();
            cin.ignore((numeric_limits<streamsize>::max)(), '\n');
            ShowConsoleCursor(false);
            cout << DOUBLE_SPACE << MAGENTA_COLOR << "Entrada no v�lida, por favor ingrese un n�mero." << endl;
            Sleep(1000);
            ShowConsoleCursor(true);
            continue;
        }

        switch (opcion) {
        case 1:
            system("cls");
            cout << YELLOW_COLOR << "Ingrese el c�digo del producto a agregar: " << RESET_COLOR;
            cin >> codigoProducto;

            if (!inventario.existeProducto(codigoProducto)) {
                ShowConsoleCursor(false);
                cout << DOUBLE_SPACE << MAGENTA_COLOR << "El producto no existe en el inventario." << RESET_COLOR;
                Sleep(1500);
                break;
            }

            if (gestionPromociones.tienePromocion(codigoProducto)) {
                PROMOCION promo = gestionPromociones.obtenerPromocion(codigoProducto);
                cout << endl << CYAN_COLOR << "Este producto tiene una promoci�n: " << endl;
                cout << GRAY_COLOR << "Descuento: " << RESET_COLOR << promo.descuento << "%" << endl;
                cout << GRAY_COLOR << "Descripci�n: " << RESET_COLOR << promo.descripcion << DOUBLE_SPACE;
            }

            cout << YELLOW_COLOR << "Ingrese la cantidad a agregar: " << RESET_COLOR;
            while (!(cin >> cantidad) || cantidad <= 0) {
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore((numeric_limits<streamsize>::max)(), '\n');
                    cout << MAGENTA_COLOR << "Debe ingresar un n�mero v�lido para la cantidad." << RESET_COLOR << DOUBLE_SPACE;
                }
                else {
                    cout << MAGENTA_COLOR << "La cantidad debe ser un n�mero positivo." << RESET_COLOR << DOUBLE_SPACE;
                }
                cout << YELLOW_COLOR << "Ingrese nuevamente la cantidad a agregar: " << RESET_COLOR;
            }

            if (inventario.verificarStock(codigoProducto, cantidad)) {
                carrito.agregarPedido(PEDIDO(clienteID, codigoProducto, cantidad));
                ShowConsoleCursor(false);
                cout << DOUBLE_SPACE << GREEN_COLOR << "Producto agregado al carrito correctamente." << RESET_COLOR;
                Sleep(1500);
            }
            else {
                ShowConsoleCursor(false);
                cout << DOUBLE_SPACE << MAGENTA_COLOR << "No hay suficiente stock de este producto." << RESET_COLOR;
                Sleep(1500);
            }
            break;

        case 2:
            carrito.verCarrito();
            break;

        case 3:
            if (!carrito.isEmpty()) {
                system("cls");
                cout << CYAN_COLOR << "Para la entrega de su pedido. �Desea ingresar una nueva direcci�n?" << endl << RESET_COLOR;
                cout << "<1> S�" << endl;
                cout << "<2> No" << endl;
                cout << YELLOW_COLOR << "Ingrese una opci�n: " << RESET_COLOR;
                int opcion;
                cin >> opcion;

                if (cin.fail()) { // Verifica si la entrada fall�
                    cin.clear(); // Limpia el estado de cin
                    cin.ignore((numeric_limits<streamsize>::max)(), '\n'); // Ignora la entrada incorrecta
                    ShowConsoleCursor(false);
                    cout << DOUBLE_SPACE << MAGENTA_COLOR << "Entrada no v�lida, por favor ingrese un n�mero." << endl;
                    Sleep(1000);
                    ShowConsoleCursor(true);
                    continue; // Contin�a al siguiente ciclo del bucle do-while
                }

                string nuevaDireccion;

                if (opcion == 1) {
                    int distrito;
                    string direccionCompleta;

                    system("cls");

                    cout << YELLOW_COLOR << "Confirme la direcci�n de entrega: " << RESET_COLOR << DOUBLE_SPACE;
                    cout << "<1> ATE" << endl;
                    cout << "<2> Barranco" << endl;
                    cout << "<3> Brena" << endl;
                    cout << "<4> Cercado" << endl;
                    cout << "<5> Chorrillos" << endl;
                    cout << "<6> Cieneguilla" << endl;
                    cout << "<7> El Agustino" << endl;
                    cout << "<8> Independencia" << endl;
                    cout << "<9> Jesus Maria" << endl;
                    cout << "<10> La Molina" << endl;
                    cout << "<11> La Victoria" << endl;
                    cout << "<12> Lince" << endl;
                    cout << "<13> Los Olivos" << endl;
                    cout << "<14> Lurin" << endl;
                    cout << "<15> Magdalena" << endl;
                    cout << "<16> Miraflores" << endl;
                    cout << "<17> Pachacamac" << endl;
                    cout << "<18> Pueblo Libre" << endl;
                    cout << "<19> Rimac" << endl;
                    cout << "<20> San Borja" << endl;
                    cout << "<21> San Isidro" << endl;
                    cout << "<22> San Juan de Lurigancho" << endl;
                    cout << "<23> San Juan de Miraflores" << endl;
                    cout << "<24> San Martin de Porres" << endl;
                    cout << "<25> Santiago de Surco" << endl;
                    cout << "<26> Santa Anita" << endl;
                    cout << "<27> Surquillo" << endl;
                    cout << "<28> Villa Maria del Triunfo" << endl;
                    cout << "<29> Villa el Salvador" << DOUBLE_SPACE;

                    cout << YELLOW_COLOR << "Ingrese el n�mero del distrito: " << RESET_COLOR;
                    cin >> distrito;

                    if (cin.fail()) { // Verifica si la entrada fall�
                        cin.clear(); // Limpia el estado de cin
                        cin.ignore((numeric_limits<streamsize>::max)(), '\n'); // Ignora la entrada incorrecta
                        ShowConsoleCursor(false);
                        cout << DOUBLE_SPACE << MAGENTA_COLOR << "Entrada no v�lida, por favor ingrese un n�mero." << endl;
                        Sleep(1000);
                        ShowConsoleCursor(true);
                        continue; // Contin�a al siguiente ciclo del bucle do-while
                    }
                    
                    switch (distrito)
                    {
                    case 1: nuevaDireccion = "ATE"; break;
                    case 2: nuevaDireccion = "Barranco"; break;
                    case 3: nuevaDireccion = "Brena"; break;
                    case 4: nuevaDireccion = "Cercado"; break;
                    case 5: nuevaDireccion = "Chorrillos"; break;
                    case 6: nuevaDireccion = "Cieneguilla"; break;
                    case 7: nuevaDireccion = "El Agustino"; break;
                    case 8: nuevaDireccion = "Independencia"; break;
					case 9: nuevaDireccion = "Jesus Maria"; break;
                    case 10: nuevaDireccion = "La Molina"; break;
                    case 11: nuevaDireccion = "La Victoria"; break;
                    case 12: nuevaDireccion = "Lince"; break;
                    case 13: nuevaDireccion = "Los Olivos"; break;
                    case 14: nuevaDireccion = "Lurin"; break;
                    case 15: nuevaDireccion = "Magdalena"; break;
                    case 16: nuevaDireccion = "Miraflores"; break;
                    case 17: nuevaDireccion = "Pachacamac"; break;
                    case 18: nuevaDireccion = "Pueblo Libre"; break;
                    case 19: nuevaDireccion = "Rimac"; break;
                    case 20: nuevaDireccion = "San Borja"; break;
                    case 21: nuevaDireccion = "San Isidro"; break;
                    case 22: nuevaDireccion = "San Juan de Lurigancho"; break;
                    case 23: nuevaDireccion = "San Juan de Miraflores"; break;
                    case 24: nuevaDireccion = "San Martin de Porres"; break;
                    case 25: nuevaDireccion = "Santiago de Surco"; break;
                    case 26: nuevaDireccion = "Santa Anita"; break;
                    case 27: nuevaDireccion = "Surquillo"; break;
                    case 28: nuevaDireccion = "Villa Maria del Triunfo"; break;
                    case 29: nuevaDireccion = "Villa el Salvador"; break;
                    }
                }
                else {
                    // Si no se ingresa una nueva direcci�n, se usa la direcci�n predeterminada del cliente
                    nuevaDireccion = CLIENTE_ACTUAL::obtenerInstancia()->obtenerDireccionClienteActual();
                }

                // Obtener una copia de los pedidos del carrito
                vector<PEDIDO> pedidosCarrito = carrito.obtenerPedidos();
                for (auto& pedido : pedidosCarrito) {
                    pedido.setDireccionEntrega(nuevaDireccion);
                    sistemaPedidos.agregarPedidoPendiente(pedido);
                }
                sistemaPedidos.guardarPedidosPendientes();
                carrito.limpiarCarrito();
                ShowConsoleCursor(false);
                cout << DOUBLE_SPACE << GREEN_COLOR << "Pedido(s) confirmado correctamente." << RESET_COLOR;
                Sleep(1500);
            }
            else {
                ShowConsoleCursor(false);
                cout << endl << MAGENTA_COLOR << "El carrito est� vac�o. No se puede confirmar el pedido." << RESET_COLOR;
                Sleep(1500);
            }
            break;

        case 4:
            if (!carrito.isEmpty()) {
                ShowConsoleCursor(false);
                cout << DOUBLE_SPACE << GREEN_COLOR << "Pedido cancelado. El carrito ha sido vaciado." << RESET_COLOR;
                carrito.limpiarCarrito();
                Sleep(1500);
            }
            else {
                ShowConsoleCursor(false);
                cout << endl << MAGENTA_COLOR << "El carrito est� vac�o. No se puede cancelar el pedido." << RESET_COLOR;
                Sleep(1500);
            }
            break;

        case 5:
            running = false;
            break;
        }
    }
}

// Funci�n para gestionar pedidos
void orderManagementMenu() {
    SISTEMA_PEDIDOS sistemaPedidos;
    // Antes del bucle o en alg�n lugar antes de utilizarlo en tu c�digo
    GESTION_INVENTARIO inventario;

    inventario.cargarInventarioDesdeArchivo(); // Cargar el inventario desde el archivo

    int opcion;

    bool running = true;

    int indicePedido;

    vector<string> districts = {
       "Miraflores", "La Victoria", "Rimac", "La Molina", "San Martin de Porres", "Chorrillos",
       "Los Olivos", "Independencia", "San Juan de Lurigancho", "ATE", "Cieneguilla", "El Agustino",
       "Santa Anita", "Pachacamac", "Lurin", "Villa Maria del Triunfo", "Villa el Salvador",
       "San Juan de Miraflores", "Santiago de Surco", "San Borja", "Barranco", "Surquillo",
       "San Isidro", "Lince", "Jesus Maria", "Brena", "Cercado", "Pueblo Libre", "Magdalena"
    };

    // Crear el grafo
    Graph g(districts);

    // A�adir aristas al grafo para San Mart�n de Porres
    g.addEdge("San Martin de Porres", "Miraflores", 15);
    g.addEdge("San Martin de Porres", "La Victoria", 10);
    g.addEdge("San Martin de Porres", "Rimac", 5);
    g.addEdge("San Martin de Porres", "La Molina", 20);
    g.addEdge("San Martin de Porres", "Chorrillos", 25);
    g.addEdge("San Martin de Porres", "Los Olivos", 6);
    g.addEdge("San Martin de Porres", "Independencia", 5);
    g.addEdge("San Martin de Porres", "San Juan de Lurigancho", 12);
    g.addEdge("San Martin de Porres", "ATE", 18);
    g.addEdge("San Martin de Porres", "Lurin", 40);
    g.addEdge("San Martin de Porres", "El Agustino", 10);
    g.addEdge("San Martin de Porres", "Santa Anita", 15);
    g.addEdge("San Martin de Porres", "Pachacamac", 35);
    g.addEdge("San Martin de Porres", "Villa Maria del Triunfo", 30);
    g.addEdge("San Martin de Porres", "Villa el Salvador", 30);
    g.addEdge("San Martin de Porres", "San Juan de Miraflores", 25);
    g.addEdge("San Martin de Porres", "Santiago de Surco", 20);
    g.addEdge("San Martin de Porres", "San Borja", 15);
    g.addEdge("San Martin de Porres", "Barranco", 20);
    g.addEdge("San Martin de Porres", "Surquillo", 15);
    g.addEdge("San Martin de Porres", "San Isidro", 12);
    g.addEdge("San Martin de Porres", "Lince", 10);
    g.addEdge("San Martin de Porres", "Jesus Maria", 9);
    g.addEdge("San Martin de Porres", "Brena", 7);
    g.addEdge("San Martin de Porres", "Cercado", 7);
    g.addEdge("San Martin de Porres", "Pueblo Libre", 10);
    g.addEdge("San Martin de Porres", "Magdalena", 12);
    g.addEdge("San Martin de Porres", "San Martin de Porres", 1);

    // A�adir aristas al grafo para R�mac
    g.addEdge("Rimac", "Miraflores", 10);
    g.addEdge("Rimac", "La Victoria", 5);
    g.addEdge("Rimac", "Rimac", 1);
    g.addEdge("Rimac", "La Molina", 15);
    g.addEdge("Rimac", "San Martin de Porres", 6);
    g.addEdge("Rimac", "Chorrillos", 18);
    g.addEdge("Rimac", "Los Olivos", 8);
    g.addEdge("Rimac", "Independencia", 8);
    g.addEdge("Rimac", "San Juan de Lurigancho", 10);
    g.addEdge("Rimac", "ATE", 12);
    g.addEdge("Rimac", "Cieneguilla", 30);
    g.addEdge("Rimac", "El Agustino", 6);
    g.addEdge("Rimac", "Santa Anita", 10);
    g.addEdge("Rimac", "Pachacamac", 30);
    g.addEdge("Rimac", "Lurin", 35);
    g.addEdge("Rimac", "Villa Maria del Triunfo", 20);
    g.addEdge("Rimac", "Villa el Salvador", 25);
    g.addEdge("Rimac", "San Juan de Miraflores", 18);
    g.addEdge("Rimac", "Santiago de Surco", 15);
    g.addEdge("Rimac", "San Borja", 10);
    g.addEdge("Rimac", "Barranco", 12);
    g.addEdge("Rimac", "Surquillo", 10);
    g.addEdge("Rimac", "San Isidro", 8);
    g.addEdge("Rimac", "Lince", 7);
    g.addEdge("Rimac", "Jesus Maria", 5);
    g.addEdge("Rimac", "Brena", 4);
    g.addEdge("Rimac", "Cercado", 3);
    g.addEdge("Rimac", "Pueblo Libre", 7);
    g.addEdge("Rimac", "Magdalena", 10);

    // A�adir aristas al grafo para La Molina
    g.addEdge("La Molina", "Miraflores", 13);
    g.addEdge("La Molina", "La Victoria", 12);
    g.addEdge("La Molina", "Rimac", 15);
    g.addEdge("La Molina", "La Molina", 1);
    g.addEdge("La Molina", "San Martin de Porres", 20);
    g.addEdge("La Molina", "Chorrillos", 20);
    g.addEdge("La Molina", "Los Olivos", 22);
    g.addEdge("La Molina", "Independencia", 20);
    g.addEdge("La Molina", "San Juan de Lurigancho", 12);
    g.addEdge("La Molina", "ATE", 8);
    g.addEdge("La Molina", "Cieneguilla", 30);
    g.addEdge("La Molina", "El Agustino", 10);
    g.addEdge("La Molina", "Santa Anita", 7);
    g.addEdge("La Molina", "Pachacamac", 25);
    g.addEdge("La Molina", "Lurin", 30);
    g.addEdge("La Molina", "Villa Maria del Triunfo", 20);
    g.addEdge("La Molina", "Villa el Salvador", 22);
    g.addEdge("La Molina", "San Juan de Miraflores", 18);
    g.addEdge("La Molina", "Santiago de Surco", 15);
    g.addEdge("La Molina", "San Borja", 10);
    g.addEdge("La Molina", "Barranco", 15);
    g.addEdge("La Molina", "Surquillo", 12);
    g.addEdge("La Molina", "San Isidro", 13);
    g.addEdge("La Molina", "Lince", 14);
    g.addEdge("La Molina", "Jesus Maria", 15);
    g.addEdge("La Molina", "Brena", 15);
    g.addEdge("La Molina", "Cercado", 17);
    g.addEdge("La Molina", "Pueblo Libre", 17);
    g.addEdge("La Molina", "Magdalena", 18);

    // A�adir aristas al grafo para Chorrilos 
    g.addEdge("Chorrillos", "Miraflores", 10);
    g.addEdge("Chorrillos", "Rimac", 18);
    g.addEdge("Chorrillos", "San Martin de Porres", 20);
    g.addEdge("Chorrillos", "La Molina", 25);
    g.addEdge("Chorrillos", "La Victoria", 15);
    g.addEdge("Chorrillos", "Los Olivos", 22);
    g.addEdge("Chorrillos", "Independencia", 22);
    g.addEdge("Chorrillos", "San Juan de Lurigancho", 22);
    g.addEdge("Chorrillos", "ATE", 25);
    g.addEdge("Chorrillos", "Cieneguilla", 30);
    g.addEdge("Chorrillos", "El Agustino", 20);
    g.addEdge("Chorrillos", "Santa Anita", 22);
    g.addEdge("Chorrillos", "Pachacamac", 15);
    g.addEdge("Chorrillos", "Lurin", 20);
    g.addEdge("Chorrillos", "Villa Maria del Triunfo", 7);
    g.addEdge("Chorrillos", "Villa el Salvador", 10);
    g.addEdge("Chorrillos", "San Juan de Miraflores", 8);
    g.addEdge("Chorrillos", "Santiago de Surco", 10);
    g.addEdge("Chorrillos", "San Borja", 15);
    g.addEdge("Chorrillos", "Barranco", 6);
    g.addEdge("Chorrillos", "Surquillo", 10);
    g.addEdge("Chorrillos", "San Isidro", 12);
    g.addEdge("Chorrillos", "Lince", 15);
    g.addEdge("Chorrillos", "Jesus Maria", 16);
    g.addEdge("Chorrillos", "Brena", 17);
    g.addEdge("Chorrillos", "Cercado", 18);
    g.addEdge("Chorrillos", "Pueblo Libre", 16);
    g.addEdge("Chorrillos", "Magdalena", 14);
    g.addEdge("Chorrillos", "Chorrillos", 1);

    // A�adir aristas al grafo para La Victoria 
    g.addEdge("La Victoria", "Miraflores", 9);
    g.addEdge("La Victoria", "Rimac", 4);
    g.addEdge("La Victoria", "San Martin de Porres", 8);
    g.addEdge("La Victoria", "La Molina", 12);
    g.addEdge("La Victoria", "Chorrillos", 17);
    g.addEdge("La Victoria", "Los Olivos", 10);
    g.addEdge("La Victoria", "Independencia", 11);
    g.addEdge("La Victoria", "San Juan de Lurigancho", 9);
    g.addEdge("La Victoria", "ATE", 10);
    g.addEdge("La Victoria", "Cieneguilla", 27);
    g.addEdge("La Victoria", "El Agustino", 4);
    g.addEdge("La Victoria", "Santa Anita", 8);
    g.addEdge("La Victoria", "Pachacamac", 30);
    g.addEdge("La Victoria", "Lurin", 33);
    g.addEdge("La Victoria", "Villa Maria del Triunfo", 17);
    g.addEdge("La Victoria", "Villa el Salvador", 22);
    g.addEdge("La Victoria", "San Juan de Miraflores", 14);
    g.addEdge("La Victoria", "Santiago de Surco", 11);
    g.addEdge("La Victoria", "San Borja", 7);
    g.addEdge("La Victoria", "Barranco", 12);
    g.addEdge("La Victoria", "Surquillo", 9);
    g.addEdge("La Victoria", "San Isidro", 7);
    g.addEdge("La Victoria", "Lince", 4);
    g.addEdge("La Victoria", "Jesus Maria", 4);
    g.addEdge("La Victoria", "Brena", 4);
    g.addEdge("La Victoria", "Cercado", 4);
    g.addEdge("La Victoria", "Pueblo Libre", 7);
    g.addEdge("La Victoria", "Magdalena", 9);
    g.addEdge("La Victoria", "La Victoria", 1);

    // A�adir aristas al grafo para Miraflores
    g.addEdge("Miraflores", "La Victoria", 7);
    g.addEdge("Miraflores", "Miraflores", 1);
    g.addEdge("Miraflores", "Rimac", 9);
    g.addEdge("Miraflores", "San Martin de Porres", 12);
    g.addEdge("Miraflores", "La Molina", 14);
    g.addEdge("Miraflores", "Chorrillos", 10);
    g.addEdge("Miraflores", "Los Olivos", 15);
    g.addEdge("Miraflores", "Independencia", 15);
    g.addEdge("Miraflores", "San Juan de Lurigancho", 16);
    g.addEdge("Miraflores", "ATE", 14);
    g.addEdge("Miraflores", "Cieneguilla", 27);
    g.addEdge("Miraflores", "El Agustino", 10);
    g.addEdge("Miraflores", "Santa Anita", 13);
    g.addEdge("Miraflores", "Pachacamac", 22);
    g.addEdge("Miraflores", "Lurin", 25);
    g.addEdge("Miraflores", "Villa Maria del Triunfo", 14);
    g.addEdge("Miraflores", "Villa el Salvador", 17);
    g.addEdge("Miraflores", "San Juan de Miraflores", 10);
    g.addEdge("Miraflores", "Santiago de Surco", 7);
    g.addEdge("Miraflores", "San Borja", 7);
    g.addEdge("Miraflores", "Barranco", 5);
    g.addEdge("Miraflores", "Surquillo", 3);
    g.addEdge("Miraflores", "San Isidro", 3);
    g.addEdge("Miraflores", "Lince", 6);
    g.addEdge("Miraflores", "Jesus Maria", 7);
    g.addEdge("Miraflores", "Brena", 8);
    g.addEdge("Miraflores", "Cercado", 8);
    g.addEdge("Miraflores", "Pueblo Libre", 7);
    g.addEdge("Miraflores", "Magdalena", 7);
   
    while (running) {
        system("cls");  
        cout << CYAN_COLOR << "=== GESTI�N DE PEDIDOS ==" << RESET_COLOR << DOUBLE_SPACE;
        cout << "<1> Ver Pedidos Pendientes" << endl;
        cout << "<2> Ver Pedidos Procesados" << endl;
        cout << "<3> Procesar Pedido" << endl;
        cout << "<4> Eliminar Pedidos" << endl;
        cout << "<5> Historial de Pedidos" << endl;
        cout << "<6> Volver";
        ShowConsoleCursor(true); // Muestra el cursor
        cout << DOUBLE_SPACE << YELLOW_COLOR << "Seleccione una opci�n: " << RESET_COLOR;
        cin >> opcion;

        // Verifica si la entrada fall�
        if (cin.fail()) { // Verifica si la entrada fall�
            cin.clear(); // Limpia el estado de cin
            cin.ignore((numeric_limits<streamsize>::max)(), '\n'); // Ignora la entrada incorrecta
            ShowConsoleCursor(false); // Oculta el cursor
            cout << DOUBLE_SPACE << MAGENTA_COLOR << "Entrada no v�lida, por favor ingrese un n�mero."; // Entrada no v�lida
            Sleep(1500); // Espera 1.5 segundos
            continue; // Contin�a al siguiente ciclo del bucle do-while
        }

        switch (opcion) {
        case 1:
            sistemaPedidos.verTodosPedidosPendientes();
            system("cls");
            break;
        case 2:
            sistemaPedidos.verTodosPedidosProcesados();
            break;
        case 3:
            system("cls");
            sistemaPedidos.procesarPedidosMenu(g);
            break;
        case 4:
            sistemaPedidos.eliminarPedidoPorIndice(indicePedido);
            break;
        case 5:
            system("cls");
            sistemaPedidos.verHistorialPedidosVendedor();
            break;
        case 6:
            running = false;
            break;
        }
    }
}

// Funci�n para mostrar el men� de gesti�n de clientes
void customerManagementMenu() {
    GESTION_CLIENTE gestionCliente;
    
    int opcion;

    do {
        system("cls");

        cout << CYAN_COLOR << "=== GESTI�N DE CLIENTES ===" << DOUBLE_SPACE << RESET_COLOR;
        cout << "<1> Ver Lista de Clientes" << endl;
        cout << "<2> Eliminar Cliente" << endl;
        cout << "<3> Buscar Clientes" << endl;
        cout << "<4> Volver";
        ShowConsoleCursor(true); // Muestra el cursor
        cout << YELLOW_COLOR << DOUBLE_SPACE << "Seleccione una opcion: " << RESET_COLOR;
        cin >> opcion;

        // Verifica si la entrada fall�
        if (cin.fail()) { // Verifica si la entrada fall�
            cin.clear(); // Limpia el estado de cin
            cin.ignore((numeric_limits<streamsize>::max)(), '\n'); // Ignora la entrada incorrecta
            ShowConsoleCursor(false); // Oculta el cursor
            cout << DOUBLE_SPACE << MAGENTA_COLOR << "Entrada no v�lida, por favor ingrese un n�mero."; // Entrada no v�lida
            Sleep(1500); // Espera 1.5 segundos
            continue; // Contin�a al siguiente ciclo del bucle do-while
        }

        ifstream file("client_registration.txt");

        switch (opcion) {
        case 1:
            if (file.peek() == ifstream::traits_type::eof()) { // Verificar si el archivo est� vac�o
                ShowConsoleCursor(false); // Oculta el cursor
                cout << MAGENTA_COLOR << DOUBLE_SPACE << "No hay ning�n cliente registrado." << endl;
                _sleep(1500); // Espera 1.5 segundos
                file.close();
                break;
            }
            system("cls");
            cout << CYAN_COLOR << "Lista de clientes:" << DOUBLE_SPACE;   
            gestionCliente.displayCustomerList();
            break;
        case 2:
            if (file.peek() == ifstream::traits_type::eof()) { // Verificar si el archivo est� vac�o
                ShowConsoleCursor(false); // Oculta el cursor
                cout << MAGENTA_COLOR << DOUBLE_SPACE << "No hay ning�n cliente registrado." << endl;
                _sleep(1500); // Espera 1.5 segundos
                file.close();
                break;
            }
            system("cls");
            cout << CYAN_COLOR << "Eliminar cliente:" << DOUBLE_SPACE << RESET_COLOR;
            {
                string email;
                cout << YELLOW_COLOR << "Ingrese el correo electr�nico del cliente a eliminar: " << RESET_COLOR;
                cin >> email;
                gestionCliente.deleteCustomer(email);
                ShowConsoleCursor(false); // Oculta el cursor
                _sleep(1500); // Espera 1.5 segundos
            }
            break;
        case 3:
            if (file.peek() == ifstream::traits_type::eof()) { // Verificar si el archivo est� vac�o
                ShowConsoleCursor(false); // Oculta el cursor
                cout << MAGENTA_COLOR << DOUBLE_SPACE << "No hay ning�n cliente registrado." << endl;
                _sleep(1500); // Espera 1.5 segundos
                file.close();
                break;
            }
            system("cls");
            cout << CYAN_COLOR << "Buscar clientes: " << DOUBLE_SPACE << RESET_COLOR;
            {
                string searchTerm;
                cout << YELLOW_COLOR << "Ingrese el t�rmino de b�squeda (nombre o apellido): " << RESET_COLOR;
                cin >> searchTerm;
                gestionCliente.searchCustomers(searchTerm);
            }
            break;
        case 4:
            break;
        }
    } while (opcion != 4);
}

void sortProductsPrice() {
    
    GESTION_PRODUCTOS productManager;

    int opcion;
	string currentLanguage = "espanol"; // Idioma predeterminado

	do {
		system("cls");
		cout << CYAN_COLOR << "=== Ordenar Productos por Precio ===" << RESET_COLOR << DOUBLE_SPACE;
		cout << "<1> Ordenar de menor a mayor" << endl;
		cout << "<2> Ordenar de mayor a menor" << endl;
		cout << "<3> Volver";
        ShowConsoleCursor(true); // Muestra el cursor
		cout << DOUBLE_SPACE << YELLOW_COLOR << "Ingrese una opci�n: " << RESET_COLOR;
		cin >> opcion;

		// Verifica si la entrada fall�
		if (cin.fail()) { // Verifica si la entrada fall�
			cin.clear(); // Limpia el estado de cin
			cin.ignore((numeric_limits<streamsize>::max)(), '\n'); // Ignora la entrada incorrecta
			ShowConsoleCursor(false); // Oculta el cursor
			cout << DOUBLE_SPACE << MAGENTA_COLOR << "Entrada no v�lida, por favor ingrese un n�mero."; // Entrada no v�lida
			Sleep(1500); // Espera 1.5 segundos
			continue; // Contin�a al siguiente ciclo del bucle do-while
		}

		switch (opcion) {
		case 1:
			system("cls");
			productManager.ordenarProductosPorPrecioAscendente();
            ShowConsoleCursor(false); // Oculta el cursor
			cout << DOUBLE_SPACE << GRAY_COLOR << "Presiona cualquier tecla para continuar...";
			_getch();
			system("cls");
			break;
		case 2:
			system("cls");
			productManager.ordenarProductosPorPrecioDescendente();
            ShowConsoleCursor(false); // Oculta el cursor
			cout << DOUBLE_SPACE << GRAY_COLOR << "Presiona cualquier tecla para continuar...";
			_getch();
			system("cls");
			break;
		case 3:
            productManagementMenu();
			break;
		}
	} while (opcion != 3);

}

void promotionsManagementMenu() {

    GESTION_PROMOCIONES gestionPromociones;
    GESTION_PRODUCTOS gestionProductos;
    int opcion;

    do
    {
        system("cls");
        ShowConsoleCursor(true);
        cout << CYAN_COLOR << "=== GESTI�N DE PROMOCIONES ===" << DOUBLE_SPACE << RESET_COLOR;
        cout << "1. Agregar Promoci�n" << endl;
        cout << "2. Eliminar Promoci�n" << endl;
        cout << "3. Mostrar Promociones" << endl;
        cout << "4. Salir";
        cout << DOUBLE_SPACE << YELLOW_COLOR << "Seleccione una opci�n: " << RESET_COLOR;
        cin >> opcion;

        // Verifica si la entrada fall�
        if (cin.fail()) { // Verifica si la entrada fall�
            cin.clear(); // Limpia el estado de cin
            cin.ignore((numeric_limits<streamsize>::max)(), '\n'); // Ignora la entrada incorrecta
            ShowConsoleCursor(false); // Oculta el cursor
            cout << DOUBLE_SPACE << MAGENTA_COLOR << "Entrada no v�lida, por favor ingrese un n�mero."; // Entrada no v�lida
            Sleep(1500); // Espera 1.5 segundos
            continue; // Contin�a al siguiente ciclo del bucle do-while
        }

        switch (opcion)
        {
        case 1: {
            system("cls");
            string codigoProducto, descripcion;
            int descuento;

            cout << YELLOW_COLOR << "Ingrese el c�digo del producto para la promoci�n: " << RESET_COLOR;
            cin >> codigoProducto;

            while (true) {
                if (!gestionProductos.existeProducto(codigoProducto))
                {
                    cout << RED_COLOR << endl << "El c�digo " << codigoProducto << " no existe." << DOUBLE_SPACE;
                    cout << YELLOW_COLOR << "Ingrese nuevamente el c�digo: " << RESET_COLOR;
                    cin >> codigoProducto;
                }
				else
				{
					break;
				}
            }

            while (true) {
                cout << endl << YELLOW_COLOR << "Ingrese el porcentaje de descuento (sin el %): " << RESET_COLOR;
                cin >> descuento;

                // Verificar si la entrada es un n�mero entero
                if (cin.fail()) { // cin.fail() devuelve true si la entrada no es del tipo esperado (en este caso, un entero)
                    cin.clear(); // Limpiar el estado de error de cin
                    cin.ignore((numeric_limits<streamsize>::max)(), '\n'); // Ignora la entrada incorrecta
                    cout << endl << RED_COLOR << "Debe ingresar un n�mero entero. Int�ntelo de nuevo." << endl;
                }
                else {
                    break; // Salir del bucle si se ingres� un n�mero entero v�lido
                }
            }

            cout << endl << YELLOW_COLOR <<"Ingrese la descripci�n de la promoci�n: " << RESET_COLOR;
            cin.ignore();
            getline(cin, descripcion);

            gestionPromociones.agregarPromocion(PROMOCION(codigoProducto, descuento, descripcion));
            ShowConsoleCursor(false);
            cout << DOUBLE_SPACE << GREEN_COLOR << "Promoci�n agregada exitosamente." << endl;
            _sleep(1500);
            break;
        }
        case 2: {
            system("cls");
            string codigoProducto;
            cout << YELLOW_COLOR << "Ingrese el c�digo del producto para eliminar la promoci�n: " << RESET_COLOR;
            cin >> codigoProducto;

            while (true) {
                if (!gestionProductos.existeProducto(codigoProducto))
                {
                    cout << RED_COLOR << endl << "El c�digo " << codigoProducto << " no existe." << DOUBLE_SPACE;
                    cout << YELLOW_COLOR << "Ingrese nuevamente el c�digo: " << RESET_COLOR;
                    cin >> codigoProducto;
                }
                else
                {
                    break;
                }
            }

            gestionPromociones.eliminarPromocion(codigoProducto);
            ShowConsoleCursor(false);
            cout << GREEN_COLOR << endl << "Promoci�n eliminada exitosamente." << endl;
            _sleep(1500);
            break;
        }
        case 3:
            gestionPromociones.mostrarPromociones();
            break;
        case 4:
            break;
        }
    } while (opcion != 4);
}