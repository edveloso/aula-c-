#include <queue>

void inverte(std::queue<char>* f) {
  if (f == nullptr) {
    return;
  }

  std::queue<char> f1;
  std::queue<char> f2;
  int m = static_cast<int>(f->size());

  // Cada rotacao coloca o ultimo elemento restante na frente de f.
  while (m >= 1) {
    int i = 0;
    while (i < m - 1) {
      f->push(f->front());
      f->pop();
      ++i;
    }

    f1.push(f->front());
    f->pop();
    --m;
  }

  while (!f1.empty()) {
    f2.push(f1.front());
    f1.pop();
  }

  while (!f2.empty()) {
    f->push(f2.front());
    f2.pop();
  }

  // Tempo O(N^2), usando somente as duas filas auxiliares e escalares.
}
