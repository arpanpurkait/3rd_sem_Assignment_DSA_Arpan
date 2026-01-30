#include<stdio.h>
#include<ctype.h>
#define MAX 100

char stack[MAX];
int top = -1;
void push(char c){
    
    stack[++top] = c;
}
char pop(){
    return stack[top--];
}
int precedence(char c){
    if (c == '+' || c == '-')
        return 1;
    else if (c == '*' || c == '/')
        return 2;
    else if (c == '^')
        return 3;
    else
        return 0;
}
int main (){
    char x;
    char infix[MAX], postfix[MAX], c;
    int i = 0, j = 0;
    printf("Enter infix expression: ");
    scanf("%s", infix);
    while(infix[i] != '\0'){

        // if operand , add to postfix
        if(isalnum(infix[i])){
            postfix[j++] = infix[i];
        }
        // if '(', push to stack
        else if(infix[i] == '('){
            push(infix[i]);
        }
        // if ')', pop and add to postfix until '(' is found
        else if(infix[i] == ')'){
            while((x = pop()) != '('){
                postfix[j++] = x;
            }
        }
        else {
            while(top != -1 && stack[top] != '(' && precedence(stack[top]) >= precedence(infix[i])){
                postfix[j++] = pop();
            }
            push(infix[i]);
        }
        i++;
    }
    // pop all operators from stack
    while(top != -1){
        postfix[j++] = pop();
    }
    postfix[j] = '\0';
    printf("Postfix expression: %s\n", postfix);
    return 0;
}