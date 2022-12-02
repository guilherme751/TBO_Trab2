#ifndef RTT_H
#define RTT_H
#include <stdio.h>

/**
 * @brief Um RTT (Round Trip Time) entre um servidor e um cliente, 
 * armazena o RTT real, aproximado e a relação entre ambos
 * 
 */
typedef struct rtt RTT;
/**
 * @brief Inicia um RTT v
 * 
 * @return RTT* 
 */
RTT * RTT_create();
/**
 * @brief Libera memória alocada 
 * 
 * @param rtt 
 */
void RTT_destroy (RTT* rtt);

void RTT_fprint (FILE* f, RTT* rtt);
/**
 * @brief Set o servidor 'a' e o cliente 'b' para um RTT
 * 
 * @param rtt 
 * @param a 
 * @param b 
 */
void set_a_b (RTT* rtt, int a, int b);
/**
 * @brief Set o RTT real de um RTT
 * 
 * @param rtt 
 * @param value_real 
 */
void setRTT_Real (RTT* rtt, double value_real);
/**
 * @brief Set o RTT aproximado de um RTT
 * 
 * @param rtt 
 * @param value_aprox 
 */
void setRTT_Aprox (RTT* rtt, double value_aprox);
/**
 * @brief Atualiza a relação entre RTT aproximado e real
 * 
 * @param rtt 
 */
void RTT_frac_update (RTT* rtt);
/**
 * @brief Cria um vetor de ponteiros para RTTs
 * 
 * @param size 
 * @return RTT** 
 */
RTT ** RTTvec_create (int size);
/**
 * @brief Destroi um vetor de ponteiros para RTTs
 * 
 * @param rttvec 
 * @param size 
 */
void RTTvec_destroy (RTT** rttvec, int size);
/**
 * @brief Ordena um vetor de ponteiros para RTTs com quick sort
 * 
 * @param rttvec 
 * @param size 
 */
void RTT_sort (RTT** rttvec, int size);
/**
 * @brief Retorna a relação entre RTT aproximado e real
 * 
 * @param rtt 
 * @return double 
 */
double retornaFrac (RTT* rtt);

void RTTvec_fprint (FILE* f, RTT** rttvec, int size);

#endif