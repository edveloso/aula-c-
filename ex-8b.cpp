template<typename Agregado, typename Tipo>
concept PegaEntreMaioresTAD = requires(Agregado a, Tipo t) {
    { a.insere(t) };
    { a.maior() };
    { a.segundomaior() };
    { a.kmaior(1) };
    { a.tamanho() };
};

const int CAPACIDADE = 100;

// Usa apenas o vetor fixo dados e variaveis escalares locais.
// Em vetor cheio, insere ignora o valor. Em consultas invalidas, retorna '\0'.
// Valores repetidos ocupam posicoes distintas; '\0' tambem pode ser inserido.
// dados permanece ordenado em ordem crescente por Bubble Sort.
// insere e O(N^2); maior, segundomaior, kmaior e tamanho sao O(1).
struct PegaEntreMaioresOrdenacaoLenta {
  char dados[CAPACIDADE]{};
  int quantidade = 0;

  void insere(char valor) {
    if (quantidade == CAPACIDADE) {
      return;
    }

    dados[quantidade] = valor;
    ++quantidade;

    for (int i = 0; i < quantidade - 1; ++i) {
      for (int j = 0; j < quantidade - 1 - i; ++j) {
        if (dados[j] > dados[j + 1]) {
          char temporario = dados[j];
          dados[j] = dados[j + 1];
          dados[j + 1] = temporario;
        }
      }
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

static_assert(PegaEntreMaioresTAD<PegaEntreMaioresOrdenacaoLenta, char>);
