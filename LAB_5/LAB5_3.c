#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * This function calculates the Fibonacci number at the specified index using an iterative approach.
 * It also measures the time taken to execute the calculation.
 *
 * @param index The index of the Fibonacci number to calculate.
 */
void calculate_fib_num_by_index(int index){
    clock_t start, end;
    double time;
    start = clock();
   unsigned long long int next = 0, previous = 1, previous_previous = 0;

    if(index == 1){
        printf("%llu", previous_previous);
    }
    if(index == 2 ){
        printf("%llu", previous);
    }
    for(int i = 2; i <= index; ++i){
        next = previous + previous_previous;
        previous_previous = previous;
        previous = next;
    }
    printf("%llu\n", next);
    end = clock();
    time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Needed time to execute: %lf seconds\n", time);
}

/**
 * This function displays the menu options for the Fibonacci program.
 * It prints the available choices to the console.
 *
 */
void show_menu() {
    printf("1. Calculate Fibonacci number by index\n");
    printf("0. Exit\n");
    printf("\nEnter your choice: ");
}

int main() {
    int choice, index_of_fibonacci;
    do {
        show_menu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the index of the fibonacci number: ");
                scanf("%d", &index_of_fibonacci);
               calculate_fib_num_by_index(index_of_fibonacci);
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
