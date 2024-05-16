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

typedef struct BinaryTree {
    Node *root;
} BinaryTree;

enum CHOICE{
    EXIT = 0,
    READ_TREE = 1,
    PRINT_TREE = 2,
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
 * This function allocates memory for a new BinaryTree structure and returns a pointer to it.
 * The root of the tree is initialized to NULL.
 * @return A pointer to the newly created BinaryTree structure
 */
BinaryTree *create_binary_tree(){
    BinaryTree *Tree = (BinaryTree *) calloc(1, sizeof(BinaryTree));
    return Tree;
}

/**
 * Reads the details of an iPhone from the user.
 * @return An initialized Iphone structure.
 */
Iphone read_phone() {
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
    printf("\n-----Model: %s-----\n", new_phone->model);
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
 * @param new_phone The iPhone details to be stored in the new node.
 * @return A pointer to the newly created node.
 */
Node* create_node(Iphone new_phone, int key) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }
    new_node->key = key;
    new_node->phone = new_phone;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

/**
 * This function is used to insert a new node into the binary tree.
 * @param current_node The current node in the binary tree
 * @param new_node The new node to be inserted into the binary tree
 */
void insert_node(Node *current_node, Node *new_node) {

    if (new_node->key < current_node->key) {
        if (current_node->left) {
            insert_node(current_node->left, new_node);
        } else {
            current_node->left = new_node;
        }
    } else if(new_node->key > current_node->key) {
        if (current_node->right) {
            insert_node(current_node->right, new_node);
        } else {
            current_node->right = new_node;
        }
        }
}

/**
 * Insert a node with the given key into the binary tree rooted at 'root'.
 * @param tree The pointer of the binary tree
 * @param key The key value to insert.
 */
void insert_node_in_tree(BinaryTree *tree, Node *new_node) {
    if (!tree->root) {
        tree->root= new_node;
    }
    insert_node(tree->root, new_node);
}


/**
 * Prints the details of an iPhone stored in a node.
 * @param iphone the phone containde in the current node
 */
void print_phone(Iphone iphone){
    printf("%s\n",iphone.model);
    printf("%d\n", iphone.price);
    printf("%d\n", iphone.year);
    printf("%d\n", iphone.capacity);
}

/**
 *Prints the key and the iPhone details of a node.
 * @param node  The node to print.
 */
void print_node(Node *node) {
    printf("Key: %d\n", node->key);
    print_phone(node->phone);
}

/**
 *This function is a helper function for printing the binary tree.
 * @param current_node The current node in the binary tree.
 */
void print_tree_helper(Node *current_node){
    if (!current_node) {
        return;
    }
    print_node(current_node);
    print_tree_helper(current_node->left);
    print_tree_helper(current_node->right);
}

/**
 * Perform a pre-order traversal of the binary tree rooted at 'root' and print the keys and the iphone inside the element.
 * @param tree The pointer of the binary tree.
 */
void print_binary_tree(BinaryTree *tree) {
    if (!tree->root ) {
        return;
    }
    print_tree_helper(tree->root);
}


/**
 * Perform an in-order traversal of the binary tree rooted at 'root' and print the keys.
 * @param node The node of the binary tree.
 */
void svd_traversal_helper(Node* node){
    if(node == NULL){
        return;
    }
    svd_traversal_helper(node->left);
    printf("%d", node->key);
    svd_traversal_helper(node->right);
}

/**
 *This function performs an in-order traversal of the binary tree rooted at 'tree'
 * and prints the keys of the nodes in the tree.
 * @param tree The pointer to the binary tree
 */
void svd_traversal(BinaryTree *tree){
    printf("The tree in a In-order traversal:");
    svd_traversal_helper(tree->root);
}

/**
 *This function is a helper function for performing a pre-order traversal of the binary tree.
 * It prints the key of each node in the tree.
 * @param node The current node in the binary tree.
 */
void vsd_traversal_helper(Node* node){
if(node == NULL){
return;
}
printf("%d", node->key);
vsd_traversal_helper(node->left);
vsd_traversal_helper(node->right);
}
/**
 * Perform a pre-order traversal of the binary tree rooted at 'node' and print the keys.
 * @param tree The poiner of the binary tree.
 */
void vsd_traversal(BinaryTree *tree){
    printf("The tree in a Pre-order traversal:");
    vsd_traversal_helper(tree->root);
}

