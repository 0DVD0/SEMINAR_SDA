#include <stdio.h>
#include <stdlib.h>

typedef struct iphone{
    char *model;
    int price;
    int year;
    int capacity;
} Iphone;

typedef struct Node {
    int key;
    struct iphone phone;
    struct Node *left;
    struct Node *right;
} Node;

enum CHOICE{
    EXIT = 0,
    READ_TREE = 1,
    PRINT_FULL_TREE = 2,
    SEARCH_NODE = 3,
    SVD = 4,
    VSD = 5,
    SDV = 6,
    BSF = 7,
    DSF = 8,
    TREE_BALANCE = 9,
    TREE_MIRROR = 10,
    CLEAN_TREE = 11,
    FREE_MEMORY = 12,

};

/**
 * Reads the details of an iPhone from the user.
 * @return An initialized Iphone structure.
 */
struct iphone read_phone() {
    Iphone* new_phone = (Iphone*)malloc(sizeof(Iphone));
    if (new_phone == NULL) {
        printf("Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }
    new_phone->model = (char*)malloc(sizeof(char) * 10);
    if (new_phone->model == NULL) {
        printf("Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }
    printf("Iphone model:");
    scanf("%s", new_phone->model);
    printf("Iphone price:");
    scanf("%d", &(new_phone->price));
    printf("Iphone year:");
    scanf("%d", &(new_phone->year));
    printf("Iphone capacity:");
    scanf("%d", &(new_phone->capacity));
    return* new_phone;
}

/**
 * Create a new node with the given key and allocate memory for it.
 * @param key The key value for the new node.
 * @return A pointer to the newly created node.
 */
Node* create_node(int key) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }
    new_node->key = key;
    new_node->phone = read_phone();
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

/**
 * Insert a node with the given key into the binary tree rooted at 'root'.
 * @param root The root of the binary tree.
 * @param key The key value to insert.
 * @return The root of the modified binary tree.
 */
Node* insert_node_in_tree(Node* root, int key) {
    if (root == NULL) {
        return create_node(key);
    }
    if (key < root->key) {
        root->left = insert_node_in_tree(root->left, key);
    } else if (key > root->key) {
        root->right = insert_node_in_tree(root->right, key);
    }
    return root; // Return the root node after insertion
}

/**
 * Prints the details of an iPhone stored in a node.
 * @param root The node containing the iPhone details to print.
 */
void print_phone(Node * root){
    Iphone phone = root->phone;
    printf("%s\n",phone.model);
    printf("%d\n", phone.price);
    printf("%d\n", phone.year);
    printf("%d\n", phone.capacity);
}

/**
 * Perform a pre-order traversal of the binary tree rooted at 'root' and print the keys and the iphone inside the element.
 * @param root The root of the binary tree.
 */
void print_full_tree(Node* root) {
    if (root != NULL) {
        printf("The phone in the %d node ", root->key);
        print_phone(root);
        print_full_tree(root->left);
        print_full_tree(root->right);
    }
}

/**
 * Perform an in-order traversal of the binary tree rooted at 'root' and print the keys.
 * @param root The root of the binary tree.
 */
void svd_traversal(Node* root){
    if(root == NULL){
        return;
    }
    svd_traversal(root->left);
    printf("%d", root->key);
    svd_traversal(root->right);
}

/**
 * Perform a pre-order traversal of the binary tree rooted at 'root' and print the keys.
 * @param root The root of the binary tree.
 */
void vsd_traversal(Node* root){
    if(root == NULL){
        return;
    }
    printf("%d", root->key);
    vsd_traversal(root->left);
    vsd_traversal(root->right);
}

/**
 * Perform a post-order traversal of the binary tree rooted at 'root' and print the keys.
 * @param root The root of the binary tree.
 */
void sdv_traversal(Node* root){
    if(root == NULL){
        return;
    }
    sdv_traversal(root->left);
    sdv_traversal(root->right);
    printf("%d", root->key);
}

/**
 * Store nodes in in-order traversal in an array
 * @param root The root of the binary tree.
 * @param nodes The array to store the nodes.
 * @param index The current index in the array.
 */
void store_in_order(Node* root, Node** nodes, int* index) {
    if (root == NULL) {
        return;
    }
    store_in_order(root->left, nodes, index);
    nodes[(*index)++] = root;
    store_in_order(root->right, nodes, index);
}

/**
 * Convert a sorted array of nodes to a balanced binary search tree.
 * @param nodes The array of sorted nodes.
 * @param start The start index of the array.
 * @param end The end index of the array.
 * @return The root of the balanced binary search tree.
 */
Node* sorted_array_to_bst(Node** nodes, int start, int end) {
    if (start > end) {
        return NULL;
    }
    int mid = (start + end) / 2;
    Node* root = nodes[mid];
    root->left = sorted_array_to_bst(nodes, start, mid - 1);
    root->right = sorted_array_to_bst(nodes, mid + 1, end);
    return root;
}

/**
 * Balance the binary tree rooted at 'root'.
 * @param root The root of the binary tree.
 * @return The root of the balanced binary tree.
 */
Node* balance_tree(Node* root) {
    if (root == NULL) {
        return NULL;
    }

    int node_count = 0;
    Node* temp = root;
    while (temp != NULL) {
        node_count++;
        temp = temp->right;
    }

    Node** nodes = (Node**)malloc(node_count * sizeof(Node*));
    int index = 0;
    store_in_order(root, nodes, &index);

    Node* new_root = sorted_array_to_bst(nodes, 0, node_count - 1);

    free(nodes);

    return new_root;
}

/**
 * Mirrors the binary tree by swapping the left and right children of every node.
 * @param root The root of the binary tree.
 */
void mirror_tree(Node* root) {
    if (root == NULL) {
        return;
    }

    mirror_tree(root->left);
    mirror_tree(root->right);

    Node* temp = root->left;
    root->left = root->right;
    root->right = temp;
}

/**
 * Search for a node with the given key in the binary tree rooted at 'root'.
 * @param root The root of the binary tree.
 * @param key The key value to search_by_key for.
 * @return A pointer to the node with the given key, or NULL if not found.
 */
Node* search_by_key(Node* root, int key) {
    if (root->key == key) {
        return root;
    }
    if (root->key < key) {
        return search_by_key(root->right, key);
    }
    return search_by_key(root->left, key);
}

/**
 * Delete the binary tree rooted at 'root' and free the memory.
 * @param root The root of the binary tree.
 */
void delete_tree(Node* root) {
    if (root != NULL) {
        delete_tree(root->left);
        delete_tree(root->right);
        free(root);
    }
}



/**
 * Calculate the height of the binary tree.
 * @param root The root of the binary tree.
 * @return The height of the binary tree.
 */
int height(Node* root) {
    if (root == NULL) {
        return 0;
    }
    int left_height = height(root->left);
    int right_height = height(root->right);
    return (left_height > right_height) ? left_height + 1 : right_height + 1;
}

/**
 * Print all nodes at a given level.
 * @param root The root of the binary tree.
 * @param level The level to print nodes from.
 */
void print_level(Node* root, int level) {
    if (root == NULL) {
        return;
    }
    if (level == 1) {
        printf("%d ", root->key);
    } else if (level > 1) {
        print_level(root->left, level - 1);
        print_level(root->right, level - 1);
    }
}

/**
 * Perform a breadth-first search (BSF) traversal of the binary tree using recursion.
 * @param root The root of the binary tree.
 */
void bsf_traversal_recursive(Node* root) {
    int h = height(root);
    for (int i = 1; i <= h; i++) {
        print_level(root, i);
    }
    printf("\n");
}

/**
 * Print the menu options for the binary tree operations.
 */
void print_menu() {
    printf("\n1. Read the tree\n");
    printf("2. Display the tree\n");
    printf("3. Search for a node by key\n");
    printf("4. SVD(in-order) traversal\n");
    printf("5. VSD(pre-order) traversal\n");
    printf("6. SDV(post-order) traversal\n");
    printf("7. BSF(Breadth-First Search) traversal\n");
    printf("8. DSF(Depth-First Search) traversal\n");
    printf("9. Balance the tree\n");
    printf("10. Mirror the tree\n");
    printf("11. Clean tree\n");
    printf("12. Free tree\n");
    printf("0. Exit\n");
    printf("Your choice:");
}

int main() {
    Node* root = NULL;
    int choice, key;

    do {
        print_menu();
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case READ_TREE:
                printf("Key of node:");
                scanf("%d", &key);
                insert_node_in_tree(root, key);
                break;

            case PRINT_FULL_TREE:
                printf("The elements of the tree are: ");
                print_full_tree(root);
                break;

            case SEARCH_NODE:
                printf("Enter the search key: ");
                scanf("%d", &key);
                if (search_by_key(root, key) != NULL) {
                    printf("The node with key %d exists in the tree.\n", key);
                } else {
                    printf("The node with key %d does not exist in the tree.\n", key);
                }
                break;

            case SVD:
                printf("The tree in a In-order traversal:");
                svd_traversal(root);
                break;

            case VSD:
                printf("The tree in a Pre-order traversal:");
                vsd_traversal(root);
                break;

            case SDV:
                printf("The tree in a Post-order traversal:");
                sdv_traversal(root);
                break;

            case BSF:
                printf("The tree in BSF traversal:");
                bsf_traversal_recursive(root);
                break;

            case DSF:
                break;

            case TREE_BALANCE:
                root = balance_tree(root);
                printf("The tree has been balanced");
                break;

            case TREE_MIRROR:
                mirror_tree(root);
                printf("The tree is mirrored");
                break;

            case CLEAN_TREE:
                delete_tree(root);
                root = NULL;
                printf("The tree has been cleaned.\n");
                break;

            case FREE_MEMORY:
                delete_tree(root);
                root = NULL;
                printf("The memory of the tree has been freed.\n");
                break;

            case EXIT:
                printf("Exiting the program.\n");
                break;

            default:
                printf("Invalid option.\n");
        }
    } while (choice != 0);

    return 0;
}
