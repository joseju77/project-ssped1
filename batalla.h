#ifndef BATALLA_H
#define BATALLA_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "civilizacion.h"

#include <iostream>

using namespace std;

struct barcoBatalla
{
    Barco *barco;
    struct nodo_doble *siguiente;
    struct nodo_doble *anterior;
};

typedef struct barco BarcoBatalla;

struct batalla
{
    BarcoBatalla *inicio;
    BarcoBatalla *final;
    size_t cantidad;
};

typedef struct batalla Batalla;

Batalla *batallaInit()
{
    Batalla *batalla = (Batalla*)malloc(sizeof(Batalla));

    if (!batalla) {
        cout << "Error al reservar memoria para la batalla" << endl;
        return NULL;
    }
    
    batalla->inicio = NULL;
    batalla->final = NULL;
    batalla->cantidad = 0;

    return batalla;
}

bool batallaVacia(Batalla *batalla)
{
    if (!batalla) {
        cout << "Batalla sin memoria" << endl;
        exit(1);
    }

    return batalla->cantidad == 0;
}

bool batallaEncolar(Batalla *batalla, BarcoBatalla *barco)
{
    if (!batalla) {
        cout << "Lista ligada doble sin memoria" << endl;
        return false;
    }

    barco->siguiente = NULL;

    if (batallaVacia(batalla)) {
        batalla->inicio = barco;
        batalla->final = barco;
        batalla->cantidad++;
        return true;
    }

    barco->anterior = batalla->final;
    batalla->final->siguiente = barco;
    batalla->final = barco;
    batalla->cantidad++;

    return true;
}

bool batallaDesencolar(Batalla *batalla)
{
    if (!batalla) {
        cout << "Batalla sin memoria" << endl;
        return false;
    } else if (batallaVacia(batalla)) {
        cout << "Batalla vacia" << endl;
        return false;
    }

    BarcoBatalla *tmp = batalla->inicio;

    batalla->inicio = tmp->siguiente;
    batalla->cantidad--;

    if (batallaVacia(batalla)) {
        batalla->final = NULL;
    } else {
        batalla->inicio->anterior = NULL;
    }

    return true;
}

Batalla *batallaFree(Batalla *batalla)
{
    if (!batalla) {
        cout << "Batalla sin memoria" << endl;
        return NULL;
    }

    while (!batallaVacia(batalla)) {
        batallaDesencolar(batalla);
    }

    free(batalla);
    batalla = NULL;

    return batalla;
}

BarcoBatalla *batallaTomar(Batalla *batalla)
{
    if (!batalla) {
        cout << "Batalla sin memoria" << endl;
        return NULL;
    } else if (batallaVacia(batalla)) {
        cout << "Batalla vacia" << endl;
        return NULL;
    }

    return batalla->inicio;
}

bool batallaMostrar(Batalla *batalla)
{
    if (!batalla) {
        cout << "Batalla sin memoria" << endl;
        return false;
    } else if (batallaVacia(batalla)) {
        cout << "Batalla vacia" << endl;
        return false;
    }

    cout << "Capacidad: " << batalla->cantidad << endl;

    BarcoBatalla *tmp = batalla->inicio;

    while (tmp) {
        barcoMostrar(tmp);
        tmp = tmp->siguiente;
        cout << "" << endl;
    }

    return true;
}

#endif
