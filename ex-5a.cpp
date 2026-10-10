#include <queue>
#include <stack>

void inverte(std::queue<char>* f) {
  if (f == nullptr) {
    return;
  }

  std::stack<char> p;

  // A pilha recebe frente->topo e devolve topo->fim, invertendo a fila.
  while (!f->empty()) {
    p.push(f->front());
    f->pop();
  }

  while (!p.empty()) {
    f->push(p.top());
    p.pop();
  }

  // Tempo O(N) e O(N) de armazenamento externo na pilha permitida.
}
