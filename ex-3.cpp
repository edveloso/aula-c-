#include <stack>

template<typename Agregado, typename Tipo>
concept FilaTAD = requires(Agregado a, Tipo t) {
  { a.frente() };
  { a.enfileira(t) };
  { a.desenfileira() };
};

struct Fila2P {
  // p1 recebe novos elementos; p2 mantém a frente da fila no topo.
  std::stack<char> p1;
  std::stack<char> p2;

  void transfereParaP2() {
    if (p2.empty()) {
      char valor;
      while (!p1.empty()) {
        valor = p1.top();
        p1.pop();
        p2.push(valor);
      }
    }
  }

  void enfileira(char valor) {
    p1.push(valor);
  }

  char frente() {
    transfereParaP2();
    if (p2.empty()) {
      return '\0';
    }
    return p2.top();
  }

  char desenfileira() {
    transfereParaP2();
    if (p2.empty()) {
      return '\0';
    }
    char valor = p2.top();
    p2.pop();
    return valor;
  }
  // Transferências ocorrem sob demanda: operações têm custo amortizado O(1).
};

static_assert(FilaTAD<Fila2P, char>);
