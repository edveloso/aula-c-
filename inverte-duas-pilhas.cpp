#include <stack>

namespace duas_pilhas {

void inverte(std::stack<char>* p) {
  if (p == nullptr) {
    return;
  }

  std::stack<char> p1;
  std::stack<char> p2;

  // Tres transferencias sao tres inversoes: uma quantidade impar inverte P.
  while (!p->empty()) {
    p1.push(p->top());
    p->pop();
  }
  while (!p1.empty()) {
    p2.push(p1.top());
    p1.pop();
  }
  while (!p2.empty()) {
    p->push(p2.top());
    p2.pop();
  }

  // Tempo O(N), usando somente as duas pilhas auxiliares permitidas.
}

}  // namespace duas_pilhas
