#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "utils.h"
#include <sys/time.h>
#include <omp.h>

int main(int argc, char* argv[])
{
struct tm *local;
time_t start;


//Getting Reference & Tolerance values
    float reference;
    float tolerance;
    int  isVerbose = 0; //false
    int count = 0;
    while(count < argc){
        if(strcmp(argv[count], "-r") == 0){
            reference = strtof(argv[count+1], NULL);
        }
        if(strcmp(argv[count], "-t") == 0){
            tolerance = strtof(argv[count+1], NULL);
        }
        if(strcmp(argv[count], "-v") == 0){
            isVerbose = 1;
        }
        count++;
    }

//Getting matrix row/col count
int rowCount;
int colCount;
scanf("%d%d", &rowCount, &colCount);
//printf("%d",rowCount);
//printf("\n%d",colCount);
//float* floatArray[rowCount][colCount];

float** rows = (float **) malloc(rowCount * sizeof(float *));
if (rows == 0)
{
    fprintf(stderr, "Couldn’t alocate sufficient space.\n");
    exit(1);
}

for (int i = 0; i < rowCount; i++)
{
    float* row = (float *) malloc(colCount * sizeof(float));
    if (row == 0)
    {
        fprintf(stderr, "Couldn’t alocate sufficient row space.\n");
        exit(1);
    }
    rows[i] = row;
}


for(int i = 0; i < rowCount; i++){
    for(int j = 0; j < colCount; j++){
        scanf("%f", &rows[i][j]);

    }
}

time(&start); // read and record clock
local = localtime(&start);
printf("# Start time and date: %s", asctime(local));
struct timeval tim;
gettimeofday(&tim, NULL);
double t1=tim.tv_sec+(tim.tv_usec/1000000.0);

 int i = 0;
 int j = 0;
int hits = 0;
#pragma omp parallel for private(i,j)
for(i = 0; i < rowCount; i++){
    for(j = 0; j < colCount; j++){
        if(approxEqual(rows[i][j], reference, tolerance) == 1){
            #pragma omp atomic
            hits++;
            if(isVerbose){
                fprintf(stdout, "r=%d, cc=%d: %.6f (thread= %d)\n",
                    i, j, rows[i][j], omp_get_thread_num());
            }
        }
    }
}
printf("Found %d approximate matches.\n",hits);

gettimeofday(&tim, NULL);
double t2=tim.tv_sec+(tim.tv_usec/1000000.0);
printf("Search time: %.6lf(s)\n", t2-t1);
  exit(0);
}

