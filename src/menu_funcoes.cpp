#include "menu_funcoes.hpp"

void exibirMenuFuncoes() {
  cout << "\n🔧 === MENU FUNÇÕES ===" << endl;
  cout << "1. 🤝 Calcular Parentesco" << endl;
  cout << "2. 👶 Contar Descendentes" << endl;
  cout << "3. 📅 Mostrar Gerações" << endl;
  cout << "0. ↩️  Voltar ao Menu Principal" << endl;
}

void processarOpcaoFuncoes(const string& opcao) {
  if (opcao == "0") return;

  switch (stoi(opcao)) {
  case 1:
    menuParentesco();
    break;
  case 2:
    menuContarDescendentes();
    break;
  case 3:
    menuMostrarGeracoes();
    break;
  default:
    cout << "❌ Opção inválida!" << endl;
    break;
  }
}

void menuFuncoes() {
  string opcao;

  do {
    exibirMenuFuncoes();
    cout << "🎯 Escolha uma opção: ";
    getline(cin, opcao);
    processarOpcaoFuncoes(opcao);

  } while (opcao != "0");
}

void menuParentesco() {
  cout << "\n🤝 --- Calcular Grau de Parentesco ---" << endl;

  // MOSTRAR TODAS AS PESSOAS PRIMEIRO
  listarPessoasComIDs();

  string id1, id2;
  cout << "\n🎯 ID da primeira pessoa: ";
  getline(cin, id1);
  cout << "🎯 ID da segunda pessoa: ";
  getline(cin, id2);

  Pessoa* p1 = buscarPessoa(id1);
  Pessoa* p2 = buscarPessoa(id2);

  if (!p1 || !p2) {
    cout << "❌ Uma ou ambas as pessoas não foram encontradas!" << endl;
    return;
  }

  int grau = calcularParentesco(p1, p2);
  if (grau >= 0) {
    cout << "📏 Grau de parentesco entre " << p1->nome << " e " << p2->nome << ": " << grau << "º grau" << endl;
  }
  else {
    cout << "ℹ️  " << p1->nome << " e " << p2->nome << " não são parentes." << endl;
  }
}

void menuContarDescendentes() {
  cout << "\n👶 --- Contar Descendentes ---" << endl;

  // MOSTRAR TODAS AS PESSOAS PRIMEIRO
  listarPessoasComIDs();

  string id;
  cout << "\n🎯 ID da pessoa: ";
  getline(cin, id);

  Pessoa* pessoa = buscarPessoa(id);
  if (!pessoa) {
    cout << "❌ Pessoa não encontrada!" << endl;
    return;
  }

  int total = contarDescendentes(pessoa);
  cout << "📊 " << pessoa->nome << " tem " << total << " descendente(s)" << endl;

  // MOSTRAR A ÁRVORE DA PESSOA PARA CONTEXTO
  cout << "\n🌳 Estrutura da árvore de " << pessoa->nome << ":" << endl;
  mostrarArvoreHierarquica(pessoa);
}

void menuMostrarGeracoes() {
  cout << "\n📅 --- Mostrar Gerações ---" << endl;

  if (arvores.empty()) {
    cout << "❌ Nenhuma árvore cadastrada!" << endl;
    return;
  }

  cout << "🌳 Árvores disponíveis:" << endl;
  for (size_t i = 0; i < arvores.size(); i++) {
    cout << i + 1 << ". " << arvores[i]->nome << " (" << arvores[i]->id << ")" << endl;
  }

  cout << "🎯 Escolha o número da árvore: ";
  string escolha;
  getline(cin, escolha);

  // CORREÇÃO: Verificação mais robusta da entrada
  if (escolha.empty()) {
    cout << "❌ Nenhuma opção selecionada!" << endl;
    return;
  }

  try {
    int index = stoi(escolha) - 1;
    if (index >= 0 && static_cast<size_t>(index) < arvores.size()) {
      if (arvores[index]->ancestralPrincipal) {
        cout << "\n📊 Gerações da Árvore " << arvores[index]->nome << ":" << endl;
        mostrarGeracoes(arvores[index]->ancestralPrincipal);
      }
      else {
        cout << "❌ Esta árvore não tem ancestral principal!" << endl;
      }
    }
    else {
      cout << "❌ Número inválido! Escolha entre 1 e " << arvores.size() << endl;
    }
  }
  catch (const exception& e) {
    cout << "❌ Opção inválida! Digite apenas números." << endl;
  }
}