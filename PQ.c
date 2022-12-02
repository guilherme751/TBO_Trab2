#include <stdio.h>
#include <stdlib.h>
#include "PQ.h"

struct pq {
    int N;
    int maxN;
    Item** pq;
    int* map;
};


static void swap(PQ* pqueue, int i, int j) {
    exch(pqueue->pq[i], pqueue->pq[j]);
    pqueue->map[id(pqueue->pq[i])] = i;
    pqueue->map[id(pqueue->pq[j])] = j;
}


static void fix_up(PQ* pqueue, int k) {    
    
    while (k > 1 && more(pqueue->pq[k/2], pqueue->pq[k])) {
        swap(pqueue, k, k/2);
        k = k/2;
    }
}
static void fix_down(PQ* pqueue, int k){
    int sz = pqueue->N;
    while (2*k <= sz) {
        int j = 2*k;
        if (j < sz && more(pqueue->pq[j], pqueue->pq[j+1])){
            j++;
        }
        if (!more(pqueue->pq[k], pqueue->pq[j])) {
            break;
        }
        
    
        swap(pqueue, k, j);
        k = j;
    }
}


PQ* PQ_init (int maxN) {
    PQ* pqueue = malloc(sizeof(PQ));
    pqueue->N = 0;
    pqueue->pq = malloc((maxN+1)* sizeof(Item*));
    pqueue->maxN = maxN;
    pqueue->map = malloc((maxN)* sizeof(int));

    return pqueue;
}


void PQ_insert(PQ* pqueue, Item* v) {
    pqueue->N++;
    pqueue->pq[pqueue->N] = v;
    pqueue->map[id(v)] = pqueue->N;
    
    fix_up(pqueue, pqueue->N);
}

Item* PQ_delmin(PQ* pqueue) {
    Item* min = pqueue->pq[1];    
    
    swap(pqueue, 1, pqueue->N);
    pqueue->N--;
    fix_down(pqueue, 1);
    return min;
}

Item* PQ_min(PQ* pqueue) {
    return pqueue->pq[1];
}

void PQ_decrease_key(PQ* pqueue, int id, double value) {
    int i = pqueue->map[id];
    
    setValue(pqueue->pq[i], value);
   
   
    
    fix_up(pqueue, i);
}

bool PQ_empty(PQ* pqueue) {
    return pqueue->N == 0;
}

int  PQ_size(PQ* pqueue) {
    return pqueue->N;
}

void PQ_finish(PQ* pqueue) {
    free(pqueue->pq);
    free(pqueue->map);
    free(pqueue);    
}

void PQ_print (PQ* pqueue) {
    puts("fila");
    for (int i=1; i<=pqueue->N; i++) {
        printf("%d:(%d), ",i,getID(pqueue->pq[i]));
    }
    
    puts("\nmap");
    for (int i=0; i<pqueue->maxN; i++) {
        printf("%d ", pqueue->map[i]);
    }
    printf("\n");
}

// int PQ_exist (PQ* pqueue, Vertex* v) {
//     for (int i=1; i<=pqueue->N; i++) {
//         if (getID(pqueue->pq[i]) == getID(v))
//             return 1;
//     }
//     return 0;
// }



