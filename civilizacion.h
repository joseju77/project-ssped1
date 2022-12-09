#ifndef CIVILIZACION_H
#define CIVILIZACION_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "lista_aldeanos.h"

using namespace std;

struct civilizacion
{
    char *nombre;
    AldeanosLista *aldeanosLista;
};

typedef struct civilizacion Civilizacion;

Civilizacion *civilizacionInit(char *nombre)
{
    Civilizacion *civilizacion = (Civilizacion*)malloc(sizeof(Civilizacion));
    if (!civilizacion) {
        cout << "Error al reservar memoria" << endl;
    }
    civilizacion->nombre = strdup(nombre);
    civilizacion->aldeanosLista = aldeanosListaInit();

    return civilizacion;
}

Civilizacion *civilizacionFree(Civilizacion *civilizacion)
{
    if (civilizacion) {
        cout << "Civilizacion sin memoria" << endl;
    }
    free(civilizacion->nombre);
    civilizacion->aldeanosLista = aldeanosListaFree(civilizacion->aldeanosLista);
    free(civilizacion);
    civilizacion = NULL;
    
    return civilizacion;
}


#endif