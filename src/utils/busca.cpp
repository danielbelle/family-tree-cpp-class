#include "../../include/utils/busca.hpp"

int buscarPessoaPorNome(const map<int, Pessoa>& arvore, const string& nome) {
  // Converter nome para minúsculas para busca case-insensitive
  string nomeLower = nome;
  transform(nomeLower.begin(), nomeLower.end(), nomeLower.begin(), ::tolower);

  for (const auto& par : arvore) {
    const Pessoa& p = par.second;

    // Converter nome da pessoa para minúsculas
    string pessoaNomeLower = p.nome;
    transform(pessoaNomeLower.begin(), pessoaNomeLower.end(), pessoaNomeLower.begin(), ::tolower);

    if (pessoaNomeLower == nomeLower) {
      return p.id;
    }
  }
  return -1; // Não encontrado
}

int buscarPessoaInterativo(const map<int, Pessoa>& arvore) {
  int opcao_busca;
  cout << "\n=== BUSCAR PESSOA ===" << endl;
  cout << "1. Buscar por ID" << endl;
  cout << "2. Buscar por nome" << endl;
  cout << "Escolha: ";
  cin >> opcao_busca;

  int pessoa_id = -1;

  if (opcao_busca == 1) {
    cout << "Digite o ID: ";
    cin >> pessoa_id;

    if (!pessoaExiste(arvore, pessoa_id)) {
      cout << "Erro: Pessoa com ID " << pessoa_id << " não encontrada!" << endl;
      return -1;
    }
  }
  else if (opcao_busca == 2) {
    string nome;
    cout << "Digite o nome: ";
    nome = lerStringUTF8();

    pessoa_id = buscarPessoaPorNome(arvore, nome);

    if (pessoa_id == -1) {
      cout << "Erro: Pessoa com nome '" << nome << "' não encontrada!" << endl;
      return -1;
    }
  }
  else {
    cout << "Opção inválida!" << endl;
    return -1;
  }

  return pessoa_id;
}