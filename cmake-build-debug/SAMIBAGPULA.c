#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 100
#define MAX_MONTHS 12
#define MAX_PRODUCTS 5

typedef struct {
    int day;
    int month;
    int year;
} Date;

typedef struct {
    Date sale_date;
    int product_id;
    char product_name[MAX_LEN];
    char product_category[MAX_LEN];
    char product_subcategory[MAX_LEN];
    double unit_price;
    int quantity_sold;
    char sale_country[MAX_LEN];
    char sale_city[MAX_LEN];
} Sale;

typedef struct {
    int product_id;
    double total_cost;
} ProductTotalCost;

typedef struct {
    char category[MAX_LEN];
    int sales_count;
} CategorySalesCount;

void readSalesData(FILE *fp, Sale **sales, int *num_sales) {
    char line[MAX_LEN];
    int count = 0;

    while (fgets(line, sizeof(line), fp)) {
        Sale sale;
        sscanf(line, "%d-%d-%d,%d,%19[^,],%19[^,],%19[^,],%lf,%d,%29[^,],%29[^\n]",
               &sale.sale_date.year, &sale.sale_date.month, &sale.sale_date.day,
               &sale.product_id, sale.product_name, sale.product_category,sale.product_subcategory,
               &sale.unit_price, &sale.quantity_sold, sale.sale_country, sale.sale_city);
        (*sales)[count++] = sale;
    }

    *num_sales = count;
}

void totalRevenuePerMonth(Sale *sales, int num_sales, int year) {
    double revenue[MAX_MONTHS] = {0};

    for (int i = 0; i < num_sales; i++) {
        if (sales[i].sale_date.year == year) {
            int month = sales[i].sale_date.month - 1;
            revenue[month] += sales[i].unit_price * sales[i].quantity_sold;
        }
    }

    printf("Total revenue per month in %d:\n", year);
    for (int i = 0; i < MAX_MONTHS; i++) {
        printf("Month %d: %.2lf\n", i + 1, revenue[i]);
    }
}

void topSellingProducts(Sale *sales, int num_sales) {
    ProductTotalCost products[MAX_PRODUCTS] = {0};

    for (int i = 0; i < num_sales; i++) {
        int id = sales[i].product_id;
        double total_cost = sales[i].unit_price * sales[i].quantity_sold;

        for (int j = 0; j < MAX_PRODUCTS; j++) {
            if (products[j].product_id == id) {
                products[j].total_cost += total_cost;
                break;
            } else if (products[j].product_id == 0) {
                products[j].product_id = id;
                products[j].total_cost = total_cost;
                break;
            }
        }
    }

    printf("\nTop 5 selling products by total revenue:\n");
    for (int i = 0; i < MAX_PRODUCTS; i++) {
        printf("Product ID: %d, Total Cost: %.2lf\n", products[i].product_id, products[i].total_cost);
    }
}

void salesPerCategory(Sale *sales, int num_sales, char *category) {
    CategorySalesCount categories[MAX_LEN] = {0};

    for (int i = 0; i < num_sales; i++) {
        if (strcmp(sales[i].product_category, category) == 0) {
            for (int j = 0; j < MAX_LEN; j++) {
                if (strcmp(categories[j].category, category) == 0) {
                    categories[j].sales_count++;
                    break;
                } else if (strlen(categories[j].category) == 0) {
                    strcpy(categories[j].category, category);
                    categories[j].sales_count = 1;
                    break;
                }
            }
        }
    }

    printf("\nSales count per category '%s':\n", category);
    for (int i = 0; i < MAX_LEN; i++) {
        if (strlen(categories[i].category) != 0) {
            printf("%s: %d\n", categories[i].category, categories[i].sales_count);
        }
    }
}

int main() {
    FILE *fp = fopen("sales.txt", "r");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    int num_sales;
    Sale *sales = malloc(MAX_LEN * sizeof(Sale));
    if (sales == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    readSalesData(fp, &sales, &num_sales);
    fclose(fp);

    int choice;
    do {
        printf("\nOptions:\n");
        printf("1. Total revenue per month\n");
        printf("2. Top 5 selling products\n");
        printf("3. Sales per category\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                int year;
                printf("Enter year: ");
                scanf("%d", &year);
                totalRevenuePerMonth(sales, num_sales, year);
                break;
            }
            case 2:
                topSellingProducts(sales, num_sales);
                break;
            case 3: {
                char category[MAX_LEN];
                printf("Enter category: ");
                scanf("%s", category);
                salesPerCategory(sales, num_sales, category);
                break;
            }
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 4);

    free(sales);
    return 0;
}