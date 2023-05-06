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
    printf("at the very start of pmerge:: start: %d, mid: %d, end: %d\n", start, mid, end);
    // I think we'll have to pass in a shared array here to collet the results;
    
    // print original aray
    printf("original array part: ");
    for (int i = start; i < end + 1; i++) {
        printf(" %d ", arr[i]);
    }
    printf("\n");
    printf("and start: %d, mid: %d, end: %d\n", start, mid, end);
    printf("************************\n");


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

    printf("size_A: %d, size_B: %d\n", size_A, size_B);

    // let's do some cases


    // case 1: size_A == size_B == 1
    if (end + 1  - start == 2) {
        printf("in the case where size_A == size_B == 1\n");
        printf("we're about to swap some elements\n");
        printArray(arr, start, end + 1);
        if (arr[start] > arr[end]) {
            int temp = arr[start];
            arr[start] = arr[end];
            arr[end] = temp;
        }
        printf("we have swapped some elements\n");
        printArray(arr, start, end + 1);
        printf("--------case A == B == 1 end run--------\n");
        return;
    }

    if (end == mid) {
        printf("===in the case where end == mid===\n");
        printf("--------case end == mid end run--------\n");
        return;
    }
    
    // case 2: size_A == 1 and size_B == 0
    if (size_A == 1 && size_B  == 0)  {
        printf("in the case where size_A == 1 and size_B == 0\n");
        printf("--------case A = 1  B = 0 end run--------\n");
        return;
    }
    if (size_A == 0 && size_B == 1) {
        printf("in the case where size_A == 0 and size_B == 1\n");
        printf("--------case A = 0  B = 1 end run--------\n");

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

    printf("size_even: %d, size_odd: %d\n", size_even, size_odd);


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


    printf("evens: ");
    printArray(evens, 0, size_even);
    printf("odds: ");
    printArray(odds, 0, size_odd);

    // merge evens and odds 

    
    int mi = size_even / 2;
    printf("running pmerge on evens\n");
    pmerge(evens, 0, mi - 1, size_even - 1);
    printf("heww0...?\n");
    printArray(evens, 0, size_even);

    mi = size_odd / 2;
    printf("Running pmerge on odds\n");
    pmerge(odds, 0 , mi - 1, size_odd - 1);

    printf("heww0...? for B!!!!\n");
    printArray(odds, 0, size_odd_A + size_odd_B);
    


    // 
    /*
    int k = start;
    printf("*** Changing value! ***\n");
    printf("arr[k: %d] changed from %d ", k, arr[k]);
    arr[k] = evens[0];
    printf("to %d\n", arr[k]);
    */
   
    printf("Before we start doing the E shit \n:");
    printf("array from start %d to end %d: ", start, end);
    printArray(arr, start, end+1);
    printf("\n");

    printf("evens: ");
    printArray(evens, 0, size_even);
    printf("\n");

    printf("odds: "); 
    printArray(odds, 0, size_odd);
    printf("\n");


    // now we can do the e shit again
    printf("starting to do the e shit: \n");
    printArray(arr, start, end +1);
    printf("\n");



    if (size_even == 2 && size_odd == 2) {
        printf("-------Doing the E shit when both lists are of size 2 --------\n");
        printArray(arr, start, end+1);
        arr[start] = evens[0];
        arr[start + 1] = min(evens[1], odds[0]);
        arr[start + 2] = max(evens[1], odds[0]);
        arr[start + 3] = odds[1];
        printArray(arr, start, end + 1);
        printf("-------- E shit of case 2 over --------\n");
        return;
    }
    



     /* 
        I'm so dumb 
        I'm so dumb 
        I'm so dumb 
        I'm so dumb 
        I'm so dumb 
        I'm so dumb 
        I'm so dumb 
        I'm so dumb 
        I'm so dumb 
        I'm so dumb 

        my loops don't work because size of D and C are not equal to end 
     */
    arr[start] = evens[0];
    for (int i = 1; i < end; i+=2){
        printf("i = %d\n", i);
        printf("evens: ");
        printArray(evens, 0, size_even);
        printf("odds: ");
        printArray(odds, 0, size_odd);
        printArray(arr, start, end + 1);

        printf("evens[i] : %d, odds[i-1] : %d\n", evens[i], odds[i-1]);
        if (evens[i] < odds[i-1]){
            printf("first condition\n");
            arr[start + i - 1] = evens[i];
            arr[start + i] = odds[i-1];
        }
        else {
            arr[start + i] = evens[i];
            arr[start + i - 1] = odds[i - 1];
        }

        printArray(arr, start, end + 1);

    }


    arr[end] = odds[size_odd-1];
    printf("done doing the e shit!\n");


    printf("--------------------- run end ----------------\n");


}
