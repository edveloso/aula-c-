#include <queue>
#include <stack>

void inverte(std::stack<char>* p) {
  std::queue<char> f;
  char dado;

  if (p == nullptr) {
    return;
  }

  // Saem topo->base para a fila e voltam nessa mesma ordem, invertendo a pilha.
  while (!p->empty()) {
    dado = p->top();
    f.push(dado);
    p->pop();
  }

  while (!f.empty()) {
    dado = f.front();
    p->push(dado);
    f.pop();
  }

  // O(N) em tempo e O(N) de armazenamento externo na fila permitida.
}
