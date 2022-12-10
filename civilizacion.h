#ifndef CIVILIZACION_H
#define CIVILIZACION_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "lista_aldeanos.h"
#include "utilidades.h"
#include "barcos.h"

using namespace std;

struct civilizacion
{
    char *nombre;
    AldeanosLista *aldeanosLista;
    Puerto *puerto;
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

    civilizacion->puerto = puertoInit();

    return civilizacion;
}

Civilizacion *civilizacionFree(Civilizacion *civilizacion)
{
    if (!civilizacion) {
        cout << "Civilizacion sin memoria" << endl;
    }
    free(civilizacion->nombre);
    civilizacion->aldeanosLista = aldeanosListaFree(civilizacion->aldeanosLista);
    free(civilizacion);
    civilizacion = NULL;
    
    return civilizacion;
}

Civilizacion *civilizacionCapturar()
{
    char *nombre = readChar("Nombre: ");
    Civilizacion *civilizacion = civilizacionInit(nombre);

    return civilizacion;
}

bool civilizacionMostrar(Civilizacion *civilizacion)
{
    if (!civilizacion) {
        cout << "Civilizacion sin memoria" << endl;
    }

    cout << "Civilizacion: " << civilizacion->nombre << endl;

    if (aldeanosListaMostrarTabla(civilizacion->aldeanosLista)) {
        cout << "Se mostro la lista de aldeanos" << endl;
    } else {
        cout << "Error al mostrar la lista de aldeanos" << endl;
        return false;
    }
    return true;
}

#endif