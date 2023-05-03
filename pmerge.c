#include <stdio.h>
#include <stdlib.h>
#include <omp.h>


void paraMerge(int *arr, int start, int mid, int end) {

    // first we need to define the arrays A and B
    int size_A = mid - start + 1; // size of left array we want to merge;
    int size_B = end  - mid; // size of right array we want to merge;

    int *left = malloc(sizeof(int*) * size_A);
    int *right = malloc(sizeof(int*) * size_B);

    // copy the elements into the arrays
    for (int i = 0; i < size_A; i++) {
        left[i] = arr[start + i];
    }
    for (int j = 0; j < size_B; j++) {
        right[j] = arr[mid + 1  + j];
    }

    // now we do the fun algorithm 

    // we should divide the arrays into p parts 
    // we should have p threads
    // A = A_1, ..., A_p
    // B = B_1, ..., B_p
    
    // ranges [la, ua] and [lb, ub]
    int la = 0;
    int lb = 0;

    int ua = size_A - 1;
    int ub = size_B - 1;

    // middles
    int ma = (la + ua) / 2;
    int mb = (lb + ub) / 2;

    // compare middles

    




}

int main(){
    return 0;
}