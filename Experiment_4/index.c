#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

typedef struct {
    int items[MAX];
    int top;
} Stack;

void initStack(Stack *s) {
    s->top = -1;
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

int isFull(Stack *s) {
    return s->top == MAX - 1;
}

void push(Stack *s, int value) {
    if (isFull(s)) {
        printf("Stack Overflow\n");
        return;
    }
    s->items[++(s->top)] = value;
}

int pop(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack Underflow\n");
        return -1;
    }
    return s->items[(s->top)--];
}

int peek(Stack *s) {
    if (isEmpty(s)) {
        return -1;
    }
    return s->items[s->top];
}

void solvePostfix(const char *inputFile, const char *outputFile) {
    FILE *fin = fopen(inputFile, "r");
    FILE *fout = fopen(outputFile, "w");
    char line[256];
    Stack s;
    
    if (!fin || !fout) {
        printf("Error opening postfix files.\n");
        return;
    }

    fprintf(fout, "--- Trace: Postfix Evaluation ---\n\n");

    while (fgets(line, sizeof(line), fin)) {
        initStack(&s);
        line[strcspn(line, "\n")] = 0; 
        fprintf(fout, "Evaluating Expression: %s\n", line);
        
        char *token = strtok(line, " ");
        while (token != NULL) {
            if (isdigit(token[0])) {
                int val = atoi(token);
                push(&s, val);
                fprintf(fout, "  [Step] Read number %d -> PUSH to stack\n", val);
            } else {
                int val2 = pop(&s);
                int val1 = pop(&s);
                int result = 0;
                
                switch(token[0]) {
                    case '+': result = val1 + val2; break;
                    case '-': result = val1 - val2; break;
                    case '*': result = val1 * val2; break;
                    case '/': result = val1 / val2; break;
                }
                push(&s, result);
                fprintf(fout, "  [Step] Read operator '%s' -> POP %d, POP %d -> Calc %d -> PUSH result\n", token, val2, val1, result);
            }
            token = strtok(NULL, " ");
        }
        fprintf(fout, "  => Final Result: %d\n\n", pop(&s));
    }
    
    fclose(fin);
    fclose(fout);
    printf("Postfix evaluation trace saved to '%s'\n", outputFile);
}

void solveStockSpan(const char *inputFile, const char *outputFile) {
    FILE *fin = fopen(inputFile, "r");
    FILE *fout = fopen(outputFile, "w");
    Stack s;
    int prices[MAX];
    int spans[MAX];
    int n = 0;

    if (!fin || !fout) {
        printf("Error opening stock files.\n");
        return;
    }

    while (fscanf(fin, "%d", &prices[n]) != EOF) {
        n++;
    }

    initStack(&s);
    push(&s, 0); 
    spans[0] = 1;

    fprintf(fout, "--- Trace: Stock Span Problem ---\n");
    fprintf(fout, "Prices Input: ");
    for(int i=0; i<n; i++) fprintf(fout, "%d ", prices[i]);
    fprintf(fout, "\n\n");

    fprintf(fout, "Day 0 (Price %d): Span is 1 (Base case). Push Index 0.\n", prices[0]);

    for (int i = 1; i < n; i++) {
        fprintf(fout, "Day %d (Price %d):\n", i, prices[i]);
        
        while (!isEmpty(&s) && prices[peek(&s)] <= prices[i]) {
            int poppedIndex = pop(&s);
            fprintf(fout, "  -> [Debug] Top price %d <= Current %d. POP index %d.\n", prices[poppedIndex], prices[i], poppedIndex);
        }

        spans[i] = (isEmpty(&s)) ? (i + 1) : (i - peek(&s));
        
        if (isEmpty(&s))
            fprintf(fout, "  -> Stack empty. Span = Day + 1 = %d.\n", spans[i]);
        else
            fprintf(fout, "  -> Top is index %d. Span = Current(%d) - Top(%d) = %d.\n", peek(&s), i, peek(&s), spans[i]);

        push(&s, i);
        fprintf(fout, "  -> PUSH index %d.\n\n", i);
    }

    fprintf(fout, "Final Spans: ");
    for (int i = 0; i < n; i++) fprintf(fout, "%d ", spans[i]);
    fprintf(fout, "\n");

    fclose(fin);
    fclose(fout);
    printf("Stock Span trace saved to '%s'\n", outputFile);
}

int main() {
    solvePostfix("input_postfix.txt", "output_postfix_trace.txt");
    solveStockSpan("input_stock.txt", "output_stock_trace.txt");
    return 0;
}