#include "menu_import_export.hpp"

void exibirMenuImportExport() {
  cout << "\n💾 === MENU IMPORTAR/EXPORTAR ===" << endl;
  cout << "1. 💾 Gravar Árvore em Arquivo" << endl;
  cout << "2. 📂 Carregar Árvore de Arquivo" << endl;
  cout << "0. ↩️  Voltar ao Menu Principal" << endl;
}

void processarOpcaoImportExport(const string& opcao) {
  if (opcao == "0") return;

  switch (stoi(opcao)) {
  case 1:
    menuGravarArvore();
    break;
  case 2:
    menuCarregarArvore();
    break;
  default:
    cout << "❌ Opção inválida!" << endl;
    break;
  }
}

void menuImportExport() {
  string opcao;

  do {
    exibirMenuImportExport();
    cout << "🎯 Escolha uma opção: ";
    getline(cin, opcao);
    processarOpcaoImportExport(opcao);

  } while (opcao != "0");
}

// Implementações das funções do menu import/export
void menuGravarArvore() {
  verificarDiretorioDados();

  if (arvores.empty()) {
    cout << "❌ Nenhuma árvore para gravar!" << endl;
    return;
  }

  cout << "\n💾 --- Gravar Árvore em Arquivo ---" << endl;

  // Usar a primeira árvore disponível (ou perguntar se tiver várias)
  ArvoreGenealogica* arvoreParaSalvar = nullptr;

  if (arvores.size() == 1) {
    arvoreParaSalvar = arvores[0];
    cout << "🌳 Salvando árvore: " << arvoreParaSalvar->nome << endl;
  }
  else {
    cout << "🌳 Árvores disponíveis:" << endl;
    for (size_t i = 0; i < arvores.size(); i++) {
      cout << i + 1 << ". " << arvores[i]->nome << " (" << arvores[i]->id << ")" << endl;
    }

    cout << "🎯 Escolha o número da árvore: ";
    string escolha;
    getline(cin, escolha);

    try {
      int index = stoi(escolha) - 1;
      if (index >= 0 && static_cast<size_t>(index) < arvores.size()) {
        arvoreParaSalvar = arvores[index];
      }
      else {
        cout << "❌ Número inválido!" << endl;
        return;
      }
    }
    catch (...) {
      cout << "❌ Opção inválida!" << endl;
      return;
    }
  }

  if (!arvoreParaSalvar) return;

  // NOVA OPÇÃO: Escolher modo de gravação
  cout << "\n📝 Modo de gravação:" << endl;
  cout << "1. 💾 Sobrescrever arquivo (apagar dados antigos)" << endl;
  cout << "2. ➕ Complementar arquivo (manter dados antigos)" << endl;
  cout << "🎯 Escolha: ";
  string modo;
  getline(cin, modo);

  if (modo == "1") {
    // Modo sobrescrever - usar função existente
    if (gravarArvoreCSV(arvoreParaSalvar)) {
      cout << "✅ Dados salvos com sucesso (sobrescritos)!" << endl;
    }
    else {
      cout << "❌ Erro ao salvar dados!" << endl;
    }
  }
  else if (modo == "2") {
    // NOVO MODO: Complementar
    if (gravarArvoreCSVComplementar(arvoreParaSalvar)) {
      cout << "✅ Dados complementados com sucesso!" << endl;
    }
    else {
      cout << "❌ Erro ao complementar dados!" << endl;
    }
  }
  else {
    cout << "❌ Opção inválida!" << endl;
  }
}

void menuCarregarArvore() {
  cout << "\n📂 --- Carregar Árvore de Arquivo ---" << endl;

  // NOVA OPÇÃO: Escolher modo de carregamento
  if (!pessoas.empty() || !arvores.empty()) {
    cout << "📝 Modo de carregamento:" << endl;
    cout << "1. 🔄 Substituir dados atuais" << endl;
    cout << "2. 🔗 Complementar dados atuais" << endl;
    cout << "🎯 Escolha: ";
    string modo;
    getline(cin, modo);

    if (modo == "1") {
      // Limpar dados atuais antes de carregar
      limparMemoria();
      cout << "🗑️  Dados atuais removidos!" << endl;
    }
    else if (modo != "2") {
      cout << "❌ Opção inválida, usando modo complementar!" << endl;
    }
  }

  cout << "📁 Carregando de: ../dados/dados.csv" << endl;

  if (carregarArvoreCSV()) {
    cout << "✅ Dados carregados com sucesso!" << endl;
  }
  else {
    cout << "❌ Erro ao carregar dados!" << endl;
  }
}



void verificarDiretorioDados() {
  string pasta_dados = "../dados/";
  string caminho_completo = pasta_dados + "dados.csv";

  cout << "🔍 Verificando diretório: " << pasta_dados << endl;

  // Tentar criar diretório
#ifdef _WIN32
  system(("mkdir \"" + pasta_dados + "\" 2>nul").c_str());
#else
  system(("mkdir -p \"" + pasta_dados + "\" 2>/dev/null").c_str());
#endif

  // Verificar se podemos escrever
  ofstream testfile(caminho_completo, ios::app);
  if (testfile.is_open()) {
    testfile.close();
    remove(caminho_completo.c_str()); // Limpar arquivo de teste
    cout << "✅ Diretório acessível para escrita" << endl;
  }
  else {
    cout << "❌ Não é possível escrever no diretório!" << endl;
  }
}
