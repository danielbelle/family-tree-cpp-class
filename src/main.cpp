#include "pch/pch.hpp"

int main() {
  configurarUTF8();

  string opcao;

  while (true) {
    exibirMenu();
    getline(cin, opcao);

    if (!deveContinuar(opcao)) {
      break;
    }

    processarOpcao(opcao);
  }

  cout << "Fechando programa..." << endl;

  return 0;
}
