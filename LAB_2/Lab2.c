#include <stdio.h>
#include <stdlib.h>
#include <string.h>
enum choice{
    EXIT = 0,
    READ_CONSOLE = 1,
    PRINT_LIST = 2,
    SEARCH_CONSOLE_BY_NAME = 3,
    FREE_LIST = 4,
    SORT_BY_NAME = 5,
    SORT_BY_PRICE = 6,
    PUSH_FRONT = 7,
    PUSH_BACK = 8,
    PUSH_POSITION = 9,
    POP_POSITION = 10,
    INVERT_LIST = 11
};

typedef struct console {
    char *companie;
    char *nume;
    char *culoare;
    int anul_lansarii;
    double pretul;

    struct console *next;
} Console;

/*
 * This function reads information about a console from the user and returns a pointer to a Console structure containing this information.
 */
Console* read_console() {
    Console *s = (Console*)malloc(sizeof(Console));
    s->companie=malloc(sizeof(char)*20);
    s->nume=malloc(sizeof(char)*20);
    s->culoare=malloc(sizeof(char)*20);

    printf("\nIntroduceti numele companiei: ");
    scanf("%s", s->companie);
    printf("\nIntroduceti anul_lansarii: ");
    scanf("%d", &s->anul_lansarii);
    printf("\nIntroduceti pretul consolei: ");
    scanf("%lf", &s->pretul);
    printf("\nIntroduceti numele consolei: ");
    scanf("%s", s->nume);
    printf("\nIntroduceti culoarea consolei: ");
    scanf("%s", s->culoare);
    s->next = NULL;
    return s;
}

/*
*This function prints all the elements in the console list, starting from the head of the list and going to the end, displaying the company name, console name, color, release year, and price of each console.
*@param head pointer pf the first element of the list
*/
void print_list(Console *head) {
    Console *current = head;
    int cons=1;
    printf("\nLista de Console:\n");
    while (current != NULL) {
        printf("Consola nr.%d\n",cons);
        printf("\nCompania: %s\n Nume: %s\n Culoare: %s\n Anul lansarii: %d\n Pretul: %.2lf$\n",
               current->companie, current->nume, current->culoare, current->anul_lansarii, current->pretul);
        printf("\n");
        current = current->next;
        cons++;
    }
}

/*
*This function searches for a console in the list by the given name and returns its position in the list or -1 if it's not found.
*@param head pointer of the first element of list
*@param name_to_find name given by the user
*/
int find_console(Console *head, char name_to_find[]) {
    Console *current = head;
    int Position = 1;
    while (current != NULL) {
        if (strcmp(current->nume, name_to_find) == 0) {
            return Position;
        }
        current = current->next;
        Position++;
    }
    return -1;
}

/*
 * This function frees the memory occupied by all nodes in the console list.
 * @param head pointer of the first element of list
 */
void free_list(Console *head) {
    Console *current = head;
    while (current != NULL) {
        Console *temp = current;
        current = current->next;
        free(temp);
    }
}

/*
 * This function inserts a console at the beginning of the list.
 *  @param head pointer of the first element of list
 *   @param new pointer of a new console type element to be inserted
 */
void push_front(Console **head, Console *new) {
    new->next = *head;
    *head = new;
}

/*
 * This function inserts a console at the end of the list.
 * @param new pointer of a new console type element to be inserted
*/
void push_back(Console **head, Console *new) {
    if (*head == NULL) {
        *head = new;
    } else {
        Console *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new;
    }
}

/*
 * This function inserts a console at a specified position in the list.
 * @param head double pointer of the first element of the list
 * @param new pointer of a new console type element to be inserted
 * @position a number to show where to insert the new element
 */
void push_position(Console **head, Console *new, int position) {
    if (position <= 0) {
        printf("Pozitie invalida.\n");
        return;
    }
    if (position == 1) {
        push_front(head, new);
    } else {
        Console *current = *head;
        int i = 1;
        while (current != NULL && i < position - 1) {
            current = current->next;
            i++;
        }
        if (current == NULL) {
            printf("Pozitie invalida.\n");
            return;
        }
        new->next = current->next;
        current->next = new;
    }
}

/*
 * This function deletes a console from a specified position in the list.
 * @param head double pointer of the first element of the list
 * @position a number to show where to insert the new element
 */
void delete_position(Console **head, int position) {
    if (*head == NULL) {
        printf("Lista este goala.\n");
        return;
    }
    if (position <= 0) {
        printf("Pozitie invalida.\n");
        return;
    }
    Console *temp = *head;
    if (position == 1) {
        *head = (*head)->next;
        free(temp->companie);
        free(temp->nume);
        free(temp->culoare);
        free(temp);
    } else {
        int i = 1;
        Console *prev = NULL;
        while (temp != NULL && i < position) {
            prev = temp;
            temp = temp->next;
            i++;
        }
        if (temp == NULL) {
            printf("Pozitie invalida.\n");
            return;
        }
        prev->next = temp->next;
        free(temp->companie);
        free(temp->nume);
        free(temp->culoare);
        free(temp);
    }
}

/*
 * This function reverses the order of elements in the list.
 *  @param head double pointer of the first element of the list
 */
void invert_list(Console **head) {
    Console *prev = NULL, *current = *head, *next = NULL;
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *head = prev;
}

