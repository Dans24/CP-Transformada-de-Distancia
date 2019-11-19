#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "pbm.h"

pixel* getImageP1(FILE* f, unsigned int *height, unsigned int *width) {
    // Check if image is P1 and get image size
    if(fscanf(f, "P1\n%u %u\n", width, height) < 2) {
        perror("Imagem inválida");
        return 0;
    }
    int h = *height;
    int w = *width;
    pixel (*img)[w] = malloc(sizeof(pixel[h][w]));
    if(img == 0) {
        perror("Falta de memória");
        return 0;
    }
    for(int i = 0; i < h; i++) {
        for(int j = 0; j < w; j++) {
            char c;
            if(fscanf(f, "%c", &c) < 1) {
                perror("Imagem truncada");
                return 0;
            }
            if(c == ' ' || c == '\n') {
                j--;
                continue;
            }
            img[i][j] = c == '1' ? MAX_PIXEL_VALUE : MIN_PIXEL_VALUE;
        }
    }
    return (pixel*) img;
}


void setImageP2(FILE* f, unsigned int height, unsigned int width, pixel (*img)[width], unsigned int levelOfGray) {
    fprintf(f, "P2\n%d %d\n%d\n", width, height, levelOfGray);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            fprintf(f, "%u ", img[i][j]);
        }
        fprintf(f, "\n");
    }
    fprintf(f, "\n");
}

void printImage(unsigned int height, unsigned int width, pixel (*img)[width]) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            pixel color = img[i][j];
            if(color == MAX_PIXEL_VALUE) {
                printf("X ");
            } else if(color == MIN_PIXEL_VALUE) {
                printf("O ");
            } else {
                printf("%u ", color);
            }
        }
        printf("\n");
    }
}

/*
int main() {
    FILE* f = fopen("exemplo.pbm", "r");
    int height = -1;
    int width = -1;
    pixel (*image)[height][width] = (pixel (*)[height][width]) getImageP1(f, &height, &width);
    printf("\n\n");
    printImage(height, width, image);
}
*/
