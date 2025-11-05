#include "../../include/ui/menu.hpp"


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

void menuInterativo(map<int, Pessoa>& arvore) {
  int opcao;
  string pastaArquivoCSV = "dados/dados.csv";

  do {
    cout << "\n=== MENU INTERATIVO ===" << endl;
    cout << "1. Adicionar nova pessoa" << endl;
    cout << "2. Definir pais para uma pessoa" << endl;
    cout << "3. Salvar alterações no CSV" << endl;
    cout << "4. Visualizar árvore atual" << endl;
    cout << "5. Listar todas as pessoas" << endl;
    cout << "6. Exibir ascendentes e descendentes" << endl;
    cout << "7. Buscar pessoa por nome" << endl;
    cout << "8. Listar árvore desde ancestral" << endl;
    cout << "9. Nível de parentesco entre duas pessoas" << endl;
    cout << "10. Contar descendentes de uma pessoa" << endl;
    cout << "11. Exibir gerações por nível" << endl;
    cout << "0. Sair" << endl;
    cout << "Escolha: ";
    cin >> opcao;

    switch (opcao) {
    case 1:
      adicionarPessoaInterativo(arvore);
      break;
    case 2:
      definirPaisParaPessoaCriada(arvore);
      break;
    case 3:
      salvarCSV(arvore, pastaArquivoCSV);
      break;
    case 4:
      verArvoreCompleta(arvore);
      break;
    case 5:
      listarTodasPessoas(arvore);
      break;
    case 6:
      exibirAscendentesEDescendentes(arvore);
      break;
    case 7:
      localizarPessoaPorNome(arvore);
      break;
    case 8:
      listarArvoreDesdeAncestral(arvore);
      break;
    case 9:
      exibirNivelParentesco(arvore);
      break;
    case 10:
      exibirContagemDescendentes(arvore);
      break;
    case 11:
      exibirGeracoesSeparadas(arvore);
      break;
    case 0:
      cout << "Saindo do menu interativo..." << endl;
      break;
    default:
      cout << "Opção inválida!" << endl;
    }
  } while (opcao != 0);
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
  vector<bool> ultimos;
  cout << "\n=== ÁRVORE ATUAL ===" << endl;
  imprimirArvore(arvore, raiz_id, 0, ultimos);
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