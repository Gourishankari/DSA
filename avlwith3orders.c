#include <stdio.h>
#include <stdlib.h>

// Structure to represent a node in the AVL tree
struct Node {
    int key;
    struct Node* left;
    struct Node* right;
    int height;
};

// Function to get the height of a node (returns -1 for a NULL node)
int getHeight(struct Node* node) {
    if (node == NULL)
        return -1;
    return node->height;
}

// Function to get the maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Function to create a new node with the given key
struct Node* createNode(int key) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 0;
    return newNode;
}

// Function to rotate a subtree rooted with y to the left
struct Node* rotateLeft(struct Node* y) {
    struct Node* x = y->right;
    struct Node* T2 = x->left;

    // Perform rotation
    x->left = y;
    y->right = T2;

    // Update heights
    y->height = 1 + max(getHeight(y->left), getHeight(y->right));
    x->height = 1 + max(getHeight(x->left), getHeight(x->right));

    return x;
}

// Function to rotate a subtree rooted with x to the right
struct Node* rotateRight(struct Node* x) {
    struct Node* y = x->left;
    struct Node* T2 = y->right;

    // Perform rotation
    y->right = x;
    x->left = T2;

    // Update heights
    x->height = 1 + max(getHeight(x->left), getHeight(x->right));
    y->height = 1 + max(getHeight(y->left), getHeight(y->right));

    return y;
}

// Function to get the balance factor of a node
int getBalance(struct Node* node) {
    if (node == NULL)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

// Function to insert a key into the AVL tree
struct Node* insert(struct Node* root, int key) {
    if (root == NULL)
        return createNode(key);

    if (key < root->key)
        root->left = insert(root->left, key);
    else if (key > root->key)
        root->right = insert(root->right, key);
    else // Duplicate keys are not allowed in AVL trees
        return root;

    // Update the height of the current node
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    // Get the balance factor of this node
    int balance = getBalance(root);

    // Left-Left case
    if (balance > 1 && key < root->left->key)
        return rotateRight(root);

    // Right-Right case
    if (balance < -1 && key > root->right->key)
        return rotateLeft(root);

    // Left-Right case
    if (balance > 1 && key > root->left->key) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    // Right-Left case
    if (balance < -1 && key < root->right->key) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

// Function to perform an in-order traversal of the AVL tree
void inOrderTraversal(struct Node* root) {
    if (root != NULL) {
        inOrderTraversal(root->left);
        printf("%d ", root->key);
        inOrderTraversal(root->right);
    }
}

// Function to perform a pre-order traversal of the AVL tree
void preOrderTraversal(struct Node* root) {
    if (root != NULL) {
        printf("%d ", root->key);
        preOrderTraversal(root->left);
        preOrderTraversal(root->right);
    }
}

// Function to perform a post-order traversal of the AVL tree
void postOrderTraversal(struct Node* root) {
    if (root != NULL) {
        postOrderTraversal(root->left);
        postOrderTraversal(root->right);
        printf("%d ", root->key);
    }
}

// Function to free the memory occupied by the AVL tree
void freeAVLTree(struct Node* root) {
    if (root != NULL) {
        freeAVLTree(root->left);
        freeAVLTree(root->right);
        free(root);
    }
}

int main() {
    struct Node* root = NULL;
    int choice, key;

    printf("AVL Tree Implementation\n");

    while (1) {
        printf("\nMenu:\n");
        printf("1. Insert\n");
        printf("2. Print In-order\n");
        printf("3. Print Pre-order\n");
        printf("4. Print Post-order\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the key to be inserted: ");
                scanf("%d", &key);
                root = insert(root, key);
                break;
            case 2:
                printf("In-order traversal: ");
                inOrderTraversal(root);
                printf("\n");
                break;
            case 3:
                printf("Pre-order traversal: ");
                preOrderTraversal(root);
                printf("\n");
                break;
            case 4:
                printf("Post-order traversal: ");
                postOrderTraversal(root);
                printf("\n");
                break;
            case 5:
                freeAVLTree(root);
                printf("AVL Tree freed.\n");
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}
