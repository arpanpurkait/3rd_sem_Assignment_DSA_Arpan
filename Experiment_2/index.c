#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int rollNumber;
    char name[50];
    int totalMarks;
} Student;

typedef struct Node {
    Student student;
    struct Node *left;
    struct Node *right;
    int height;
} Node;

int height(Node *N);
int max(int a, int b);
Node *newNode(Student s);
Node *rightRotate(Node *y);
Node *leftRotate(Node *x);
int getBalance(Node *N);
Node *insert(Node *node, Student s);
void preOrder(Node *root, FILE *fp);
void inOrder(Node *root, FILE *fp);
void postOrder(Node *root, FILE *fp);
void readFileAndBuildTree(const char *filename, Node **root);

int main() {
    Node *root = NULL;

    printf("--- Building AVL Tree (Verbose Mode) ---\n");
    readFileAndBuildTree("input.txt", &root);
    printf("\nTree construction complete.\n\n");

    FILE *fpPre = fopen("output_preorder.txt", "w");
    FILE *fpIn = fopen("output_inorder.txt", "w");
    FILE *fpPost = fopen("output_postorder.txt", "w");

    if (!fpPre || !fpIn || !fpPost) {
        printf("Error creating output files.\n");
        exit(1);
    }

    fprintf(fpPre, "Roll\tName\tMarks\n----\t----\t-----\n");
    preOrder(root, fpPre);
    printf("Pre-order traversal saved to 'output_preorder.txt'\n");

    fprintf(fpIn, "Roll\tName\tMarks\n----\t----\t-----\n");
    inOrder(root, fpIn);
    printf("In-order traversal saved to 'output_inorder.txt'\n");

    fprintf(fpPost, "Roll\tName\tMarks\n----\t----\t-----\n");
    postOrder(root, fpPost);
    printf("Post-order traversal saved to 'output_postorder.txt'\n");

    fclose(fpPre);
    fclose(fpIn);
    fclose(fpPost);

    return 0;
}

int height(Node *N) {
    if (N == NULL)
        return 0;
    return N->height;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

Node *newNode(Student s) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->student = s;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return (node);
}

Node *rightRotate(Node *y) {
    Node *x = y->left;
    Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    printf("  -> [Verbose] Performed Right Rotation on Node %d\n", y->student.rollNumber);
    return x;
}

Node *leftRotate(Node *x) {
    Node *y = x->right;
    Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    printf("  -> [Verbose] Performed Left Rotation on Node %d\n", x->student.rollNumber);
    return y;
}

int getBalance(Node *N) {
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

Node *insert(Node *node, Student s) {
    if (node == NULL) {
        printf("Inserted Node: %d (%s)\n", s.rollNumber, s.name);
        return newNode(s);
    }

    if (s.rollNumber < node->student.rollNumber)
        node->left = insert(node->left, s);
    else if (s.rollNumber > node->student.rollNumber)
        node->right = insert(node->right, s);
    else
        return node;

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

    if (balance > 1 && s.rollNumber < node->left->student.rollNumber) {
        printf("  -> [Verbose] Tree unbalanced at %d (Left-Left Case)\n", node->student.rollNumber);
        return rightRotate(node);
    }

    if (balance < -1 && s.rollNumber > node->right->student.rollNumber) {
        printf("  -> [Verbose] Tree unbalanced at %d (Right-Right Case)\n", node->student.rollNumber);
        return leftRotate(node);
    }

    if (balance > 1 && s.rollNumber > node->left->student.rollNumber) {
        printf("  -> [Verbose] Tree unbalanced at %d (Left-Right Case)\n", node->student.rollNumber);
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && s.rollNumber < node->right->student.rollNumber) {
        printf("  -> [Verbose] Tree unbalanced at %d (Right-Left Case)\n", node->student.rollNumber);
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void preOrder(Node *root, FILE *fp) {
    if (root != NULL) {
        fprintf(fp, "%d\t%s\t%d\n", root->student.rollNumber, root->student.name, root->student.totalMarks);
        preOrder(root->left, fp);
        preOrder(root->right, fp);
    }
}

void inOrder(Node *root, FILE *fp) {
    if (root != NULL) {
        inOrder(root->left, fp);
        fprintf(fp, "%d\t%s\t%d\n", root->student.rollNumber, root->student.name, root->student.totalMarks);
        inOrder(root->right, fp);
    }
}

void postOrder(Node *root, FILE *fp) {
    if (root != NULL) {
        postOrder(root->left, fp);
        postOrder(root->right, fp);
        fprintf(fp, "%d\t%s\t%d\n", root->student.rollNumber, root->student.name, root->student.totalMarks);
    }
}

void readFileAndBuildTree(const char *filename, Node **root) {
    FILE *fp = fopen(filename, "r");
    Student s;
    if (fp == NULL) {
        printf("Error: Could not open file %s\n", filename);
        exit(1);
    }
    while (fscanf(fp, "%d %s %d", &s.rollNumber, s.name, &s.totalMarks) != EOF) {
        *root = insert(*root, s);
    }
    fclose(fp);
}