#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#include <time.h>
#define ARR_LENGTH 1000000
//-------------------------------------------------------------------------

long long int readQPC()
{
    LARGE_INTEGER count;
    QueryPerformanceCounter(&count);
    return((long long int)count.QuadPart);
}

//-------------------------------------------------------------------------

void swap(int *a, int *b) {
  int t = *a;
  *a = *b;
  *b = t;
}

//-------------------------------------------------------------------------

int partition(long int array[], int low, int high) {

  long int pivot = array[high];
  int i = (low - 1);

  for (int j = low; j < high; j++) {
    if (array[j] <= pivot) {
      i++;
      swap(&array[i], &array[j]);
    }
  }
  swap(&array[i + 1], &array[high]);
  return (i + 1);
}

//-------------------------------------------------------------------------

void quickSort(int array[], int low, int high) {
  if (low < high) {
    int pi = partition(array, low, high);
    quickSort(array, low, pi - 1);
    quickSort(array, pi + 1, high);
  }
}

//-------------------------------------------------------------------------

int main(){

    FILE *times;
    FILE *sorted;
    sorted = fopen("sorted.txt","w");
    times = fopen("times.txt","w");
    fclose(times);
    fclose(sorted);

    long int range[] = {10, 50, 100, 500, 1000, 2000, 5000, 10000, 20000, 50000, 100000, 200000, 300000, 500000, 700000, 900000, 1000000};
    long int arraySize = sizeof (range)/sizeof(range[0]);

    for(int j = 0; j < arraySize;j++)
    {
    long int NUM = range[j];
    int Itters=10;
    int *numberArray = malloc (ARR_LENGTH * sizeof *numberArray);
    //long int numberArray[NUM],i;
    int i;

    FILE *myFile;
    myFile = fopen("liczby.txt", "r");

    if (myFile == NULL){
        printf("problem z plikiem\n");
        exit (0);
    }

    for (i = 0; i < NUM; i++){
        fscanf(myFile, "%ld,",&numberArray[i] );
    }

    sorted = fopen("sorted.txt","a");
    times = fopen("times.txt","a");

    long int b[NUM];

    fprintf(times,"dla: %d\n",range[j]);
    printf("%d\n",range[j]);

    for(int i=0; i<Itters;i++){
        long long int  elapsed,frequency,start;
        elapsed=0;
        QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);

        memcpy(((long int *)b),((long int *)numberArray), sizeof(long int)*NUM);

        start = readQPC();

        long int s = sizeof(b) / sizeof(b[0]);
        quickSort(b, 0, s - 1);

        elapsed = readQPC() - start;
        fprintf(times,"%d\n",elapsed);
    }

     fprintf(times,"\n\n");
     fclose(times);
     fclose(myFile);

     for (i = 0; i < NUM; i++){
        fprintf(sorted,"%ld\n ", b[i]);
     }

    fprintf(sorted,"%\n\n");
    fclose(sorted);
    }
    //free()
    return 0;
}


