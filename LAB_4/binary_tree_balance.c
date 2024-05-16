#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    char *name;
    int age;
    float height;
    struct Node *left;
    struct Node *right;
} Node;

// Funcția pentru citirea datelor unui nod de la tastatură
Node* read_node() {
    Node *new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }
    printf("Enter key: ");
    scanf("%d", &new_node->key);
    printf("Enter name: ");
    new_node->name = (char*)malloc(50 * sizeof(char));
    scanf("%s", new_node->name);
    printf("Enter age: ");
    scanf("%d", &new_node->age);
    printf("Enter get_height: ");
    scanf("%f", &new_node->height);
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

// Funcția pentru inserarea unui nod în arbore
Node* insert_node(Node* root, Node* new_node) {
    if (root == NULL) {
        return new_node;
    }
    if (new_node->key < root->key) {
        root->left = insert_node(root->left, new_node);
    } else if (new_node->key > root->key) {
        root->right = insert_node(root->right, new_node);
    }
    return root;
}

// Funcția pentru afișarea detaliilor unui nod
void print_node(Node *node) {
    printf("Key: %d, Name: %s, Age: %d, Height: %.2f\n", node->key, node->name, node->age, node->height);
}

// Funcția pentru afișarea întregului arbore în ordine crescătoare a cheilor
void print_inorder(Node* root) {
    if (root != NULL) {
        print_inorder(root->left);
        print_node(root);
        print_inorder(root->right);
    }
}

// Funcția pentru căutarea unui nod în arbore după cheie
Node* search_node(Node* root, int key) {
    if (root == NULL || root->key == key) {
        return root;
    }
    if (key < root->key) {
        return search_node(root->left, key);
    }
    return search_node(root->right, key);
}

// Funcția pentru parcurgerea arborelui în adâncime (DFS) folosind recursivitatea
void dfs_traversal(Node* root) {
    if (root != NULL) {
        print_node(root);
        dfs_traversal(root->left);
        dfs_traversal(root->right);
    }
}

// Funcția pentru calculul înălțimii unui nod
int get_height(Node* root) {
    if (root == NULL) {
        return 0;
    }
    int left_height = get_height(root->left);
    int right_height = get_height(root->right);
    return (left_height > right_height) ? left_height + 1 : right_height + 1;
}

// Funcția pentru afișarea nivelului unui nod
void print_level(Node* root, int level) {
    if (root == NULL) {
        return;
    }
    if (level == 1) {
        print_node(root);
    } else if (level > 1) {
        print_level(root->left, level - 1);
        print_level(root->right, level - 1);
    }
}

// Funcția pentru parcurgerea arborelui în lărgime (BFS) folosind coada
void bfs_traversal(Node* root) {
    int h = get_height(root);
    for (int i = 1; i <= h; i++) {
        print_level(root, i);
    }
}

// Funcția pentru ștergerea întregului arbore și eliberarea memoriei
void delete_tree(Node* root) {
    if (root != NULL) {
        delete_tree(root->left);
        delete_tree(root->right);
        free(root->name);
        free(root);
    }
}

// Funcția pentru oglindirea arborelui
void mirror_tree(Node* root) {
    if (root == NULL) {
        return;
    }

    // Schimbăm subarborii stâng și drept
    Node* temp = root->left;
    root->left = root->right;
    root->right = temp;

    // Aplicăm oglindirea pe subarborii stâng și drept
    mirror_tree(root->left);
    mirror_tree(root->right);
}

// Funcția pentru calculul factorului de echilibru al unui nod
int balance_factor(Node* node) {
    if (node == NULL) {
        return 0;
    }
    return get_height(node->left) - get_height(node->right);
}

// Funcția pentru rotirea la dreapta a unui nod
Node* rotate_right(Node* node) {
    Node* new_root = node->left;
    node->left = new_root->right;
    new_root->right = node;
    return new_root;
}

// Funcția pentru rotirea la stânga a unui nod
Node* rotate_left(Node* node) {
    Node* new_root = node->right;
    node->right = new_root->left;
    new_root->left = node;
    return new_root;
}

// Funcția pentru balansarea unui nod
Node* balance_node(Node* node) {
    if (node == NULL) {
        return NULL;
    }

    // Calculăm factorul de echilibru al nodului
    int balance = balance_factor(node);

    // Dacă nodul este dezechilibrat spre stânga
    if (balance > 1) {
        // Verificăm dacă subarborele stâng este dezechilibrat spre stânga sau spre dreapta
        if (balance_factor(node->left) > 0) {
            // Dacă este dezechilibrat spre stânga, aplicăm o rotație la dreapta
            node->left = rotate_left(node->left);
        }
        // Aplicăm o rotație la dreapta pe nodul curent
        return rotate_right(node);
    }
        // Dacă nodul este dezechilibrat spre dreapta
    else if (balance < -1) {
        // Verificăm dacă subarborele drept este dezechilibrat spre stânga sau spre dreapta
        if (balance_factor(node->right) < 0) {
            // Dacă este dezechilibrat spre dreapta, aplicăm o rotație la stânga
            node->right = rotate_right(node->right);
        }
        // Aplicăm o rotație la stânga pe nodul curent
        return rotate_left(node);
    }

    return node;
}

// Funcția pentru balansarea întregului arbore
Node* balance_tree(Node* root) {
    if (root == NULL) {
        return NULL;
    }

    // Balansăm fiecare nod din arbore
    root = balance_node(root);
    root->left = balance_tree(root->left);
    root->right = balance_tree(root->right);

    return root;
}

// Funcția pentru curățarea elementelor arborelui
void clear_tree(Node* root) {
    if (root != NULL) {
        clear_tree(root->left);
        clear_tree(root->right);
        free(root->name);
        free(root);
    }
}

int main() {
    Node* root = NULL;
    int choice, key;
    Node* temp;

    do {
        printf("\n1. Read tree\n");
        printf("2. Print tree\n");
        printf("3. Search node\n");
        printf("4. DFS traversal\n");
        printf("5. BFS traversal\n");
        printf("6. Mirror tree\n");
        printf("7. Clear tree\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                temp = read_node();
                root = insert_node(root, temp);
                break;
            case 2:
                if (root == NULL) {
                    printf("Tree is empty.\n");
                } else {
                    printf("Tree elements:\n");
                    print_inorder(root);
                }
                break;
            case 3:
                printf("Enter key to search: ");
                scanf("%d", &key);
                temp = search_node(root, key);
                if (temp != NULL) {
                    printf("Node found: ");
                    print_node(temp);
                } else {
                    printf("Node not found.\n");
                }
                break;
            case 4:
                printf("DFS traversal:\n");
                dfs_traversal(root);
                break;
            case 5:
                printf("BFS traversal:\n");
                bfs_traversal(root);
                break;
            case 6:
                printf("Mirroring the tree...\n");
                mirror_tree(root);
                printf("Tree mirrored.\n");
                break;
            case 7:
                printf("Clearing the tree...\n");
                clear_tree(root);
                root = NULL;
                printf("Tree cleared.\n");
                break;
            case 8:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 8);

    return 0;
}












