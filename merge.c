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