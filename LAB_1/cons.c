#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max 10

typedef struct car{
    char *brand;
    int year_of_brand;
    int price;
}car;

/**
 * This function reads each character from the file until the end-of-file (EOF) is reached.
 *
 * @param fp A pointer to the file to be counted.
 * @return The number of lines in the file.
 */
int count_lines(FILE* fp) {
    char ch;
    int lines = 0;
    while(!feof(fp))
    {
        ch = fgetc(fp);
        if(ch == '\n')
        {
            lines++;
        }
    }
    rewind(fp);
    return ++lines;
}

/**
 * This function prints the content of a car array to the console.
 *
 * @param car_array A pointer to the car array to be printed.
 * @param nr_lines The number of elements in the car array.
 *
 */
void print_array(car *car_array, int nr_lines){
    for(int i = 0; i < nr_lines; i++) {
        printf("%s %d %d\n", car_array[i].brand, car_array[i].year_of_brand, car_array[i].price);
    }
    printf("\n");
}

/**
 * This function searches for a car in the array based on the year of manufacture.
 * It prints the details of the found car(s) and their positions in the array.
 * If no car is found, it prints a message indicating that no car was found.
 *
 * @param nr_lines The total number of cars in the array.
 * @param year_in The year of manufacture to search for.
 * @param car_array A pointer to the array of cars.
 *
 */
void find_car_by_year(int nr_lines,int year_in,car *car_array){
    int count=0;
    for(int i=0; i<nr_lines; i++){
        if (year_in == car_array[i].year_of_brand ){
            printf("masina a fost gasita in pozitia %d \n%s %d %d \n", i, car_array[i].brand , car_array[i].year_of_brand, car_array[i].price);
            ++count;
        }
    }
    if (count == 0){
        printf(" nicio masina nu a fost gasita dupa anul dat");
    }
    printf("\n");
}

/**
 * This function searches for a car in the array based on the brand.
 * It prints the details of the found car(s) and their positions in the array.
 * If no car is found, it prints a message indicating that no car was found.
 *
 * @param nr_lines The total number of cars in the array.
 * @param brand_in The brand to search for.
 * @param car_array A pointer to the array of cars.
 *
 */
void find_car_by_brand(int nr_lines,char *brand_in,car *car_array){
    int count=0;
    for(int i=0; i<nr_lines; i++){
        if (strcmp(brand_in, car_array[i].brand) == 0){
            printf("%s %d %d\n", car_array[i].brand , car_array[i].year_of_brand, car_array[i].price);
            ++count;
        }
    }
    if (count == 0){
        printf(" nicio masina nu a fost gasita dupa numele dat");
    }
    printf("\n");
}

/**
 * This function searches for a car in the array based on the price.
 * It prints the details of the found car(s) and their positions in the array.
 * If no car is found, it prints a message indicating that no car was found.
 *
 * @param nr_lines The total number of cars in the array.
 * @param price_in The price to search for.
 * @param car_array A pointer to the array of cars.
 *
 */
void find_car_by_price(int nr_lines,int price_in,car *car_array){
    int count=0;
    for(int i=0; i<nr_lines; i++){
        if (price_in == car_array[i].price ){
            printf("%s %d %d\n", car_array[i].brand , car_array[i].year_of_brand, car_array[i].price);
            ++count;
        }
    }
    if (count == 0){
        printf(" nicio masina nu a fost gasita dupa pretul dat");
    }
    printf("\n");
}

/**
 * This function swaps the content of two car structures.
 *
 * @param a A pointer to the first car structure.
 * @param b A pointer to the second car structure.
 *
 */
void swap_elements(car *a, car *b){
car temp=*a;
*a = *b;
*b = temp;
}

