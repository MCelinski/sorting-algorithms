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

// zamiana dwoch elementow
  void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
  }

  void heapify(int arr[], int n, int i) {
    // deklaracja relacji korzenia, lewego i prawego dziecka
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
      largest = left;

    if (right < n && arr[right] > arr[largest])
      largest = right;

    // zamiana i dalsze kopcowanie jeœlikorzen  nie jest najwiekszy
    if (largest != i) {
      swap(&arr[i], &arr[largest]);
      heapify(arr, n, largest);
    }
  }

  void heapSort(int arr[], int n) {
    // tworzenie kopca
    for (int i = n / 2 - 1; i >= 0; i--)
      heapify(arr, n, i);

    // sortowanie
    for (int i = n - 1; i >= 0; i--) {
      swap(&arr[0], &arr[i]);
      heapify(arr, i, 0);
    }
  }



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
        heapSort(b,NUM);


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
    return 0;
}

