#include "../../include/core/arvore.hpp"
#include "../../include/utils/validacao.hpp"
#include <iostream>
#include <queue>
#include <set>
#include <functional>

using namespace std;

map<int, Pessoa> construirArvore(vector<Pessoa>& pessoas) {
  map<int, Pessoa> arvore;

  // Primeiro, adiciona todas as pessoas ao mapa
  for (auto& p : pessoas) {
    arvore[p.id] = p;
  }

  // Constrói as relações de filhos
  for (auto& par : arvore) {
    Pessoa& p = par.second;

    // Se tem pai, adiciona esta pessoa como filho do pai
    if (p.id_pai > 0 && pessoaExiste(arvore, p.id_pai)) {
      arvore[p.id_pai].filhos.push_back(p.id);
    }

    // Se tem mãe, adiciona esta pessoa como filho da mãe
    if (p.id_mae > 0 && pessoaExiste(arvore, p.id_mae)) {
      arvore[p.id_mae].filhos.push_back(p.id);
    }
  }

  // Remove duplicatas nos vetores de filhos
  for (auto& par : arvore) {
    Pessoa& p = par.second;
    removerDuplicatas(p.filhos);
  }

  return arvore;
}

void encontrarRaiz(const map<int, Pessoa>& arvore, int& raiz_id) {
  // A raiz é alguém que não tem pais definidos e tem pelo menos um filho
  for (const auto& par : arvore) {
    const Pessoa& p = par.second;
    if (p.id_pai == 0 && p.id_mae == 0 && !p.filhos.empty()) {
      raiz_id = p.id;
      return;
    }
  }

  // Se não encontrou, procura por alguém sem pais
  for (const auto& par : arvore) {
    const Pessoa& p = par.second;
    if (p.id_pai == 0 && p.id_mae == 0) {
      raiz_id = p.id;
      return;
    }
  }
}

bool validarArvore(const map<int, Pessoa>& arvore) {
  // Verifica se não há pessoas que são pais de si mesmas
  for (const auto& par : arvore) {
    const Pessoa& p = par.second;

    // Uma pessoa não pode ser pai/mãe de si mesma
    if (p.id_pai == p.id || p.id_mae == p.id) {
      cout << "Erro: Pessoa " << p.nome << " é pai/mãe de si mesma!" << endl;
      return false;
    }

    // Verifica relações de casamento
    if (p.id_conjuge > 0) {
      if (!pessoaExiste(arvore, p.id_conjuge)) {
        cout << "Erro: Conjuge ID " << p.id_conjuge << " não encontrado para " << p.nome << endl;
        return false;
      }

      const Pessoa& conjuge = arvore.at(p.id_conjuge);

      // Verifica se o casamento é mútuo
      if (conjuge.id_conjuge != p.id) {
        cout << "Erro: Casamento não mútuo entre " << p.nome << " e " << conjuge.nome << endl;
        return false;
      }
    }
  }

  cout << "Árvore validada com sucesso!" << endl;
  return true;
}

int obterProximoId(const map<int, Pessoa>& arvore) {
  if (arvore.empty()) {
    return 1; // Primeiro ID se a árvore estiver vazia
  }

  // Encontrar o maior ID atual
  int maior_id = 0;
  for (const auto& par : arvore) {
    if (par.first > maior_id) {
      maior_id = par.first;
    }
  }

  return maior_id + 1; // Próximo ID disponível
}

void adicionarPessoa(map<int, Pessoa>& arvore, const Pessoa& nova_pessoa) {
  // Criar uma cópia da pessoa com ID gerado automaticamente
  Pessoa pessoa_com_id = nova_pessoa;
  pessoa_com_id.id = obterProximoId(arvore);

  // Adicionar nova pessoa
  arvore[pessoa_com_id.id] = pessoa_com_id;

  // Atualizar relações com pais se especificados
  if (pessoa_com_id.id_pai > 0 && pessoaExiste(arvore, pessoa_com_id.id_pai)) {
    arvore[pessoa_com_id.id_pai].filhos.push_back(pessoa_com_id.id);
    removerDuplicatas(arvore[pessoa_com_id.id_pai].filhos);
  }

  if (pessoa_com_id.id_mae > 0 && pessoaExiste(arvore, pessoa_com_id.id_mae)) {
    arvore[pessoa_com_id.id_mae].filhos.push_back(pessoa_com_id.id);
    removerDuplicatas(arvore[pessoa_com_id.id_mae].filhos);
  }

  cout << "Pessoa " << pessoa_com_id.nome << " adicionada com sucesso! (ID: " << pessoa_com_id.id << ")" << endl;
}

