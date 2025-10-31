#include "pch.hpp"

using namespace std;
using namespace arvore;

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

  cout << endl;
  cout << "Fechando programa..." << endl;

  return 0;
}
