#include "vertex.h"
#include <stdio.h>
#include <stdlib.h>

struct vertex {
    int id;
    long double value;
    int tipo;
};

Vertex* initVertex (int id) {
    Vertex* v = calloc(1,sizeof(Vertex));
    v->id = id;
    v->value = -1;
    v->tipo = DEFAULT;

    return v;
}

void destroyVertex (Vertex* v) {
    free(v);
}

long double getValue (Vertex* v) {
    return v->value;
}

void setValue (Vertex* v, long double value) {
    v->value = value;
}

int getID (Vertex* v) {
    return v->id;
}

void setTipo (Vertex* v, int tipo) {
    v->tipo = tipo;
}

int getTipo (Vertex* v) {
    return v->tipo;
}

void printvertex (Vertex* v) {
    printf("id: %d\n", v->id);
}