#ifndef BARCOS_H
#define BARCOS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <iostream>
#include "pila_guerreros.h"


struct barco
{
    int id;
	float combustible;
	float velocidad;
	float armadura;
	PilaGuerreros *guerreros;
    struct barco *siguiente;
    struct barco *anterior;
};

typedef struct barco Barco;

Barco *barcoInit(int id, float combustible, float velocidad, float armadura)
{
    Barco *barco = (Barco*)malloc(sizeof(Barco));

    if (!barco) {
        cout << "Error al reservar memoria para el barco" << endl;
        return NULL;
    }

    barco->id = id;
    barco->combustible = combustible;
    barco->velocidad = velocidad;
    barco->armadura = armadura;
    barco->anterior = NULL;
    barco->siguiente = NULL;
    barco->guerreros = pilaGuerrerosInit();
    
    return barco;
}

Barco *barcoFree(Barco *barco)
{
    if (barco) {
        free(barco);
        barco = NULL;
    }
    return barco;
}

Barco *barcoCapturar()
{
    int id = readInt("Id: ");
    float combustible = readFloat("Combustible: ");
    float velocidad = readFloat("Velocidad: ");
    float armadura = readFloat("Armadura: ");

    Barco *barco = barcoInit(id, combustible, velocidad, armadura);

    return barco;
}

bool barcoMostrar(Barco *barco)
{
    if (barco) {
        cout << "Id: " << barco->id << endl << "Combustible: " << barco->combustible << endl << "Velocidad: " << barco->velocidad << endl << "Armadura: " << barco->armadura << endl << endl;
        return true;
    }
    return false;
}

struct puerto
{
    Barco *inicio;
    Barco *final;
    size_t cantidad;
};

typedef struct puerto Puerto;

Puerto *puertoInit()
{
    Puerto *puerto = (Puerto*)malloc(sizeof(Puerto));

    if (!puerto) {
        cout << "Error al reservar memoria para el puerto" << endl;
        return NULL;
    }
    
    puerto->inicio = NULL;
    puerto->final = NULL;
    puerto->cantidad = 0;

    return puerto;
}

bool puertoVacia(Puerto *puerto)
{
    if (!puerto) {
        cout << "Puerto sin memoria" << endl;
        exit(1);
    }

    return puerto->cantidad == 0;
}

bool puertoInsertarInicio(Puerto *puerto, Barco *barco)
{
    if (!puerto) {
        cout << "Puerto sin memoria" << endl;
        return false;
    }

    if (puertoVacia(puerto)) {
        puerto->inicio = barco;
        puerto->final = barco;
        puerto->cantidad++;
        return true;
    }
    
    barco->siguiente = puerto->inicio;
    puerto->inicio->anterior = barco;
    puerto->inicio = barco;
    puerto->cantidad++;
    return true;
}

bool puertoInsertarFinal(Puerto *puerto, Barco *barco)
{
    if (!puerto) {
        cout << "Puerto sin memoria" << endl;
        return false;
    }


    if (puertoVacia(puerto)) {
        puerto->inicio = barco;
        puerto->final = barco;
        puerto->cantidad++;
        return true;
    }

    barco->anterior = puerto->final;
    puerto->final->siguiente = barco;
    puerto->final = barco;
    puerto->cantidad++;

    return true;
}

bool puertoMostrar(Puerto *puerto)
{
    if (!puerto) {
        cout << "Puerto sin memoria" << endl;
        return false;
    } else if (puertoVacia(puerto)) {
        cout << "Puerto vacio" << endl;
        return false;
    }

    cout << "Capacidad: " << puerto->cantidad << endl;
    Barco *tmp = puerto->inicio;

    while (tmp) {
        barcoMostrar(tmp);
        tmp = tmp->siguiente;
        cout << "" << endl;
    }

    return true;
}

bool puertoEliminarInicio(Puerto *puerto)
{
    if (!puerto) {
        cout << "Puerto sin memoria" << endl;
        return false;
    } else if (puertoVacia(puerto)) {
        cout << "Puerto vacio" << endl;
        return false;
    }

    Barco *tmp = puerto->inicio;

    puerto->inicio = tmp->siguiente;
    puerto->cantidad--;

    if (puertoVacia(puerto)) {
        puerto->final = NULL;
    } else {
        puerto->inicio->anterior = NULL;
    }

    tmp = barcoFree(tmp);
    tmp = NULL;

    return true;
}

bool puertoEliminarFinal(Puerto *puerto)
{
    if (!puerto) {
        cout << "Puerto sin memoria" << endl;
        return false;
    } else if (puertoVacia(puerto)) {
        cout << "Puerto vacio" << endl;
        return false;
    }

    Barco *tmp = puerto->final;

    puerto->final = tmp->anterior;
    puerto->cantidad--;
    
    tmp = barcoFree(tmp);
    tmp = NULL;

    if (puertoVacia(puerto)) {
        puerto->final = NULL;
        puerto->inicio = NULL;
    } else {
        puerto->final->siguiente = NULL;
    }

    return true;
}

Puerto *puertoFree(Puerto *puerto)
{
    if (!puerto) {
        cout << "Puerto sin memoria" << endl;
        return NULL;
    }

    while (!puertoVacia(puerto)) {
        puertoEliminarInicio(puerto);
    }

    free(puerto);
    puerto = NULL;

    return puerto;
}

Barco *puertoBuscar(Puerto *puerto, int id)
{
    if (!puerto) {
        cout << "Puerto sin memoria" << endl;
        return NULL;
    }

    Barco *tmp = puerto->inicio;

    while (tmp) {
        if (id == tmp->id) {
            return tmp;
        }
        tmp = tmp->siguiente;
    }

    return NULL;
}

#endif