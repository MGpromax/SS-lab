#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char prod[3][10] = {"A->aBa", "B->bB", "B->@"};
char input[10], stack[25];
int top = -1, j = 0, k, l;

void push(char item) { stack[++top] = item; }
void pop() { top = top - 1; }
void display() { for (j = top; j >= 0; j--) printf("%c", stack[j]); }
void stackpush(char p) {
  if (p == 'A') {
    pop();
    for (j = strlen(prod[0]) - 1; j >= 3; j--)
      push(prod[0][j]);
  } else {
    pop();
    for (j = strlen(prod[1]) - 1; j >= 3; j--)
      push(prod[1][j]);
  }
}

int main() {
  printf("first(A)={a}\t");
  printf("follow(A)={$}\n");
  printf("first(B)={b,@}\t");
  printf("follow(B)={a}\n\n");
  printf("\t a \t b \t $ \n");
  printf("A\t%s\n", prod[0]);
  printf("B\t%s\t%s\n", prod[2], prod[1]);
  printf("Enter the input string terminated with $ to parse: ");
  scanf("%s", input);

  for (int i = 0; input[i] != '\0'; i++) {
    if ((input[i] != 'a') && (input[i] != 'b') && (input[i] != '$')) {
      printf("Invalid string");
      exit(0);
    }
  }

  if (input[strlen(input) - 1] != '$') {
    printf("\n\nInput string entered without end marker $\n");
    exit(0);
  }

  push('$');
  push('A');
  int i = 0;
  printf("\n\nstack\tInput\taction");
  printf("\n---------\n");

  while (i != strlen(input) && stack[top] != '$') {
    printf("\n");
    display();
    printf("\t");
    printf("%s\t", (input + i));

    if (stack[top] == 'A') {
      printf("A->aBa");
      stackpush('A');
    } else if (stack[top] == 'B') {
      if (input[i] != 'b') {
        printf("B->@");
        printf("\tmatched @");
        pop();
      } else {
        printf("B->bB");
        stackpush('B');
      }
    } else {
      if (stack[top] == input[i]) {
        printf("pop%c", input[i]);
        printf("\tmatched %c", input[i]);
        pop();
        i++;
      } else {
        break;
      }
    }
  }

  if (stack[top] == '$' && input[i] == '$') {
    printf("\n$\t$");
    printf("\nValid string Accepted\n");
  } else {
    printf("\nInvalid string rejected\n");
  }

  return 0;
}
