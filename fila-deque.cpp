#include "deque.cpp"

template<typename Agregado, typename Tipo>
concept FilaTAD = requires(Agregado a, Tipo t) {
  { a.frente() };
  { a.enfileira(t) };
  { a.desenfileira() };
};

struct FilaDeque {
  Deque d;

  char frente() {
    return d.inicio();
  }

  void enfileira(char valor) {
    d.insereFim(valor);
  }

  char desenfileira() {
    return d.removeInicio();
  }
};

static_assert(DequeTAD<Deque, char>);
static_assert(FilaTAD<FilaDeque, char>);
