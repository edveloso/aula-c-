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
// insere e tamanho sao O(1); maior e segundomaior sao O(N).
// kmaior faz selecoes por varredura, com custo O(N*K).
struct PegaEntreMaioresNaoOrdenado {
  char dados[CAPACIDADE]{};
  int quantidade = 0;

  void insere(char valor) {
    if (quantidade == CAPACIDADE) {
      return;
    }
    dados[quantidade] = valor;
    ++quantidade;
  }

  char maior() {
    if (quantidade == 0) {
      return '\0';
    }

    char resultado = dados[0];
    for (int i = 1; i < quantidade; ++i) {
      if (dados[i] > resultado) {
        resultado = dados[i];
      }
    }
    return resultado;
  }

  char segundomaior() {
    if (quantidade < 2) {
      return '\0';
    }
    return kmaior(2);
  }

  char kmaior(int k) {
    if (k < 1 || k > quantidade) {
      return '\0';
    }

    int restantes = k;
    int temLimite = 0;
    char limite = '\0';

    while (restantes > 0) {
      int encontrou = 0;
      char candidato = '\0';

      for (int i = 0; i < quantidade; ++i) {
        if ((!temLimite || dados[i] < limite) &&
            (!encontrou || dados[i] > candidato)) {
          candidato = dados[i];
          encontrou = 1;
        }
      }

      int ocorrencias = 0;
      for (int i = 0; i < quantidade; ++i) {
        if (dados[i] == candidato) {
          ++ocorrencias;
        }
      }

      if (restantes <= ocorrencias) {
        return candidato;
      }

      restantes -= ocorrencias;
      limite = candidato;
      temLimite = 1;
    }

    return '\0';
  }

  int tamanho() {
    return quantidade;
  }
};

static_assert(PegaEntreMaioresTAD<PegaEntreMaioresNaoOrdenado, char>);
