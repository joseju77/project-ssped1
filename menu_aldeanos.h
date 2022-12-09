#ifndef MENU_ALDEANOS_H
#define MENU_ALDEANOS_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

#include "lista_aldeanos.h"
#include "aldeano.h"

enum OPTIONS {
    INIT,
    FREE,
    AGREGAR_INICIO, AGREGAR_FINAL, AGREGAR,
    ELIMINAR_INICIO, ELIMINAR_FINAL, ELIMINAR,
    MOSTRAR, MOSTRAR_TABLA,
    EXIT
};


void menuAldeanos(AldeanosLista *aldeanosLista) 
{
    int opt;
    Aldeano *aldeano;
    size_t posicion;

    do
    {
        system("CLS");
        cout << "Lista de Aldeanos" << endl << INIT << ") Iniciar" << endl
            << FREE << ") Liberar" << endl
            << AGREGAR_INICIO << ") Agregar al inicio" << endl
            << AGREGAR_FINAL << ") Agregar al final" << endl
            << AGREGAR << ") Agregar en alguna posicion" << endl
            << ELIMINAR_INICIO << ") Eliminar al inicio" << endl
            << ELIMINAR_FINAL << ") Eliminar al final" << endl
            << ELIMINAR << ") Eliminar en alguna posicion" << endl
            << MOSTRAR << ") Mostrar" << endl
            << MOSTRAR_TABLA << ") Mostrar Tabla" << endl
            << EXIT << ") Salir" << endl << "Opcion: ";
        cin >> opt;
        cin.ignore();
        switch (opt)
        {
            case INIT:
                aldeanosLista = aldeanosListaInit();
                if (aldeanosLista) {
                    cout << "Se inicio la lista de aldeanos" << endl;
                } else {
                    cout << "Error al iniciar la lista de aldeanos" << endl;
                }
                break;
            case FREE:
                aldeanosLista = aldeanosListaFree(aldeanosLista);
                if (!aldeanosLista) {
                    cout << "Se libero la lista de aldeanos"<< endl;
                } else {
                    cout << "Error al liberar la lista de aldeanos"<< endl;
                }
                break;
            case AGREGAR_INICIO:
                aldeano = aldeanoCapturar();
                cin.ignore();
                if (aldeano) {
                    if(aldeanosListaAgregarInicio(aldeanosLista, aldeano)) {
                        cout << "Se agrego el aldeano al inicio" << endl;
                        break;
                    }
                }
                cout << "Hubo un error al agregar el aldeano" << endl;
                break;
            case AGREGAR_FINAL:
                aldeano = aldeanoCapturar();
                cin.ignore();
                if (aldeano) {
                    if(aldeanosListaAgregarFinal(aldeanosLista, aldeano)) {
                        cout << "Se agrego el aldeano al final" << endl;
                        break;
                    }
                }
                cout << "Hubo un error al agregar el aldeano" << endl;
                break;
            case AGREGAR:
                cout << "Posicion: ";
                cin >> posicion;
                cin.ignore();
                aldeano = aldeanoCapturar();
                cin.ignore();
                if (aldeano) {
                    if(aldeanosListaAgregar(aldeanosLista, aldeano, posicion)) {
                        cout << "Se agrego el aldeano en la posicion: " << posicion << endl;
                        break;
                    }
                }
                cout << "Hubo un error al agregar el aldeano" << endl;
                break;
            case ELIMINAR_INICIO:
                if(aldeanosListaEliminarInicio(aldeanosLista)) {
                    cout << "Se elimino el primer aldeano" << endl;
                } else {
                    cout << "Hubo un error al eliminar el aldeano" << endl;
                }
                break;
            case ELIMINAR_FINAL:
                if(aldeanosListaEliminarFinal(aldeanosLista)) {
                    cout << "Se elimino el ultimo aldeano" << endl;
                } else {
                    cout << "Hubo un error al eliminar el aldeano" << endl;
                }
                break;
            case ELIMINAR:
                cout << "Posicion: ";
                cin >> posicion;
                cin.ignore();
                if(aldeanosListaEliminar(aldeanosLista, posicion)) {
                    cout << "Se elimino el aldeano de la posicion: " << posicion << endl;
                } else {
                    cout << "Hubo un error al eliminar al aldeano" << endl;
                }
                break;
            case MOSTRAR:
                if(!aldeanosListaMostrar(aldeanosLista)) {
                    cout << "Lista de aldeanos vacia" << endl;
                }
                break;
            case MOSTRAR_TABLA:
                if(!aldeanosListaMostrarTabla(aldeanosLista)) {
                    cout << "Lista de aldeanos vacia" << endl;
                }
                break;
            default:
                break;
        }
        cout << endl << "<<Enter>>";
        cin.get();
    } while (opt != EXIT);
    
}

#endif