 /**
  *This function is a helper function for performing a post-order traversal of the binary tree.
 * It prints the key of each node in the tree.
  * @param node  The current node in the binary tree.
  */
void sdv_traversal_helper(Node* node){
    if(node == NULL){
        return;
    }
    sdv_traversal_helper(node->left);
    sdv_traversal_helper(node->right);
    printf("%d", node->key);
}

/**
 * Perform a post-order traversal of the binary tree rooted at 'root' and print the keys.
 * @param tree The pointer of the binary tree.
 */
void sdv_traversal(BinaryTree *tree){
    printf("The tree in a Post-order traversal:");
    sdv_traversal_helper(tree->root);
}

/**
 * Store nodes in in-order traversal in an array
 * @param node The node of the binary tree.
 * @param nodes The array to store the nodes.
 * @param index The current index in the array.
 */
void store_in_order(Node* node, Node** nodes, int* index) {
    if (node == NULL) {
        return;
    }
    store_in_order(node->left, nodes, index);
    nodes[(*index)++] = node;
    store_in_order(node->right, nodes, index);
}

/**
 * Convert a sorted array of nodes to a balanced binary search tree.
 * @param nodes The array of sorted nodes.
 * @param start The start index of the array.
 * @param end The end index of the array.
 * @return The root of the balanced binary search tree.
 */
Node* convert_array_to_bst(BinaryTree *tree, Node** nodes, int start, int end) {
    if (start > end) {
        return NULL;
    }
    int mid = (start + end) / 2;
    Node *root= nodes[mid];
    tree->root->left = convert_array_to_bst(tree, nodes, start, mid - 1);
    tree->root->right = convert_array_to_bst(tree, nodes, mid + 1, end);
    return root;
}

/**
 * Balance the binary tree rooted at 'root'.
 * @param root The root of the binary tree.
 * @return The root of the balanced binary tree.
 */
Node* balance_tree(BinaryTree *tree) {
    if (tree == NULL) {
        return NULL;
    }

    int node_count = 0;
    Node* temp = tree->root;
    while (temp != NULL) {
        node_count++;
        temp = temp->right;
    }

    Node** nodes = (Node**)malloc(node_count * sizeof(Node*));
    int index = 0;
    store_in_order(tree->root, nodes, &index);

    Node* new_root = convert_array_to_bst(tree, nodes, 0, node_count - 1);

    free(nodes);

    return new_root;
}

/**
 *This function is a helper function for mirroring the binary tree.
 * It swaps the left and right children of every node.
 * @param node The node of the binary tree.
 */
void mirror_tree_helper(Node* node){
    if (node == NULL) {
        return;
    }

    mirror_tree_helper(node->left);
    mirror_tree_helper(node->right);

    Node* temp = node->left;
    node->left = node->right;
    node->right = temp;
}

/**
 * Mirrors the binary tree by swapping the left and right children of every node.
 * @param tree The pointer of the binary tree.
 */
void mirror_tree(BinaryTree* tree) {
    mirror_tree_helper(tree->root);
}

/**
 *This function is a helper function for searching a node with a given key in the binary tree.
 * @param current_node
 * @param key
 * @return A pointer to the node with the given key, or NULL if not found.
 */
Node *search_by_key_helper(Node *current_node, int key){
    if (current_node->key == key) {
        return current_node;
    }
    if (current_node->key < key) {
        return search_by_key_helper(current_node->right, key);
    }
    return search_by_key_helper(current_node->left, key);
}

/**
 * Search for a node with the given key in the binary tree rooted at 'root'.
 * @param tree The root of the binary tree.
 * @param key The key value to search_node_by_key for.
 */
Node* search_node_by_key(BinaryTree *tree, int key) {
   if(!tree){
       return NULL;
   }
    search_by_key_helper(tree->root, key);
}

/**
 * Delete the binary tree rooted at 'node' and free the memory.
 * @param node The node of the binary tree.
 */
void delete_node(Node* node) {
    if (node != NULL) {
        delete_node(node->left);
        delete_node(node->right);
        free(node);
    }
}

/**
 *Deletes the binary tree rooted at 'tree' and frees the memory.
 * @param tree The pointer to the binary tree to be deleted.
 */
void delete_tree(BinaryTree *tree){
    if(!tree){
        return;
    }
    delete_node(tree->root);
}
/**
 * Calculate the get_height of the binary tree.
 * @param root The root of the binary tree.
 * @return The get_height of the binary tree.
 */
int get_height(Node* node) {
    if (node == NULL) {
        return 0;
    }
    int left_height = get_height(node->left);
    int right_height = get_height(node->right);
    return (left_height > right_height) ? left_height + 1 : right_height + 1;
}

/**
 * Print all nodes at a given level.
 * @param node The node of the binary tree.
 * @param level The level to print nodes from.
 */
void print_level(Node* node, int level) {
    if (node == NULL) {
        return;
    }
    if (level == 1) {
        printf("%d ", node->key);
    } else if (level > 1) {
        print_level(node->left, level - 1);
        print_level(node->right, level - 1);
    }
}

/**
 * Perform a breadth-first search (BSF) traversal of the binary tree using recursion.
 * @param root The root of the binary tree.
 */
void bsf_traversal_recursive(BinaryTree* tree) {
    int h = get_height(tree->root);
    for (int i = 1; i <= h; i++) {
        print_level(tree->root, i);
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
    BinaryTree *binary_tree = create_binary_tree();
    int choice, key;

    printf("Binaray tree\n");
    print_binary_tree(binary_tree)
    ;
    do {
        print_menu();
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case READ_TREE:
                printf("Key of node:");
                scanf("%d", &key);
                Iphone new_iphone = read_phone();
                Node *new_node = create_node(new_iphone, key);
                insert_node_in_tree(binary_tree, new_node);
                break;

            case PRINT_TREE:
                printf("The elements of the tree are: ");
                print_binary_tree(binary_tree);
                break;

            case SEARCH_NODE:
                printf("Enter the search key: ");
                scanf("%d", &key);
                Node *node = search_node_by_key(binary_tree,key);
                    if (node->key == key) {
                        print_node(node);
                    } else {
                        printf("this key is not found in any node");
                    }

                break;

            case SVD:
                svd_traversal(binary_tree);
                break;

            case VSD:
                vsd_traversal(binary_tree);
                break;

            case SDV:
                sdv_traversal(binary_tree);
                break;

            case BSF:
                printf("The tree in BSF traversal:");
                bsf_traversal_recursive(binary_tree);
                break;

            case DSF:
                break;

            case TREE_BALANCE:
               binary_tree->root = balance_tree(binary_tree);
                printf("The tree has been balanced");
                break;

            case TREE_MIRROR:
                mirror_tree(binary_tree);
                printf("The tree is mirrored");
                break;

            case CLEAN_TREE:
                delete_tree(binary_tree);
                printf("The tree has been cleaned.\n");
                break;

            case FREE_MEMORY:
                delete_tree(binary_tree);
                free(binary_tree);
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
