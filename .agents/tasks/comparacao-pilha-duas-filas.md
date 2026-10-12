# Comparação: `PilhaDuasFilas` (C++) × `Pilha2F` (Python)

## Resumo

1. **O algoritmo central é equivalente apenas sob precondições.** Para uma pilha que não contém `char '\0'` e não excede a capacidade de 100 elementos, os dois códigos fazem o mesmo: inserem o novo valor em `f2`, transferem `f1` para o final de `f2` preservando a ordem FIFO e transferem `f2` de volta para `f1`. Assim, o novo valor fica na frente de `f1`, que é o topo. Contudo, o Python determina o término das transferências por tamanho; o C++ usa `frente() != '\0'`. Portanto, o comportamento não é equivalente para todos os valores de `char`: `\0` é um valor válido no TAD C++ e interrompe as transferências prematuramente.
2. O C++ faz os dois transbordos em laços embutidos, não tem API de tamanho nem ciclo de vida explícito, é concreto para `char` e usa `\0` tanto como valor-sentinela de vazio quanto como retorno de remoção/consulta em estrutura vazia. O Python é parametrizado/anotado para `str`, expõe `tamanho()`, inicializa/libera explicitamente e usa a contagem, sem sentinela de dados.
3. **Quanto à restrição estrutural original, o C++ atende:** `PilhaDuasFilas` contém exatamente duas `FilaDeque` e usa somente variáveis locais `char` nos laços; não há STL, referências (`&`/`&&`), algoritmos prontos, vetores/listas auxiliares ou sobrecarga de operadores. Essa conclusão é independente da ressalva funcional do sentinela `\0`.
4. Há problemas materiais de API/integração: `FilaDeque` e `PilhaDuasFilas` não expõem `tamanho()`, logo não implementam a interface usada pelo Python; o `Makefile` atual compila `main.cpp`, mas esse `main` só inclui/testa `FilaDeque`, não `PilhaDuasFilas`; e incluir simultaneamente `fila-deque.cpp` e `pilha-duas-filas.cpp` no mesmo arquivo causa redefinições, pois o segundo já inclui o primeiro.

## Evidências

### Ordem e custo do algoritmo

- Em `pilha-duas-filas.cpp:17-30`, `empilha` executa a mesma sequência conceitual do Python:
  1. `f2.enfileira(valor)` (`linha 18`);
  2. retira da frente de `f1` e enfileira no fim de `f2` (`linhas 20-23`);
  3. retira da frente de `f2` e enfileira no fim de `f1` (`linhas 25-28`).
- Em `fila-deque.cpp:11-19`, a fila insere no fim (`d.insereFim`) e remove/consulta no início (`d.removeInicio`/`d.inicio`). Assim, cada transferência preserva a ordem FIFO, como `transbordaFila` no Python. Depois da primeira transferência, `f2` contém `[novo, antigo topo, ...]`; depois da segunda, `f1` conserva essa ordem. `topo()` consulta `f1.frente()` em `pilha-duas-filas.cpp:13-15`, e `desempilha()` remove essa mesma frente em `linhas 32-34`.
- Consequentemente, `empilha` movimenta o novo elemento uma vez e os `N` anteriores duas vezes: tempo O(N), espaço auxiliar O(1); `topo` e `desempilha` são O(1), exatamente como a estratégia descrita no Python.
- A diferença decisiva está em `pilha-duas-filas.cpp:20` e `:25`: os laços testam `f1.frente() != '\0'` e `f2.frente() != '\0'`. A referência usa `origem.tamanho() > 0`. Em `deque.cpp:27-31`, `inicio()` retorna `\0` quando vazio, mas pode igualmente retornar um elemento armazenado cujo valor é `\0`. Exemplo: após empilhar `A`, `\0`, `B`, um transbordo para ao encontrar `\0`, deixando elementos não transferidos. Pior, empilhar `\0` em uma pilha vazia faz o segundo laço não executar, mantendo esse elemento em `f2` em vez de `f1`.

### Diferenças de interface e ciclo de vida

