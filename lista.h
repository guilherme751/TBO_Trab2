#include <stdio.h>
#include <stdlib.h>
#include "vertex.h"
#include <stdbool.h>

#ifndef listacomsentinela_h
#define listacomsentinela_h

typedef struct Celula tCelula;
typedef struct Lista tLista;
/**
 * @brief Inicia uma lista simplemente encadeada com sentinela homogênea vazia
 * 
 * @return tLista* 
 */
tLista* IniciaLista ();
/**
 * @brief Verifica se uma lista está vazia
 * 
 * @param lista 
 * @return int 
 */
int EhListaVazia (tLista* lista);
/**
 * @brief Insere um vértice na lista com peso
 * 
 * @param vertice 
 * @param peso 
 * @param lista 
 */
void InsereLista (Vertex* vertice, long double peso, tLista* lista); 
/**
 * @brief 
 * 
 * @param lista 
 * @param peso 
 * @param i 
 * @return Vertex* 
 */
Vertex* RetornaVerticeIcomPeso (tLista* lista, long double* peso, int i);


/**
 * @brief Libera memória alocada
 * 
 * @param lista 
 */
void DestroiLista (tLista* lista);
/**
 * @brief Retorna o tamanho da lista
 * 
 * @param lista 
 * @return int 
 */
int RetornaTamLista (tLista* lista);
/**
 * @brief Itera sobre a lista retornando a próxima célula e setando o vértice e o peso
 * da célula atual
 * 
 * @param lista 
 * @param c 
 * @param v 
 * @param peso 
 * @param first 
 * @return tCelula* 
 */
tCelula* itera_Lista (tLista* lista, tCelula* c, Vertex** v, long double* peso, bool first);










#endif