/*
 * This comparison function is used to sort the console list by name in alphabetical order.
 *  @param a  pointer one of the elemenets to compare
 *   @param b  pointer one of the elemenets to compare
 */
int comapre_name(const void *a, const void *b) {
    const Console *consoleA = *(const Console **)a;
    const Console *consoleB = *(const Console **)b;
    return strcmp(consoleA->nume, consoleB->nume);
}

/*
 * This comparison function is used to sort the console list by price in ascending order.
 *  @param a  pointer one of the elemenets to compare
 *  @param b  pointer one of the elemenets to compare
*/
int compare_price(const void *a, const void *b) {
    const Console *consoleA = *(const Console **)a;
    const Console *consoleB = *(const Console **)b;
    return (consoleA->pretul > consoleB->pretul) - (consoleA->pretul < consoleB->pretul);
}

/*
 * This function sorts the console list by name using the QuickSort algorithm and the Compare_Name() comparison function.
 * @param head double pointer of the first element of the list
 */
void sort_by_name(Console **head) {
    int nr_console = 0;
    Console *current_n = *head;
    while (current_n != NULL) {
        nr_console++;
        current_n = current_n->next;
    }

    Console **array = (Console **)malloc(nr_console * sizeof(Console *));
    current_n = *head;
    for (int i = 0; i < nr_console; ++i) {
        array[i] = current_n;
        current_n = current_n->next;
    }

    qsort(array, nr_console, sizeof(Console *), comapre_name);

    for (int i = 0; i < nr_console - 1; ++i) {
        array[i]->next = array[i + 1];
    }
    array[nr_console - 1]->next = NULL;
    *head = array[0];

    free(array);

    printf("Lista a fost sortata dupa denumire.\n");
}

/*
 * This function sorts the console list by price using the QuickSort algorithm and the Compare_Price() comparison function.
 * @param head double pointer of the first element of the list
 */
void sort_by_price(Console **head) {
    int nr_console = 0;
    Console *current = *head;
    while (current != NULL) {
        nr_console++;
        current = current->next;
    }

    Console **array_p = (Console **)malloc(nr_console * sizeof(Console *));
    current = *head;
    for (int i = 0; i < nr_console; ++i) {
        array_p[i] = current;
        current = current->next;
    }

    qsort(array_p, nr_console, sizeof(Console *), compare_price);

    for (int i = 0; i < nr_console - 1; ++i) {
        array_p[i]->next = array_p[i + 1];
    }
    array_p[nr_console - 1]->next = NULL;
    *head = array_p[0];

    free(array_p);

    printf("Lista a fost sortata dupa pret.\n");
}

int main() {
    Console *head = NULL;
    int choice, position;
    char *name_to_find;
    name_to_find= malloc(sizeof(char) * 10);
    do {
        printf("\n");
        printf(" 1. Citire consolei\n");
        printf(" 2. Afisare listei\n");
        printf(" 3. Cautare consolei dupa nume\n");
        printf(" 4. Eliberare memorie lista\n");
        printf(" 5. Sortare lista dupa nume\n");
        printf(" 6. Sortare dupa pret\n");
        printf(" 7. Inserare consola la inceputul listei\n");
        printf(" 8. Inserare consola la sfarsitul listei\n");
        printf(" 9. Inserare consola la o anumita position\n");
        printf("10. Stergere consola de pe o anumita position\n");
        printf("11. Inversare lista\n");
        printf(" 0. Iesire\n");
        printf("Alegerea: ");
        scanf("%d", &choice);
        switch (choice) {
            case READ_CONSOLE:
                push_back(&head, read_console());
                break;
            case PRINT_LIST:
                print_list(head);
                break;
            case SEARCH_CONSOLE_BY_NAME:
                printf("Introduceti numele consolei de cautat: ");
                scanf("%s", name_to_find);
                position = find_console(head, name_to_find);
                if (position != -1) {
                    printf("consola cu numele '%s' se afla pe pozitia %d in lista.\n", name_to_find, position);
                } else {
                    printf("consola cu numele '%s' nu a fost gasit in lista.\n", name_to_find);
                }
                break;
            case FREE_LIST:
                free_list(head);
                head = NULL;
                printf("Lista a fost eliberata.\n");
                break;
            case SORT_BY_NAME:
                sort_by_name(&head);
                break;
            case SORT_BY_PRICE:
                sort_by_price(&head);
                break;
            case PUSH_FRONT:
                push_front(&head, read_console());
                break;
            case PUSH_BACK:
                push_back(&head, read_console());
                break;
            case PUSH_POSITION:
                printf("Introduceti pozitia la care sa fie inserata consola: ");
                scanf("%d", &position);
                push_position(&head, read_console(), position);
                break;
            case POP_POSITION:
                printf("Introduceti pozitia de pe care sa fie stearsa consola: ");
                scanf("%d", &position);
                delete_position(&head, position);
                break;
            case INVERT_LIST:
                invert_list(&head);
                printf("Lista a fost inversata.\n");
                break;
            case EXIT:
                printf("Iesire din program.\n");
                break;
            default:
                printf("Optiune invalida. Va rugam sa incercati din nou.\n");
                break;
        }
    } while (choice != 0);
    free(name_to_find);
    free(head);

    return 0;
}