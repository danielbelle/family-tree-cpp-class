#include "menu_exibir.hpp"

// FUNÇÕES AUXILIARES ESPECÍFICAS DO MENU EXIBIR
void listarPessoasComIDs() {
  cout << "\n📋 --- Lista Completa de Pessoas com IDs ---" << endl;
  if (pessoas.empty()) {
    cout << "ℹ️  Nenhuma pessoa cadastrada." << endl;
    return;
  }

  for (auto pessoa : pessoas) {
    cout << "🆔 " << pessoa->id << " | 👤 " << pessoa->nome;
    if (!pessoa->dataNascimento.empty()) {
      cout << " | 📅 " << pessoa->dataNascimento;
    }
    cout << " | ⚧️ " << (pessoa->genero == 'M' ? "Masculino" : "Feminino") << endl;
  }
}

void listarArvoresComIDs() {
  cout << "\n🌳 --- Lista Completa de Árvores com IDs ---" << endl;
  if (arvores.empty()) {
    cout << "ℹ️  Nenhuma árvore genealógica cadastrada." << endl;
    return;
  }

  for (auto arvore : arvores) {
    cout << "🆔 " << arvore->id << " | 🌳 " << arvore->nome;
    cout << " | 👥 " << arvore->pessoas.size() << " pessoas";
    if (arvore->ancestralPrincipal) {
      cout << " | 👑 " << arvore->ancestralPrincipal->nome;
    }
    cout << endl;
  }
}

// FUNÇÃO PRIVADA - apenas usada neste arquivo
void mostrarArvoreComRelacoesCompletasRecursivo(Pessoa* pessoa, int nivel, vector<bool> ultimos) {
  if (pessoa == nullptr) return;

  // Imprimir indentação
  for (int i = 0; i < nivel; i++) {
    if (i == nivel - 1) {
      cout << (ultimos[i] ? "└── " : "├── ");
    }
    else {
      cout << (ultimos[i] ? "    " : "│   ");
    }
  }

  // Imprimir informações da pessoa
  cout << pessoa->nome << " (" << pessoa->id << ")";

  // Mostrar pais
  if (pessoa->pai || pessoa->mae) {
    cout << " | Pais: ";
    if (pessoa->pai) {
      cout << pessoa->pai->nome;
    }
    else {
      cout << "Pai não definido";
    }
    cout << ", ";
    if (pessoa->mae) {
      cout << pessoa->mae->nome;
    }
    else {
      cout << "Mãe não definida";
    }
  }
  cout << endl;

  // Processar filhos
  size_t numFilhos = pessoa->filhos.size();
  for (size_t i = 0; i < numFilhos; i++) {
    vector<bool> novosUltimos = ultimos;
    novosUltimos.push_back(i == numFilhos - 1);
    mostrarArvoreComRelacoesCompletasRecursivo(pessoa->filhos[i], nivel + 1, novosUltimos);
  }
}

// FUNÇÃO PÚBLICA
void mostrarArvoreComRelacoesCompletas(Pessoa* pessoa) {
  mostrarArvoreComRelacoesCompletasRecursivo(pessoa, 0, vector<bool>());
}

void exibirMenuExibir() {
  cout << "\n👀 === MENU EXIBIR ===" << endl;
  cout << "1. 📈 Exibir Ascendentes de uma Pessoa" << endl;
  cout << "2. 📉 Exibir Descendentes de uma Pessoa" << endl;
  cout << "3. 🌲 Listar Árvore Completa" << endl;
  cout << "4. 🔍 Buscar Pessoa por Nome" << endl;
  cout << "5. 📋 Listar Todas as Pessoas" << endl;
  cout << "6. 📊 Listar Todas as Árvores" << endl;
  cout << "0. ↩️  Voltar ao Menu Principal" << endl;
}

void processarOpcaoExibir(const string& opcao) {
  if (opcao == "0") return;

  switch (stoi(opcao)) {
  case 1:
    menuExibirAscendentes();
    break;
  case 2:
    menuExibirDescendentes();
    break;
  case 3:
    menuListarArvoreCompleta();
    break;
  case 4:
    menuBuscarPessoaPorNome();
    break;
  case 5:
    menuListarPessoas();
    break;
  case 6:
    menuListarArvores();
    break;
  default:
    cout << "❌ Opção inválida!" << endl;
    break;
  }
}

void menuExibir() {
  string opcao;

  do {
    exibirMenuExibir();
    cout << "🎯 Escolha uma opção: ";
    getline(cin, opcao);
    processarOpcaoExibir(opcao);

  } while (opcao != "0");
}

// Implementações das funções do menu exibir
void menuExibirAscendentes() {
  cout << "\n📈 --- Exibir Ascendentes ---" << endl;
  listarPessoasComIDs(); // MOSTRAR TODOS OS IDs PRIMEIRO

  string idPessoa;
  cout << "\n🎯 ID da Pessoa: ";
  getline(cin, idPessoa);

  Pessoa* pessoa = buscarPessoa(idPessoa);
  if (pessoa == nullptr) {
    cout << "❌ Pessoa não encontrada!" << endl;
    return;
  }

  vector<Pessoa*> ascendentes = buscarAscendentes(pessoa);
  if (ascendentes.empty()) {
    cout << "ℹ️  Nenhum ascendente encontrado para " << pessoa->nome << endl;
  }
  else {
    cout << "👴👵 Ascendentes de " << pessoa->nome << ":" << endl;
    for (auto ascendente : ascendentes) {
      cout << "  - " << ascendente->nome << " (" << ascendente->id << ")" << endl;
    }
  }
}

