#include "pch/pch.hpp"

using namespace std;
using namespace arvore;


void configurarUTF8() {
#ifdef _WIN32
  SetConsoleOutputCP(CP_UTF8);
  SetConsoleCP(CP_UTF8);
#endif
}

void exibirMenu() {
  cout << "===================================" << endl;
  cout << "      ARVORE GENEALOGICA C++" << endl;
  cout << "===================================" << endl;
  cout << "Projeto de Arvore Genealogica em C++17" << endl;
  cout << endl;
  cout << "Digite 0 para SAIR e FECHAR" << endl;
  cout << "Digite qualquer outra coisa para continuar" << endl;
  cout << "===================================" << endl;
  cout << "Opcao: ";
}

void processarOpcao(const string& opcao) {
  cout << endl;
  cout << "+++++++++++++++++++++++++++++++++++" << endl;
  cout << "RESULTADO:" << endl;
  cout << "Voce digitou: '" << opcao << "'" << endl;
  cout << "Estruturas carregadas com sucesso!" << endl;
  cout << "+++++++++++++++++++++++++++++++++++" << endl;
  cout << endl;

  // Pequena pausa para ler o resultado
  system("timeout 1 > nul");
}

bool deveContinuar(const string& opcao) {
  return opcao != "0";
}