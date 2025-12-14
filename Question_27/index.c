#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

typedef struct Stack {
    Node* data[100];
    int top;
} Stack;

void initStack(Stack* s) {
    s->top = -1;
}

int isEmpty(Stack* s) {
    return s->top == -1;
}

void push(Stack* s, Node* node) {
    s->data[++s->top] = node;
}

Node* pop(Stack* s) {
    return s->data[s->top--];
}

void inorderIterative(Node* root) {
    Stack s;
    initStack(&s);

    Node* current = root;

    while (current != NULL || !isEmpty(&s)) {
        while (current != NULL) {
            push(&s, current);
            current = current->left;
        }

        current = pop(&s);
        printf("%d ", current->data);

        current = current->right;
    }
}

int main() {
    Node* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);

    inorderIterative(root);

    return 0;
}
