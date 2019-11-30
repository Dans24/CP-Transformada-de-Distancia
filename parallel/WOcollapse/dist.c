#include "dist.h"

int main(int argc, char* argv[]) {
    if(argc < 4) return 1;
    char* inputFilename = argv[1];
    char* outputFilename = argv[2];
    char* outputTime = argv[3];
    unsigned int height;
    unsigned int width;
    FILE* inputFile = fopen(inputFilename, "r");
    pixel (*input)[width] = (pixel (*)[width]) getImageP1(inputFile, &height, &width);
    if(!input) return 1;
    pixel (*output)[width];
    //tempo antes de começar o algoritmo
    double start_time = omp_get_wtime();
    int iter = dist(height, width, input, &output);
    //tempo do algoritmo
    double time = omp_get_wtime() - start_time;
    if(!output) return 1;
    setImageP2(fopen(outputFilename,"w"),height,width,output,iter);
    free(output);
    //guardar em ficheiro o tempo total
    FILE* times = fopen(outputTime, "a");
    int n_threads = 0;
    #pragma omp parallel
    {
        #pragma omp master
        {
            n_threads = omp_get_num_threads();
        }
    }
    fprintf(times, "Tempo do algoritmo com %d threads : %f\n",n_threads,time);
    return 0;
}

unsigned int dist(unsigned int height, unsigned int width, pixel (*img)[width], pixel (**output)[width]) {
    pixel (*aux)[width] = calloc(1, sizeof(pixel[height][width]));
    int iter;
    int whitePixel = 1; // inicializado a 1 para entrar no for loop
    for (iter = 1; iter < MAX_PIXEL_VALUE && whitePixel; iter++) { // trocar por um "do while"?
        whitePixel = 0;
        #pragma omp parallel for schedule(guided)
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
