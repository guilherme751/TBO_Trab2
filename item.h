#ifndef ITEM_H
#define ITEM_H
#include "vertex.h"
typedef Vertex Item;

#define id(A)          (getID(A))                           // retorna identificador do nó
#define value(A)        (getValue(A))                       // retorna valor do nó
#define more(A, B)      (value(A) > value(B))           // compara nós, por valor
#define exch(A, B)      { Item* t = A; A = B; B = t; }   // troca dois nós


#endif
