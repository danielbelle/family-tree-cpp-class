#include "../../include/ui/impressao.hpp"

/**
 * Imprime os prefixos visuais da árvore
 */
void imprimirPrefixos(int nivel, const vector<bool>& ultimos) {
  for (int i = 0; i < nivel; i++) {
    if (i == nivel - 1) {
      // Último nível: usa os caracteres de árvore 
      cout << (ultimos[i] ? "   └── " : "   ├── ");
    }
    else {
      // Níveis anteriores: usa espaçamento ou linha vertical 
      cout << (ultimos[i] ? "    " : "   │");
    }
  }
}

/**
 * Imprime informações de uma pessoa e seu cônjuge
 */
void imprimirPessoaComConjuge(const Pessoa& p, const map<int, Pessoa>& arvore) {
  cout << p.nome << " (" << p.genero << ", nasc. " << p.ano_nascimento << ") [ID: " << p.id << "]";

  if (p.id_conjuge > 0 && pessoaExiste(arvore, p.id_conjuge)) {
    const Pessoa& conjuge = arvore.at(p.id_conjuge);
    cout << " 💑 " << conjuge.nome << " (" << conjuge.genero << ", nasc. " << conjuge.ano_nascimento << ") [ID: " << conjuge.id << "]";
  }
}

/**
 * Imprime a árvore genealógica de forma hierárquica
 */
void imprimirArvore(const map<int, Pessoa>& arvore, int pessoa_id, int nivel, vector<bool>& ultimos) {
  if (!pessoaExiste(arvore, pessoa_id)) return;

  const Pessoa& p = arvore.at(pessoa_id);

  imprimirPrefixos(nivel, ultimos);
  imprimirPessoaComConjuge(p, arvore);
  cout << endl;

  if (!p.filhos.empty()) {
    ultimos.push_back(false);

    for (size_t i = 0; i < p.filhos.size(); i++) {
      if (i == p.filhos.size() - 1) {
        ultimos[nivel] = true;
      }
      imprimirArvore(arvore, p.filhos[i], nivel + 1, ultimos);
    }

    ultimos.pop_back();
  }
}

/**
 * Imprime árvore usando abordagem iterativa (usando imprimirPrefixos)
 */
void imprimirArvoreIterativa(const map<int, Pessoa>& arvore, int raiz_id) {
  if (!pessoaExiste(arvore, raiz_id)) return;

  // Estrutura que mantém o estado igual à versão recursiva
  struct NodeState {
    int id;
    int nivel;
    vector<bool> ultimos;
  };

  stack<NodeState> pilha;
  pilha.push({ raiz_id, 0, {} });

  while (!pilha.empty()) {
    NodeState current = pilha.top();
    pilha.pop();

    const Pessoa& p = arvore.at(current.id);

    imprimirPrefixos(current.nivel, current.ultimos);
    imprimirPessoaComConjuge(p, arvore);
    cout << endl;

    // Adiciona filhos à pilha (em ordem reversa para manter ordem correta)
    for (int i = p.filhos.size() - 1; i >= 0; --i) {
      vector<bool> ultimos_filho = current.ultimos;

      if (static_cast<size_t>(i) == p.filhos.size() - 1) {
        if (ultimos_filho.size() > static_cast<size_t>(current.nivel)) {
          ultimos_filho[current.nivel] = true;
        }
        else {
          ultimos_filho.push_back(true);
        }
      }
      else {
        if (ultimos_filho.size() > static_cast<size_t>(current.nivel)) {
          ultimos_filho[current.nivel] = false;
        }
        else {
          ultimos_filho.push_back(false);
        }
      }

      pilha.push({ p.filhos[i], current.nivel + 1, ultimos_filho });
    }
  }
}

/**
 * Exibe a linha de ascendência de uma pessoa
 */
void exibirLinhaAscendencia(const map<int, Pessoa>& arvore, int pessoa_id) {
  if (!pessoaExiste(arvore, pessoa_id)) return;

  const Pessoa& p = arvore.at(pessoa_id);

  if (p.id_pai > 0) exibirLinhaAscendencia(arvore, p.id_pai);
  else if (p.id_mae > 0) exibirLinhaAscendencia(arvore, p.id_mae);

  if (p.id_pai > 0 || p.id_mae > 0) cout << " -> ";
  cout << p.nome << " (" << p.genero << ", nasc. " << p.ano_nascimento << ")";
}

