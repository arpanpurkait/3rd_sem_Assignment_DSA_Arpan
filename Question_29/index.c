#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* newNode(int data) {
    struct Node* n = (struct Node*)malloc(sizeof(struct Node));
    n->data = data;
    n->left = NULL;
    n->right = NULL;
    return n;
}

void serialize(struct Node* root, FILE* fp) {
    if (root == NULL) {
        fprintf(fp, "# ");
        return;
    }
    fprintf(fp, "%d ", root->data);
    serialize(root->left, fp);
    serialize(root->right, fp);
}

struct Node* deserialize(FILE* fp) {
    char buf[10];
    if (fscanf(fp, "%s", buf) != 1)
        return NULL;

    if (buf[0] == '#')
        return NULL;

    struct Node* root = newNode(atoi(buf));
    root->left = deserialize(fp);
    root->right = deserialize(fp);
    return root;
}

struct Node* prev = NULL;

void flatten(struct Node* root) {
    if (root == NULL)
        return;

    flatten(root->right);
    flatten(root->left);

    root->right = prev;
    root->left = NULL;
    prev = root;
}

int main() {
    struct Node* root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(5);
    root->left->left = newNode(3);
    root->left->right = newNode(4);
    root->right->right = newNode(6);

    FILE* fp = fopen("tree.txt", "w");
    serialize(root, fp);
    fclose(fp);

    fp = fopen("tree.txt", "r");
    struct Node* newRoot = deserialize(fp);
    fclose(fp);

    flatten(newRoot);

    struct Node* curr = newRoot;
    while (curr) {
        printf("%d ", curr->data);
        curr = curr->right;
    }

    return 0;
}