- **Helper versus laços:** o Python centraliza a transferência em `transbordaFila(origem, destino)` e a invoca duas vezes. O C++ replica os dois laços diretamente em `PilhaDuasFilas::empilha` (`pilha-duas-filas.cpp:20-28`). Essa diferença, por si só, não altera a ordem nem a complexidade; altera apenas reutilização e torna o teste sentinela parte da implementação.
- **Tamanho:** `PilhaDuasFilas` declara apenas `topo`, `empilha` e `desempilha` (`pilha-duas-filas.cpp:13-34`). `FilaDeque` também só declara `frente`, `enfileira` e `desenfileira` (`fila-deque.cpp:11-19`). Não há `tamanho()` na cadeia C++; embora `Deque` mantenha `quantidade` publicamente (`deque.cpp:21-23`), ela não é exposta pela abstração de fila/pilha. Já o Python usa `f1.tamanho()` para a própria pilha e para todo transbordo.
- **Verificação de conceito:** `PilhaTAD` em `pilha-duas-filas.cpp:3-7` verifica somente a existência de `topo`, `empilha` e `desempilha`; ele não valida tamanho, tipos de retorno, comportamento em vazio ou limites. Os `static_assert`s em `linhas 37-39` passam sem demonstrar equivalência à interface Python estendida.
- **Inicialização e liberação:** `Pilha2F.cria()` constrói/inicializa duas filas e `libera()` delega a liberação. O C++ não possui `cria` ou `libera`; a inicialização ocorre pelos inicializadores de membro de `Deque` — `dados[CAPACIDADE]{}`, índices e quantidade em `deque.cpp:20-23` — quando os membros `f1` e `f2` são construídos. Como só há armazenamento embutido, não há recurso dinâmico a liberar explicitamente.
- **Tipo:** a referência é descrita sobre `str` e aceita a interface genérica `FilaTAD[str]`; o código C++ é explicitamente de `char` em `FilaDeque` (`fila-deque.cpp:11-19`) e `PilhaDuasFilas` (`pilha-duas-filas.cpp:17,32`). Além do domínio menor, `char '\0'` tem a ambiguidade funcional acima.
- **Vazio e cheio:** `Deque::inicio`, `fim`, `removeInicio` e `removeFim` retornam `\0` em vazio (`deque.cpp:27-31`, `:35-39`, `:70-74`, `:85-89`). `insereInicio` e `insereFim` retornam sem sinalizar erro quando `quantidade == CAPACIDADE` (`deque.cpp:46-48`, `:57-59`); logo, a capacidade é fixa em 100 (`linha 18`) e uma inserção em pilha cheia é silenciosamente descartada. A referência fornecida não especifica esse contrato de vazio/cheio e, principalmente, não usa o conteúdo do elemento para reconhecer vazio.

### Restrições C++ e integração/compilação

- `PilhaDuasFilas` tem somente `FilaDeque f1` e `FilaDeque f2` como membros (`pilha-duas-filas.cpp:9-10`); `FilaDeque` contém somente `Deque d` (`fila-deque.cpp:8-9`). Os únicos auxiliares de `empilha` são `char elemento` (`linhas 21 e 26`). Isso satisfaz duas filas como armazenamento e espaço auxiliar constante.
- Os arquivos lidos usam array nativo (`char dados[CAPACIDADE]`), inteiros e cópias de `char`; não usam containers/algoritmos STL, referências ou sobrecargas de `operator=`. Portanto atendem às proibições declaradas na solicitação original.
- `Makefile:1-2` compila somente `main.cpp`. O `main.cpp:2` inclui `fila-deque.cpp` e o programa de `main.cpp:4-15` cria/testa somente `FilaDeque`; não há inclusão, instanciação ou teste de `PilhaDuasFilas`. Assim, `make build` não valida a nova pilha.
- `pilha-duas-filas.cpp:1` inclui `fila-deque.cpp`, e este inclui `deque.cpp` (`fila-deque.cpp:1`). Se um `main.cpp` tentar testar a pilha acrescentando `#include "pilha-duas-filas.cpp"` sem remover o `#include "fila-deque.cpp"` atual, as definições de conceitos, `Deque` e `FilaDeque` serão vistas duas vezes no mesmo translation unit, ocasionando erro de redefinição. Compilar o arquivo da pilha isoladamente não fornece `main`, portanto não forma executável sozinho.
- Foi tentada somente uma validação não geradora de artefato, `clang++ -std=c++20 -fsyntax-only pilha-duas-filas.cpp`, mas ela excedeu o limite do ambiente após 120 s sem saída. Portanto, esta análise não declara uma confirmação de compilação por execução; os apontamentos de integração acima foram estabelecidos pela leitura dos arquivos.

## Conclusões e recomendações

A estratégia de duas filas do C++ corresponde à estratégia da referência no caso restrito de dados diferentes de `\0` e capacidade disponível. Ela respeita a exigência de duas filas e espaço auxiliar constante, mas não possui equivalência total de domínio nem de interface: o uso de `\0` como teste de vazio conflita com o requisito de aceitar `char`, e falta a API `tamanho()` presente na referência.

Recomenda-se corrigir materialmente a detecção de esvaziamento para se basear em uma contagem exposta pela fila/deque, e não no valor do elemento; isso preserva `\0` como dado válido. Caso a intenção seja espelhar integralmente a interface de referência, deve-se também expor `tamanho()` em `FilaDeque` e `PilhaDuasFilas`. Por fim, o teste de integração deve incluir a pilha de forma única (ou estruturar declarações em cabeçalhos com proteção contra inclusão), e o `main`/Makefile deve exercitar `PilhaDuasFilas` em vez de compilar apenas a fila.
