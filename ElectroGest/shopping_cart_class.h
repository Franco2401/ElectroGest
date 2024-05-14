#pragma once
#include "order_class.h"
#include <vector>
#include <conio.h>

class CARRO_COMPRAS {
private:
    std::vector<PEDIDO> pedidos;

public:
    // Agregar un pedido al carrito
    void agregarPedido(const PEDIDO& pedido) {
        pedidos.push_back(pedido);
    }

    // Ver el contenido del carrito
    void verCarrito() const {
        if (pedidos.empty()) {
            ShowConsoleCursor(false);
            std::cout << endl << MAGENTA_COLOR << "El carrito est� vac�o.";
            Sleep(1500);
        }
        else {
            system("cls");
            std::cout << CYAN_COLOR << "=== Carrito de Compras ===" << DOUBLE_SPACE;
            for (const auto& pedido : pedidos) {
                std::cout << BLUE_COLOR << "C�digo: " << RESET_COLOR << pedido.getCodigoProducto() << BLUE_COLOR << ", Cantidad: " << RESET_COLOR <<pedido.getCantidad() << "\n";
            }
            ShowConsoleCursor(false);
            cout << DOUBLE_SPACE << GRAY_COLOR << "Presione cualquier tecla para continuar...";      
            _getch();
        }
    }

    // M�todo para limpiar el carrito
    void limpiarCarrito() {
        pedidos.clear();
    }

    // M�todo para verificar si el carrito est� vac�o
    bool isEmpty() const {
        return pedidos.empty();
    }

    // M�todo para obtener los pedidos del carrito
    const std::vector<PEDIDO>& getPedidos() const {
        return pedidos;
    }
};