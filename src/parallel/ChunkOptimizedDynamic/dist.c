#include "dist.h"

int distChunk(unsigned int ii, unsigned int jj, unsigned int height, unsigned int width, unsigned int imgHeight, unsigned int imgWidth, pixel (*in)[imgWidth], pixel (*out)[imgWidth]);

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
    int whitePixel = 1;
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
    for (iter = 1; iter < MAX_PIXEL_VALUE && whitePixel; iter++) {
        #pragma omp parallel
        {
            whitePixel = 0;
            #pragma omp for schedule(dynamic) nowait reduction(||:whitePixel)
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
            #pragma omp for schedule(dynamic) nowait reduction(||:whitePixel)
            for(int j = 1; j < width - chunkHeight - 1; j += chunkWidth - 1) {
                int cj = j / (chunkWidth-2);
                if(hasWhite[ci][cj] == 0) continue;
                int whitePixelTemp = distChunk(i, j, height - i - 1, width - 1, height, width, img, aux);
                hasWhite[ci][cj] -= whitePixelTemp ? 0 : 1;
                whitePixel |= whitePixelTemp;
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

int distChunk(unsigned int ii, unsigned int jj, unsigned int height, unsigned int width, unsigned int imgHeight, unsigned int imgWidth, pixel (*in)[imgWidth], pixel (*out)[imgWidth]) {
    int whitePixel = 0;
    for (int i = ii; i < height + ii; i++) {
        for (int j = jj; j < width + jj; j++) {
            if (in[i][j] == MIN_PIXEL_VALUE) continue;
            pixel min = MAX_PIXEL_VALUE;
            for (int ki = -1; ki <= 1; ki++) {
                for (int kj = -1; kj <= 1; kj++) {
                    if(ki == 0 && kj == 0) continue;
                    pixel color = in[i + ki][j + kj];
                    if(color < min) {
                        min = color;
                    }
                }
            }
            if(min < MAX_PIXEL_VALUE) {
                out[i][j] = min + 1;
            } else {
                out[i][j] = in[i][j];
                whitePixel = 1;
            }
        }
    }
    return whitePixel;
}
