#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to initialize the array with random numbers
void init_array(int *arr, int size) {
    srand(time(NULL)); // Initialize random seed
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 100; // Generate random numbers between 0 and 99
    }
}

// Function to print the array
void print_array(int *arr, int size) {
    printf("Array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Function to free dynamically allocated memory
void free_array(int *arr) {
    free(arr);
}

// Function to swap two elements
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Bubble Sort
void bubbleSort(int *arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

// Merge Sort
void merge(int array[], int left, int middle, int right) {
    int n1 = middle - left + 1;
    int n2 = right - middle;

    int left_array[n1], right_array[n2];

    for (int i = 0; i < n1; i++)
        left_array[i] = array[left + i];
    for (int j = 0; j < n2; j++)
        right_array[j] = array[middle + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (left_array[i] <= right_array[j]) {
            array[k] = left_array[i];
            i++;
        } else {
            array[k] = right_array[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        array[k] = left_array[i];
        i++;
        k++;
    }

    while (j < n2) {
        array[k] = right_array[j];
        j++;
        k++;
    }
}

void merge_sort(int array[], int left, int right) {
    if (left < right) {
        int middle = left + (right - left) / 2;

        merge_sort(array, left, middle);
        merge_sort(array, middle + 1, right);

        merge(array, left, middle, right);
    }
}

void show_menu() {
    printf("1. Initialize Array with Random Numbers\n");
    printf("2. Print Array\n");
    printf("3. Bubble Sort\n");
    printf("4. Merge Sort\n");
    printf("5. Free Memory\n");
    printf("0. Exit\n");
    printf("\nEnter your choice: ");
}

int main() {
    int choice, size_of_array;
    int *array;
    clock_t start, end;

    printf("Enter the size_of_array of the array: ");
    scanf("%d", &size_of_array);

    array = (int *)malloc(size_of_array * sizeof(int));

    do {
        show_menu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                init_array(array, size_of_array);
                printf("Array initialized with random numbers.\n");
                break;
            case 2:
                print_array(array, size_of_array);
                break;
            case 3:
                start = clock();
                bubbleSort(array, size_of_array);
                end = clock() - start;
                double time = (double) end/ CLOCKS_PER_SEC;
                printf("time needed for sorting: %f seconds\n", time);
                break;
            case 4:
                merge_sort(array, 0, size_of_array - 1);
                printf("Array sorted using Merge Sort.\n");
                break;
            case 5:
                free_array(array);
                printf("Memory freed.\n");
                break;
            case 0:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 0);

    return 0;
}