void menuExibirDescendentes() {
  cout << "\n📉 --- Exibir Descendentes ---" << endl;
  listarPessoasComIDs(); // MOSTRAR TODOS OS IDs PRIMEIRO

  string idPessoa;
  cout << "\n🎯 ID da Pessoa: ";
  getline(cin, idPessoa);

  Pessoa* pessoa = buscarPessoa(idPessoa);
  if (pessoa == nullptr) {
    cout << "❌ Pessoa não encontrada!" << endl;
    return;
  }

  vector<Pessoa*> descendentes = buscarDescendentes(pessoa);
  if (descendentes.empty()) {
    cout << "ℹ️  Nenhum descendente encontrado para " << pessoa->nome << endl;
  }
  else {
    cout << "👶 Descendentes de " << pessoa->nome << ":" << endl;
    for (auto descendente : descendentes) {
      cout << "  - " << descendente->nome << " (" << descendente->id << ")" << endl;
    }
  }
}

void menuListarArvoreCompleta() {
  cout << "\n🌲 --- Listar Árvore Completa ---" << endl;
  listarArvoresComIDs(); // MOSTRAR TODAS AS ÁRVORES PRIMEIRO

  string idArvore;
  cout << "\n🎯 ID da Árvore Genealógica: ";
  getline(cin, idArvore);

  ArvoreGenealogica* arvore = buscarArvoreGenealogica(idArvore);
  if (arvore == nullptr) {
    cout << "❌ Árvore Genealógica não encontrada!" << endl;
    return;
  }

  if (arvore->ancestralPrincipal == nullptr) {
    cout << "⚠️  Esta árvore não tem um ancestral principal definido!" << endl;
    return;
  }

  cout << "\n🌳 Árvore Genealógica: " << arvore->nome << endl;
  cout << "👑 Ancestral Principal: " << arvore->ancestralPrincipal->nome << endl;
  cout << "📊 Estrutura Hierárquica (mostrando relações de parentesco):" << endl;

  // Usar a função nova para mostrar pais/mães
  mostrarArvoreComRelacoesCompletas(arvore->ancestralPrincipal);
}

void menuBuscarPessoaPorNome() {
  string nome;

  cout << "\n🔍 --- Buscar Pessoa por Nome ---" << endl;
  cout << "📝 Nome (ou parte do nome): ";
  getline(cin, nome);

  vector<Pessoa*> resultado = buscarPessoasPorNome(nome);
  if (resultado.empty()) {
    cout << "ℹ️  Nenhuma pessoa encontrada com o nome: " << nome << endl;
  }
  else {
    cout << "👥 Pessoas encontradas:" << endl;
    for (auto pessoa : resultado) {
      cout << "  - " << pessoa->nome << " (ID: " << pessoa->id << ", Nasc: "
        << pessoa->dataNascimento << ", Gênero: " << pessoa->genero << ")" << endl;
    }
  }
}

void menuListarPessoas() {
  cout << "\n📋 --- Lista de Todas as Pessoas ---" << endl;
  if (pessoas.empty()) {
    cout << "ℹ️  Nenhuma pessoa cadastrada." << endl;
  }
  else {
    for (auto pessoa : pessoas) {
      cout << "🆔 ID: " << pessoa->id << " | 👤 Nome: " << pessoa->nome
        << " | 📅 Nasc: " << pessoa->dataNascimento
        << " | ⚧️  Gênero: " << pessoa->genero << endl;

      if (pessoa->pai || pessoa->mae) {
        cout << "   👨‍👩‍👧‍👦 Pais: ";
        if (pessoa->pai) cout << pessoa->pai->nome;
        if (pessoa->pai && pessoa->mae) cout << ", ";
        if (pessoa->mae) cout << pessoa->mae->nome;
        cout << endl;
      }

      if (!pessoa->filhos.empty()) {
        cout << "   👶 Filhos: ";
        for (size_t i = 0; i < pessoa->filhos.size(); i++) {
          cout << pessoa->filhos[i]->nome;
          if (i < pessoa->filhos.size() - 1) {
            cout << ", ";
          }
        }
        cout << endl;
      }
      cout << endl;
    }
  }
}

void menuListarArvores() {
  cout << "\n📊 --- Lista de Todas as Árvores Genealógicas ---" << endl;
  if (arvores.empty()) {
    cout << "ℹ️  Nenhuma árvore genealógica cadastrada." << endl;
  }
  else {
    for (auto arvore : arvores) {
      cout << "🆔 ID: " << arvore->id << " | 🌳 Nome: " << arvore->nome
        << " | 👥 Pessoas: " << arvore->pessoas.size();
      if (arvore->ancestralPrincipal) {
        cout << " | 👑 Ancestral Principal: " << arvore->ancestralPrincipal->nome;
      }
      cout << endl;
    }
  }
}