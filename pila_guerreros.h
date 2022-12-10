#ifndef PILA_GUERREROS_H
#define PILA_GUERREROS_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "utilidades.h"

using namespace std;

struct guerrero
{
    int id, salud;
    float fuerza, escudo;
    char *tipo;
    struct guerrero *siguiente;
};

typedef struct guerrero Guerrero;

Guerrero *guerreroInit(int id, float salud, float fuerza, float escudo, char *tipo)
{
    Guerrero *guerrero = (Guerrero*)malloc(sizeof(Guerrero));

    if (!guerrero) {
        cout << "Error al reservar memoria para el guerrero" << endl;
        return NULL;
    }

    guerrero->id = id;
    guerrero->salud = salud;
    guerrero->fuerza = fuerza;
    guerrero->escudo = escudo;
    guerrero->tipo = strdup(tipo);
    guerrero->siguiente = NULL;
    
    return guerrero;
}

Guerrero *guerreroFree(Guerrero *guerrero)
{
    if (guerrero) {
        free(guerrero);
        guerrero = NULL;
    }
    return guerrero;
}

Guerrero *guerreroCapturar()
{
    int id = readInt("Id: ");
    int salud = readInt("Salud: ");
    float fuerza = readFloat("Fuerza: ");
    float escudo = readFloat("Escudo: ");
    cin.ignore();
    char *tipo = readChar("Tipo (tirador, mago, asesino, tanque): ");
    
    

    Guerrero *guerrero = guerreroInit(id, salud, fuerza, escudo, tipo);

    return guerrero;
}

bool guerreroMostrar(Guerrero *guerrero)
{
    if (guerrero) {
        cout << "Id: " << guerrero->id << endl << "Salud: " << guerrero->salud << endl << "Fuerza: " << guerrero->fuerza << endl << "Escudo: " << guerrero->escudo << endl << "Tipo: " << guerrero->tipo << endl << endl;
        return true;
    }
    return false;
}

bool guerreroMostrarFila(Guerrero *guerrero)
{
    if (guerrero) {
        printf("|%4i|%5i|%.2f|%.2f|%15s|\n", guerrero->id, guerrero->salud, guerrero->fuerza, guerrero->escudo, guerrero->tipo);
        return true;
    }
    return false;
}

struct pila
{
    Guerrero *raiz;
    size_t cantidad;
};

typedef struct pila PilaGuerreros;

PilaGuerreros *pilaGuerrerosInit()
{
    PilaGuerreros *pilaGuerreros = (PilaGuerreros*)malloc(sizeof(PilaGuerreros));

    if (!pilaGuerreros) {
        cout << "Error al reservar memoria para la pila" << endl;
        return NULL;
    }
    
    pilaGuerreros->raiz = NULL;
    pilaGuerreros->cantidad = 0;

    return pilaGuerreros;
}

bool pilaGuerrerosVacia(PilaGuerreros *pilaGuerreros)
{
    if (!pilaGuerreros) {
        cout << "Pila sin memoria" << endl;
        exit(1);
    }

    return pilaGuerreros->cantidad == 0;
}

bool pilaGuerrerosApilar(PilaGuerreros *pilaGuerreros, Guerrero *guerrero)
{
    if (!pilaGuerreros) {
        cout << "Pila sin memoria" << endl;
        return false;
    }

    guerrero->siguiente = pilaGuerreros->raiz;
    pilaGuerreros->raiz = guerrero;
    pilaGuerreros->cantidad++;

    return true;
}

bool pilaGuerrerosMostrar(PilaGuerreros *pilaGuerreros)
{
    if (!pilaGuerreros) {
        cout << "Pila sin memoria" << endl;
        return false;
    } else if (pilaGuerrerosVacia(pilaGuerreros)) {
        cout << "Pila vacia" << endl;
        return false;
    }

    cout << "Cantidad: " << pilaGuerreros->cantidad << endl;
    Guerrero *tmp = pilaGuerreros->raiz;
    printf("|%4s|%5s|%5s|%5s|%15s|\n", "ID", "Salud", "Fuerza", "Escudo", "Tipo");
    while (tmp) {
        guerreroMostrarFila(tmp);
        tmp = tmp->siguiente;
    }
    
    return true;
}

bool pilaGuerrerosDesapilar(PilaGuerreros *pilaGuerreros)
{
    if (!pilaGuerreros) {
        cout << "Pila sin memoria" << endl;
        return false;
    } else if (pilaGuerrerosVacia(pilaGuerreros)) {
        cout << "Pila vacia" << endl;
        return false;
    }

    Guerrero *tmp = pilaGuerreros->raiz;
    pilaGuerreros->raiz = tmp->siguiente;

    guerreroFree(tmp);
    tmp = NULL;
    pilaGuerreros->cantidad--;

    return true;
}


PilaGuerreros *pilaGuerrerosFree(PilaGuerreros *pilaGuerreros)
{
    if (!pilaGuerreros) {
        cout << "Pila sin memoria" << endl;
        return NULL;
    }

    while (!pilaGuerrerosVacia(pilaGuerreros)) {
        pilaGuerrerosDesapilar(pilaGuerreros);
    }

    free(pilaGuerreros);
    pilaGuerreros = NULL;

    return pilaGuerreros;
}

bool pilaGuerrerosTope(PilaGuerreros *pilaGuerreros)
{
    if (!pilaGuerreros) {
        cout << "Pila sin memoria" << endl;
        return false;
    } else if (pilaGuerrerosVacia(pilaGuerreros)) {
        cout << "Pila vacia" << endl;
        return false;
    }

    guerreroMostrar(pilaGuerreros->raiz);

    return true;
}

#endif