template<typename Iterador, typename Tipo>
concept IteradorTAD = requires(Iterador it) {
  { it.terminou() };
  { it.atual() };
  { it.proximo() };
};

template<typename Agregado, typename Tipo>
concept SacoTAD = requires(Agregado a, Tipo dado) {
  { a.cria() };
  { a.libera() };
  { a.vazio() };
  { a.tamanho() };
  { a.adiciona(dado) };
  { a.itera() };
  { a.busca(dado) };
  { a.remove(a.itera()) };
};

template<typename Agregado, typename Tipo>
concept SacoVaiEVemTAD = requires(Agregado a, Tipo dado) {
  { a.cria() };
  { a.libera() };
  { a.vazio() };
  { a.tamanho() };
  { a.adiciona(dado) };
  { a.itera() };
  { a.iteravolta() };
  { a.busca(dado) };
  { a.remove(a.itera()) };
};

// A lista duplamente encadeada permite caminhar para tras em O(1) por passo
// pelo campo anterior, sem copiar os elementos para outra estrutura.
struct NoEnc {
  char dado;
  NoEnc* proximo;
  NoEnc* anterior;
};

struct IteradorNoEnc {
  NoEnc* no;
  int sentido;

  // Para iterador terminado, atual devolve '\0' e proximo nao altera o estado.
  bool terminou() {
    return no == nullptr;
  }

  char atual() {
    if (terminou()) {
      return '\0';
    }
    return no->dado;
  }

  void proximo() {
    if (terminou()) {
      return;
    }

    if (sentido > 0) {
      no = no->proximo;
    } else {
      no = no->anterior;
    }
  }
};

// cria e vazio sao O(1). libera e um percurso completo sao O(N).
// tamanho, adiciona, itera e iteravolta sao O(1).
// As acoes do iterador sao O(1) por passo; busca e O(N) no pior caso.
// remove e O(1). O armazenamento total e O(N), um no por elemento.
struct SacoVaiEVem {
  NoEnc* inicio;
  NoEnc* fim;
  int quantidade;

  void cria() {
    inicio = nullptr;
    fim = nullptr;
    quantidade = 0;
  }

  void libera() {
    NoEnc* atual = inicio;
    while (atual != nullptr) {
      NoEnc* seguinte = atual->proximo;
      delete atual;
      atual = seguinte;
    }
    inicio = nullptr;
    fim = nullptr;
    quantidade = 0;
  }

  bool vazio() {
    return quantidade == 0;
  }

  int tamanho() {
    return quantidade;
  }

  // Insere no inicio em O(1) e aceita dados repetidos.
  void adiciona(char dado) {
    NoEnc* novo = new NoEnc;
    novo->dado = dado;
    novo->anterior = nullptr;
    novo->proximo = inicio;

    if (inicio != nullptr) {
      inicio->anterior = novo;
    } else {
      fim = novo;
    }

    inicio = novo;
    ++quantidade;
  }

  IteradorNoEnc itera() {
    IteradorNoEnc it;
    it.no = inicio;
    it.sentido = 1;
    return it;
  }

  IteradorNoEnc iteravolta() {
    IteradorNoEnc it;
    it.no = fim;
    it.sentido = -1;
    return it;
  }

  IteradorNoEnc busca(char dado) {
    IteradorNoEnc it = itera();
    while (!it.terminou()) {
      if (it.atual() == dado) {
        return it;
      }
      it.proximo();
    }
    return it;
  }

  // Se it terminou, nada e removido. Ao remover, it e qualquer iterador que
  // apontava para o no removido tornam-se invalidos.
  void remove(IteradorNoEnc it) {
    if (it.terminou()) {
      return;
    }

    NoEnc* removido = it.no;
    if (removido->anterior != nullptr) {
      removido->anterior->proximo = removido->proximo;
    } else {
      inicio = removido->proximo;
    }

    if (removido->proximo != nullptr) {
      removido->proximo->anterior = removido->anterior;
    } else {
      fim = removido->anterior;
    }

    delete removido;
    --quantidade;
  }
};

static_assert(IteradorTAD<IteradorNoEnc, char>);
static_assert(SacoTAD<SacoVaiEVem, char>);
static_assert(SacoVaiEVemTAD<SacoVaiEVem, char>);
