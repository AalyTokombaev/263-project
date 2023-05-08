
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define SIZE 16

void printArray(int *arr, int start, int end){
    for (int i = start; i < end; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}


void merge(int* arr, int start, int middle, int end) {

    int size_l = middle - start + 1; // size of left array we want to merge;
    int size_r = end  - middle; // size of right array we want to merge;

    int *left = malloc(sizeof(int*) * size_l);
    int *right = malloc(sizeof(int*) * size_r);

    // copy the left and right arrays
    for (int i = 0; i < size_l; i++) {
        left[i] = arr[start + i];
    }
    for (int j = 0; j < size_r; j++) {
        right[j] = arr[middle + 1  + j];
    }

    int i = 0; // index for left
    int j = 0; // index for right
    int k = start; // index for arr

    // go through each array and merge
    while (i < size_l && j < size_r) {

        if (left[i] <= right[j]) {
            arr[k] = left[i];
            i++;
        } else {
            arr[k] = right[j];
            j++;
        }

        k++;
    }

    // add the rest of the element
    // if is done it should not run 
    while (i < size_l) {
        arr[k] = left[i];
        i++;
        k++;
    }

    while (j < size_r) {
        arr[k] = right[j];
        j++;
        k++;
    }
    // should work
    
}

void mergeSort(int *arr, int start, int end) {

    if (start < end) {
        // find the middle and mergesort the left and right
        int middle = start + (end - start) / 2;
        mergeSort(arr, start, middle); 
        mergeSort(arr, middle + 1, end);
        merge(arr, start, middle, end);
    }
}

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
        

    // first we need to define the arrays A and B
    int size_A = mid - start + 1;
    int size_B = end - mid;
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
    

    for (int i = 1; i < size_even; i++){
        int e = 2*i;
        int o = 2*i - 1;
        arr[start + e] = max(evens[i], odds[i - 1]);
        arr[start + o] = min(evens[i], odds[i - 1]);
    }

    arr[start] = evens[0];
    arr[end] = odds[size_odd-1];
}

void pmergeSort(int *arr, int start, int end) {
    if (start < end) {
        // find the middle and mergesort the left and right
        // int middle = start + (end - start) / 2;
        int middle  = start + (end - start)/ 2;
        // int middle = (start + end) / 2;

        // print start middle and end
        // printf("start: %d, middle: %d, end: %d\n", start, middle, end);
        pmergeSort(arr, start, middle);
        pmergeSort(arr, middle + 1, end);
        // parallel region goes here ;) 
        pmerge(arr, start, middle, end);
    }
    
}



int main(){
    int arr[SIZE] = {1, 3, 2, 6, 4, 5, 8, 7, 10, 9, 12, 11, 14, 13, 16, 15};

    printf("arr before sort: ");
    printArray(arr, 0, SIZE);
    printf("\n");

    pmergeSort(arr, 0, SIZE - 1); // 13 because of 0 indexing, I'm so fuckign stupid
    printf("this is in main: arr after sort: ");
    printArray(arr, 0, SIZE);
    printf("\n");
    
    return 0;

}