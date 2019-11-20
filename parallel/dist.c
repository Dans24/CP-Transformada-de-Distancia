#include "dist.h"

int main(int argc, char* argv[]) {
    if(argc < 3) return 1;
    char* inputFilename = argv[1];
    char* outputFilename = argv[2];
    unsigned int height;
    unsigned int width;
    FILE* inputFile = fopen(inputFilename, "r");
    pixel (*input)[width] = (pixel (*)[width]) getImageP1(inputFile, &height, &width);
    if(!input) return 1;
    pixel (*output)[width];
    double start_time = omp_get_wtime();
    int iter = dist(height, width, input, &output);
    double time = omp_get_wtime() - start_time;
    printf("time: %f s\n", time);
    if(!output) return 1;
    FILE* outputFile = fopen(outputFilename, "w");
    setImageP2(outputFile, height, width, output, iter);
    free(output);
    return 0;
}

unsigned int dist(unsigned int height, unsigned int width, pixel (*img)[width], pixel (**output)[width]) {
    pixel (*aux)[width] = calloc(1, sizeof(pixel[height][width]));
    int iter;
    int whitePixel = 1; // inicializado a 1 para entrar no for loop
    for (iter = 1; iter < MAX_PIXEL_VALUE && whitePixel; iter++) { // trocar por um "do while"?
        //double start_time = omp_get_wtime();
        whitePixel = 0;
        #pragma omp parallel for
        for (int i = 1; i < height - 1; i++) {
            for (int j = 1; j < width - 1; j++) {
                if (img[i][j] == MIN_PIXEL_VALUE) continue; // avança pixeis pretos
                pixel min = MAX_PIXEL_VALUE;
                for (int ki = -1; ki <= 1; ki++) {
                    for (int kj = -1; kj <= 1; kj++) {
                        if(ki == 0 && kj == 0) continue;
                        pixel color = img[i + ki][j + kj];
                        if(color < min) {
                            min = color;
                        }
                    }
                }
                if(min < MAX_PIXEL_VALUE) {
                    aux[i][j] = min + 1;
                } else {
                    aux[i][j] = img[i][j];
                    whitePixel = 1;
                }
            }
        }
        //double time = omp_get_wtime() - start_time;
        //printf("time: %f s\n", time);
        // swap source e aux
        //#pragma omp single
        //{
        pixel (*temp)[width] = img;
        img = aux;
        aux = temp;
        //}
        //#pragma omp barrier
    }
    
    if(iter % 2 == 1) {
        *output = aux;
    } else {
        free(aux);
        *output = img;
    }
    return iter;
}
