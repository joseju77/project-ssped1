#ifndef UTILIDADES_H
#define UTILIDADES_H

#include <stdio.h>
#include <stdlib.h>

char buffer[100];

char *readChar(char *message)
{
    printf("%s", message);
    char *chr;
    chr = fgets(buffer, sizeof(buffer), stdin);
    if (chr) {
        buffer[strlen(buffer) - 1] = '\0';
        chr = buffer;
    }
    return chr;
}

int readInt(char *message)
{
    int integer;

    printf("%s", message);
    scanf("%i", &integer);

    return integer;
}

float readFloat(char *message)
{
    float flo;

    printf("%s", message);
    scanf("%f", &flo);

    return flo;
}

char readCharNP(char *message)
{
    char val[100];
    printf("%s", message);
    scanf("%s", &val);
    return val[100];
}


#endif