/**
 * This function sorts the car array based on the price in ascending order.
 * It uses the bubble sort algorithm to compare adjacent elements and swap them if necessary.
 * After each pass, the largest element "bubbles" up to its correct position at the end of the array.
 * The process is repeated until the entire array is sorted.
 *
 * @param nr_lines The total number of cars in the array.
 * @param car_array A pointer to the array of cars.
 *
 */
void sort_by_price(int nr_lines, car *car_array){
    for (int i = 0; i < nr_lines-1 ; ++i) {
        for (int j = 0; j < nr_lines-i-1 ; ++j) {
            if(car_array[j].price > car_array[j + 1].price){
                swap_elements(&car_array[j], &car_array[j + 1]);
            }
        }
    }
    print_array(car_array, nr_lines);
}

/**
 * This function sorts the car array based on the year of manufacture in ascending order.
 * It uses the bubble sort algorithm to compare adjacent elements and swap them if necessary.
 * After each pass, the largest element "bubbles" up to its correct position at the end of the array.
 * The process is repeated until the entire array is sorted.
 *
 * @param nr_lines The total number of cars in the array.
 * @param car_array A pointer to the array of cars.
 */
void sort_by_year(int nr_lines,car *car_array){
    for (int i = 0; i < nr_lines-1 ; ++i) {
        for (int j = 0; j < nr_lines-i-1 ; ++j) {
            if(car_array[j].year_of_brand > car_array[j + 1].year_of_brand){
                swap_elements(&car_array[j], &car_array[j + 1]);
            }
        }
    }
    print_array(car_array, nr_lines);
}

/**
 * This function is used as a comparison function for the qsort() function.
 * It compares two car structures based on their brand names.
 *
 * @param p A pointer to the first car structure to be compared.
 * @param q A pointer to the second car structure to be compared.
 *
 * @return An integer less than, equal to, or greater than zero if the brand name of the first car is found, respectively, to be less than, to match, or to be greater than the brand name of the second car.
 */
int compare_elements(const void* p, const void* q)
{
    return strcmp(((car*)p)->brand,((car*)q)->brand);
}

/**
 * This function sorts the car array based on the brand names in ascending order.
 * It uses the qsort() function from the C standard library to perform the sorting.
 * The compare_elements() function is used as the comparison function for qsort().
 * After sorting, the sorted array is printed using the print_array() function.
 *
 * @param nr_lines The total number of cars in the array.
 * @param car_array A pointer to the array of cars.
 *
 */
void sort_by_brand(int nr_lines,car *car_array) {
    qsort(car_array, nr_lines, sizeof(car), compare_elements);
    print_array(car_array, nr_lines);
}

/**
 * This function adds a new car to the array.
 * It prompts the user to input the brand, price, and year of manufacture for the new car.
 * The new car is then added to the end of the array and the updated array is printed.
 *
 * @param nr_lines The current number of cars in the array.
 * @param car_array A pointer to the array of cars.
 *
 */
void add_member(int nr_lines, car *car_array) {

    car new_car;
    new_car.brand = malloc(sizeof(char) * max);
    if (new_car.brand == NULL) {
        printf("Alocarea de memorie a esuat");
        return;
    }
    printf("Introdu numele (fara spatii): ");
    scanf("%s", new_car.brand);

    printf("Introdu pretul: ");
    scanf("%d", &new_car.price);

    printf("Introdu anul fabricatiei: ");
    scanf("%d", &new_car.year_of_brand);


    car_array[nr_lines] = new_car;

    (nr_lines)++;

    print_array(car_array, nr_lines);
}

/**
 * This function deletes a car from the array based on the user's input position.
 * It prompts the user to enter the position of the car to be deleted.
 * If the position is valid, it frees the memory allocated to the brand name of the car at that position.
 * Then, it shifts all the subsequent cars in the array to fill the gap, effectively deleting the selected car.
 * Finally, it decrements the total number of cars in the array and prints the updated array.
 *
 * @param nr_lines The current number of cars in the array.
 * @param car_array A pointer to the array of cars.
 *
 */
