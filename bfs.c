#include <stdio.h>
#include <stdlib.h>

// Structure for a binary tree node
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to insert a node in BST
struct Node* insert(struct Node* root, int data) {
    if (root == NULL) {
        return createNode(data);
    } else {
        if (data <= root->data) {
            root->left = insert(root->left, data);
        } else {
            root->right = insert(root->right, data);
        }
        return root;
    }
}

// Function to delete a node from BST
struct Node* delete(struct Node* root, int data) {
    if (root == NULL) {
        return root;
    } else if (data < root->data) {
        root->left = delete(root->left, data);
    } else if (data > root->data) {
        root->right = delete(root->right, data);
    } else {
        // Case 1: No child or only one child
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }

        // Case 2: Two children
        struct Node* temp = root->right;
        while (temp->left != NULL) {
            temp = temp->left;
        }
        root->data = temp->data;
        root->right = delete(root->right, temp->data);
    }
    return root;
}

// Function for in-order traversal (left-root-right)
void inOrder(struct Node* root, FILE* fp) {
    if (root == NULL) {
        return;
    }
    inOrder(root->left, fp);
    fprintf(fp, "%d ", root->data);
    inOrder(root->right, fp);
}

// Function for pre-order traversal (root-left-right)
void preOrder(struct Node* root, FILE* fp) {
    if (root == NULL) {
        return;
    }
    fprintf(fp, "%d ", root->data);
    preOrder(root->left, fp);
    preOrder(root->right, fp);
}

// Function for post-order traversal (left-right-root)
void postOrder(struct Node* root, FILE* fp) {
    if (root == NULL) {
        return;
    }
    postOrder(root->left, fp);
    postOrder(root->right, fp);
    fprintf(fp, "%d ", root->data);
}

// Function to create a log file and call traversal functions
void logTraversal(struct Node* root) {
    FILE* fp = fopen("bst_traversal.log", "w");
    if (fp == NULL) {
        printf("Error opening the log file.");
        return;
    }

    fprintf(fp, "In-order traversal: ");
    inOrder(root, fp);
    fprintf(fp, "\n");

    fprintf(fp, "Pre-order traversal: ");
    preOrder(root, fp);
    fprintf(fp, "\n");

    fprintf(fp, "Post-order traversal: ");
    postOrder(root, fp);
    fprintf(fp, "\n");

    fclose(fp);
}

int main() {
    struct Node* root = NULL;

    // Insert nodes in BST
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 70);
    root = insert(root, 60);
    root = insert(root, 80);

    // Delete node from BST
    root = delete(root, 20);

    // Log traversal in a file
    logTraversal(root);

    return 0;
}
