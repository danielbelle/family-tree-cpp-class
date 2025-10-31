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
  cout << "5 - SALVAR BANCO (arquivo único)" << endl;
  cout << "6 - CARREGAR BANCO (arquivo único)" << endl;
  cout << "7 - Listar Árvores Salvas" << endl;
  cout << "0 - SAIR" << endl;
  cout << "===================================" << endl;
  cout << "Pessoas cadastradas: " << pessoasGlobal.size() << endl;
  cout << "Árvores criadas: " << arvoresGlobal.size() << endl;
  cout << "===================================" << endl;
  cout << "Opção: ";
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
  case 0:
    cout << "Saindo do programa..." << endl;
    break;

  case 1: {
    Pessoa* novaPessoa = criarPessoaInterface();
    if (novaPessoa) {
      cout << "✅ Operação concluída com sucesso!" << endl;
    }
    else {
      cout << "❌ Falha ao criar pessoa!" << endl;
    }
    break;
  }

  case 2: {
    Familia* novaFamilia = criarFamiliaInterface();
    if (novaFamilia) {
      cout << "✅ Operação concluída com sucesso!" << endl;
    }
    else {
      cout << "❌ Falha ao criar família!" << endl;
    }
    break;
  }

  case 3:
    criarArvoreInterface();
    cout << "✅ Operação concluída com sucesso!" << endl;
    break;

  case 4:
    listarPessoas();
    break;

  case 5:
    salvarArquivoUnico();
    break;

  case 6:
    carregarArquivoUnico();
    break;

  case 7:
    listarArvoresSalvasInterface();
    break;

  default:
    cout << "❌ Opção inválida: '" << opcao << "'" << endl;
    cout << "Por favor, escolha uma opção entre 0 e 7." << endl;
    break;
  }

  // Pausar apenas se não for sair
  if (opcaoNum != 0) {
    pausar();
  }
}

bool deveContinuar(const string& opcao) {
  // Converter para número e verificar se é 0
  try {
    return stoi(opcao) != 0;
  }
  catch (const exception&) {
    return true; // Se não é número, continua (será tratado como inválido)
  }
}