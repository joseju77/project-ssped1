#ifndef CIVILIZACIONES_H
#define CIVILIZACIONES_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "civilizacion.h"
#include <iostream>

using namespace std;

struct nodo_doble
{
    Civilizacion *dato;
    struct nodo_doble *siguiente;
    struct nodo_doble *anterior;
};

typedef struct nodo_doble NodoDoble;

NodoDoble *NodoDobleInit(Civilizacion *dato)
{
    NodoDoble *nodo = (NodoDoble*)malloc(sizeof(NodoDoble));

    if (!nodo) {
        cout << "Error al reservar memoria para el nodo doble" << endl;
        return NULL;
    }

    nodo->dato = dato;
    nodo->siguiente = NULL;
    nodo->anterior = NULL;
    
    return nodo;
}

struct listaligadadoble
{
    NodoDoble *inicio;
    NodoDoble *final;
    size_t cantidad;
};

typedef struct listaligadadoble ListaLigadaDoble;

ListaLigadaDoble *ListaLigadaDobleInit()
{
    ListaLigadaDoble *listaLigadaDoble = (ListaLigadaDoble*)malloc(sizeof(ListaLigadaDoble));

    if (!listaLigadaDoble) {
        cout << "Error al reservar memoria para la lista ligada doble" << endl;
        return NULL;
    }
    
    listaLigadaDoble->inicio = NULL;
    listaLigadaDoble->final = NULL;
    listaLigadaDoble->cantidad = 0;

    return listaLigadaDoble;
}

bool ListaLigadaDobleVacia(ListaLigadaDoble *listaLigadaDoble)
{
    if (!listaLigadaDoble) {
        cout << "Lista ligada doble sin memoria" << endl;
        exit(1);
    }

    return listaLigadaDoble->cantidad == 0;
}

bool ListaLigadaDobleInsertarInicio(ListaLigadaDoble *listaLigadaDoble, Civilizacion *dato)
{
    if (!listaLigadaDoble) {
        cout << "Lista ligada doble sin memoria" << endl;
        return false;
    }

    NodoDoble *nuevo = NodoDobleInit(dato);

    if (ListaLigadaDobleVacia(listaLigadaDoble)) {
        listaLigadaDoble->inicio = nuevo;
        listaLigadaDoble->final = nuevo;
        listaLigadaDoble->cantidad++;
        return true;
    }
    
    nuevo->siguiente = listaLigadaDoble->inicio;
    listaLigadaDoble->inicio->anterior = nuevo;
    listaLigadaDoble->inicio = nuevo;
    listaLigadaDoble->cantidad++;
    return true;
}

bool ListaLigadaDobleInsertarFinal(ListaLigadaDoble *listaLigadaDoble, Civilizacion *dato)
{
    if (!listaLigadaDoble) {
        cout << "Lista ligada doble sin memoria" << endl;
        return false;
    }

    NodoDoble *nuevo = NodoDobleInit(dato);

    if (ListaLigadaDobleVacia(listaLigadaDoble)) {
        listaLigadaDoble->inicio = nuevo;
        listaLigadaDoble->final = nuevo;
        listaLigadaDoble->cantidad++;
        return true;
    }

    nuevo->anterior = listaLigadaDoble->final;
    listaLigadaDoble->final->siguiente = nuevo;
    listaLigadaDoble->final = nuevo;
    listaLigadaDoble->cantidad++;

    return true;
}

bool ListaLigadaDobleMostrar(ListaLigadaDoble *listaLigadaDoble)
{
    if (!listaLigadaDoble) {
        cout << "Lista ligada doble sin memoria" << endl;
        return false;
    } else if (ListaLigadaDobleVacia(listaLigadaDoble)) {
        cout << "Lista ligada doble vacia" << endl;
        return false;
    }

    cout << "Capacidad: " << listaLigadaDoble->cantidad << endl;
    NodoDoble *tmp = listaLigadaDoble->inicio;

    while (tmp) {
        if (civilizacionMostrar(tmp->dato)) {
            cout << "Se mostro civilizacion" << endl;
        } else {
            cout << "Error al mostrar civilizacion" << endl;
        }
        tmp = tmp->siguiente;
        cout << "" << endl;
    }

    return true;
}

bool ListaLigadaDobleEliminarInicio(ListaLigadaDoble *listaLigadaDoble)
{
    if (!listaLigadaDoble) {
        cout << "Lista ligada doble sin memoria" << endl;
        return false;
    } else if (ListaLigadaDobleVacia(listaLigadaDoble)) {
        cout << "Lista ligada doble vacia" << endl;
        return false;
    }

    NodoDoble *tmp = listaLigadaDoble->inicio;

    listaLigadaDoble->inicio = tmp->siguiente;
    listaLigadaDoble->cantidad--;

    if (ListaLigadaDobleVacia(listaLigadaDoble)) {
        listaLigadaDoble->final = NULL;
    } else {
        listaLigadaDoble->inicio->anterior = NULL;
    }

    civilizacionFree(tmp->dato);
    free(tmp);
    tmp = NULL;

    return true;
}

bool ListaLigadaDobleEliminarFinal(ListaLigadaDoble *listaLigadaDoble)
{
    if (!listaLigadaDoble) {
        cout << "Lista ligada doble sin memoria" << endl;
        return false;
    } else if (ListaLigadaDobleVacia(listaLigadaDoble)) {
        cout << "Lista ligada doble vacia" << endl;
        return false;
    }

    NodoDoble *tmp = listaLigadaDoble->final;

    listaLigadaDoble->final = tmp->anterior;
    listaLigadaDoble->final->siguiente = NULL;
    listaLigadaDoble->cantidad--;

    civilizacionFree(tmp->dato);
    free(tmp);
    tmp = NULL;

    if (ListaLigadaDobleVacia(listaLigadaDoble)) {
        listaLigadaDoble->final = NULL;
        listaLigadaDoble->inicio = NULL;
    }

    return true;
}

ListaLigadaDoble *ListaLigadaDobleFree(ListaLigadaDoble *listaLigadaDoble)
{
    if (!listaLigadaDoble) {
        cout << "Lista ligada doble sin memoria" << endl;
        return NULL;
    }

    while (!ListaLigadaDobleVacia(listaLigadaDoble)) {
        ListaLigadaDobleEliminarInicio(listaLigadaDoble);
    }

    free(listaLigadaDoble);
    listaLigadaDoble = NULL;

    return listaLigadaDoble;
}

typedef ListaLigadaDoble Civilizaciones;

#define civilizacionesInit ListaLigadaDobleInit
#define civilizacionesFree ListaLigadaDobleFree
#define civilizacionesInsertarInicio ListaLigadaDobleInsertarInicio
#define civilizacionesInsertarFinal ListaLigadaDobleInsertarFinal
#define civilizacionesMostrar ListaLigadaDobleMostrar
#define civilizacionesEliminarInicio ListaLigadaDobleEliminarInicio
#define civilizacionesEliminarFinal ListaLigadaDobleEliminarFinal

Civilizacion *civilizacionesBuscar(Civilizaciones *civilizaciones, char *nombre)
{
    if (!civilizaciones) {
        cout << "Civilizaciones sin memoria" << endl;
        return NULL;
    }

    NodoDoble *tmp = civilizaciones->inicio;

    while (tmp) {
        if (strcmp(nombre, tmp->dato->nombre) == 0) {
            return tmp->dato;
        }
        tmp = tmp->siguiente;
    }

    return NULL;
}

#endif