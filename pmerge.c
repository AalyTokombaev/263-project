#include <stdio.h>
#include <stdlib.h>
#include <omp.h>


void paraMerge(int *arr, int start, int mid, int end) {

    // I'm just gonna assume they're sorted 

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

    // maybe we could do odd/even sorting here 
    
    // Do I even need this?
    // split A into odd indices and even indices
    int middle = size_A / 2;
    if (middle % 2 == 1) {
        middle++;
    }
    // hey I coild do this in parallel!
    int *A_even = malloc(sizeof(int*) * middle);
    int *A_odd = malloc(sizeof(int*) * (size_A - middle));


    // for even a_i
    int j = 0;
    for (int i = 0; i < size_A; i++) {
        if (i % 2 == 0) {
            A_even[j] = left[i];
            j++;
        }
    }

    // for odd a_i
    j = 0;
    for (int i = 0; i < size_A; i++) {
        if (i % 2 == 1) {
            A_odd[j] = left[i];
            j++;
        }
    }

    // i don't know if I need this
    middle = size_B / 2;
    if (middle % 2 == 1) {
        middle++;
    }

    int *B_even = malloc(sizeof(int*) * middle);
    int *B_odd = malloc(sizeof(int*) * (size_B - middle));

    j = 0;
    for (int i = 0; i < size_B; i++) {
        if (i % 2 == 0) {
            B_even[j] = right[i];
            j++;
        }
    }








}

int main(){
    return 0;
}