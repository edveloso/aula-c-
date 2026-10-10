template<typename Agregado, typename Tipo>
concept DequeTAD = requires(Agregado a, Tipo t) {
  // requer operação de consulta ao elemento 'inicio'
  { a.inicio() };
  // requer operação de consulta ao elemento 'fim'
  { a.fim() };
  // requer operação 'insereInicio' sobre tipo 't'
  { a.insereInicio(t) };
  // requer operação 'insereFim' sobre tipo 't'
  { a.insereFim(t) };
  // requer operação 'removeInicio' e retorna tipo 't'
  { a.removeInicio() };
  // requer operação 'removeFim' e retorna tipo 't'
  { a.removeFim() };
};

const int CAPACIDADE = 100;

struct Deque {
  char dados[CAPACIDADE]{};
  int inicioIndice = 0;
  int fimIndice = 0;
  int quantidade = 0;

  // inicioIndice aponta para o primeiro dado; fimIndice aponta para a vaga.
  // As operações só ajustam índices e quantidade, sem deslocar elementos: O(1).
  char inicio() {
    if (quantidade == 0) {
      return '\0';
    }
    return dados[inicioIndice];
  }

  char fim() {
    if (quantidade == 0) {
      return '\0';
    }
    int ultimoIndice = fimIndice - 1;
    if (ultimoIndice < 0) {
      ultimoIndice = CAPACIDADE - 1;
    }
    return dados[ultimoIndice];
  }

  void insereInicio(char elemento) {
    if (quantidade == CAPACIDADE) {
      return;
    }
    --inicioIndice;
    if (inicioIndice < 0) {
      inicioIndice = CAPACIDADE - 1;
    }
    dados[inicioIndice] = elemento;
    ++quantidade;
  }

  void insereFim(char elemento) {
    if (quantidade == CAPACIDADE) {
      return;
    }
    dados[fimIndice] = elemento;
    ++fimIndice;
    if (fimIndice == CAPACIDADE) {
      fimIndice = 0;
    }
    ++quantidade;
  }

  char removeInicio() {
    if (quantidade == 0) {
      return '\0';
    }
    char elemento = dados[inicioIndice];
    ++inicioIndice;
    if (inicioIndice == CAPACIDADE) {
      inicioIndice = 0;
    }
    --quantidade;
    return elemento;
  }

  char removeFim() {
    if (quantidade == 0) {
      return '\0';
    }
    --fimIndice;
    if (fimIndice < 0) {
      fimIndice = CAPACIDADE - 1;
    }
    --quantidade;
    return dados[fimIndice];
  }
};

static_assert(DequeTAD<Deque, char>); // testa se Deque está correto
