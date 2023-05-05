#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "mergesort.c"

int min(int a, int b) {
    if (a < b) {
        return a;
    }
    else {
        return b;
    }
}

int max(int a, int b) {
    if (a < b) {
        return b;
    }
    else {
        return a;
    }
}

void paraMerge(int *arr, int start, int mid, int end) {

    // I think we'll have to pass in a shared array here to collet the results;


    // print original aray
    printf("original array: ");
    for (int i = start; i < end; i++) {
        printf(" %d ", arr[i]);
    }


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

    // print right and left 
    printf("array A: "); 
    printArray(left, size_A);

    printf("array B: ");
    printArray(right, size_B);

    // maybe we could do odd/even sorting here 
    
    // Do I even need this?
    // split A into odd indices and even indices
    int size_even_A = size_A / 2;
    if (size_even_A % 2 == 1) {
        size_even_A++;
    }
    int rest_A = size_A - size_even_A;

    // hey I coild do this in parallel!
    int *A_even = malloc(sizeof(int*) * size_even_A);
    int *A_odd = malloc(sizeof(int*) * (rest_A));

    // print even and odd A 
    print("A_even: ");
    printArray(A_even, size_even_A);
    print("A_odd: ");
    printArray(A_odd, rest_A);



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
    int size_even_B = size_B / 2;
    if (size_even_B % 2 == 1) {
        size_even_B++;
    }
    int rest_B = size_B - size_even_B;

    int *B_even = malloc(sizeof(int*) * size_even_B);
    int *B_odd = malloc(sizeof(int*) * rest_B);
    
    // for even b_i
    j = 0;
    for (int i = 0; i < size_B; i++) {
        if (i % 2 == 0) {
            B_even[j] = right[i];
            j++;
        }
    }

    // for odd b_i
    j = 0;
    for (int i = 0; i < size_B; i++) {
        if (i % 2 == 1) {
            B_odd[j] = right[i];
            j++;
        }
    }

    //print even and odd B
    print("B_even: ");
    printArray(B_even, size_even_B);
    print("B_odd: ");
    printArray(B_odd, rest_B);

    // now that we have the arrays, we can merge A_even and B_even
    
    int size_C = size_even_A + size_even_B;
    int *C = malloc(sizeof(int*) * size_C);

    // merge A_even and B_even
    int i = 0;
    int k = 0;
    int l = 0;
    while (i < size_C) {
        if (A_even[k] < B_even[l]) {
            C[i] = A_even[k];
            k++;
        } else {
            C[i] = B_even[l];
            l++;
        }
        i++;
    }



    int size_D = rest_A + rest_B;
    int *D = malloc(sizeof(int*) * size_D);

    // merge A_odd and B_odd
    i = 0;
    k = 0;
    l = 0;
    while (i < size_D) {
        if (A_odd[k] < B_odd[l]) {
            D[i] = A_odd[k];
            k++;
        } else {
            D[i] = B_odd[l];
            l++;
        }
        i++;
    }
    //finally let's print C and D
    print("C: ");
    printArray(C, size_C);
    print("D: ");
    printArray(D, size_D);

    int e = size_C + size_D; // size of the original array (I hope)
    int *E = malloc(sizeof(int*) * e);
    // set E[0] to be C[0]
    E[0] = C[0];

    for (int i = 1; i < e - 1; i++){
        if (i % 2 == 0) {
            E[i] = min(C[i + 1], D[i]);
        } else {
            E[i] = max(C[i + 1], D[i]);
        }
    }

    // set last element of E to be last element of D 
    E[e - 1] = D[size_D - 1];

    // let's print E
    printf("array E: ");
    printArray(E, e);

    // finally let's copy E into the original array
    for (int i = 0; i < e; i++) {
        arr[start + i] = E[i];
    }

    // God I hope this works


}
