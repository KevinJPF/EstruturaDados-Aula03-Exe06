#include "pilha.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

void strrev(char *str) {
  int start = 0;
  int end = strlen(str) - 1;
  char temp;

  while (start < end) {
    temp = str[start];
    str[start] = str[end];
    str[end] = temp;

    start++;
    end--;
  }
}

int prio(char o) {
  switch (o) {
  case '(':
    return 0;
  case '+':
  case '-':
    return 1;
  case '*':
  case '/':
    return 2;
  }
  return -1; // operador inválido!
}

char *prefixa(char *e) {
  static char s[256];
  int j = 0;
  Pilha P = pilha(256);
  for (int i = strlen(e) - 1; i >= 0; i--)
    if (e[i] == ')')
      empilha(')', P);
    else if (isdigit(e[i]))
      s[j++] = e[i];
    else if (strchr("+-/*", e[i])) {
      while (!vaziap(P) && prio(topo(P)) >= prio(e[i]))
        s[j++] = desempilha(P);
      empilha(e[i], P);
    } else if (e[i] == '(') {
      while (topo(P) != ')')
        s[j++] = desempilha(P);
      desempilha(P);
    }
  while (!vaziap(P))
    s[j++] = desempilha(P);
  s[j] = '\0';
  destroip(&P);
  strrev(s);
  return s;
}

int valpre(char *e) {
  Pilha P = pilha(256);
  for (int i = strlen(e) - 1; i >= 0; i--)
    if (isdigit(e[i]))
      empilha(e[i] - '0', P);
    else {
      int x = desempilha(P);
      int y = desempilha(P);
      switch (e[i]) {
      case '+':
        empilha(x + y, P);
        break;
      case '-':
        empilha(x - y, P);
        break;
      case '*':
        empilha(x * y, P);
        break;
      case '/':
        empilha(x / y, P);
        break;
      }
    }
  int z = desempilha(P);
  destroip(&P);
  return z;
}

int main(void) {
  char e[513];
  printf("Infixa? ");
  fgets(e, sizeof(e), stdin);
  printf("Prefixa: %s\n", prefixa(e));
  printf("Valor Numerico: %d\n", valpre(prefixa(e)));
  return 0;
}
