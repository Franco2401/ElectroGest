#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <conio.h>
#include "client_class.h"

class GESTION_CLIENTE {
public:

    // M�todo para registrar un nuevo cliente
    void displayCustomerList() {
        ifstream file("client_registration.txt");
        if (file.is_open()) {
            string line;

            // Imprimir encabezados de la tabla
            cout << CYAN_COLOR
                << left << setw(15) << "ID Cliente"
                << left << setw(15) << "Nombre"
                << setw(20) << "Apellido"
                << setw(35) << "Correo"
                << setw(20) << "Direcci�n"
                << setw(15) << "Tel�fono"
                << setw(25) << "Fecha de Nacimiento"
                << setw(10) << "G�nero"
                << RESET_COLOR << endl;

            // Imprimir separador de columnas
            cout << YELLOW_COLOR
                << setw(15) << setfill('-') << ""
                << setw(15) << ""
                << setw(20) << ""
                << setw(35) << ""
                << setw(20) << ""
                << setw(15) << ""
                << setw(25) << ""
                << setw(10) << ""
                << setfill(' ') << RESET_COLOR << endl;

            while (getline(file, line)) {
                istringstream iss(line);
                string idCliente, nombre, apellido, correo, contrasenia, direccion, telefono, fechaNacimiento, genero;

                // Leer los campos separados por coma
                getline(iss, idCliente, ',');
                getline(iss, nombre, ',');
                getline(iss, apellido, ',');
                getline(iss, correo, ',');
                getline(iss, contrasenia, ',');
                getline(iss, direccion, ',');
                getline(iss, telefono, ',');
                getline(iss, fechaNacimiento, ',');
                getline(iss, genero, ',');

                // Mostrar la informaci�n del cliente en una sola l�nea
                cout << left
                    << setw(15) << idCliente
                    << setw(15) << nombre
                    << setw(20) << apellido
                    << setw(35) << correo
                    << setw(20) << direccion
                    << setw(15) << telefono
                    << setw(25) << fechaNacimiento
                    << setw(10) << genero << DOUBLE_SPACE;

            }
            file.close();
            ShowConsoleCursor(false);
            cout << GRAY_COLOR << "\nPresiona cualquier tecla para continuar..." << RESET_COLOR;
            _getch();
        }
        else {
            cout << DOUBLE_SPACE << MAGENTA_COLOR << "No se pudo abrir el archivo de registro de clientes." << endl;
            Sleep(1500);
        }
    }

    // M�todo para eliminar un nuevo cliente
    void deleteCustomer(string email) {
        vector<string> lines;
        bool found = false; // Variable para rastrear si se encuentra el cliente
        ifstream file("client_registration.txt");
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                if (line.find(email) == string::npos) { // Si la l�nea no contiene el correo electr�nico del cliente a eliminar
                    lines.push_back(line); // Conservar la l�nea
                }
                else {
                    found = true; // Se encontr� el cliente
                    cout << DOUBLE_SPACE << GREEN_COLOR << "Cliente eliminado correctamente." << endl;
                }
            }
            file.close();
        }
        else {
            cout << DOUBLE_SPACE << MAGENTA_COLOR << "No se pudo abrir el archivo de registro de clientes." << endl;
            return;
        }

        // Escribir las l�neas restantes en el archivo
        ofstream outFile("client_registration.txt");
        for (const string& line : lines) {
            outFile << line << endl;
        }
        outFile.close();

        // Si el cliente no se encontr�, imprimir un mensaje
        if (!found) {
            ShowConsoleCursor(false);
            cout << DOUBLE_SPACE << MAGENTA_COLOR << "El cliente con el correo electr�nico " << email << " no se encontr� en el archivo." << endl;
            _sleep(1500); // Esperar 1.5 segundos
        }
    }

    // M�todo para buscar clientes por nombre
    void searchCustomers(const string& searchTerm) {
        ifstream file("client_registration.txt");
        if (file.is_open()) {

            string line;
            bool found = false;
            while (getline(file, line)) {
                istringstream iss(line);
                string nombre, apellido, correo, direccion, telefono, fechaNacimiento, genero;

                // Leer los campos separados por coma
                getline(iss, nombre, ',');
                getline(iss, apellido, ',');
                getline(iss, correo, ',');
                getline(iss, direccion, ',');
                getline(iss, telefono, ',');
                getline(iss, fechaNacimiento, ',');
                getline(iss, genero, ',');

                if (nombre.find(searchTerm) != string::npos || apellido.find(searchTerm) != string::npos) {
                    cout << CYAN_COLOR << DOUBLE_SPACE << "Cliente encontrado:" << RESET_COLOR << endl;
                    cout << BLUE_COLOR << "Nombres: " << RESET_COLOR << nombre << " " << apellido << endl;
                    cout << BLUE_COLOR << "Correo: " << RESET_COLOR << correo << endl;
                    cout << BLUE_COLOR << "Direcci�n: " << RESET_COLOR << direccion << endl;
                    cout << BLUE_COLOR << "Tel�fono: " << RESET_COLOR << telefono << endl;
                    cout << BLUE_COLOR << "Fecha de nacimiento: " << RESET_COLOR << fechaNacimiento << endl;
                    cout << BLUE_COLOR << "G�nero: " << RESET_COLOR << genero << endl;
                    found = true;
                }
            }

            file.close();
            if (!found) {
                ShowConsoleCursor(false);
                cout << MAGENTA_COLOR << DOUBLE_SPACE << "No se encontraron clientes con el nombre proporcionado." << endl;
                _sleep(1500); // Esperar 1.5 segundos
            }
            else {
                ShowConsoleCursor(false);
				cout << DOUBLE_SPACE << GRAY_COLOR << "Presiona cualquier tecla para continuar...";
				_getch();
			
            }
        }
        else {
            cout << DOUBLE_SPACE << MAGENTA_COLOR << "No se pudo abrir el archivo de registro de clientes." << endl;
        }
    }

    bool numeroExistente(const string& telefono) {
        ifstream file("client_registration.txt");
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                size_t pos = line.find(telefono);
                if (pos != string::npos) {
                    return true; // Si el n�mero ya existe en el archivo
                }
            }
            file.close();
        }
        return false; // Si el n�mero no existe en el archivo
    }

};