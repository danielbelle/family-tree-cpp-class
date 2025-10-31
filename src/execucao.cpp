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

  void salvarArquivoUnico() {
    cout << "=== SALVAR BANCO DE DADOS ===" << endl;

    if (persistencia::salvarBancoDeDados(arvoresGlobal, pessoasGlobal)) {
      cout << "✅ Banco de dados salvo com sucesso em data/armazenamento.json" << endl;
      cout << "   Árvores salvas: " << arvoresGlobal.size() << endl;
      cout << "   Pessoas salvas: " << pessoasGlobal.size() << endl;
    }
    else {
      cout << "❌ Falha ao salvar banco de dados" << endl;
    }
  }

  void carregarArquivoUnico() {
    cout << "=== CARREGAR BANCO DE DADOS ===" << endl;

    if (persistencia::carregarBancoDeDados(arvoresGlobal, pessoasGlobal)) {
      cout << "✅ Banco de dados carregado com sucesso!" << endl;
      cout << "   Árvores: " << arvoresGlobal.size() << endl;
      cout << "   Pessoas: " << pessoasGlobal.size() << endl;
    }
    else {
      cout << "❌ Nenhum banco de dados encontrado ou erro ao carregar" << endl;
    }
  }

  void salvarArvoreInterface() {
    cout << "=== SALVAR ÁRVORE (Compatibilidade) ===" << endl;

    if (arvoresGlobal.empty()) {
      cout << "❌ Erro: Nenhuma árvore para salvar" << endl;
      return;
    }

    string nomeArquivo;
    cout << "Nome para salvar a árvore: ";
    getline(cin, nomeArquivo);

    if (nomeArquivo.empty()) {
      cout << "❌ Erro: Nome não pode ser vazio" << endl;
      return;
    }

    // Usar a primeira árvore para compatibilidade
    if (persistencia::salvarArvore(arvoresGlobal[0], nomeArquivo)) {
      cout << "✅ Árvore salva com sucesso!" << endl;
    }
    else {
      cout << "❌ Falha ao salvar árvore" << endl;
    }
  }

  void carregarArvoreInterface() {
    cout << "=== CARREGAR ÁRVORE (Compatibilidade) ===" << endl;

    vector<string> arvores = persistencia::listarArvoresSalvas();

    if (arvores.empty()) {
      cout << "Nenhuma árvore salva encontrada." << endl;
      return;
    }

    cout << "Árvores disponíveis:" << endl;
    for (size_t i = 0; i < arvores.size(); i++) {
      cout << i + 1 << " - " << arvores[i] << endl;
    }

    cout << "0 - Cancelar" << endl;
    cout << "Escolha uma árvore: ";

    int escolha;
    cin >> escolha;
    cin.ignore();

    if (escolha == 0) return;

    if (escolha < 1 || escolha > static_cast<int>(arvores.size())) {
      cout << "❌ Escolha inválida" << endl;
      return;
    }

    string nomeArvore = arvores[escolha - 1];

    // Limpar árvores atuais
    for (auto arvore : arvoresGlobal) {
      delete arvore;
    }
    arvoresGlobal.clear();
    pessoasGlobal.clear();

    // Carregar nova árvore
    ArvoreGenealogica* arvoreCarregada = persistencia::carregarArvore(nomeArvore);

    if (arvoreCarregada) {
      arvoresGlobal.push_back(arvoreCarregada);

      // Popular pessoas globais a partir da árvore carregada
      for (const auto& par : arvoreCarregada->indicePessoas) {
        pessoasGlobal[par.first] = par.second;
      }
      cout << "✅ Árvore carregada com sucesso!" << endl;
    }
  }

  void listarArvoresSalvasInterface() {
    cout << "=== ÁRVORES SALVAS ===" << endl;

    vector<string> arvores = persistencia::listarArvoresSalvas();

    if (arvores.empty()) {
      cout << "Nenhuma árvore salva encontrada." << endl;
      return;
    }

    cout << "Árvores no banco de dados:" << endl;
    for (const auto& nome : arvores) {
      cout << "📁 " << nome << ".json" << endl;
    }
    cout << "Total: " << arvores.size() << " árvores" << endl;
  }

}