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
// QuickSelect preserva os elementos, mas pode alterar a ordem de dados.
// maior chama kmaior(1) e segundomaior chama kmaior(2).
// insere e tamanho sao O(1); kmaior, maior e segundomaior sao O(N) esperado
// e O(N^2) no pior caso. O espaco auxiliar e O(1), pois QuickSelect e iterativo.
// O pior caso ocorre com particoes muito desbalanceadas pelo pivo simples no fim,
// por exemplo, quando a entrada ja esta ordenada.
struct PegaEntreMaioresQuickSelect {
  char dados[CAPACIDADE]{};
  int quantidade = 0;

  void insere(char valor) {
    if (quantidade == CAPACIDADE) {
      return;
    }
    dados[quantidade] = valor;
    ++quantidade;
  }

  int particiona(int baixo, int alto) {
    char pivo = dados[alto];
    int menor = baixo;

    for (int i = baixo; i < alto; ++i) {
      if (dados[i] <= pivo) {
        char temporario = dados[menor];
        dados[menor] = dados[i];
        dados[i] = temporario;
        ++menor;
      }
    }

    char temporario = dados[menor];
    dados[menor] = dados[alto];
    dados[alto] = temporario;
    return menor;
  }

  char maior() {
    return kmaior(1);
  }

  char segundomaior() {
    return kmaior(2);
  }

  char kmaior(int k) {
    if (k < 1 || k > quantidade) {
      return '\0';
    }

    int alvo = quantidade - k;
    int baixo = 0;
    int alto = quantidade - 1;

    while (baixo <= alto) {
      int indicePivo = particiona(baixo, alto);
      if (indicePivo == alvo) {
        return dados[indicePivo];
      }
      if (indicePivo < alvo) {
        baixo = indicePivo + 1;
      } else {
        alto = indicePivo - 1;
      }
    }

    return '\0';
  }

  int tamanho() {
    return quantidade;
  }
};

static_assert(PegaEntreMaioresTAD<PegaEntreMaioresQuickSelect, char>);
