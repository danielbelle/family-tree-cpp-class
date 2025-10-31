#include "pch/pch.hpp"

using namespace std;
using namespace arvore;

// Definição das variáveis globais dentro do namespace
namespace execucao {
  vector<ArvoreGenealogica*> arvoresGlobal;
  unordered_map<string, Pessoa*> pessoasGlobal;
}

// Implementações das funções dentro do namespace
namespace execucao {

  void limparTela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
  }

  void pausar() {
    cout << "Pressione Enter para continuar...";
    cin.get();
  }

  Pessoa* criarPessoaInterface() {
    string nome, dataNascimento;
    char genero;

    cout << "=== CRIAR PESSOA ===" << endl;

    cout << "Nome completo: ";
    getline(cin, nome);

    if (nome.empty()) {
      cout << "❌ Erro: Nome não pode ser vazio" << endl;
      return nullptr;
    }

    // Verificar se pessoa já existe
    if (pessoasGlobal.find(nome) != pessoasGlobal.end()) {
      cout << "❌ Erro: Pessoa com este nome já existe" << endl;
      return nullptr;
    }

    cout << "Data de nascimento (DD/MM/AAAA): ";
    getline(cin, dataNascimento);

    cout << "Gênero (M/F): ";
    cin >> genero;
    cin.ignore();

    genero = toupper(genero);
    if (genero != 'M' && genero != 'F') {
      cout << "❌ Erro: Gênero deve ser 'M' ou 'F'" << endl;
      return nullptr;
    }

    Pessoa* novaPessoa = criarPessoa(nome, dataNascimento, genero);
    pessoasGlobal[nome] = novaPessoa;

    // Adicionar pessoa a todas as árvores existentes
    for (auto& arvore : arvoresGlobal) {
      arvore->indicePessoas[nome] = novaPessoa;
    }

    cout << "✅ Pessoa criada com sucesso!" << endl;
    cout << "Nome: " << novaPessoa->nome << endl;
    cout << "Data: " << novaPessoa->dataNascimento << endl;
    cout << "Gênero: " << novaPessoa->genero << endl;

    return novaPessoa;
  }

  Familia* criarFamiliaInterface() {
    cout << "=== CRIAR FAMÍLIA ===" << endl;

    if (pessoasGlobal.empty()) {
      cout << "❌ Erro: Nenhuma pessoa cadastrada. Crie pessoas primeiro." << endl;
      return nullptr;
    }

    cout << "Pessoas cadastradas:" << endl;
    int index = 1;
    unordered_map<int, Pessoa*> indicePessoas;
    vector<Pessoa*> homens;
    vector<Pessoa*> mulheres;

    for (auto& par : pessoasGlobal) {
      Pessoa* p = par.second;
      cout << index << " - " << p->nome
        << " (" << p->genero << ")"
        << " - " << p->dataNascimento << endl;

      indicePessoas[index] = p;
      if (p->genero == 'M') homens.push_back(p);
      else mulheres.push_back(p);
      index++;
    }

    if (homens.empty() || mulheres.empty()) {
      cout << "❌ Erro: É necessário pelo menos 1 homem e 1 mulher para criar uma família" << endl;
      return nullptr;
    }

    int escolhaPai, escolhaMae;

    cout << endl << "Selecione o PAI (número): ";
    cin >> escolhaPai;
    cin.ignore();

    if (indicePessoas.find(escolhaPai) == indicePessoas.end() ||
      indicePessoas[escolhaPai]->genero != 'M') {
      cout << "❌ Erro: Seleção inválida ou pessoa não é do gênero masculino" << endl;
      return nullptr;
    }
    Pessoa* pai = indicePessoas[escolhaPai];

    cout << "Selecione a MÃE (número): ";
    cin >> escolhaMae;
    cin.ignore();

    if (indicePessoas.find(escolhaMae) == indicePessoas.end() ||
      indicePessoas[escolhaMae]->genero != 'F') {
      cout << "❌ Erro: Seleção inválida ou pessoa não é do gênero feminino" << endl;
      return nullptr;
    }
    Pessoa* mae = indicePessoas[escolhaMae];

    Familia* novaFamilia = criarFamilia(pai, mae);
    pai->familiaOrigem = novaFamilia;
    mae->familiaOrigem = novaFamilia;

    cout << "✅ Família criada com sucesso!" << endl;
    cout << "Pai: " << pai->nome << endl;
    cout << "Mãe: " << mae->nome << endl;

    return novaFamilia;
  }

  void criarArvoreInterface() {
    cout << "=== CRIAR ÁRVORE GENEALÓGICA ===" << endl;

    ArvoreGenealogica* novaArvore = criarArvore();

    // Adicionar pessoas existentes à nova árvore
    for (auto& par : pessoasGlobal) {
      novaArvore->indicePessoas[par.first] = par.second;
    }

    arvoresGlobal.push_back(novaArvore);

    cout << "✅ Árvore genealógica criada com sucesso!" << endl;
    cout << "Total de árvores: " << arvoresGlobal.size() << endl;
    cout << "Pessoas na árvore: " << novaArvore->indicePessoas.size() << endl;
  }

  void listarPessoas() {
    cout << "=== PESSOAS CADASTRADAS ===" << endl;

    if (pessoasGlobal.empty()) {
      cout << "Nenhuma pessoa cadastrada." << endl;
      return;
    }

    for (auto& par : pessoasGlobal) {
      Pessoa* p = par.second;
      cout << "Nome: " << p->nome << endl;
      cout << "Data: " << p->dataNascimento << endl;
      cout << "Gênero: " << p->genero << endl;
      cout << "Família: " << (p->familiaOrigem ? "Vinculada" : "Não vinculada") << endl;
      cout << "------------------------" << endl;
    }

    cout << "Total: " << pessoasGlobal.size() << " pessoas" << endl;
  }
}