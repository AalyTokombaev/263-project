#include <stdio.h>
#include <stdlib.h>

void printArray(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]); 
    }
}

void merge(int* arr, int start, int middle, int end) {
    // this will later be parallelzed

    //  prints for debugging, I'll keep them here in case I'll need to debug again later.
    /*
    printf("In merge\n");
    printf("start: %d, middle: %d, end: %d\n", start, middle, end);
    printf("part arr: ");
    for (int i = start; i < end; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    printf("arr: ");
    printArray(arr, 14);
    printf("\n");
    */


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

    //  prints for debugging, I'll keep them here in case I'll need to debug again later.
    /*
    printf("in mergesort\n");
    printf("start: %d, end: %d\n", start, end);
    printf("part arr: ");
    for (int i = start; i < end; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    printf("arr: ");
    printArray(arr, 14);
    printf("\n");
    */



    if (start < end) {
        // find the middle and mergesort the left and right
        int middle = start + (end - start) / 2;
        mergeSort(arr, start, middle); 
        mergeSort(arr, middle + 1, end);
        merge(arr, start, middle, end);
    }
    
}





// I mean merge sort is quote simple
int main(){
    int arr[14] = {2, 1, 3, 6, 5, 4, 1, 2, 9, 8, 8, 7, 1, 2};

    printf("arr before sort: ");
    printArray(arr, 14);
    printf("\n");

    mergeSort(arr, 0, 13);
    printf("arr after sort: ");
    printArray(arr, 14);
    printf("\n");
    
    return 0;

}


// p: start index, r = end index 
// mergesort interval [p, r]
