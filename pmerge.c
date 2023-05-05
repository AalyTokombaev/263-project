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

void pmerge(int *arr, int start, int mid, int end) {
    printf("at the very start of pmerge:: start: %d, mid: %d, end: %d\n", start, mid, end);
    

    


    // let's do some base cases 


    // I think we'll have to pass in a shared array here to collet the results;

    
    printf("running pmerge with array: \n");
    // print original aray
    printf("original array part: ");
    for (int i = start; i < end+ 1; i++) {
        printf(" %d ", arr[i]);
    }
    printf("\n");
    printf("and start: %d, mid: %d, end: %d\n", start, mid, end);
    printf("************************\n");


    // I'm just gonna assume they're sorted 

    // first we need to define the arrays A and B
    int size_A = mid - start + 1; // size of left array we want to merge;
    int size_B = end - mid; // size of right array we want to merge;

    printf("size_A: %d, size_B: %d\n", size_A, size_B);

    // let's do some cases


    // case 1: size_A == size_B == 1
    if (end + 1 - start == 2) {
        printf("in the case where size_A == size_B == 1\n");
        if (arr[start] > arr[end]) {
            int temp = arr[start];
            arr[start] = arr[end];
            arr[end] = temp;
        }
        printf("--------case end run--------\n");
        return;
    }

    if (end == mid) {
        printf("===in the case where end == mid===\n");
        return;
    }
    
    // case 2: size_A == 1 and size_B == 0
    if (size_A == 1 && size_B  == 0)  {
        printf("in the case where size_A == 1 and size_B == 0\n");
        return;
    }
    if (size_A == 0 && size_B == 1) {
        printf("in the case where size_A == 0 and size_B == 1\n");

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

    printf("A: ");
    printArray(A, 0, size_A);

    printf("B: ");
    printArray(B, 0, size_B);

    // find even a_i and even b_i
    /* If the length of the array is odd, then the ammount of evens will be one larger than the ammount of odds */
    int size_even_A = size_A / 2;
    if (size_A % 2 != 0) {
        size_even_A++;
    }
    int size_even_B = size_B / 2;
    if (size_B % 2 != 0) {
        size_even_B++;
    }


    printf("size_even_A: %d, size_even_B: %d\n", size_even_A, size_even_B);


    // No we can find the even a's and b's 

    int *evens = malloc((size_even_A + size_even_B) * sizeof(int*));

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
            printf("%d, %d, %d\n", i, B[i], j-1);
            odds[j - 1 + size_odd_A] = B[i];
        }
    }

    printf("evens: ");
    printArray(evens, 0, size_even_A + size_even_B);
    printf("odds: ");
    printArray(odds, 0, size_odd_A + size_odd_B);

    // merge evens and odds 

    int mi = size_even_A + size_even_B;
    pmerge(evens, 0, mi /2  , size_even_A + size_even_B - 1);
    printf("heww0...?\n");
    printArray(evens, 0, size_even_A + size_even_B);

    mi = size_odd_A + size_odd_B;

    pmerge(odds, mi/2, mi - 1, size_odd_A + size_odd_B - 1);
    printf("heww0...? for B!!!!\n");
    printArray(odds, 0, size_odd_A + size_odd_B);



    int *e = malloc((end+1) * sizeof(int*));

    e[0] = evens[0];
    for (int i = 1; i < end; i += 2) {
        if (evens[i+1] < odds[i+1]){
            e[i] = evens[i+1];
            e[i+1] = odds[i];
        } else {
            e[i] = odds[i];
            e[i+1] = evens[i+1];
        }
    
    }

    printf("%d\n", odds[size_odd - 1]);
    e[end-1] = odds[size_odd - 1];

    printf("e: ");
    printArray(e, 0, end);

    printf("--------------------- run end ----------------\n");


}