/**
 * Exibe gerações organizadas por nível
 */
void exibirGeracoesPorNivel(const map<int, Pessoa>& arvore, int pessoa_id) {
  if (!pessoaExiste(arvore, pessoa_id)) return;

  queue<pair<int, int>> fila;
  fila.push({ pessoa_id, 0 });
  int nivel_atual = 0;

  while (!fila.empty()) {
    auto [atual, nivel] = fila.front();
    fila.pop();

    const Pessoa& p = arvore.at(atual);

    if (nivel > nivel_atual) {
      nivel_atual = nivel;
      cout << "\n--- GERAÇÃO " << nivel << " ---" << endl;
    }

    cout << "  ";
    imprimirPessoaComConjuge(p, arvore);
    cout << endl;

    for (int filho_id : p.filhos) {
      fila.push({ filho_id, nivel + 1 });
    }
  }
}

/**
 * Lista árvore completa a partir de um ancestral
 */
void listarArvoreDesdeAncestral(map<int, Pessoa>& arvore) {
  int pessoa_id = buscarPessoaInterativo(arvore);
  if (pessoa_id == -1) return;

  const Pessoa& ancestral = arvore.at(pessoa_id);
  cout << "\n=== ÁRVORE COMPLETA DESDE " << ancestral.nome << " ===" << endl;

  imprimirArvoreIterativa(arvore, pessoa_id);

  int total_descendentes = contarDescendentes(arvore, pessoa_id);
  cout << "\n--- ESTATÍSTICAS ---" << endl;
  cout << "Total de descendentes: " << total_descendentes << endl;
  cout << "Filhos diretos: " << ancestral.filhos.size() << endl;
}

/**
 * Exibe ascendentes e descendentes de uma pessoa
 */
void exibirAscendentesEDescendentes(map<int, Pessoa>& arvore) {
  int pessoa_id = buscarPessoaInterativo(arvore);
  if (pessoa_id == -1) return;

  const Pessoa& pessoa = arvore.at(pessoa_id);
  cout << "\n=== LINHAGEM COMPLETA DE " << pessoa.nome << " ===" << endl;

  cout << "\n--- ASCENDENTES ---" << endl;
  exibirLinhaAscendencia(arvore, pessoa_id);
  cout << endl;

  cout << "\n--- DESCENDENTES ---" << endl;
  imprimirArvoreIterativa(arvore, pessoa_id);

  cout << "\n--- ESTATÍSTICAS ---" << endl;
  cout << "Filhos diretos: " << pessoa.filhos.size() << endl;
}

/**
 * Exibe nível de parentesco entre duas pessoas
 */
void exibirNivelParentesco(map<int, Pessoa>& arvore) {
  cout << "\n=== NÍVEL DE PARENTESCO ===" << endl;

  cout << "Primeira pessoa:" << endl;
  int pessoa1_id = buscarPessoaInterativo(arvore);
  if (pessoa1_id == -1) return;

  cout << "\nSegunda pessoa:" << endl;
  int pessoa2_id = buscarPessoaInterativo(arvore);
  if (pessoa2_id == -1) return;

  const Pessoa& p1 = arvore.at(pessoa1_id);
  const Pessoa& p2 = arvore.at(pessoa2_id);
  int nivel = calcularParentesco(arvore, pessoa1_id, pessoa2_id);

  cout << "\n=== RESULTADO ===" << endl;
  cout << "Pessoa 1: " << p1.nome << " (ID: " << p1.id << ", nasc. " << p1.ano_nascimento << ")" << endl;
  cout << "Pessoa 2: " << p2.nome << " (ID: " << p2.id << ", nasc. " << p2.ano_nascimento << ")" << endl;


  switch (nivel) {
  case -1:
    cout << "❌ Não há parentesco entre as duas pessoas." << endl;
    break;
  case 0:
    cout << "👤 São a mesma pessoa!" << endl;
    break;
  default:
    cout << "📏 Nível de parentesco: " << nivel << " grau(s) de separação" << endl;

    if (nivel == 1) {
      if (p1.id_pai == pessoa2_id || p1.id_mae == pessoa2_id) {
        cout << "   👶 " << p1.nome << " é filho(a) de " << p2.nome << endl;
      }
      else if (p2.id_pai == pessoa1_id || p2.id_mae == pessoa1_id) {
        cout << "   👨‍👧 " << p1.nome << " é pai/mãe de " << p2.nome << endl;
      }
      else if (p1.id_conjuge == pessoa2_id) {
        cout << "   💑 " << p1.nome << " é cônjuge de " << p2.nome << endl;
      }
      else {
        cout << "   🔗 Parentesco direto" << endl;
      }
    }
    else if (nivel == 2) {
      cout << "   👥 Parentesco de segundo grau (avós/netos, tios/sobrinhos)" << endl;
    }
    else if (nivel == 3) {
      cout << "   👥 Parentesco de terceiro grau (bisavós/bisnetos, primos)" << endl;
    }
    else {
      cout << "   👥 Parentesco distante" << endl;
    }
    break;
  }
}