void delete_member(int nr_lines, car *car_array) {
        int pos;
        printf("Introduceti pozitia masinii de sters (1-%d): ", nr_lines);
        scanf("%d", &pos);

        if (pos < 1 || pos > nr_lines) {
            printf("Pozitie invalida.\n");
            return;
        }

        free(car_array[pos - 1].brand);

        for (int i = pos - 1; i < nr_lines - 1; i++) {
            car_array[i] = car_array[i + 1];
        }

        (nr_lines)--;

    print_array(car_array, nr_lines);
    }

int main() {
    int an, pret;
    char *brand;
    car *car_array;
    brand= malloc(sizeof(char) * 10);
    FILE *f = fopen("C:\\Users\\Asus\\Desktop\\SEMINAR SDA\\LAB_1\\masini.txt", "rw+");
    if (f == NULL) {
        printf("fisierul nu poate fii citit");
        return 0;
    }

    int nr_of_lines = count_lines(f);
    car_array= malloc(sizeof(car) * nr_of_lines);
    for (int i = 0; i < nr_of_lines; i++) {
        car_array[i].brand = malloc(sizeof(char) * 10);
        fscanf(f, "%s %d %d", car_array[i].brand, &car_array[i].year_of_brand, &car_array[i].price);
    }
    fclose(f);

    print_array(car_array, nr_of_lines);

    int option,opt_sort,alegere;
    do  {
        printf("alegeti ce vreti sa faceti cu matricea data:\n1(gasiti o masina anumita dupa valoare)\n2(sortarea elementelor dupa un camp anumit)\n3(inserati un element nou in tablou)\n4(stergeti un element)\n5(afisati lista)\n0(iesiti):\n");
        scanf("%d", &option);
        switch (option) {
            case 1:
                do {
                    printf("\nalegeti dupa ce informatii vrei sa gasisiti masina: \n1(brand)\n2(an)\n3(pret)\n4(iesiti):\n");
                    scanf("%d", &alegere);
                    switch (alegere) {
                            case 1:
                                printf("\ndati un nume pentru cautare:\n");
                            scanf("%s", brand);
                            find_car_by_brand(nr_of_lines, brand, car_array);
                            break;
                            case 2:
                                printf("dati un an pentru cautare:");
                            scanf("%d", &an);
                            find_car_by_year(nr_of_lines, an, car_array);
                            break;
                            case 3:
                                printf("dati un pret pentru cautare:");
                            scanf("%d", &pret);
                            find_car_by_price(nr_of_lines, pret, car_array);
                            break;
                            case 4:
                                printf("ne intoarcem in meniul principal...\n");
                            break;
                            default:
                                printf("dati un numar corescunzator");
                        }
                } while (alegere != 4);
                break;
            case 2:
                do {
                printf("\ndupa care camp vreti sa sortati:\n1(brand)\n2(year)\n3(price)\n4(inapoi)\n");
                scanf("%d", &opt_sort);
                    switch (opt_sort) {
                        case 1:
                            printf("lista sortata dupa brand:\n");
                            sort_by_brand(nr_of_lines, car_array);
                            break;
                        case 2:
                            printf("lista sortata dupa an\n");
                            sort_by_year(nr_of_lines, car_array);
                            break;
                        case 3:
                            printf("lista sortata dupa pret\n");
                            sort_by_price(nr_of_lines, car_array);
                            break;
                        case 4:
                            printf("iesim in meniu...\n");
                            break;
                    }
                } while (opt_sort != 4);
                break;
            case 3:
                add_member(nr_of_lines, car_array);
                break;
            case 4:
                delete_member(nr_of_lines, car_array);
                break;
            case 5:
                printf("LISTA DISPONIBILA:\n");
                print_array(car_array, nr_of_lines);
                break;
            case 0:
                printf("iesim din program...");
                break;
        }
    }while(option != 0);
    free(brand);
    free(car_array);
return 0;
}