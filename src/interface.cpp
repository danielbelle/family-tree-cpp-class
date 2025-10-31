#include "pch/pch.hpp"
#include "core/execucao.hpp"

using namespace execucao;

void configurarUTF8() {
#ifdef _WIN32
  SetConsoleOutputCP(CP_UTF8);
  SetConsoleCP(CP_UTF8);
#endif
}

void exibirMenu() {
  limparTela();
  cout << "===================================" << endl;
  cout << "      ÁRVORE GENEALÓGICA C++" << endl;
  cout << "===================================" << endl;
  cout << "1 - Criar Pessoa" << endl;
  cout << "2 - Criar Família" << endl;
  cout << "3 - Criar Árvore Genealógica" << endl;
  cout << "4 - Listar Pessoas" << endl;
  cout << "0 - SAIR" << endl;
  cout << "===================================" << endl;
  cout << "Pessoas cadastradas: " << pessoasGlobal.size() << endl;
  cout << "Árvore: " << (arvoreGlobal ? "Criada" : "Não criada") << endl;
  cout << "===================================" << endl;
  cout << "Opção: ";
}

void processarOpcao(const string& opcao) {
  cout << endl;

  if (opcao == "1") {
    Pessoa* novaPessoa = criarPessoaInterface();
    if (novaPessoa) {
      cout << "✅ Operação concluída com sucesso!" << endl;
    }
    else {
      cout << "❌ Falha ao criar pessoa!" << endl;
    }
  }
  else if (opcao == "2") {
    Familia* novaFamilia = criarFamiliaInterface();
    if (novaFamilia) {
      cout << "✅ Operação concluída com sucesso!" << endl;
    }
    else {
      cout << "❌ Falha ao criar família!" << endl;
    }
  }
  else if (opcao == "3") {
    criarArvoreInterface();
    cout << "✅ Operação concluída com sucesso!" << endl;
  }
  else if (opcao == "4") {
    listarPessoas();
  }
  else if (opcao == "0") {
    cout << "Saindo do programa..." << endl;
  }
  else {
    cout << "❌ Opção inválida: '" << opcao << "'" << endl;
    cout << "Por favor, escolha uma opção entre 0 e 4." << endl;
  }

  if (opcao != "0") {
    pausar();
  }
  }

bool deveContinuar(const string& opcao) {
  return opcao != "0";
}