void definirPais(map<int, Pessoa>& arvore, int id_filho) {
  if (!pessoaExiste(arvore, id_filho)) {
    cout << "Erro: Pessoa com ID " << id_filho << " não encontrada!" << endl;
    return;
  }

  Pessoa& filho = arvore[id_filho];
  cout << "\nDefinindo pais para: " << filho.nome << " (ID: " << id_filho << ")" << endl;

  if (filho.id_pai > 0 && filho.id_mae > 0) {
    cout << "Esta pessoa já tem ambos os pais definidos!" << endl;
    cout << "Pai: " << arvore[filho.id_pai].nome << " (ID: " << filho.id_pai << ")" << endl;
    cout << "Mãe: " << arvore[filho.id_mae].nome << " (ID: " << filho.id_mae << ")" << endl;
    return;
  }

  int id_parente;
  cout << "Digite o ID do pai ou mãe existente: ";
  cin >> id_parente;

  if (!pessoaExiste(arvore, id_parente)) {
    cout << "Erro: Pessoa com ID " << id_parente << " não encontrada!" << endl;
    return;
  }

  Pessoa& parente = arvore[id_parente];
  cout << "Parente selecionado: " << parente.nome << " (" << parente.genero << ") [ID: " << id_parente << "]";

  if (parente.id_conjuge > 0) {
    Pessoa& conjuge = arvore[parente.id_conjuge];
    cout << " 💑 " << conjuge.nome << " (" << conjuge.genero << ")" << endl;
  }
  else {
    cout << " (sem cônjuge)" << endl;
  }

  // Lógica para definir parentesco baseado no gênero
  if (parente.genero == 'M') {
    filho.id_pai = id_parente;
    arvore[id_parente].filhos.push_back(filho.id);
    removerDuplicatas(arvore[id_parente].filhos);
    cout << parente.nome << " definido como pai de " << filho.nome << endl;
  }
  else if (parente.genero == 'F') {
    filho.id_mae = id_parente;
    arvore[id_parente].filhos.push_back(filho.id);
    removerDuplicatas(arvore[id_parente].filhos);
    cout << parente.nome << " definida como mãe de " << filho.nome << endl;
  }

  cout << "Relações de parentesco definidas com sucesso!" << endl;
}

int calcularParentesco(const map<int, Pessoa>& arvore, int pessoa1_id, int pessoa2_id) {
  if (!pessoaExiste(arvore, pessoa1_id) || !pessoaExiste(arvore, pessoa2_id)) {
    return -1; // Pessoa não encontrada
  }

  if (pessoa1_id == pessoa2_id) {
    return 0; // Mesma pessoa
  }

  // Usar BFS para encontrar o caminho mais curto
  queue<pair<int, int>> fila; // (pessoa_id, distancia)
  set<int> visitados;

  fila.push({ pessoa1_id, 0 });
  visitados.insert(pessoa1_id);

  while (!fila.empty()) {
    auto [atual, distancia] = fila.front();
    fila.pop();

    const Pessoa& p = arvore.at(atual);

    // Verificar pais, cônjuge e filhos
    vector<int> parentes;
    if (p.id_pai > 0) parentes.push_back(p.id_pai);
    if (p.id_mae > 0) parentes.push_back(p.id_mae);
    if (p.id_conjuge > 0) parentes.push_back(p.id_conjuge);
    for (int filho_id : p.filhos) {
      parentes.push_back(filho_id);
    }

    for (int parente_id : parentes) {
      if (parente_id == pessoa2_id) {
        return distancia + 1; // Encontrou!
      }

      if (visitados.find(parente_id) == visitados.end() && pessoaExiste(arvore, parente_id)) {
        visitados.insert(parente_id);
        fila.push({ parente_id, distancia + 1 });
      }
    }
  }

  return -1; // Não há parentesco
}

int contarDescendentes(const map<int, Pessoa>& arvore, int pessoa_id) {
  if (!pessoaExiste(arvore, pessoa_id)) {
    return 0;
  }

  int total = 0;
  function<void(int)> contar = [&](int id) {
    const Pessoa& p = arvore.at(id);
    for (int filho_id : p.filhos) {
      total++;
      contar(filho_id);
    }
    };

  contar(pessoa_id);
  return total;
}