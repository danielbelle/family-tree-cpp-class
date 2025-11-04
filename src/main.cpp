#include "main.hpp"

// Variáveis globais
vector<Pessoa*> pessoas;
vector<ArvoreGenealogica*> arvores;

int main() {
  configurarUTF8();

  // Garantir que a memória seja liberada ao sair
  atexit(limparMemoria);

  cout << "🌳 Iniciando Sistema de Árvore Genealógica..." << endl;
  menuPrincipal();

  cout << "👋 Programa finalizado." << endl;
  return 0;
}

void configurarUTF8() {
#ifdef _WIN32
  SetConsoleOutputCP(CP_UTF8);
  SetConsoleCP(CP_UTF8);
#endif
}