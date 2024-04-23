#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX 100

typedef struct {
    double total_cost;
    char category[MAX];
} total_cost;
typedef struct sale_id {
    int an;
    int luna;
    int zi;
    char sale_date[MAX];
    int product_id;
    char product_name[MAX];
    char product_category[MAX];
    char product_subcategory[MAX];
    double unit_price;
    unsigned int quantity_sold;
    char sale_country[MAX];
    char sale_city[MAX];
} sale;

int count_lines(FILE* fp) {
    char ch;
    int lines = 0;
    while ((ch = fgetc(fp)) != EOF) {
        if (ch == '\n') {
            lines++;
        }
    }
    rewind(fp);
    return lines;
}

void read_file(sale *vect, int nr_lines,FILE* f){
    for (int i = 0; i < nr_lines; i++) {
        fscanf(f, "%19[^,],%d,%19[^,],%19[^,],%19[^,],%lf,%d,%29[^,],%29[^\n]",
               vect[i].sale_date, &vect[i].product_id, vect[i].product_name,
               vect[i].product_category, vect[i].product_subcategory, &vect[i].unit_price,
               &vect[i].quantity_sold, vect[i].sale_country, vect[i].sale_city);
        sscanf(vect[i].sale_date, "%d-%d-%d", &vect[i].an, &vect[i].luna, &vect[i].zi);
    }
}

void display(sale *vect, int nr_elemente) {

    for (int i = 0; i < nr_elemente; i++) {
        printf("%d ELEMENT:\n", i + 1);
        printf("data:%s\n", vect[i].sale_date);
        printf("ID:%d\n", vect[i].product_id);
        printf("denumire:%s\n", vect[i].product_name);
        printf("categoria:%s\n", vect[i].product_category);
        printf("sub-categoria:%s\n", vect[i].product_subcategory);
        printf("pretul:%.2lf\n", vect[i].unit_price);
        printf("cantitatea:%d\n", vect[i].quantity_sold);
        printf("tara:%s\n", vect[i].sale_country);
        printf("orasul:%s\n", vect[i].sale_city);
    }
}

void venitul_anual(sale *vect, int anul,int nr_lines){
    double venitul_anual=0, venitul_luna=0;

    for(int k=1; k <= 12;k++) {
        for (int i = 0; i < nr_lines; i++) {
            if (anul == vect[i].an && k==vect[i].luna ) {
                venitul_luna = venitul_luna + (vect[i].unit_price * vect[i].quantity_sold);
            }
        }
        if(venitul_luna!=0){
            printf("Venitul pe luna %d este:%.2fl$\n", k, venitul_luna);
        }else {
            printf("Luna %d nu a fost niciun venit\n",k);
        }
        venitul_anual = venitul_anual + venitul_luna;
        }
    if (venitul_anual!=0){
        printf("Venitul anual este: %.2fl$\n", venitul_anual);
    }else {
        printf("Nu a fost nici-un venit anul asta\n");
    }
}

void top_five_categories(sale *vect, int nr_lines) {
    total_cost categories[MAX] = {0};


    for (int i = 0; i < nr_lines; i++) {
        int found = 0;
        for (int j = 0; j < MAX; j++) {
           if (strcmp(categories[j].category, vect[i].product_category) == 0) {
                categories[j].total_cost += vect[i].unit_price * vect[i].quantity_sold;
                found = 1;
                break;
            }
        }
      if (found==0) {
            for (int j = 0; j < MAX; j++) {
                if (categories[j].total_cost == 0) {
                    strcpy(categories[j].category, vect[i].product_category);
                    categories[j].total_cost += vect[i].unit_price * vect[i].quantity_sold;
                    break;
                }
            }
        }
    }

    // Bubble sort to find top five categories
    for (int i = 0; i < MAX - 1; i++) {
        for (int j = 0; j < MAX - i - 1; j++) {
            if (categories[j].total_cost < categories[j + 1].total_cost) {
                total_cost temp = categories[j];
                categories[j] = categories[j + 1];
                categories[j + 1] = temp;
            }
        }
    }

    // Display top five categories
    printf("Top 5 categorii:\n");
    for (int i = 0; i < 5; i++) {
        printf("Category: %s, Total Cost: %.2lf$\n", categories[i].category, categories[i].total_cost);
    }
}

void totalSalesForCategory(sale *vect, int nr_lines, char *category) {
    double total_sales = 0;

    for (int i = 0; i < nr_lines; i++) {
        if (strcmp(vect[i].product_category, category) == 0) {
            total_sales += vect[i].unit_price * vect[i].quantity_sold;
        }
    }

    printf("Total sales for category '%s': %.2lf$\n", category, total_sales);
}

void cityWithMaxSalesInCountry(sale *vect, int nr_lines, char *country) {
    double max_sales = 0;
    char max_sales_city[MAX] = "";

    for (int i = 0; i < nr_lines; i++) {
        if (strcmp(vect[i].sale_country, country) == 0) {
            double current_sales = vect[i].unit_price * vect[i].quantity_sold;
            if (current_sales > max_sales) {
                max_sales = current_sales;
                strcpy(max_sales_city, vect[i].sale_city);
            }
        }
    }

    if (max_sales > 0) {
        printf("City with max sales in %s: %s (Total sales: %.2lf$)\n", country, max_sales_city, max_sales);
    } else {
        printf("No sales found in %s\n", country);
    }
}


int main() {
    int nr_of_lines, nr_elemente,an,alegere;
    sale *vect;
    char category[MAX], country[MAX];

    FILE *f = fopen("C:\\Users\\Asus\\Desktop\\SEMINAR SDA\\TASK_1\\sales.txt", "rw+");
    if (f == NULL) {
        printf("fisierul nu poate fi citit");
        return 0;
    }

    nr_of_lines = count_lines(f);
    vect=malloc(sizeof(sale)*nr_of_lines);

    read_file(vect,nr_of_lines,f);

    fclose(f);

   do {
       printf("1. Aflati venitul anual si lunar\n");
       printf("2. Top 5 categori dupa venitul generat\n");
       printf("3. Vanzarile per categorie\n");
       printf("4. Orasul din orice tara cu cele mai mari vanzari\n");
       printf("5. Printati cateva elemente ca sa verificati integritatea fileului\n");
       printf("0. Iesiti din program\n");
       printf("ALEGERE:");
       scanf("%d",&alegere);
       switch (alegere) {
           case 1:
               an=0;
           printf("dati anul pentru care vreti sa aflati venitul:");
           scanf("%d", &an);
           venitul_anual(vect, an, nr_of_lines);
               break;
           case 2:
               top_five_categories(vect,nr_of_lines);
               break;
           case 3:
               printf("Enter category: ");
               scanf("%s", category);
               totalSalesForCategory(vect, nr_of_lines, category);
               break;
           case 4:
               printf("Enter country: ");
               scanf("%s", country);
               cityWithMaxSalesInCountry(vect, nr_of_lines, country);
               break;
           case 5:
               printf("Cate elemente vreti sa printati:");
               scanf("%d",&nr_elemente);
               if(nr_of_lines<nr_elemente || nr_elemente < 0 ){
                   printf("Dati un numar corespunzator");
                   break;
               } else {
                   display(vect, nr_elemente);
               }
               break;
           case 0:
               break;
       }
   } while (alegere !=0);
    free(vect);
    return 0;
}