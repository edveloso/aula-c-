namespace exercicio_7b {

// Converte uma expressao aritmetica totalmente parentizada para notacao polonesa reversa.
void polonesa(char expressao[], int N, char saida_polonesa[]) {
  if (saida_polonesa == 0) {
    return;
  }

  saida_polonesa[0] = '\0';
  if (expressao == 0 || N <= 0) {
    return;
  }

  // Limite fixo para manter a pilha de operadores em um array nativo C++20.
  static const int CAPACIDADE_MAXIMA = 1000;
  char operadores[CAPACIDADE_MAXIMA];
  int topo = 0;
  int saida = 0;

  for (int i = 0; i < N && expressao[i] != '\0'; ++i) {
    char simbolo = expressao[i];

    if (simbolo == ' ' || simbolo == '\t' || simbolo == '\n' || simbolo == '\r') {
      continue;
    }

    if ((simbolo >= 'A' && simbolo <= 'Z') ||
        (simbolo >= '0' && simbolo <= '9')) {
      saida_polonesa[saida] = simbolo;
      ++saida;
    } else if (simbolo == '+' || simbolo == '-' || simbolo == '*' || simbolo == '/') {
      if (topo >= CAPACIDADE_MAXIMA) {
        saida_polonesa[0] = '\0';
        return;
      }
      operadores[topo] = simbolo;
      ++topo;
    } else if (simbolo == ')') {
      if (topo > 0) {
        --topo;
        saida_polonesa[saida] = operadores[topo];
        ++saida;
      }
    }
  }

  saida_polonesa[saida] = '\0';
}

}  // namespace exercicio_7b
