#include "../../include/core/arvore.hpp"

/**
 * Constrói a árvore genealógica a partir de uma lista de pessoas
 */
map<int, Pessoa> construirArvore(vector<Pessoa>& pessoas) {
  map<int, Pessoa> arvore;

  for (auto& p : pessoas) {
    arvore[p.id] = p;
  }

  for (auto& par : arvore) {
    Pessoa& p = par.second;
    if (p.id_pai > 0 && pessoaExiste(arvore, p.id_pai)) {
      arvore[p.id_pai].filhos.push_back(p.id);
    }
    if (p.id_mae > 0 && pessoaExiste(arvore, p.id_mae)) {
      arvore[p.id_mae].filhos.push_back(p.id);
    }
  }

  for (auto& par : arvore) {
    removerDuplicatas(par.second.filhos);
  }

  return arvore;
}

/**
 * Encontra a raiz da árvore (pessoa sem pais com filhos)
 */
void encontrarRaiz(const map<int, Pessoa>& arvore, int& raiz_id) {
  for (const auto& par : arvore) {
    const Pessoa& p = par.second;
    if (p.id_pai == 0 && p.id_mae == 0 && !p.filhos.empty()) {
      raiz_id = p.id;
      return;
    }
  }

  for (const auto& par : arvore) {
    const Pessoa& p = par.second;
    if (p.id_pai == 0 && p.id_mae == 0) {
      raiz_id = p.id;
      return;
    }
  }
}

/**
 * Valida a consistência da árvore genealógica
 */
bool validarArvore(const map<int, Pessoa>& arvore) {
  for (const auto& par : arvore) {
    const Pessoa& p = par.second;

    if (p.id_pai == p.id || p.id_mae == p.id) {
      cout << "Erro: Pessoa " << p.nome << " é pai/mãe de si mesma!" << endl;
      return false;
    }

    if (p.id_conjuge > 0) {
      if (!pessoaExiste(arvore, p.id_conjuge)) {
        cout << "Erro: Conjuge ID " << p.id_conjuge << " não encontrado para " << p.nome << endl;
        return false;
      }

      const Pessoa& conjuge = arvore.at(p.id_conjuge);
      if (conjuge.id_conjuge != p.id) {
        cout << "Erro: Casamento não mútuo entre " << p.nome << " e " << conjuge.nome << endl;
        return false;
      }
    }
  }

  cout << "Árvore validada com sucesso!" << endl;
  return true;
}

/**
 * Expande os vizinhos de uma pessoa para busca
 */
void expandirParentes(const map<int, Pessoa>& arvore, int pessoa_id,
  map<int, int>& visitados, queue<int>& fila) {
  const Pessoa& p = arvore.at(pessoa_id);
  vector<int> parentes;

  if (p.id_pai > 0) parentes.push_back(p.id_pai);
  if (p.id_mae > 0) parentes.push_back(p.id_mae);
  if (p.id_conjuge > 0) parentes.push_back(p.id_conjuge);
  parentes.insert(parentes.end(), p.filhos.begin(), p.filhos.end());

  for (int parente_id : parentes) {
    if (pessoaExiste(arvore, parente_id) && !visitados.count(parente_id)) {
      visitados[parente_id] = visitados[pessoa_id] + 1;
      fila.push(parente_id);
    }
  }
}

/**
 * Calcula parentesco usando BFS bidirecional (Busca em Largura Bidirecional)
 */
int calcularParentesco(const map<int, Pessoa>& arvore, int pessoa1_id, int pessoa2_id) {
  if (!pessoaExiste(arvore, pessoa1_id) || !pessoaExiste(arvore, pessoa2_id)) {
    return -1;
  }

  if (pessoa1_id == pessoa2_id) return 0;

  map<int, int> visitado1, visitado2;
  queue<int> q1, q2;

  q1.push(pessoa1_id); visitado1[pessoa1_id] = 0;
  q2.push(pessoa2_id); visitado2[pessoa2_id] = 0;

  while (!q1.empty() || !q2.empty()) {
    if (!q1.empty()) {
      int atual = q1.front(); q1.pop();
      if (visitado2.count(atual)) return visitado1[atual] + visitado2[atual];
      expandirParentes(arvore, atual, visitado1, q1);
    }

    if (!q2.empty()) {
      int atual = q2.front(); q2.pop();
      if (visitado1.count(atual)) return visitado1[atual] + visitado2[atual];
      expandirParentes(arvore, atual, visitado2, q2);
    }
  }

  return -1;
}

