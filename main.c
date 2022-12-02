#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "PQ.h"
#include "vertex.h"
#include <time.h>
#include "RTT.h"
/**
 * @brief Lê o arquivo de entrada, construindo o grafo a partir dos dados lidos
 * 
 * @param inFile 
 * @return Graph* 
 */
static Graph* LeArquivo_ConstroiGrafo (FILE* inFile);
/**
 * @brief Calcula o caminho mínimo de todos os vértices servidores e clientes para 
 * todos os outros vértices, usando o algoritmo de Dijkstra
 * 
 * @param G 
 * @return long** 
 */
static long double** dijkstra_all_S_and_C_pairs (Graph* G);
/**
 * @brief Libera memória alocada por uma matriz de 'size' linhas
 * 
 * @param mat 
 * @param size 
 */
void liberaMatriz (long double ** mat, int size);

int main (int argc, char** argv) {  
    if (argc != 3) {
        puts("Use: ./exe <entrada.txt> <saida.txt>");
    }     
   
    FILE* inFile= fopen(argv[1], "r");    
    if (!inFile) {
        puts("File not Found");
        exit(1);
    }        
    
    Graph* G =  LeArquivo_ConstroiGrafo(inFile);     
    
    long double** shortestDistance_All = dijkstra_all_S_and_C_pairs(G);
    
    //a quantidade de RTTs a serem calculados é o produto entre a quantidade de servidores
    //e clientes
    int size = returnNumServers(G) * returnNumClients(G);
    //inicia um vetor de ponteiros para um RTT
    RTT** rttvec = RTTvec_create(size);   
    
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

   
    return 0;
}

static Graph* LeArquivo_ConstroiGrafo (FILE* inFile) {
    int V, E;
    int numServidores, numClientes, numMonitores;    
    //lê o número de vértices e de arestas
    fscanf(inFile, "%d %d\n", &V, &E);    
    int aux;
    //lê o número de servidores, clientes e monitores
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
    //lê as arestas e adiciona elas no grafo
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

void liberaMatriz (long double ** mat, int size) {
    for (int i=0; i<size; i++) {
        free(mat[i]);
    }
    free(mat);
}
