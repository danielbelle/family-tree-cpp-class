#include "../../include/ui/menu.hpp"



// Array de tópicos do menu usando structures
vector<TopicoMenu> menus = {
{
  "👥 GESTÃO DE PESSOAS",
  {
    {"Adicionar nova pessoa", adicionarPessoaInterativo},
    {"Definir pais para pessoa", definirPaisParaPessoaCriada},
    {"Buscar pessoa por nome", localizarPessoaPorNome},
    {"Listar todas pessoas", listarTodasPessoas}
  }
},
  {
    "🌳 VISUALIZAÇÃO DA ÁRVORE",
    {
      {"Ver árvore completa", verArvoreCompleta},
      {"Listar árvore desde ancestral", listarArvoreDesdeAncestral},
      {"Exibir ascendentes e descendentes", exibirAscendentesEDescendentes},
      {"Exibir gerações por nível", exibirGeracoesSeparadas}
    }
  },
  {
    "📊 ANÁLISE E ESTATÍSTICAS",
    {
      {"Nível de parentesco", exibirNivelParentesco},
      {"Contar descendentes", exibirContagemDescendentes},
      {"Estatísticas avançadas", exibirEstatisticasAvancadas},
      {"Validar inconsistências", [](map<int, Pessoa>& arvore) {
        validarInconsistencias(arvore);
      }}
    }
  },
  {
    "💾 ARMAZENAMENTO",
    {
      {"Salvar alterações no CSV", [](map<int, Pessoa>& arvore) {
        salvarCSV(arvore, "dados/dados.csv");
      }}
    }
  }
};

/**
 * Exibe menu secundário para um tópico específico
 */
void exibirMenuSecundario(map<int, Pessoa>& arvore, size_t topico_idx) {
  int opcao;
  const TopicoMenu& topico = menus[topico_idx];

  do {
    cout << "\n=== " << topico.nome << " ===" << endl;
    for (size_t i = 0; i < topico.opcoes.size(); i++) {
      cout << i + 1 << ". " << topico.opcoes[i].descricao << endl;
    }
    cout << "0. Voltar ao menu principal\nEscolha: ";
    cin >> opcao;

    if (opcao > 0 && static_cast<size_t>(opcao) <= topico.opcoes.size()) {
      topico.opcoes[opcao - 1].acao(arvore);
    }
    else if (opcao != 0) {
      cout << "❌ Opção inválida!" << endl;
    }
  } while (opcao != 0);
}

/**
 * Menu interativo inteligente com structures
 */
void menuInterativo(map<int, Pessoa>& arvore) {
  int opcao;
  do {
    cout << "\n=== 🏠 MENU PRINCIPAL ===" << endl;
    for (size_t i = 0; i < menus.size(); i++) {
      cout << i + 1 << ". " << menus[i].nome << endl;
    }
    cout << "0. Sair\nEscolha: ";
    cin >> opcao;

    if (opcao > 0 && static_cast<size_t>(opcao) <= menus.size()) {
      exibirMenuSecundario(arvore, opcao - 1);
    }
    else if (opcao != 0) {
      cout << "❌ Opção inválida!" << endl;
    }
  } while (opcao != 0);

  cout << "👋 Saindo do sistema..." << endl;
}

void adicionarPessoaInterativo(map<int, Pessoa>& arvore) {
  Pessoa nova;
  nova.id = 0;

  cout << "Nome: ";
  nova.nome = lerStringUTF8();

  nova.genero = solicitarGeneroValido();

  cout << "Ano de nascimento: ";
  cin >> nova.ano_nascimento;

  nova.id_pai = 0;
  nova.id_mae = 0;
  nova.id_conjuge = 0;

  adicionarPessoa(arvore, nova);
}

void definirPaisParaPessoaCriada(map<int, Pessoa>& arvore) {
  int id_filho;
  cout << "Digite o ID da pessoa que deseja definir os pais: ";
  cin >> id_filho;
  definirPais(arvore, id_filho);
}

void verArvoreCompleta(map<int, Pessoa>& arvore) {
  int raiz_id;
  encontrarRaiz(arvore, raiz_id);
  cout << "\n=== ÁRVORE ATUAL ===" << endl;
  imprimirArvoreIterativa(arvore, raiz_id);
}

void listarTodasPessoas(map<int, Pessoa>& arvore) {
  cout << "\n=== LISTA DE PESSOAS ===" << endl;
  for (const auto& par : arvore) {
    const Pessoa& p = par.second;
    cout << "ID: " << p.id << " | " << p.nome << " (" << p.genero << ") | Nasc: " << p.ano_nascimento;
    if (p.id_pai > 0) cout << " | Pai: " << p.id_pai;
    if (p.id_mae > 0) cout << " | Mãe: " << p.id_mae;
    if (p.id_conjuge > 0) cout << " | Cônjuge: " << p.id_conjuge;
    cout << " | Filhos: " << p.filhos.size();
    cout << endl;
  }
}

void localizarPessoaPorNome(map<int, Pessoa>& arvore) {
  string nomeBusca = "";
  cout << "Digite o nome: ";
  nomeBusca = lerStringUTF8();

  int pessoa_id = buscarPessoaPorNome(arvore, nomeBusca);

  if (pessoa_id == -1) {
    cout << "Erro: Pessoa com nome '" << nomeBusca << "' não encontrada!" << endl;
  }
  else {
    const Pessoa& p = arvore.at(pessoa_id);
    cout << "Pessoa encontrada: " << p.nome << " (ID: " << pessoa_id << ") Gênero: " << p.genero << " Nasc: " << p.ano_nascimento << endl;
    cout << "Pai: " << (p.id_pai > 0 ? arvore.at(p.id_pai).nome : "Não definido") << endl;
    cout << "Mãe: " << (p.id_mae > 0 ? arvore.at(p.id_mae).nome : "Não definido") << endl;
    cout << "Cônjuge: " << (p.id_conjuge > 0 ? arvore.at(p.id_conjuge).nome : "Não definido") << endl;
    cout << "Filhos: " << p.filhos.size() << endl;
  }
}