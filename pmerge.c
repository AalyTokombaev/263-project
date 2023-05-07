#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "mergesort.c"

int max(int a, int b) {
    if (a > b) {
        return a;
    }
    return b;
}

int min(int a, int b){
    if (a < b) {
        return a;
    }
    return b;
}

void pmerge(int *arr, int start, int mid, int end) {
    // I think we'll have to pass in a shared array here to collet the results;
    
    // print original aray
        

    // I'm just gonna assume they're sorted 

    // first we need to define the arrays A and B

    int size_A = mid - start + 1;
    int size_B = end - mid;
    /*
    if ((end - start + 1) % 2 == 0) {
        size_A = mid - start; // size of left array we want to merge;
        size_B = end - mid + 1; // size of right array we want to merge;
    } else {
        size_A = mid - start + 1; // size of left array we want to merge;
        size_B = end - mid; // size of right array we want to merge;
    }
    */


    // let's do some cases


    // case 1: size_A == size_B == 1
    if (end + 1  - start == 2) {
        if (arr[start] > arr[end]) {
            int temp = arr[start];
            arr[start] = arr[end];
            arr[end] = temp;
        }
        return;
    }

    if (end == mid) {
        return;
    }
    
    // case 2: size_A == 1 and size_B == 0
    if (size_A == 1 && size_B  == 0)  {
        return;
    }
    if (size_A == 0 && size_B == 1) {
        return;
    }

    // now that we've done the base cases we should have two sorted arrays A and B 
    int *A = (int *)malloc(size_A * sizeof(int));
    int *B = (int *)malloc(size_B * sizeof(int));
    
    
    int j = 0;
    for (int i = start; i < mid + 1; i++) {
        A[j] = arr[i];
        j++;
    }
    j = 0;
    for (int i = mid + 1; i < end + 1; i++) {
        B[j] = arr[i];
        j++;
    }


    // find even a_i and even b_i
    /* If the length of the array is odd, then the ammount of evens will be one larger than the ammount of odds */
    int size_even_A = size_A / 2;
    if (size_A % 2 != 0 && size_A != 2) {
        size_even_A++;
    }
    int size_even_B = size_B / 2;
    if (size_B % 2 != 0 && size_B != 2) {
        size_even_B++;
    }


    // printf("size_even_A: %d, size_even_B: %d\n", size_even_A, size_even_B);


    // No we can find the even a's and b's 
    int size_even = size_even_A + size_even_B;

    int *evens = malloc((size_even) * sizeof(int*));

    // int *even_A = malloc(size_even_A * sizeof(int*));
    // int *even_B = malloc(size_even_B * sizeof(int*));
    
    int size_odd_A = size_A - size_even_A;
    int size_odd_B = size_B - size_even_B;

    int size_odd = size_odd_A + size_odd_B;
    int *odds = malloc(size_odd * sizeof(int*));

    // int *odd_A = malloc((size_A - size_even_A) * sizeof(int*));
    // int *odd_B = malloc((size_B - size_even_B) * sizeof(int*));



    // Fill up the odd and even arrays
    j = 0;
    for (int i = 0; i < size_A; i++) {
        if (i % 2 == 0) {
            evens[j] = A[i];
            j++;
        } else {
            odds[j - 1] = A[i];
        }
    }

    j = 0;
    for (int i = 0; i < size_B; i++) {
        if (i % 2 == 0) {
            evens[j + size_even_A ] = B[i];
            j++;
        } else {
            // printf("%d, %d, %d\n", i, B[i], j-1);
            odds[j - 1 + size_odd_A] = B[i];
        }
    }



    // merge evens and odds 
    int mi = size_even / 2;
    pmerge(evens, 0, mi - 1, size_even - 1);

    mi = size_odd / 2;
    pmerge(odds, 0 , mi - 1, size_odd - 1);







    if (size_even == 2 && size_odd == 2) {
        arr[start] = evens[0];
        arr[start + 1] = min(evens[1], odds[0]);
        arr[start + 2] = max(evens[1], odds[0]);
        arr[start + 3] = odds[1];
        return;
    }
    

    # pragma omp for
    for (int i = 1; i < size_even; i++){
        int e = 2*i;
        int o = 2*i - 1;
        arr[start + e] = max(evens[i], odds[i - 1]);
        arr[start + o] = min(evens[i], odds[i - 1]);
    }

    arr[start] = evens[0];
    arr[end] = odds[size_odd-1];
    


}
