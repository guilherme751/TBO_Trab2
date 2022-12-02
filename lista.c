#include "lista.h"
#include "vertex.h"


struct Celula {
    Vertex* v;
    tCelula* prox;
    long double peso;
};

 struct Lista {
    tCelula* prim;
    tCelula* ult;
 };
 
bool EhListaVazia (tLista* lista) {
    if (lista->prim == NULL && lista->ult ==NULL)
        return true;
    else    
        return false;    
 }

tLista* IniciaLista () {
    tLista* lista = (tLista*) malloc (sizeof(tLista));

    lista->prim = NULL;
    lista->ult = NULL;

    return lista;    
}


void InsereLista (Vertex* vertice, long double peso, tLista* lista) {
    
    tCelula* nova = (tCelula*) malloc (sizeof(tCelula));
    
    nova->prox = NULL;

    if (EhListaVazia(lista)) {
        lista->prim = nova;
        lista->ult = nova;
    }
    else {        
        lista->ult->prox = nova;       
        lista->ult = nova;
        
    }
    nova->v = vertice;
    nova->peso = peso;

}
// Vertex* RetornaVerticeIcomPeso (tLista* lista, long double* peso, int i) {
//     tCelula* p = lista->prim;
    
//     int j = 0;
//     while (i>j) {
//         p=p->prox;
//         j++;
//     }
//     *peso = p->peso;
//     return p->v;
// }



void DestroiLista (tLista* lista) {
    tCelula* p = lista->prim;
    tCelula* aux;
    
    while (p!=NULL) {

        aux = p->prox;               
        free(p);
        p = aux;
    }
    free(lista);
    
}

int RetornaTamLista (tLista* lista) {
    tCelula* p = lista->prim;
    int i = 0;
        
    while (p) {        
        i++;
        p = p->prox;
    }

    return i;
}


tCelula* itera_Lista (tLista* lista, tCelula* c, Vertex** v, long double* peso, bool first) {
    if (first) {
        c = lista->prim;
    }
    if (c == NULL) return NULL;
    *peso = c->peso;
    *v = c->v;

    return c->prox;
}
