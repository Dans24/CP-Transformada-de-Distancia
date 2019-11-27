#ifndef DIST_H
#define DIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#include "pbm.h"

/**
 * @brief Gera uma matriz com a transformada de distância
 * A matrix de source deve apenas conter valores MIN_PIXEL_VALUE ou MAX_PIXEL_VALUE.
 * Os valores de pixeis iguais ao MIN_PIXEL_VALUE não são alterados.
 * Os valores de pixeis iguais ao MAX_PIXEL_VALUE são alterados para a distância até ao
 * pixel com valor de MIN_PIXEL_VALUE mais próximo.
 * A matriz source pode ser alterada.
 * 
 * @param height Altura da imagem
 * @param width Largura da imagem
 * @param img Matriz da imagem a ser processada
 * @param output Retorna a matriz processada
 * @return Número de iterações
*/
unsigned int dist(unsigned int height, unsigned int width, pixel (*img)[width], pixel (**output)[width]);

#endif