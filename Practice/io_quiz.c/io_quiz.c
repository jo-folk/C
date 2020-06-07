#include <stdio.h>
#include <stdlib.h>

float **AllocateArrayOfArrays(int P, int *Lengths)

{
int i, j;

float **arr = (float **)malloc(P * sizeof(float *));

for(i=0; i< P; i++)

arr[i] = (float *)malloc(Lengths[i] * sizeof(float));

for(i =0; i<P;i++)

for(j=0;j<Lengths[i];j++)

arr[i][j] = rand() % 100 + 1;

return arr;

}

//To free the allocated memory:

void destroyArray(float** arr)

{

free(*arr);

free(arr);

}

int main()
{

float **arrayFloat; //array of arrays variable to hold the float values

int rowlength,colLenArr[rowlength];

rowlength = 3;
for(int i=0; i<3;i++)
colLenArr[i] = i+1;
arrayFloat = AllocateArrayOfArrays(rowlength, colLenArr);
for(i =0; i<rowlength;i++)
{

for(int j=0;j<colLenArr[i];j++)

printf("%.2f ", arrayFloat[i][j]);
printf("\n");   
}
destroyArray(arrayFloat);
}