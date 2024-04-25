#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max 10

struct car{
    char *brand;
    int year_of_brand;
    int price;
};

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

void find_car_by_year(int nr_lines,int year_in,struct car *vect){
    int count=0;
    for(int i=0; i<nr_lines; i++){
if (year_in == vect[i].year_of_brand ){
    printf("masina a fost gasita in pozitia %d \n%s %d %d \n",i,vect[i].brand , vect[i].year_of_brand, vect[i].price);
    ++count;
}
    }
    if (count == 0){
        printf(" nicio masina nu a fost gasita dupa anul dat");
    }
    printf("\n");
}

void find_car_by_brand(int nr_lines,char *brand_in,struct car *vect){
    int count=0;
    for(int i=0; i<nr_lines; i++){
        if (strcmp(brand_in,vect[i].brand)== 0){
            printf("%s %d %d\n",vect[i].brand , vect[i].year_of_brand, vect[i].price);
            ++count;
        }
    }
    if (count == 0){
        printf(" nicio masina nu a fost gasita dupa numele dat");
    }
    printf("\n");
}

void find_car_by_price(int nr_lines,int price_in,struct car *vect){
    int count=0;
    for(int i=0; i<nr_lines; i++){
        if (price_in == vect[i].price ){
            printf("%s %d %d\n",vect[i].brand , vect[i].year_of_brand, vect[i].price);
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

    FILE *f = fopen("C:\\Users\\Asus\\Desktop\\Labsda1\\masini.txt", "rw+");
    if (f == NULL) {
        printf("fisierul nu poate fii citit");
        return 0;
    }

    int nr_of_lines = count_lines(f);
    struct car vect[nr_of_lines];
    for (int i = 0; i < nr_of_lines; i++) {
        vect[i].brand = malloc(sizeof(char) * 10);
        fscanf(f, "%s %d %d", vect[i].brand, &vect[i].year_of_brand, &vect[i].price);
    }
    fclose(f);

    printf("lista disponibila\n");
    for (int i = 0; i < nr_of_lines; i++) {
        printf("%s %d %d\n", vect[i].brand, vect[i].year_of_brand, vect[i].price);
    }

    while (1) {
        int alegere;
        printf("\nalegeti dupa ce informatii vrei sa gasisiti masina: \n1(brand)\n2(an)\n3(pret)\n4(iesiti):\n");
        scanf("%d", &alegere);
        switch (alegere) {
            case 1:
                printf("\ndati un nume pentru cautare:\n");
                scanf("%s", brand);
                find_car_by_brand(nr_of_lines, brand, vect);
                break;
            case 2:
                printf("dati un an pentru cautare:");
                scanf("%d", &an);
                find_car_by_year(nr_of_lines, an, vect);
                break;
            case 3:
                printf("dati un pret pentru cautare:");
                scanf("%d", &pret);
                find_car_by_price(nr_of_lines, pret, vect);
                break;
            case 4:
              return 0;
            default:
                printf("dati un numar corescunzator\n");
        }
    }
}