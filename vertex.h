#ifndef VERTEX_H
#define VERTEX_H
#define DEFAULT 0
#define SERVER 1
#define MONITOR 2
#define CLIENT 3
/**
 * @brief Um vértice do grafo, possui um id e um valor.
 * Tipos possíveis: DEFAULT, SERVER, MONITOR, CLIENT
 * 
 */
typedef struct vertex Vertex;

/**
 * @brief Inicia um vértice com id 'id'
 * 
 * @param id 
 * @return Vertex* 
 */
Vertex* initVertex (int id);

/**
 * @brief Libera memória alocada para um vértice
 * 
 * @param v 
 */
void destroyVertex (Vertex* v);

/**
 * @brief Retorna o valor de um vértice
 * 
 * @param v 
 * @return long double 
 */
long double getValue (Vertex* v);

/**
 * @brief Seta o valor do vértice
 * 
 * @param v 
 * @param value 
 */
void setValue (Vertex* v, long double value);

/**
 * @brief Retorna o id do vértice
 * 
 * @param v 
 * @return int 
 */
int getID (Vertex* v);

/**
 * @brief Pré condição: 'tipo' é um tipo válido 
 * seta o tipo do vértice de acordo com as constantes pré definidas
 * 
 * @param v 
 * @param tipo 
 */
void setTipo (Vertex* v, int tipo);

/**
 * @brief Retorna o tipo do objeto
 * 
 * @param v 
 * @return int 
 */
int getTipo (Vertex* v);



#endif