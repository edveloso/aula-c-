#include "deque.cpp"

template<typename Agregado, typename Tipo>
concept PilhaTAD = requires(Agregado a, Tipo t) {
  { a.topo() };
  { a.empilha(t) };
  { a.desempilha() };
};

struct PilhaDeque {
  Deque d;

  char topo() {
    return d.fim();
  }

  void empilha(char valor) {
    d.insereFim(valor);
  }

  char desempilha() {
    return d.removeFim();
  }
};

static_assert(PilhaTAD<PilhaDeque, char>); // testa se Pilha está correta


#include <iostream>
int main(){
  PilhaDeque d;
  d.empilha('a');
  d.empilha('b');
  d.empilha('c');
  std::cout << d.desempilha();
  std::cout << d.desempilha();
  std::cout << d.desempilha();
  std::cout << d.topo();

  return 0;

}