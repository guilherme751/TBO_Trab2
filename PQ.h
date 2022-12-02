#ifndef PQ_H
#define PQ_H

#include <stdbool.h>
#include "item.h"

typedef struct pq PQ;
/**
 * @brief cria uma min PQ com capacidade maxN
 * 
 * @param maxN 
 * @return PQ* 
 */
PQ* PQ_init (int maxN); 

/**
 * @brief Insere Item na PQ. A maior prioridade é a do Item com menor campo 'value'
 * 
 * @param pqueue 
 * @param v 
 */
void PQ_insert(PQ* pqueue, Item* v);   

/**
 * @brief // Muda a prioridade do nó com identificador 'id' para 'value'
 * 
 * @param pqueue 
 * @param id 
 * @param value 
 */
void PQ_decrease_key(PQ* pqueue, int id, double value); 

Item* PQ_delmin(PQ* pqueue);

/**
 * @brief Retorna Item com menor campo 'value' da PQ
 * 
 * @param pqueue 
 * @return Item* 
 */
Item* PQ_min(PQ* pqueue);   

/**
 * @brief Retorna True se a PQ não tem elementos
 * 
 * @param pqueue 
 * @return true 
 * @return false 
 */
bool PQ_empty(PQ* pqueue); 

/**
 * @brief Número de elementos na PQ
 * 
 * @return int 
 */
int  PQ_size();         
/**
 * @brief Libera memória alocada para PQ
 * 
 * @param pqueue 
 */
void PQ_finish(PQ* pqueue);

int PQ_exist (PQ* pqueue, Vertex* v);
#endif
