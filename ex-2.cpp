#include <queue>
#include <string>

template<typename Agregado, typename Tipo>
concept PilhaTAD = requires(Agregado a, Tipo t) {
  { a.topo() };
  { a.empilha(t) };
  { a.desempilha() };
};

struct Pilha2F {
  std::queue<char> f1;
  std::queue<char> f2;
  // Invariante: o topo da pilha permanece na frente de f1.

  char topo() {
    if (f1.empty()) {
      return '\0';
    }
    return f1.front(); // O(1)
  }

  void empilha(char valor) {
    char elemento;
    f2.push(valor);

    // Move os elementos antigos para tras do novo topo: O(N).
    while (!f1.empty()) {
      elemento = f1.front();
      f1.pop();
      f2.push(elemento);
    }

    while (!f2.empty()) {
      elemento = f2.front();
      f2.pop();
      f1.push(elemento);
    }
  }

  char desempilha() {
    if (f1.empty()) {
      return '\0';
    }
    char elemento = f1.front();
    f1.pop();
    return elemento; // O(1)
  }
};

static_assert(PilhaTAD<Pilha2F, char>);




#include <iostream>
int main(){
  Pilha2F d;
  std::string s =  "skatenaveia";
  for(char c : s){
    d.empilha(c);
  }
  while(d.topo() != '\0'){
    std::cout << d.desempilha();
  }

  return 0;

}