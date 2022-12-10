#ifndef MENU_ALDEANOS_H
#define MENU_ALDEANOS_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

#include "lista_aldeanos.h"
#include "aldeano.h"
#include "barcos.h"

enum OPTIONS {
    INIT,
    FREE,
    AGREGAR_INICIO, AGREGAR_FINAL, AGREGAR,
    ELIMINAR_INICIO, ELIMINAR_FINAL, ELIMINAR,
    MOSTRAR, MOSTRAR_TABLA, PUERTO,
    AGREGAR_BARCO_INICIO, AGREGAR_BARCO_FIN, ELIMINAR_BARCO_INICIO, ELIMINAR_BARCO_FIN, MOSTRAR_BARCOS, BUSCAR_BARCOS,
    AGREGAR_GUERRERO, ELIMINAR_GUERRERO, MOSTRAR_ULTIMO_GUERRERO, MOSTRAR_GUERREROS,
    BATALLA, BATALLA_AGREGAR_INICIO, BATALLA_AGREGAR_FINAL, BATALLA_SACAR_BARCO, BATALLA_MOSTRAR,
    EXIT
};


void menuPuerto(Puerto *puerto, char *nombreCivi);

void menuBarco(Barco *barco, int id);

void menuBatalla(Batalla *barco, Puerto *puerto);

void menuAldeanos(AldeanosLista *aldeanosLista, char *nombreCivi, Puerto *puerto, Batalla *batalla) 
{
    int opt;
    Aldeano *aldeano;
    size_t posicion;
    do
    {
        system("CLS");
        cout << "Lista de Aldeanos (" << nombreCivi << ")" << endl << INIT << ") Iniciar" << endl
            << FREE << ") Liberar" << endl
            << AGREGAR_INICIO << ") Agregar al inicio" << endl
            << AGREGAR_FINAL << ") Agregar al final" << endl
            << AGREGAR << ") Agregar en alguna posicion" << endl
            << ELIMINAR_INICIO << ") Eliminar al inicio" << endl
            << ELIMINAR_FINAL << ") Eliminar al final" << endl
            << ELIMINAR << ") Eliminar en alguna posicion" << endl
            << MOSTRAR << ") Mostrar" << endl
            << MOSTRAR_TABLA << ") Mostrar Tabla" << endl
            << PUERTO << ") Puerto" << endl
            << BATALLA << ") Batalla" << endl
            << EXIT << ") Regresar" << endl << "Opcion: ";
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
            case PUERTO:
                menuPuerto(puerto, nombreCivi);
                break;
            case BATALLA:
                menuBatalla(batalla, puerto);
                break;
            default:
                break;
        }
        if (opt != EXIT) {
            cout << endl << "<<Enter>>";
            cin.get();
        }
    } while (opt != EXIT);
}

void menuBatalla(Batalla *batalla, Puerto *puerto)
{
    int opt;
    Barco *barco;
    do
    {
        system("CLS");
        cout << "Batalla " << endl
            << BATALLA_AGREGAR_INICIO << ") Agregar barco del inicio" << endl
            << BATALLA_AGREGAR_FINAL << ") Agregar barco del final" << endl
            << BATALLA_SACAR_BARCO << ") Sacar barco de la batalla" << endl
            << BATALLA_MOSTRAR << ") Mostrar barcos en batalla" << endl
            << EXIT << ") Regresar" << endl << "Opcion: ";
        cin >> opt;
        cin.ignore();
        switch (opt)
        {
            case BATALLA_AGREGAR_INICIO:
                if (puertoVacia(puerto)) {
                    cout << "Puerto vacio" << endl;
                    break;
                }
                barco = puerto->inicio;
                if (barco->combustible > 0.0) {
                    barco->velocidad = readFloat("Nueva velocidad: ");
                    cin.ignore();
                    puertoEliminarInicio(puerto, 1);
                    batallaEncolar(batalla, barco);
                    cout << "Barco agregado a la batalla" << endl;
                    break;
                }
                cout << "Barco sin combustible, no se agrego a la batalla" << endl;
                break;
            case BATALLA_AGREGAR_FINAL:
                if (puertoVacia(puerto)) {
                    cout << "Puerto vacio" << endl;
                    break;
                }
                barco = puerto->final;
                if (barco->combustible > 0.0) {
                    barco->velocidad = readFloat("Nueva velocidad: ");
                    cin.ignore();
                    puertoEliminarFinal(puerto, 1);
                    batallaEncolar(batalla, barco);
                    cout << "Barco agregado a la batalla" << endl;
                    break;
                }
                cout << "Barco sin combustible, no se agrego a la batalla" << endl;
                break;
            case BATALLA_SACAR_BARCO:
                barco = batallaTomar(batalla);
                int destino;
                barco->velocidad = 0.0;
                barco->armadura = readFloat("Nueva armadura: ");
                barco->combustible = readFloat("Nuevo combustible: ");
                if (barco->armadura != 0.0) {
                    do
                    {
                        cout << "Donde se insertara el barco" << endl << "1) Inicio del puerto" << endl << "2) Fin del puerto" << endl << "Opcion: ";
                        cin >> destino;
                        cin.ignore();
                        if (destino == 1) {
                            batallaDesencolar(batalla);
                            puertoInsertarInicio(puerto, barco);
                            break;
                        }
                        else if (destino == 2) {
                            batallaDesencolar(batalla);
                            puertoInsertarFinal(puerto, barco);
                            break;
                        }
                        else {
                            cout << "Opcion invalida" << endl << "<<ENTER>>";
                            cin.get();
                        }
                    } while (destino != 1 || destino != 2);
                    cout << "Barco insertado en el puerto" << endl;
                    cin.ignore();
                } else {
                    cin.ignore();
                    batallaDesencolar(batalla);
                    barcoFree(barco);
                    barco = NULL;
                    cout << "El barco fue destruido, no se inserto en el puerto" << endl;
                }
                break;
            case BATALLA_MOSTRAR:
                batallaMostrar(batalla);
                break;
            default:
                break;
        }
        if (opt != EXIT) {
            cout << endl << "<<Enter>>";
            cin.get();
        }
    } while (opt != EXIT);
}