/**
 * Exibe contagem de descendentes
 */
void exibirContagemDescendentes(map<int, Pessoa>& arvore) {
  cout << "\n=== CONTAGEM DE DESCENDENTES ===" << endl;

  int pessoa_id = buscarPessoaInterativo(arvore);
  if (pessoa_id == -1) return;

  const Pessoa& pessoa = arvore.at(pessoa_id);
  int total_descendentes = contarDescendentes(arvore, pessoa_id);
  int filhos_diretos = pessoa.filhos.size();
  int filhos_indiretos = total_descendentes - filhos_diretos;

  cout << "\n=== RESULTADO ===" << endl;
  cout << "Pessoa: " << pessoa.nome << " (ID: " << pessoa.id << ", nasc. " << pessoa.ano_nascimento << ")" << endl;
  cout << "📊 ESTATÍSTICAS DE DESCENDENTES:" << endl;
  cout << "   • Filhos diretos: " << filhos_diretos << endl;
  cout << "   • Descendentes indiretos: " << filhos_indiretos << endl;
  cout << "   • TOTAL de descendentes: " << total_descendentes << endl;

  if (filhos_diretos > 0) {
    cout << "\n👶 FILHOS DIRETOS:" << endl;
    for (int filho_id : pessoa.filhos) {
      const Pessoa& filho = arvore.at(filho_id);
      int netos = contarDescendentes(arvore, filho_id);
      cout << "   • " << filho.nome << " (ID: " << filho.id << ", nasc. " << filho.ano_nascimento << ")";
      if (netos > 0) {
        cout << " → " << netos << " descendente(s)";
      }
      cout << endl;
    }
  }
}

/**
 * Exibe gerações separadas por nível
 */
void exibirGeracoesSeparadas(map<int, Pessoa>& arvore) {
  cout << "\n=== GERAÇÕES SEPARADAS POR NÍVEL ===" << endl;

  int pessoa_id = buscarPessoaInterativo(arvore);
  if (pessoa_id == -1) return;

  const Pessoa& pessoa = arvore.at(pessoa_id);

  cout << "\n=== GERAÇÕES A PARTIR DE " << pessoa.nome << " ===" << endl;
  cout << "Ancestral: " << pessoa.nome << " (" << pessoa.genero << ", nasc. " << pessoa.ano_nascimento << ") [ID: " << pessoa.id << "]" << endl;

  if (pessoa.id_conjuge > 0 && pessoaExiste(arvore, pessoa.id_conjuge)) {
    const Pessoa& conjuge = arvore.at(pessoa.id_conjuge);
    cout << "Cônjuge: " << conjuge.nome << " (" << conjuge.genero << ", nasc. " << conjuge.ano_nascimento << ") [ID: " << conjuge.id << "]" << endl;
  }

  cout << "=====================================" << endl;

  exibirGeracoesPorNivel(arvore, pessoa_id);

  int total_descendentes = contarDescendentes(arvore, pessoa_id);
  cout << "\n--- ESTATÍSTICAS ---" << endl;
  cout << "Total de descendentes: " << total_descendentes << endl;
}

/**
 * Exibe estatísticas avançadas da árvore
 */
void exibirEstatisticasAvancadas(map<int, Pessoa>& arvore) {
  EstatisticasArvore stats = calcularEstatisticas(arvore);

  cout << "\n=== ESTATÍSTICAS ===" << endl;
  cout << "📊 RESUMO DA ÁRVORE GENEALÓGICA:" << endl;
  cout << "• Total de pessoas: " << stats.total_pessoas << endl;
  cout << "• Gerações: " << stats.geracoes << endl;
}