#include "dist.h"

int main(int argc, char* argv[]) {
    if(argc < 3) return 1;
    char* inputFilename = argv[1];
    char* outputTime = argv[2];
    unsigned int height;
    unsigned int width;
    pixel (*input)[width] = (pixel (*)[width]) getImageP1(fopen(inputFilename, "r"), &height, &width);
    if(!input) return 1;
    pixel (*output)[width];
    //tempo antes de começar o algoritmo
    double initial = omp_get_wtime();
    int iter = dist(height, width, input, &output);
    //tempo depois de terminar o algoritmo
    double time = omp_get_wtime() - initial;
    if(!output) return 1;
    free(output);
    //guardar em ficheiro o tempo total
    FILE* times = fopen(outputTime, "a");
    fprintf(times, "Algorithm time : %f\n",time);
    return 0;
}

unsigned int dist(unsigned int height, unsigned int width, pixel (*img)[width], pixel (**output)[width]) {
    pixel (*aux)[width] = calloc(1, sizeof(pixel[height][width]));
    int iter;
    int whitePixel = 1; // inicializado a 1 para entrar no for loop
    int chunkHeight = 256;
    int chunkWidth = 2048;
    int ni = (height-2)/chunkHeight + 1;
    int nj = (width-2)/chunkWidth + 1;
    int hasWhite[ni][nj];
    for(int i = 0; i < ni; i++) {
        for(int j = 0; j < nj; j++) {
            hasWhite[i][j] = 2;
        }
    }
    for (iter = 1; iter < MAX_PIXEL_VALUE && whitePixel; iter++) { // trocar por um "do while"?
        whitePixel = 0;
        for(int i = 1; i < height - chunkHeight - 1; i += chunkHeight - 1) {
            for(int j = 1; j < width - chunkHeight - 1; j += chunkWidth - 1) {
                int ci = i / (chunkHeight-2);
                int cj = j / (chunkWidth-2);
                if(hasWhite[ci][cj] == 0) continue;
                int whitePixelTemp = distChunk(i, j, chunkHeight, chunkWidth, height, width, img, aux);
                hasWhite[ci][cj] -= whitePixelTemp ? 0 : 1;
                whitePixel |= whitePixelTemp;
            }
        }
        int i = height / (chunkHeight - 1);
        int ci = i / (chunkHeight-2);
        for(int j = 1; j < width - chunkHeight - 1; j += chunkWidth - 1) {
            int cj = j / (chunkWidth-2);
            if(hasWhite[ci][cj] == 0) continue;
            int whitePixelTemp = distChunk(i, j, height - i - 1, width - 1, height, width, img, aux);
            hasWhite[ci][cj] -= whitePixelTemp ? 0 : 1;
            whitePixel |= whitePixelTemp;
        }
        pixel (*temp)[width] = img;
        img = aux;
        aux = temp;
    }
    if(iter % 2 == 1) {
        *output = aux;
    } else {
        free(aux);
        *output = img;
    }
    return iter;
}