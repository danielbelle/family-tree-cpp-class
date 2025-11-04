#include "menu_principal.hpp"

void exibirMenuPrincipal() {
  cout << "\n🎯 === SISTEMA DE ÁRVORE GENEALÓGICA ===" << endl;
  cout << "1. 📝 Menu Criar" << endl;
  cout << "2. 👀 Menu Exibir" << endl;
  cout << "3. 💾 Menu Importar/Exportar" << endl;
  cout << "4. 🔧 Menu Funções" << endl;
  cout << "0. ❌ Sair" << endl;
}

void processarOpcaoPrincipal(const string& opcao) {
  if (opcao == "0") return;

  switch (stoi(opcao)) {
  case 1:
    menuCriar();
    break;
  case 2:
    menuExibir();
    break;
  case 3:
    menuImportExport();
    break;
  case 4:
    menuFuncoes();
    break;
  default:
    cout << "❌ Opção inválida!" << endl;
    break;
  }
}

void menuPrincipal() {
  string opcao;

  do {
    exibirMenuPrincipal();
    cout << "🎯 Escolha uma opção: ";
    getline(cin, opcao);
    processarOpcaoPrincipal(opcao);

  } while (opcao != "0");
}