#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "PQ.h"
#include "vertex.h"
#include <time.h>
#include "RTT.h"

static Graph* LeArquivo_ConstroiGrafo (FILE* inFile);

static long double** dijkstra_all_S_and_C_pairs (Graph* G);

static void liberaMatriz (long double** mat, int size) ;

int main (int argc, char** argv) {    
    printf("\033[0;32m");
    FILE* inFile= fopen(argv[1], "r");

    if (!inFile) {
        puts("File not Found");
        exit(1);
    }    
    clock_t start, end;

    Graph* G =  LeArquivo_ConstroiGrafo(inFile);  
    //imprimeGrafo(G);
    int size= returnNumServers(G) * returnNumClients(G);
    RTT** rttvec = RTTvec_create(size);   
   
    start = clock();
    long double** shortestDistance_All = dijkstra_all_S_and_C_pairs(G);
    
    end = clock();

    calculate_RTTs_Reais(G, shortestDistance_All, rttvec);

    calculate_RTTs_Aproximados(G, shortestDistance_All ,rttvec);
    
    RTT_sort(rttvec, size);
    

    FILE* outFile = fopen(argv[2], "w");

    RTTvec_fprint(outFile, rttvec, size);

    //Area de liberação de memória
    
    liberaMatriz(shortestDistance_All, returnNumVertices(G));
    RTTvec_destroy(rttvec, size);
    destroyGraph(G);
    fclose(inFile);
    fclose(outFile);
    double seconds =(double) (end-start)/CLOCKS_PER_SEC;

    printf("Tempo de processamento: %lf\n", seconds);
    return 0;
}

static Graph* LeArquivo_ConstroiGrafo (FILE* inFile) {
    int V, E;
    int numServidores, numClientes, numMonitores;    

    fscanf(inFile, "%d %d\n", &V, &E);    
    int aux;
    fscanf(inFile, "%d %d %d\n", &numServidores, &numClientes, &numMonitores);
    Graph* G = initGraph(V, numServidores, numClientes, numMonitores);
    for (int i=0; i<numServidores; i++) {
        fscanf(inFile, "%d\n", &aux);
        addServidor(G, aux);
    } 
    for (int i=0; i<numClientes; i++) {
        fscanf(inFile, "%d\n", &aux);
        addCliente(G, aux);
    }  
    for (int i=0; i<numMonitores; i++) {
        fscanf(inFile, "%d\n", &aux);
        addMonitor(G, aux);
    }     
    int u, v;
    long double weight;
    for (int i=0; i<E; i++) {
        fscanf(inFile, "%d %d %LF\n", &u, &v, &weight);
        addEdge(G, u, v, weight);
    }

    return G;
}

static long double** dijkstra_all_S_and_C_pairs (Graph* G) {  

    int numVertices = returnNumVertices(G);
    long double** dist = malloc(sizeof(long double*)*numVertices);
    for (int i=0; i<numVertices; i++) {
        dist[i] = calloc(numVertices, sizeof(long double));
        if (!ehVerticePadrao(G, i))
            dijkstraAlgorithm(G, i, dist[i]);
    }   

    
    return dist;
}

static void liberaMatriz (long double** mat, int size) {
    for (int i=0; i<size; i++) {
        free(mat[i]);
    }
    free(mat);
}