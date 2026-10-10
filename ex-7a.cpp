namespace exercicio_7a {

// Avalia uma expressao em notacao polonesa reversa com variaveis A ate G.
int avaliaPolonesa(const char expressao[], const int valores[], int N) {
  if (expressao == 0 || valores == 0 || N < 1 || N > 7) {
    return 0;
  }

  int pilha[7];
  int topo = 0;

  for (int i = 0; expressao[i] != '\0'; ++i) {
    char simbolo = expressao[i];

    if (simbolo >= 'A' && simbolo <= 'G') {
      int indice = simbolo - 'A';
      if (indice >= N || topo == 7) {
        return 0;
      }
      pilha[topo] = valores[indice];
      ++topo;
    } else if (simbolo == '+' || simbolo == '-' || simbolo == '*' || simbolo == '/') {
      if (topo < 2) {
        return 0;
      }

      int direito = pilha[topo - 1];
      int esquerdo = pilha[topo - 2];
      topo -= 2;

      if (simbolo == '/' && direito == 0) {
        return 0;
      }

      if (simbolo == '+') {
        pilha[topo] = esquerdo + direito;
      } else if (simbolo == '-') {
        pilha[topo] = esquerdo - direito;
      } else if (simbolo == '*') {
        pilha[topo] = esquerdo * direito;
      } else {
        pilha[topo] = esquerdo / direito;
      }
      ++topo;
    } else {
      return 0;
    }
  }

  if (topo != 1) {
    return 0;
  }

  // Com {3, 3, 2, 1, 1}, AB+CED/-* resulta em 6, e nao em -4.
  return pilha[0];
}

}  // namespace exercicio_7a
