#ifndef MENU_CIVILIZACIONES_H
#define MENU_CIVILIZACIONES_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

#include "civilizaciones.h"
#include "menu_aldeanos.h"

enum OPCIONES {
    INICIAR,
    LIBERAR,
    INSERTAR_INICIO, INSERTAR_FINAL,
    ELIMINAR_INICIO_C, ELIMINAR_FINAL_C,
    MOSTRAR_C, BUSCAR,
    EXIT_C
};


void menuCivilizaciones(Civilizaciones *civilizaciones) 
{
    int opt;
    Civilizacion *civilizacion;
    size_t posicion;

    do
    {
        system("CLS");
        cout << "Lista de Civilizaciones" << endl << INICIAR << ") Iniciar" << endl
            << LIBERAR << ") Liberar" << endl
            << INSERTAR_INICIO << ") Agregar al inicio" << endl
            << INSERTAR_FINAL << ") Agregar al final" << endl
            << ELIMINAR_INICIO_C << ") Eliminar al inicio" << endl
            << ELIMINAR_FINAL_C << ") Eliminar al final" << endl
            << MOSTRAR_C << ") Mostrar" << endl
            << BUSCAR << ") Buscar" << endl
            << EXIT_C << ") Salir" << endl << "Opcion: ";
        cin >> opt;
        cin.ignore();
        switch (opt)
        {
            case INIT:
                civilizaciones = civilizacionesInit();
                if (civilizaciones) {
                    cout << "Se inicio la lista de civilizaciones" << endl;
                } else {
                    cout << "Error al iniciar la lista de aldeanos" << endl;
                }
                break;
            case FREE:
                civilizaciones = civilizacionesFree(civilizaciones);
                if (!civilizaciones) {
                    cout << "Se libero la lista de civilizaciones"<< endl;
                } else {
                    cout << "Error al liberar la lista de civilizaciones"<< endl;
                }
                break;
            case INSERTAR_INICIO:
                civilizacion = civilizacionCapturar();
                if (civilizacion) {
                    if(civilizacionesInsertarInicio(civilizaciones, civilizacion)) {
                        cout << "Se agrego la civilizacion al inicio" << endl;
                        break;
                    }
                }
                cout << "Hubo un error al agregar la civilizacion" << endl;
                break;
            case INSERTAR_FINAL:
                civilizacion = civilizacionCapturar();
                if (civilizacion) {
                    if(civilizacionesInsertarFinal(civilizaciones, civilizacion)) {
                        cout << "Se agrego la civilizacion al final" << endl;
                        break;
                    }
                }
                cout << "Hubo un error al agregar la civilizacion" << endl;
                break;
            case ELIMINAR_INICIO_C:
                if(civilizacionesEliminarInicio(civilizaciones)) {
                    cout << "Se elimino la primera civilizacion" << endl;
                } else {
                    cout << "Hubo un error al eliminar la primera civilizacion" << endl;
                }
                break;
            case ELIMINAR_FINAL_C:
                if(civilizacionesEliminarInicio(civilizaciones)) {
                    cout << "Se elimino la ultima civilizacion" << endl;
                } else {
                    cout << "Hubo un error al eliminar la ultima civilizacion" << endl;
                }
                break;
            case MOSTRAR_C:
                if(!civilizacionesMostrar(civilizaciones)) {
                    cout << "Lista de civilizaciones vacia" << endl;
                }
                break;
            case BUSCAR: {
                char *nombre = readChar("Nombre de la civilizacion: ");
                civilizacion = civilizacionesBuscar(civilizaciones, nombre);
                if(civilizacion) {
                    menuAldeanos(civilizacion->aldeanosLista, nombre);
                    break;
                }
                cout << "No se encontro la civilizacion" << endl;
                break;
                }
            default:
                break;
        }
        cout << endl << "<<Enter>>";
        cin.get();
    } while (opt != EXIT_C);
    
}

#endif