template<typename Agregado, typename Tipo>
concept PilhaTAD = requires(Agregado a, Tipo t) {
  { a.topo() };
  { a.desempilha() };
  { a.empilha(t) };
};

const int CAPACIDADE_PILHA_MIN = 100;

struct PilhaMin {
  int dados[CAPACIDADE_PILHA_MIN]{};
  int minimos[CAPACIDADE_PILHA_MIN]{};
  int quantidade = 0;

  // Em pilha vazia, consultas e desempilha retornam 0.
  // Em pilha cheia, empilha ignora o valor recebido.
  int topo() {
    if (quantidade == 0) {
      return 0;
    }
    return dados[quantidade - 1];
  }

  int desempilha() {
    if (quantidade == 0) {
      return 0;
    }
    --quantidade;
    return dados[quantidade];
  }

  void empilha(int valor) {
    if (quantidade == CAPACIDADE_PILHA_MIN) {
      return;
    }

    dados[quantidade] = valor;
    if (quantidade == 0 || valor < minimos[quantidade - 1]) {
      minimos[quantidade] = valor;
    } else {
      minimos[quantidade] = minimos[quantidade - 1];
    }
    ++quantidade;
  }

  int obterMinimo() {
    if (quantidade == 0) {
      return 0;
    }
    return minimos[quantidade - 1];
  }
};

static_assert(PilhaTAD<PilhaMin, int>); // testa se PilhaMin está correto
