#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max 10

struct car{
    char *brand;
    int year_of_brand;
    int price;
};

/**
* This function reads a file character by character and counts the number of newline characters ('\n').
* It then rewinds the file pointer to the beginning of the file and returns the total number of lines.
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
 * This function searches for a car in the vector based on the given year.
 * It prints the details of the found cars and their positions in the vector.
 * If no car is found, it prints a message indicating that no car was found.
 *
 * @param nr_lines The total number of cars in the vector.
 * @param year_in The year to search for.
 * @param car_array A pointer to the vector of cars.
 *
 */
void find_car_by_year(int nr_lines,int year_in,struct car *car_array){
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
 * This function searches for a car in the vector based on the given brand.
 * It prints the details of the found cars and their positions in the vector.
 * If no car is found, it prints a message indicating that no car was found.
 *
 * @param nr_lines The total number of cars in the vector.
 * @param brand_in The brand to search for.
 * @param car_array A pointer to the vector of cars.
 *
 */
void find_car_by_brand(int nr_lines,char *brand_in,struct car *car_array){
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
 * This function searches for a car in the vector based on the given price.
 * It prints the details of the found cars and their positions in the vector.
 * If no car is found, it prints a message indicating that no car was found.
 *
 * @param nr_lines The total number of cars in the vector.
 * @param price_in The price to search for.
 * @param car_array A pointer to the vector of cars.
 *
 */
void find_car_by_price(int nr_lines,int price_in,struct car *car_array){
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


int main() {
    int an, pret;
    char brand[max];

    FILE *f = fopen("C:\\Users\\Asus\\Desktop\\SEMINAR SDA\\LAB_1\\masini.txt", "rw+");
    if (f == NULL) {
        printf("fisierul nu poate fii citit");
        return 0;
    }

    int nr_of_lines = count_lines(f);
    struct car car_array[nr_of_lines];
    for (int i = 0; i < nr_of_lines; i++) {
        car_array[i].brand = malloc(sizeof(char) * 10);
        fscanf(f, "%s %d %d", car_array[i].brand, &car_array[i].year_of_brand, &car_array[i].price);
    }
    fclose(f);

    printf("lista disponibila\n");
    for (int i = 0; i < nr_of_lines; i++) {
        printf("%s %d %d\n", car_array[i].brand, car_array[i].year_of_brand, car_array[i].price);
    }

    while (1) {
        int alegere;
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
              return 0;
            default:
                printf("dati un numar corescunzator\n");
        }
    }
}