/**
 * Obtém o próximo ID disponível
 */
int obterProximoId(const map<int, Pessoa>& arvore) {
  if (arvore.empty()) return 1;

  int maior_id = 0;
  for (const auto& par : arvore) {
    if (par.first > maior_id) maior_id = par.first;
  }

  return maior_id + 1;
}

/**
 * Adiciona uma nova pessoa à árvore
 */
void adicionarPessoa(map<int, Pessoa>& arvore, const Pessoa& nova_pessoa) {
  Pessoa pessoa_com_id = nova_pessoa;
  pessoa_com_id.id = obterProximoId(arvore);

  arvore[pessoa_com_id.id] = pessoa_com_id;

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

/**
 * Define pais para uma pessoa existente
 */
void definirPais(map<int, Pessoa>& arvore, int id_filho) {
  if (!pessoaExiste(arvore, id_filho)) {
    cout << "Erro: Pessoa com ID " << id_filho << " não encontrada!" << endl;
    return;
  }

  Pessoa& filho = arvore[id_filho];
  cout << "\nDefinindo pais para: " << filho.nome << " (ID: " << id_filho << ", Nasc: " << filho.ano_nascimento << ")" << endl;

  if (filho.id_pai > 0 && filho.id_mae > 0) {
    cout << "Esta pessoa já tem ambos os pais definidos!" << endl;
    cout << "Pai: " << arvore[filho.id_pai].nome << " (ID: " << filho.id_pai << ", Nasc: " << arvore[filho.id_pai].ano_nascimento << ")" << endl;
    cout << "Mãe: " << arvore[filho.id_mae].nome << " (ID: " << filho.id_mae << ", Nasc: " << arvore[filho.id_mae].ano_nascimento << ")" << endl;
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
  cout << "Parente selecionado: " << parente.nome << " (" << parente.genero << ", Nasc: " << parente.ano_nascimento << ") [ID: " << id_parente << "]";

  if (parente.id_conjuge > 0) {
    Pessoa& conjuge = arvore[parente.id_conjuge];
    cout << " 💑 " << conjuge.nome << " (" << conjuge.genero << ", Nasc: " << conjuge.ano_nascimento << ")" << endl;
  }
  else {
    cout << " (sem cônjuge)" << endl;
  }

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

/**
 * Conta descendentes usando DFS iterativo
 */
int contarDescendentes(const map<int, Pessoa>& arvore, int pessoa_id) {
  if (!pessoaExiste(arvore, pessoa_id)) return 0;

  int total = 0;
  stack<int> pilha;
  pilha.push(pessoa_id);

  while (!pilha.empty()) {
    int atual = pilha.top();
    pilha.pop();

    const Pessoa& p = arvore.at(atual);
    for (int filho_id : p.filhos) {
      total++;
      pilha.push(filho_id);
    }
  }

  return total;
}

/**
 * Calcula estatísticas avançadas da árvore
 */
EstatisticasArvore calcularEstatisticas(const map<int, Pessoa>& arvore) {
  EstatisticasArvore stats = { 0, 0 };
  if (arvore.empty()) return stats;

  stats.total_pessoas = arvore.size();

  for (const auto& par : arvore) {
    const Pessoa& p = par.second;

    // Calcula gerações (profundidade máxima)
    queue<pair<int, int>> fila;
    set<int> visitados;
    fila.push({ p.id, 0 });
    visitados.insert(p.id);

    while (!fila.empty()) {
      auto [atual, nivel] = fila.front();
      fila.pop();

      if (nivel > stats.geracoes) stats.geracoes = nivel;

      const Pessoa& atual_p = arvore.at(atual);
      for (int filho_id : atual_p.filhos) {
        if (!visitados.count(filho_id)) {
          visitados.insert(filho_id);
          fila.push({ filho_id, nivel + 1 });
        }
      }
    }
  }

  return stats;
}