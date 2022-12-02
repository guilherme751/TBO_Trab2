#include "graph.h"
#include "lista.h"
#include "vertex.h"
#include "PQ.h"

#define INFINITY 10000000000
struct graph
{
    int numVertices;
    Vertex **vertices;
    tLista **adjList;
    int numServers;
    int *servers;
    int numMonitors;
    int *monitors;
    int numClients;
    int *clients;
};


Graph *initGraph(int numVertices, int numServers, int numClients, int numMonitors){
    Graph *G = malloc(sizeof(Graph));
    G->numVertices = numVertices;
    G->vertices = calloc(numVertices, sizeof(Vertex *));
    G->adjList = calloc(numVertices, sizeof(tLista *));

    G->numClients = G->numMonitors = G->numServers = 0;
    G->servers = malloc(numServers * sizeof(int));
    G->clients = malloc(numClients * sizeof(int));
    G->monitors = malloc(numMonitors * sizeof(int));

    for (int i = 0; i < numVertices; i++){
        G->vertices[i] = initVertex(i);
    }

    for (int i = 0; i < numVertices; i++){
        G->adjList[i] = IniciaLista();
    }
    return G;
}

void addEdge(Graph *G, int u, int v, long double weight){
    InsereLista(G->vertices[v], weight, G->adjList[u]);
}

void addServidor(Graph *G, int s){
    setTipo(G->vertices[s], SERVER);
    G->servers[G->numServers++] = s;
}
void addCliente(Graph *G, int c){
    setTipo(G->vertices[c], CLIENT);
    G->clients[G->numClients++] = c;
}
void addMonitor(Graph *G, int m){
    setTipo(G->vertices[m], MONITOR);
    G->monitors[G->numMonitors++] = m;
}



void destroyGraph(Graph *G){
    for (int i = 0; i < G->numVertices; i++){
        DestroiLista(G->adjList[i]);
    }
    free(G->adjList);
    for (int i = 0; i < G->numVertices; i++){
        destroyVertex(G->vertices[i]);
    }
    free(G->vertices);
    free(G->monitors);
    free(G->clients);
    free(G->servers);
    free(G);
}

void dijkstraAlgorithm(Graph *G, int source, long double *dist)
{

    setValue(G->vertices[source], 0);

    PQ *Q = PQ_init(G->numVertices);

    for (int i = 0; i < G->numVertices; i++) {
        if (i != source){
            setValue(G->vertices[i], INFINITY);
        }

        PQ_insert(Q, G->vertices[i]);
    }

    long double alt, peso;
    tCelula* c;
    Vertex* v;
    bool first;
    while (!PQ_empty(Q)) {    

        Vertex *u = PQ_delmin(Q);
        first = true;
        while (true) {
            c = itera_Lista(G->adjList[getID(u)], c, &v, &peso, first);
            
            first = false;            
            alt = getValue(u) + peso;
            if (alt <= getValue(v))
            {                
                setValue(v, alt);  
                             
                PQ_decrease_key(Q, getID(v), alt);                
            }
            if (c==NULL)    break;
        }
        
        
    }
    //O(V)
    for (int i = 0; i < G->numVertices; i++) {
        dist[i] = getValue(G->vertices[i]);
    }

    PQ_finish(Q);
}

int returnNumVertices(Graph *G) {
    return G->numVertices;
}

void calculate_RTTs_Reais(Graph *G, long double **dist, RTT** rttvec) {
    
    int k=0;
    for (int i = 0; i < G->numServers; i++){
        for (int j = 0; j < G->numClients; j++){
            set_a_b(rttvec[k], G->servers[i], G->clients[j]);
            setRTT_Real(rttvec[k],dist[G->servers[i]][G->clients[j]] +
                                    dist[G->clients[j]][G->servers[i]]);
            k++;
            
        }
    }        
}

void calculate_RTTs_Aproximados(Graph *G, long double **dist, RTT** rttvec) {    
    int k=0;
    long double menor;
    for (int i = 0; i < G->numServers; i++) {
        for (int j = 0; j < G->numClients; j++) {
            for (int m = 0; m < G->numMonitors; m++) {
                
                long double RTT_SM = dist[G->servers[i]][G->monitors[m]] +
                                dist[G->monitors[m]][G->servers[i]];

                long double RTT_MC = dist[G->monitors[m]][G->clients[j]] +
                                dist[G->clients[j]][G->monitors[m]];

                long double RTT_Aprox = RTT_SM + RTT_MC;
                
                if (m==0) {
                    menor = RTT_Aprox;
                }
                else if (RTT_Aprox < menor) {
                    menor = RTT_Aprox;
                }
            }            
            
            setRTT_Aprox(rttvec[k], menor);
            RTT_frac_update(rttvec[k]);
            k++;
        }
    }    
    
}

bool ehVerticePadrao(Graph *G, int i) {
    return getTipo(G->vertices[i]) == 0;
}

int returnNumServers(Graph *G) {
    return G->numServers;
}

int returnNumClients (Graph* G) {
    return G->numClients;
}