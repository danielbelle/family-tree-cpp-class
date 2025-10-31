#include "pch/pch.hpp"
#include "core/execucao.hpp"

using namespace execucao;

void configurarUTF8() {
#ifdef _WIN32
  SetConsoleOutputCP(CP_UTF8);
  SetConsoleCP(CP_UTF8);
#endif
}

// Função para verificar se deve continuar (incluindo tratamento do botão X)
bool deveContinuar(const string& opcao) {
  // Se a opção for "0", sair
  if (opcao == "0") {
    return false;
  }

  // Verificar se é um número válido entre 1-4
  try {
    int opcaoNum = stoi(opcao);
    return (opcaoNum >= 1 && opcaoNum <= 4);
  }
  catch (const exception&) {
    // Se não é número, é inválido mas continua (será tratado como inválido)
    return true;
  }
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
  cout << "0 - SAIR (ou use o botão X)" << endl;  // ← Adicionei esta informação
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

  default:
    cout << "❌ Opção inválida: '" << opcao << "'" << endl;
    cout << "Por favor, escolha uma opção entre 0 e 4." << endl;
    break;
  }

  // Pausar apenas se não for sair
  if (opcaoNum != 0) {
    pausar();
  }
}