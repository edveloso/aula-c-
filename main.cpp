#include <iostream>

#include "ex-7a.cpp"
#include "ex-7b.cpp"

int main() {
  int falhas = 0;

  const int valoresSeis[] = {3, 3, 2, 1, 1};
  int obtidoSeis = exercicio_7a::avaliaPolonesa("AB+CED/-*", valoresSeis, 5);
  std::cout << "AB+CED/-* (A+B) * (C-(E/D)): esperado 6, obtido "
            << obtidoSeis;
  if (obtidoSeis == 6) {
    std::cout << " - passou";
  } else {
    std::cout << " - falhou";
    ++falhas;
  }
  std::cout << '\n';

  const int valoresMenosQuatro[] = {3, 3, 2};
  int obtidoMenosQuatro =
      exercicio_7a::avaliaPolonesa("CAB+-", valoresMenosQuatro, 3);
  std::cout << "CAB+- C-(A+B): esperado -4, obtido " << obtidoMenosQuatro;
  if (obtidoMenosQuatro == -4) {
    std::cout << " - passou";
  } else {
    std::cout << " - falhou";
    ++falhas;
  }
  std::cout << '\n';

  char expressao[] = "((A+B)*(C-(F/D)))";
  char saida[sizeof(expressao)];
  exercicio_7b::polonesa(expressao, static_cast<int>(sizeof(expressao) - 1), saida);
  const char esperadoPolonesa[] = "AB+CFD/-*";
  int conversaoCorreta = 1;
  for (int i = 0; saida[i] != '\0' || esperadoPolonesa[i] != '\0'; ++i) {
    if (saida[i] != esperadoPolonesa[i]) {
      conversaoCorreta = 0;
      break;
    }
  }

  std::cout << "((A+B)*(C-(F/D))): esperado AB+CFD/-*, obtido " << saida;
  if (conversaoCorreta) {
    std::cout << " - passou";
  } else {
    std::cout << " - falhou";
    ++falhas;
  }
  std::cout << '\n';

  return falhas == 0 ? 0 : 1;
}
