# Implementation Plan

- [ ] 1. Criar a inversão por duas pilhas auxiliares em `namespace duas_pilhas`.
      Em `inverte-duas-pilhas.cpp`, incluir somente `<stack>` e implementar `void inverte(std::stack<char>* p)`: retornar para ponteiro nulo, declarar apenas `p1`, `p2` e, se necessário, um `char`, e transferir integralmente `p -> p1 -> p2 -> p` com `top()`, `push()` e `pop()`. Documentar em português que as três transferências são três inversões (quantidade ímpar), portanto invertem a pilha em O(N), usando exclusivamente as duas pilhas auxiliares permitidas.
      Files: criar `inverte-duas-pilhas.cpp`.
      Verify: `make build` — o projeto continua compilando, pois `main.cpp` ainda não inclui o novo arquivo nesta etapa.

- [ ] 2. Criar a inversão por uma pilha auxiliar com extração repetida da base em `namespace uma_pilha`.
      Em `inverte-uma-pilha.cpp`, incluir somente `<stack>` e implementar `void inverte(std::stack<char>* p)`: retornar se `p == nullptr`, declarar somente `std::stack<char> p1`, `char x`, `int m = static_cast<int>(p->size())` e contadores escalares. Enquanto `m >= 1`, mover exatamente `m - 1` topos de `p` para `p1` com contador, retirar para `x` o fundo original agora exposto, mover exatamente os mesmos `m - 1` topos de `p1` de volta para `p` com outro contador — sem testar `p1.empty()`, porque sua parte inferior acumula valores — empilhar `x` em `p1` e decrementar `m`; ao final, transferir toda `p1` para `p`. Usar comentários em português explicando que duas transferências completas seriam a identidade e que a extração repetida da base torna esta solução O(N²), sem armazenamento externo além da única pilha permitida e escalares.
      Files: criar `inverte-uma-pilha.cpp`.
      Verify: `make build` — o programa existente continua compilando antes da integração dos novos arquivos.

- [ ] 3. Substituir o teste atual de fila por testes independentes para as duas novas funções de inversão.
      Em `main.cpp`, manter apenas os includes `<iostream>` e `<stack>`, trocar `#include "inverte-pilha.cpp"` por `#include "inverte-duas-pilhas.cpp"` e `#include "inverte-uma-pilha.cpp"`, e preservar uma única `main`. Para cada namespace, criar uma pilha própria com `A`, `B`, `C`, copiar a pilha exclusivamente para exibição topo→base antes da chamada, invocar respectivamente `duas_pilhas::inverte(&p)` ou `uma_pilha::inverte(&p)`, e copiar/exibir novamente após a chamada; os rótulos devem identificar claramente qual algoritmo está sendo demonstrado. Não incluir `inverte-pilha.cpp`, `ex-4a.cpp` ou módulos não relacionados.
      Files: modificar `main.cpp`.
      Verify: executar `make build` e depois `./main`. A saída deve identificar os dois algoritmos e, para cada teste, mostrar a pilha antes como `C B A` e depois como `A B C` (topo → base). Se, excepcionalmente, o alvo `build` não compilar `main.cpp`, executar como alternativa `clang++ -std=c++20 main.cpp -o main` e então `./main`, com a mesma saída esperada.