void menuBarco(PilaGuerreros *pilaGuerreros, int id)
{
    int opt;
    Guerrero *guerrero;
    do
    {
        system("CLS");
        cout << "Lista de Guerreros (Barco - " << id << ")" << endl
            << AGREGAR_GUERRERO << ") Agregar guerrero" << endl
            << ELIMINAR_GUERRERO << ") Eliminar guerrero" << endl
            << MOSTRAR_ULTIMO_GUERRERO << ") Mostrar ultimo guerrero" << endl
            << MOSTRAR_GUERREROS << ") Mostrar guerreros" << endl
            << EXIT << ") Regresa" << endl << "Opcion: ";
        cin >> opt;
        cin.ignore();
        switch (opt)
        {
            case AGREGAR_GUERRERO:
                guerrero = guerreroCapturar();
                if(pilaGuerrerosApilar(pilaGuerreros, guerrero)) {
                    cout << "Se agrego el guerrero" << endl;
                    break;
                }
                cout << "Hubo un error al agregar el guerrero" << endl;
                cin.get();
                break;
            case ELIMINAR_GUERRERO:
                if(pilaGuerrerosDesapilar(pilaGuerreros)) {
                    cout << "Se elimino el guerrero" << endl;
                    break;
                }
                cout << "Hubo un error al eliminar el guerrero" << endl;
                break;
            case MOSTRAR_ULTIMO_GUERRERO:
                if(!pilaGuerrerosTope(pilaGuerreros)) {
                    cout << "Pila de guerreros vacia" << endl;
                    break;
                }
                break;
            case MOSTRAR_GUERREROS:
                if(!pilaGuerrerosMostrar(pilaGuerreros)) {
                    cout << "Pila de guerreros vacia" << endl;
                    break;
                }
                break;
            default:
                break;
        }
        if (opt != EXIT) {
            cout << endl << "<<Enter>>";
            cin.get();
        }
    } while (opt != EXIT);
}

void menuPuerto(Puerto *puerto, char *nombreCivi)
{
    int opt;
    Barco *barco;
    do
    {
        system("CLS");
        cout << "Lista de Barcos (" << nombreCivi << ")" << endl
            << AGREGAR_BARCO_INICIO << ") Agregar al inicio" << endl
            << AGREGAR_BARCO_FIN << ") Agregar al final" << endl
            << ELIMINAR_BARCO_INICIO << ") Eliminar al inicio" << endl
            << ELIMINAR_BARCO_FIN << ") Eliminar al final" << endl
            << MOSTRAR_BARCOS << ") Mostrar" << endl
            << BUSCAR_BARCOS << ") Buscar" << endl
            << EXIT << ") Regresar" << endl << "Opcion: ";
        cin >> opt;
        cin.ignore();
        switch (opt)
        {
            case AGREGAR_BARCO_INICIO:
                barco = barcoCapturar();
                cin.ignore();
                if(puertoInsertarInicio(puerto, barco)) {
                    cout << "Se agrego el barco al inicio" << endl;
                    break;
                }
                cout << "Hubo un error al agregar el barco" << endl;
                break;
            case AGREGAR_BARCO_FIN:
                barco = barcoCapturar();
                cin.ignore();
                if(puertoInsertarFinal(puerto, barco)) {
                    cout << "Se agrego el barco al final" << endl;
                    break;
                }
                cout << "Hubo un error al agregar el barco" << endl;
                break;
            case ELIMINAR_BARCO_INICIO:
                if(puertoEliminarInicio(puerto)) {
                    cout << "Se elimino el primer barco" << endl;
                    break;
                }
                cout << "Hubo un error al eliminar el barco" << endl;
                break;
            case ELIMINAR_BARCO_FIN:
                if(puertoEliminarFinal(puerto)) {
                    cout << "Se elimino el ultimo barco" << endl;
                    break;
                }
                cout << "Hubo un error al eliminar el ultimo barco" << endl;
                break;
            case MOSTRAR_BARCOS:
                if(!puertoMostrar(puerto)) {
                    cout << "Lista de barcos vacia" << endl;
                }
                break;
            case BUSCAR_BARCOS: {
                int id = readInt("Id del barco: ");
                barco = puertoBuscar(puerto, id);
                cin.ignore();
                if(barco) {
                    menuBarco(barco->guerreros, id);
                    break;
                }
                cout << "No se encontro el barco" << endl;
                break;
                }
            default:
                break;
        }
        if (opt != EXIT) {
            cout << endl << "<<Enter>>";
            cin.get();
        }
    } while (opt != EXIT);
}



#endif