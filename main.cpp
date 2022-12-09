#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "menu_aldeanos.h"
#include "civilizacion.h"

int main() {
    Civilizacion *civilizacion = civilizacionInit("Romanos");
    menuAldeanos(civilizacion->aldeanosLista);

    civilizacion = civilizacionFree(civilizacion);

    return EXIT_SUCCESS;
}