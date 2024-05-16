#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// Function to merge two sorted arrays
void merge(int *array, int left, int middle, int right) {
    int first_number = middle - left + 1;
    int last_number = right - middle;

    // Create temporary arrays
    int left_array[first_number], right_array[last_number];

    for (int i = 0; i < first_number; i++)
        left_array[i] = array[left + i];
    for (int j = 0; j < last_number; j++)
        right_array[j] = array[middle + 1 + j];

    // Merge the temporary arrays back into array[left_array.right_array]
    int i = 0, j = 0, k = left;
    while (i < first_number && j < last_number) {
        if (left_array[i] <= right_array[j]) {
            array[k] = left_array[i];
            i++;
        } else {
            array[k] = right_array[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of left_array[], if any
    while (i < first_number) {
        array[k] = left_array[i];
        i++;
        k++;
    }

    // Copy the remaining elements of right_array[], if any
    while (j < last_number) {
        array[k] = right_array[j];
        j++;
        k++;
    }
}

// Main function to perform merge sort
void mergeSort(int *array, int left, int right) {
    if (left < right) {
        // Find the middle point
        int middle = left + (right - left) / 2;

        // Sort first and second halves
        mergeSort(array, left, middle);
        mergeSort(array, middle + 1, right);

        // Merge the sorted halves
        merge(array, left, middle, right);
    }
}


int main(){

    int* array;
    int array_size;
    srand(time(NULL));
    printf("What size do you want the array to be:");
    scanf("%d", &array_size);
    array = malloc(sizeof(int) * array_size);
    for (int i = 0; i < array_size; ++i) {
      array[i] = rand() % 100;
    }


    for (int i = 0; i < array_size; ++i) {
        printf("%d", array[i]);
    }


    clock_t start = clock();
    for (int i = 0; i < array_size; ++i) {
        for (int j = 0; j < array_size; ++j) {
            if (array[i]>array[j]){
                int temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
    }
    clock_t end = clock();

    double elapsed = (double)(end-start) / CLOCKS_PER_SEC;
    printf("%f seconds", elapsed);



    free(array);
    return 0;
}