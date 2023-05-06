#include <stdio.h>
#include <stdlib.h>
#include "mergesort.c"



void npmerge(int *arr, int start, int mid, int end){
    int sizeA = mid - start + 1;
    int sizeB = end - mid;

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
    if (sizeA == 1 && sizeB  == 0)  {
        printf("in the case where size_A == 1 and size_B == 0\n");
        return;
    }
    if (sizeA == 0 && sizeB == 1) {
        printf("in the case where size_A == 0 and size_B == 1\n");

        return;
    }


    int *A = malloc(sizeof(int) * sizeA);
    for (int i = 0; i < sizeA; i++) {
        A[i] = arr[start + i];
    }

    int *B = malloc(sizeof(int) * sizeB);
    for (int i = 0; i < sizeB; i++) {
        B[i] = arr[mid + 1 + i];
    }


    int size_even_A = sizeA / 2;
    if (sizeA % 2 != 0) {
        size_even_A++;
    }
    int size_odd_A = sizeA - size_even_A;

    int size_even_B = sizeB / 2;
    if (sizeB % 2 != 0) {
        size_even_B++;
    }
    int size_odd_B = sizeB - size_even_B;

    int size_even = size_even_A + size_even_B;
    int size_odd = size_odd_A + size_odd_B;
    
    int *C = malloc(sizeof(int) * size_even);
    int *D = malloc(sizeof(int) * size_odd);


    // empty A fisrt
    int j = 0;
    for (int i = 0; i < sizeA; i++){
        if (i % 2 == 0){
            C[j] = A[j];
        }

    }
    

}