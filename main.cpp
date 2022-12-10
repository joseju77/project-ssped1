#include <stdio.h>
#include <stdlib.h>
#include <iostream>

// #include "menu_aldeanos.h"
// #include "civilizacion.h"
// #include "civilizaciones.h"
#include "menu_civilizaciones.h"

int main() {
    Civilizaciones *civilizaciones = civilizacionesInit();
    menuCivilizaciones(civilizaciones);

    civilizaciones = civilizacionesFree(civilizaciones);

    return EXIT_SUCCESS;
}