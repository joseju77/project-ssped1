#ifndef ALDEANO_H
#define ALDEANO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

#include "utilidades.h"

using namespace std;

struct aldeano
{
    char *nombre;
    int edad;
    int salud;
};

typedef struct aldeano Aldeano;

Aldeano *aldeanoInit(char *nombre = "", int edad = 0, int salud = 0)
{
    Aldeano *aldeano = (Aldeano*)malloc(sizeof(Aldeano));
    if (aldeano) {
        aldeano->nombre = strdup(nombre);
        aldeano->edad = edad;
        aldeano->salud = salud;
    }
    return aldeano;
}

Aldeano *aldeanoFree(Aldeano *aldeano)
{
    if (aldeano) {
        free(aldeano->nombre);
        aldeano->nombre = NULL;
        free(aldeano);
        aldeano = NULL;
    }
    return aldeano;
}

Aldeano *aldeanoCapturar()
{
    char* nombre = readChar("Nombre: ");
    int edad = readInt("Edad: ");
    int salud = readInt("Salud: ");
    

    Aldeano *aldeano = aldeanoInit(nombre, edad, salud);

    return aldeano;
}

bool aldeanoMostrar(Aldeano *aldeano)
{
    if (aldeano) {
        cout << "Nombre: " << aldeano->nombre << endl << "Edad: " << aldeano->edad << endl << "Salud: " << aldeano->salud << endl << endl;
        return true;
    }
    return false;
}

bool aldeanoMostrarFila(Aldeano *aldeano)
{
    if (aldeano) {
        printf("|%-20s|%4i|%5i|\n", aldeano->nombre, aldeano->edad, aldeano->salud);
        return true;
    }
    return false;
}



#endif