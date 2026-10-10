#include <stack>

namespace uma_pilha {

void inverte(std::stack<char>* p) {
  if (p == nullptr) {
    return;
  }

  std::stack<char> p1;
  char x;
  int m = static_cast<int>(p->size());

  // Duas transferencias completas seriam a identidade.
  // Extrair repetidamente a base torna a inversao possivel com uma pilha.
  while (m >= 1) {
    int i = 0;
    while (i < m - 1) {
      p1.push(p->top());
      p->pop();
      ++i;
    }

    x = p->top();
    p->pop();

    i = 0;
    while (i < m - 1) {
      p->push(p1.top());
      p1.pop();
      ++i;
    }

    p1.push(x);
    --m;
  }

  while (!p1.empty()) {
    p->push(p1.top());
    p1.pop();
  }

  // Tempo O(N^2), usando somente a pilha auxiliar permitida e escalares.
}

}  // namespace uma_pilha
