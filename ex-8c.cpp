template<typename Agregado, typename Tipo>
concept PegaEntreMaioresTAD = requires(Agregado a, Tipo t) {
    { a.insere(t) };
    { a.maior() };
    { a.segundomaior() };
    { a.kmaior(1) };
    { a.tamanho() };
};

const int CAPACIDADE = 100;

// Usa somente os vetores fixos dados e auxiliar, alem de variaveis escalares locais.
// Em vetor cheio, insere ignora o valor. Em consultas invalidas, retorna '\0'.
// Valores repetidos ocupam posicoes distintas; '\0' tambem pode ser inserido.
// dados permanece ordenado em ordem crescente por Merge Sort iterativo.
// insere e O(N log N), com O(N) auxiliar; as consultas e tamanho sao O(1).
struct PegaEntreMaioresOrdenacaoEficiente {
  char dados[CAPACIDADE]{};
  char auxiliar[CAPACIDADE]{};
  int quantidade = 0;

  void insere(char valor) {
    if (quantidade == CAPACIDADE) {
      return;
    }

    dados[quantidade] = valor;
    ++quantidade;

    int largura = 1;
    while (largura < quantidade) {
      int inicio = 0;
      while (inicio < quantidade) {
        int meio = inicio + largura;
        int fim = inicio + 2 * largura;

        if (meio > quantidade) {
          meio = quantidade;
        }
        if (fim > quantidade) {
          fim = quantidade;
        }

        int esquerda = inicio;
        int direita = meio;
        int destino = inicio;

        while (esquerda < meio && direita < fim) {
          if (dados[esquerda] <= dados[direita]) {
            auxiliar[destino] = dados[esquerda];
            ++esquerda;
          } else {
            auxiliar[destino] = dados[direita];
            ++direita;
          }
          ++destino;
        }

        while (esquerda < meio) {
          auxiliar[destino] = dados[esquerda];
          ++esquerda;
          ++destino;
        }

        while (direita < fim) {
          auxiliar[destino] = dados[direita];
          ++direita;
          ++destino;
        }

        for (int i = inicio; i < fim; ++i) {
          dados[i] = auxiliar[i];
        }

        inicio += 2 * largura;
      }
      largura *= 2;
    }
  }

  char maior() {
    if (quantidade == 0) {
      return '\0';
    }
    return dados[quantidade - 1];
  }

  char segundomaior() {
    if (quantidade < 2) {
      return '\0';
    }
    return dados[quantidade - 2];
  }

  char kmaior(int k) {
    if (k < 1 || k > quantidade) {
      return '\0';
    }
    return dados[quantidade - k];
  }

  int tamanho() {
    return quantidade;
  }
};

static_assert(PegaEntreMaioresTAD<PegaEntreMaioresOrdenacaoEficiente, char>);
