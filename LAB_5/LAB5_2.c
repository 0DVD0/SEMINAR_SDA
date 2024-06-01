#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * This function takes an integer pointer to an array and its size as parameters.
 * It then iterates over each element of the array and assigns a random number between 0 and 999 to it.
 *
 * @param arr Pointer to the array to be initialized.
 * @param size Size of the array.
 */
void init_array(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 1000;
    }
}

/**
 * This function prints the elements of an integer array to the console.
 *
 * @param arr Pointer to the array to be printed.
 * @param size Size of the array.
 */
void print_array(int *arr, int size) {
    printf("Array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

/**
 * This function frees the alocated memory of the array.
 * @param arr the array
 **/
void free_array(int *arr) {
    free(arr);
}

/**
* This function performs a linear search on an integer array.
*
* @param array Pointer to the array to be searched.
* @param array_size Size of the array.
* @param element_to_search Element to search for in the array.
*
*/
void liniar_search(int *array, int array_size, int element_to_search){
    for(int i = 0; i < array_size; i++){
        if(array[i] == element_to_search){
            printf("Element found at index %d\n", i);
            return;
        }
    }
    printf("Element not found\n");
}

/**
 * This function merges two subarrays of the array.
 *
 * @param array Pointer to the array to be sorted.
 * @param left The starting index of the first subarray.
 * @param middle The ending index of the first subarray and starting index of the second subarray.
 * @param right The ending index of the second subarray.
 *
 */
void merge(int *array, int left, int middle, int right) {
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
/**
* This function performs a merge sort on an integer array, preparing it for the binary search.
*
* @param array Pointer to the array to be sorted.
* @param left The starting index of the array to be sorted.
* @param right The ending index of the array to be sorted.
*
*/
void merge_sort(int *array, int left, int right) {
    if (left < right) {
        int middle = left + (right - left) / 2;

        merge_sort(array, left, middle);
        merge_sort(array, middle + 1, right);

        merge(array, left, middle, right);
    }
}

/**
 * This function performs a binary search on an integer array.
 *
 * @param array Pointer to the array to be searched.
 * @param element_to_search Element to search for in the array.
 * @param low The lower bound of the search range.
 * @param high The upper bound of the search range.
 *
 */
void binary_search(int *array, int element_to_search, int low, int high) {
    if (high >= low) {
        int mid = low + (high - low) / 2;


        if (array[mid] == element_to_search) {
            printf("Found element in position %d\n", mid);
            return;
        }

        if (array[mid] > element_to_search) {
            return binary_search(array, element_to_search, low, mid - 1);
        }else {
            return binary_search(array, element_to_search, mid + 1, high);
        }
    }

    printf("Element not found in array\n");
}

/**
 * This function displays the menu options for the Fibonacci program.
 * It prints the available choices to the console.
 *
 */
void show_menu() {
    printf("1. Initialize Array with Random Numbers\n");
    printf("2. Print Array\n");
    printf("3. Liniar Search\n");
    printf("4. Binary Search\n");
    printf("5. Free Memory\n");
    printf("0. Exit\n");
    printf("\nEnter your choice: ");
}

int main() {
    srand(time(NULL));
    int choice, size_of_array, element_to_search;
    int *array;
    double time;
    clock_t start, end;
    do {
        show_menu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the size of the array: ");
                scanf("%d", &size_of_array);
                array = (int *)malloc(size_of_array * sizeof(int));
                init_array(array, size_of_array);
                printf("Array initialized with random numbers.\n");
                break;
            case 2:
                print_array(array, size_of_array);
                break;
            case 3:
                printf("Give an element to search:");
                scanf("%d",&element_to_search );
                start = clock();
                liniar_search(array,size_of_array, element_to_search);
                end = clock();
                time = (double)(end - start) / CLOCKS_PER_SEC;
                printf("time needed for searching: %f seconds\n", time);
                break;
            case 4:
                merge_sort(array,0, size_of_array-1);
                printf("Give an element to search:");
                scanf("%d",&element_to_search );
                start = clock();
                binary_search(array, element_to_search, 0, size_of_array - 1);
                end = clock();
                time = (double)(end - start) / CLOCKS_PER_SEC;
                printf("time needed for searching: %f seconds\n", time);
                break;
            case 5:
                free_array(array);
                printf("Memory freed.\n");
                break;
            case 0:
                free_array(array);
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 0);

    return 0;
}
