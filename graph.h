#ifndef GRAPH_H
#define GRAPH_h
#include "RTT.h"
#include "stdbool.h"
typedef struct graph Graph;
/**
 * @brief Inicia um grafo especial com vértices que podem ser servidores, 
 * clientes, monitores ou padrão. 
 * 
 * @param numVertices 
 * @param numServers 
 * @param numClients 
 * @param numMonitors 
 * @return Graph* 
 */
Graph* initGraph (int numVertices, int numServers, int numClients, int numMonitors);
/**
 * @brief Adiciona uma aresta (u,v) no gráfico de peso 'weight'
 * 
 * @param G 
 * @param u 
 * @param v 
 * @param weight 
 */
void addEdge (Graph* G, int u, int v, long double weight);
/**
 * @brief Adiciona um vértice servidor
 * 
 * @param G 
 * @param s 
 */
void addServidor (Graph* G, int s);
/**
 * @brief Adiciona um vértice cliente
 * 
 * @param G 
 * @param c 
 */
void addCliente (Graph* G, int c);
/**
 * @brief Adiciona um vértice monitor
 * 
 * @param G 
 * @param m 
 */
void addMonitor (Graph* G, int m);


/**
 * @brief Libera memória alocada
 * 
 * @param G 
 */
void destroyGraph (Graph* G);
/**
 * @brief Executa o algoritmo de Dijkstra a partir da fonte 'source'
 * 
 * @param G 
 * @param source 
 * @param dist 
 */
void dijkstraAlgorithm (Graph* G, int source, long double* dist);
/**
 * @brief Retorna o número de vértices do grafo
 * 
 * @param G 
 * @return int 
 */
int returnNumVertices (Graph* G);
/**
 * @brief Calcula os RTTs Reais do grafo e adiciona no vetor 'rttvec'
 * 
 * @param G 
 * @param dist 
 * @param rttvec 
 */
void calculate_RTTs_Reais(Graph *G, long double **dist, RTT** rttvec);
/**
 * @brief Calcula os RTTs Aproximados do grafo e adiciona no vetor 'rttvec'
 * 
 * @param G 
 * @param dist 
 * @param rttvec 
 */
void calculate_RTTs_Aproximados(Graph *G, long double **dist, RTT** rttvec);
/**
 * @brief Verifica se é um vértice padrão
 * 
 * @param G 
 * @param i 
 * @return true 
 * @return false 
 */
bool ehVerticePadrao (Graph* G, int i);
/**
 * @brief Retorna o número de servidores
 * 
 * @param G 
 * @return int 
 */
int returnNumServers (Graph* G);
/**
 * @brief Retorna o número de clientes
 * 
 * @param G 
 * @return int 
 */
int returnNumClients (Graph* G);

#endif