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

  cout << "Programa finalizado." << endl;
  return 0;
}

void configurarHandlerFechamento() {
  // Implementação vazia por enquanto
  // Pode ser usada para configurar handlers de sinal no futuro
}

void exibirMenu() {
  cout << "=== SISTEMA DE ÁRVORE GENEALÓGICA ===" << endl;
  cout << "1. Caso 1" << endl;
  cout << "2. Caso 2" << endl;
  cout << "0. Sair" << endl;
  cout << "Escolha uma opção: ";
}

bool deveContinuar(const string& opcao) {
  int numeroDeOpcoes = 2;
  // Se a opção for "0", sair
  if (opcao == "0") {
    return false;
  }

  // Verificar se é um número válido entre 1-2
  try {
    int opcaoNum = stoi(opcao);
    return (opcaoNum >= 1 && opcaoNum <= numeroDeOpcoes);
  }
  catch (const exception&) {
    // Se não é número, é inválido mas continua (será tratado como inválido)
    return true;
  }
}

void configurarUTF8() {
#ifdef _WIN32
  SetConsoleOutputCP(CP_UTF8);
  SetConsoleCP(CP_UTF8);
#endif
}

void processarOpcao(const string& opcao) {
  cout << endl;

  // Converter string para int para usar no switch
  int opcaoNum;
  try {
    opcaoNum = stoi(opcao);
  }
  catch (const exception&) {
    opcaoNum = -1; // Opção inválida
  }

  switch (opcaoNum) {
  case 1:
    cout << "caso1" << endl;
    break;
  case 2:
    cout << "caso2" << endl;
    break;
  default:
    cout << "Opção inválida." << endl;
    break;
  }
}