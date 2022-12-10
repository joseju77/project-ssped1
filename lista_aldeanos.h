#ifndef LISTA_ALDEANOS_H
#define LISTA_ALDEANOS_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "aldeano.h"

#define CAPACIDAD 3

struct lista_aldeanos
{
    Aldeano **aldeanos;
    size_t cantidad;
    size_t capacidad;
};

typedef struct lista_aldeanos AldeanosLista;

AldeanosLista *aldeanosListaInit()
{
    AldeanosLista *aldeanosLista = (AldeanosLista*)malloc(sizeof(AldeanosLista));
    if (aldeanosLista)
    {
        aldeanosLista->aldeanos = (Aldeano**)malloc(sizeof(Aldeano*) * CAPACIDAD);
        aldeanosLista->cantidad = 0;
        aldeanosLista->capacidad = CAPACIDAD;
    }
    return aldeanosLista;
}

AldeanosLista *aldeanosListaFree(AldeanosLista *aldeanosLista)
{
    if (aldeanosLista) {
        if (aldeanosLista->aldeanos) {
            for (size_t i = 0; i < aldeanosLista->cantidad; i++) {
                free(aldeanosLista->aldeanos[i]);
            }
            free(aldeanosLista->aldeanos);
            aldeanosLista->aldeanos = NULL;
            free(aldeanosLista);
            aldeanosLista = NULL;
        }
    }
    return aldeanosLista;
}

bool aldeanosListaMostrar(AldeanosLista *aldeanosLista)
{
    if (aldeanosLista) {
        cout << "Cantidad: " << aldeanosLista->cantidad << " | Capacidad: " << aldeanosLista->capacidad << endl;
        for (size_t i = 0; i < aldeanosLista->cantidad; i++) {
            aldeanoMostrar(aldeanosLista->aldeanos[i]);

        }
        return true;
    }
    return false;
}

bool aldeanosListaMostrarTabla(AldeanosLista *aldeanosLista)
{
    if (aldeanosLista) {
        cout << "Cantidad: " << aldeanosLista->cantidad << " | Capacidad: " << aldeanosLista->capacidad << endl;
        printf("|%-20s|%-4s|%-5s|\n", "Nombre", "Edad", "Salud");
        for (size_t i = 0; i < aldeanosLista->cantidad; i++) {
            aldeanoMostrarFila(aldeanosLista->aldeanos[i]);
        }
        return true;
    }
    return false;
}

bool aldeanosListaLlena(AldeanosLista *aldeanosLista)
{
    if (!aldeanosLista) {
        cout << "No existe aldeanosLista" << endl;
        exit(1);
    }
    return aldeanosLista->cantidad == aldeanosLista->capacidad;
}

bool aldeanosListaExpandir(AldeanosLista *aldeanosLista)
{
    if (aldeanosLista)
    {
        size_t nuevaCapacidad = aldeanosLista->cantidad + CAPACIDAD;
        Aldeano **temp = (Aldeano**)realloc(aldeanosLista->aldeanos, sizeof(Aldeano*) * nuevaCapacidad);
        if (temp) {
            cout << "Lista de aldeanos expandida" << endl;
            aldeanosLista->aldeanos = temp;
            aldeanosLista->capacidad = nuevaCapacidad;
            return true;
        }
    }
    return false;
}

bool aldeanosListaAgregarFinal(AldeanosLista *aldeanosLista, Aldeano *aldeano)
{
    if (aldeanosLista) {
        if (aldeanosListaLlena(aldeanosLista)) {
            aldeanosListaExpandir(aldeanosLista);
        }
        aldeanosLista->aldeanos[aldeanosLista->cantidad] = aldeano;
        aldeanosLista->cantidad++;
        return true;
    }
    return false;
}

bool aldeanosListaVacia(AldeanosLista *aldeanosLista)
{
    if (!aldeanosLista) {
        cout << "Lista de Aldeanos vacia" << endl;
        exit(1);
    }
    return aldeanosLista->cantidad == 0;
}

bool aldeanosListaEliminarFinal(AldeanosLista *aldeanosLista)
{
    if (aldeanosLista) {
        if (!aldeanosListaVacia(aldeanosLista)) {
            aldeanosLista->aldeanos[aldeanosLista->cantidad - 1] = aldeanoFree(aldeanosLista->aldeanos[aldeanosLista->cantidad - 1]);
            if (!aldeanosLista->aldeanos[aldeanosLista->cantidad - 1]) {
                aldeanosLista->cantidad--;
                return true;
            }
        }
    }
    return false;
}

bool aldeanosListaEliminar(AldeanosLista *aldeanosLista, size_t posicion)
{
    if (aldeanosLista) {
        if (posicion > aldeanosLista->cantidad) {
            return false;
        }
        if (!aldeanosListaVacia(aldeanosLista)) {
            aldeanosLista->aldeanos[posicion] = aldeanoFree(aldeanosLista->aldeanos[posicion]);
            for (size_t i = posicion; i < aldeanosLista->cantidad; i++) {
                aldeanosLista->aldeanos[i] = aldeanosLista->aldeanos[i + 1];
            }
            aldeanosLista->cantidad--;
            return true;
        }
    }
    return false;
}

bool aldeanosListaEliminarInicio(AldeanosLista *aldeanosLista)
{
    if (aldeanosLista) {
        if (!aldeanosListaVacia(aldeanosLista)) {
            aldeanosLista->aldeanos[0] = aldeanoFree(aldeanosLista->aldeanos[0]);
            for (size_t i = 0; i < aldeanosLista->cantidad; i++) {
                aldeanosLista->aldeanos[i] = aldeanosLista->aldeanos[i + 1];
            }
            aldeanosLista->cantidad--;
            return true;
        }
    }
    return false;
}

bool aldeanosListaAgregar(AldeanosLista *aldeanosLista, Aldeano *aldeano, size_t posicion)
{
    if (aldeanosLista) {
        if (posicion > aldeanosLista->cantidad) {
            return false;
        }
        if (aldeanosListaLlena(aldeanosLista)) {
            aldeanosListaExpandir(aldeanosLista);
        }
        for (size_t i = aldeanosLista->capacidad - 1; i > posicion; i--) {
            aldeanosLista->aldeanos[i] = aldeanosLista->aldeanos[i - 1];
        }
        aldeanosLista->aldeanos[posicion] = aldeano;
        aldeanosLista->cantidad++;
        return true;
    }
    return false;
}

bool aldeanosListaAgregarInicio(AldeanosLista *aldeanosLista, Aldeano *jugador)
{
    if (aldeanosLista) {
        if (aldeanosListaLlena(aldeanosLista)) {
            aldeanosListaExpandir(aldeanosLista);
        }
        for (size_t i = aldeanosLista->capacidad - 1; i > 0; i--) {
            aldeanosLista->aldeanos[i] = aldeanosLista->aldeanos[i - 1];
        }
        aldeanosLista->aldeanos[0] = jugador;
        aldeanosLista->cantidad++;
        return true;
    }
    return false;
}

#endif