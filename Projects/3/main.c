/* COP 3502C Programming Assignment 3
This program is written by: Joanna Folk */

#include<stdlib.h>
#include<stdio.h>
#include	"leak_detector_c.h"

typedef struct Point { 
   int x, y; 
} Point;
Point *my_loc;

/* a function to read the data from in.txt */
Point *ReadData(int *size,int *num_queries,int *t,Point queries[]){
    // allocating memory to the my loaction global variable 
    my_loc=(Point*) malloc(sizeof(Point)); 
    Point *arr;

    char filename[]="in.txt";// filename
    FILE *inputFile;

    //opening the file
    inputFile=fopen(filename,"r");
    if( inputFile == NULL ) {
		printf("Error: opening the file...exiting\n");
        return NULL;
	}

    //reading the file's first line
    fscanf(inputFile,"%d%d%d%d%d",&(my_loc->x),&(my_loc->y),size,num_queries,t);

    // allocating memory to the points array
    arr=(Point*) malloc((*size)*sizeof(Point));

    // reading the locations of people
    for(int i=0;i<*size;i++){
        fscanf(inputFile,"%d%d",&(arr[i].x),&(arr[i].y));
    }
    
    // reading the locations of queries
    for(int i=0;i<*num_queries;i++){
        fscanf(inputFile,"%d%d",&(queries[i].x),&(queries[i].y));
    }
    //closing file
    fclose( inputFile );
    return arr;
}

int compareTo(Point *A, Point *B){

    //if same points
    if(A->x==B->x && A->y==B->y){
        return 0;
    }

    // calculating the square of distance of from my location
    int distA_square=(A->x-my_loc->x)*(A->x-my_loc->x) + (A->y-my_loc->y)*(A->y-my_loc->y);
    int distB_square=(B->x-my_loc->x)*(B->x-my_loc->x) + (B->y-my_loc->y)*(B->y-my_loc->y);

    //if both points are at equal distance from my location
    if(distA_square==distB_square){
        // if different x coordinate
        if(A->x!=B->x)
            return A->x<B->x?-1:1 ;
        // if y coordinate is different
        else 
            return A->y<B->y?-1:1 ;
    }

    // returning -1 if point1 is closer to me than point2 else returning 1
    return distA_square<distB_square?-1:1;

}


int binarySearch(Point arr[], Point *item, int size)
{
    int l = 0, h = size - 1;
    int mid;
    while (l <= h)
    {
        mid = (l + h) / 2;
        // Check if item is present at mid
        if (compareTo(&arr[mid] ,item)==0)
            return mid;
         // If item greater, ignore left half
        if (compareTo(&arr[mid], item)<0)
            l = mid + 1;

        // If item is smaller, ignore right half
        else
            h = mid - 1;
    }
    // if we reach here, then element was
    // not present
    return -1;
}


// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
void merge(Point arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;

    /* create temp arrays */
    Point *L = (Point*) malloc(n1*sizeof(Point));
    Point *R = (Point*) malloc(n2*sizeof(Point));

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];

    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (compareTo(&L[i], &R[j])<0)
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    /* Copy the remaining elements of L[], if there
       are any */
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
    free(L);
    free(R);
}
/* Function to sort an array using insertion sort*/
void insertionSort(Point arr[], int l,int r)
{
    int i, j;
    Point item;
    for (i = l+1; i < r; i++)
    {
         item = arr[i];

        /* Move elements of arr[l..r-1], that are
          greater than key, to one position ahead
          of their current position */
          for(j=i-1; j>=l; j--)
          {
              if(compareTo(&arr[j],&item)<0)
                arr[j+1] = arr[j];
              else
                break;

          }
          arr[j+1] = item;
    }
}
/* l is for left index and r is right index of the
   sub-array of arr to be sorted */
void mergeSort(Point arr[], int l, int r,int t)
{  
     if( r-l<t){
         insertionSort(arr,l,r);
    }
    if (l < r)
    {
        // get the mid point
        int m = (l+r)/2;

        // Sort first and second halves
        mergeSort(arr, l, m,t);
        mergeSort(arr, m+1, r,t);

       // printf("Testing l=%d r=%d m=%d\n", l, r, m);

        merge(arr, l, m, r);
    }
}

/*a  wrapper function to call the merge sort function */
void sort(Point arr[],int size,int t){
    mergeSort(arr, 0, size-1,t);
}


int main(){
    atexit(report_mem_leak);
    FILE *outFile = fopen("out.txt", "w"); 
    int size;int num_queries;int t;
    Point *arr;
    Point queries[200000];

    arr=ReadData(&size,&num_queries,&t,queries);

    sort(arr,size,t);
    for(int i=0;i<size;i++){
        fprintf(outFile,"%d %d\n",arr[i].x,arr[i].y);
    }
    for(int i=0;i<num_queries;i++){
        int ans=binarySearch(arr,&queries[i],size);
        if(ans==-1){
            fprintf(outFile,"%d %d not found\n",queries[i].x,queries[i].y);
        }
        else{
            fprintf(outFile,"%d %d found at rank %d\n",queries[i].x,queries[i].y,ans+1);
        }
    }
    fclose(outFile);
    
    free(my_loc);
    free(arr);

    return 0;
}