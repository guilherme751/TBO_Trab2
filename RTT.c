#include "RTT.h"

#include <stdlib.h>

struct rtt {
    long double real;
    long double aprox;
    long double frac;
    int a, b;
};

static int compFunc (const void* a, const void* b) {
    RTT* rtt1 = *(RTT**) a;
    RTT* rtt2 = *(RTT**) b;
    if (rtt1->frac > rtt2->frac)
        return 1;
    else if (rtt1->frac < rtt2->frac)
        return -1;
    else
        return 0;
}

RTT * RTT_create() {
    RTT* rtt = calloc(1, sizeof(RTT));   

    return rtt;
}

void RTT_destroy (RTT* rtt) {
    free(rtt);
}

void RTT_fprint (FILE* f, RTT* rtt) {
    fprintf(f, "%d %d %.16lf\n", rtt->a, rtt->b, (double)rtt->frac);
}

void set_a_b (RTT* rtt, int a, int b) {
    rtt->a = a;
    rtt->b = b;
}

void setRTT_Real (RTT* rtt, double value_real) {
    rtt->real = (long double)value_real;
}

void setRTT_Aprox (RTT* rtt, double value_aprox) {
    rtt->aprox = (long double)value_aprox;
}

void RTT_frac_update (RTT* rtt) {
    rtt->frac = (long double) (rtt->aprox/rtt->real);
}

RTT ** RTTvec_create (int size) {
    RTT** rttvec = calloc(size, sizeof(RTT*));
    for (int i=0; i<size; i++) {
        rttvec[i] = RTT_create();
    }

    return rttvec;
}

void RTTvec_destroy (RTT** rttvec, int size) {
    for (int i=0; i<size; i++) {
        RTT_destroy(rttvec[i]);
    }
    free(rttvec);
}

void RTTvec_fprint (FILE* f, RTT** rttvec, int size) {
    for (int i=0; i<size; i++) {
        RTT_fprint(f, rttvec[i]);
    }
}

void RTT_sort (RTT** rttvec, int size) {
    qsort(rttvec, size, sizeof(RTT*), compFunc);
}

double retornaFrac (RTT* rtt) {
    return rtt->frac;
} 