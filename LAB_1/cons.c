#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max 10

typedef struct car{
    char *brand;
    int year_of_brand;
    int price;
}car;

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

void afisare(car *vect,int *nr_lines){
    for(int i = 0; i < *nr_lines; i++) {
        printf("%s %d %d\n", vect[i].brand, vect[i].year_of_brand, vect[i].price);
    }
    printf("\n");
}

void find_car_by_year(int nr_lines,int year_in,car *vect){
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
void find_car_by_brand(int nr_lines,char *brand_in,car *vect){
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
void find_car_by_price(int nr_lines,int price_in,car *vect){
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

void schimbare(car *a,car *b){
car temp=*a;
*a = *b;
*b = temp;
}
void sort_by_price(int nr_lines, car *vect){
    for (int i = 0; i < nr_lines-1 ; ++i) {
        for (int j = 0; j < nr_lines-i-1 ; ++j) {
            if(vect[j].price > vect[j+1].price){
                schimbare(&vect[j],&vect[j+1]);
            }
        }
    }
    afisare(vect,&nr_lines);
}
void sort_by_year(int nr_lines,car *vect){
    for (int i = 0; i < nr_lines-1 ; ++i) {
        for (int j = 0; j < nr_lines-i-1 ; ++j) {
            if(vect[j].year_of_brand > vect[j+1].year_of_brand){
                schimbare(&vect[j],&vect[j+1]);
            }
        }
    }
    afisare(vect,&nr_lines);
}

int comparare(const void* p, const void* q)
{
    return strcmp(((car*)p)->brand,((car*)q)->brand);
}
void sort_by_brand(int nr_lines,car *vect) {
    qsort(vect, nr_lines, sizeof(car), comparare);
    afisare(vect, &nr_lines);
}

void add_member(int *nr_lines, car *vect) {

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


    vect[*nr_lines] = new_car;

    (*nr_lines)++;

    afisare(vect,nr_lines);
}

void delete_member(int *nr_lines, car *vect) {
        int pos;
        printf("Introduceti pozitia masinii de sters (1-%d): ", *nr_lines);
        scanf("%d", &pos);

        if (pos < 1 || pos > *nr_lines) {
            printf("Pozitie invalida.\n");
            return;
        }

        free(vect[pos - 1].brand);

        for (int i = pos - 1; i < *nr_lines - 1; i++) {
            vect[i] = vect[i + 1];
        }

        (*nr_lines)--;

        afisare(vect,nr_lines);
    }



int main() {
    int an, pret;
    char *brand;
    car *vect;
    brand= malloc(sizeof(char) * 10);
    FILE *f = fopen("C:\\Users\\Asus\\Desktop\\SEMINAR SDA\\LAB_1\\masini.txt", "rw+");
    if (f == NULL) {
        printf("fisierul nu poate fii citit");
        return 0;
    }

    int nr_of_lines = count_lines(f);
    vect= malloc(sizeof(car) * nr_of_lines);
    for (int i = 0; i < nr_of_lines; i++) {
        vect[i].brand = malloc(sizeof(char) * 10);
        fscanf(f, "%s %d %d", vect[i].brand, &vect[i].year_of_brand, &vect[i].price);
    }
    fclose(f);

    afisare(vect,&nr_of_lines);

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
                            sort_by_brand(nr_of_lines, vect);
                            break;
                        case 2:
                            printf("lista sortata dupa an\n");
                            sort_by_year(nr_of_lines,vect);
                            break;
                        case 3:
                            printf("lista sortata dupa pret\n");
                            sort_by_price(nr_of_lines,vect);
                            break;
                        case 4:
                            printf("iesim in meniu...\n");
                            break;
                    }
                } while (opt_sort != 4);
                break;
            case 3:
                add_member(&nr_of_lines,vect);
                break;
            case 4:
                delete_member(&nr_of_lines,vect);
                break;
            case 5:
                printf("LISTA DISPONIBILA:\n");
                afisare(vect,&nr_of_lines);
                break;
            case 0:
                printf("iesim din program...");
                break;
        }
    }while(option != 0);
    free(brand);
    free(vect);
return 0;
}