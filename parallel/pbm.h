#ifndef PBM_H
#define PBM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef unsigned char pixel;

/// Valor máximo do pixel
#if !defined(MAX_PIXEL_VALUE)
#define MAX_PIXEL_VALUE 255
#endif // MAX_PIXEL_VALUE

/// Valor mínimo do pixel
#if !defined(MIN_PIXEL_VALUE)
#define MIN_PIXEL_VALUE 0
#endif // MIN_PIXEL_VALUE

/**
 * @brief Lê o ficheiro e retorna uma matriz com os pixeis da imagem
 * A função apenas suporta ficheiros bpm P1 sem comentários
 * @param f Ficheiro da imagem
 * @param height Retorna a altura da imagem
 * @param width Retorna a largura da imagem
 * @return Retorna a imagem guardada no ficheiro ou NULL em caso de erro
 */
pixel* getImageP1(FILE* f, unsigned int *height, unsigned int *width);

/**
 * @brief Guarda no ficheiro a matriz
 * 
 * @param f Ficheiro da imagem
 * @param height Altura da imagem
 * @param width Largura da imagem
 * @param img Imagem a ser guardada
 * @param levelOfGray Número de níveis de cinzento
 */
void setImageP2(FILE* f, unsigned int height, unsigned int width, pixel (*img)[width], unsigned int levelOfGray);

/**
 * @brief Imprime a imagem no ecrã
 * 
 * @param height Altura da imagem
 * @param width Largura da imagem
 * @param img Matriz da imagem a ser imprimida no ecrã
 */
void printImage(unsigned int height, unsigned int width, pixel (*img)[width]);

#endif