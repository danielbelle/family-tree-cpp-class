#include "../../include/ui/impressao.hpp"
#include "../../include/core/arvore.hpp"
#include "../../include/utils/busca.hpp"
#include "../../include/utils/validacao.hpp"
#include <iostream>
#include <queue>
#include <functional>

using namespace std;

// Função unificada para imprimir árvore/descendentes
void imprimirArvore(const map<int, Pessoa>& arvore, int pessoa_id, int nivel, vector<bool>& ultimos) {
  if (!pessoaExiste(arvore, pessoa_id)) return;

  const Pessoa& p = arvore.at(pessoa_id);

  // Imprime a estrutura visual
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

  // Imprime a pessoa
  cout << p.nome << " (" << p.genero << ") [ID: " << p.id << "]";

  // Se tem conjuge, imprime também
  if (p.id_conjuge > 0 && pessoaExiste(arvore, p.id_conjuge)) {
    const Pessoa& conjuge = arvore.at(p.id_conjuge);
    cout << " 💑 " << conjuge.nome << " (" << conjuge.genero << ") [ID: " << conjuge.id << "]";
  }
  cout << endl;

  // Imprime os filhos recursivamente
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

void exibirLinhaAscendencia(const map<int, Pessoa>& arvore, int pessoa_id) {
  if (!pessoaExiste(arvore, pessoa_id)) return;

  const Pessoa& p = arvore.at(pessoa_id);

  // Primeiro exibe os ascendentes recursivamente
  if (p.id_pai > 0) {
    exibirLinhaAscendencia(arvore, p.id_pai);
  }
  else if (p.id_mae > 0) {
    exibirLinhaAscendencia(arvore, p.id_mae);
  }

  // Depois exibe a pessoa atual
  if (p.id_pai > 0 || p.id_mae > 0) {
    cout << " -> ";
  }

  cout << p.nome << " (" << p.genero << ")";
}

void exibirGeracoesPorNivel(const map<int, Pessoa>& arvore, int pessoa_id) {
  if (!pessoaExiste(arvore, pessoa_id)) return;

  queue<pair<int, int>> fila; // (pessoa_id, nivel)
  fila.push({ pessoa_id, 0 });

  int nivel_atual = 0;

  while (!fila.empty()) {
    auto [atual, nivel] = fila.front();
    fila.pop();

    const Pessoa& p = arvore.at(atual);

    // Se mudou de nível, imprime cabeçalho
    if (nivel > nivel_atual) {
      nivel_atual = nivel;
      cout << "\n--- GERAÇÃO " << nivel << " ---" << endl;
    }

    // Imprime a pessoa
    cout << "  " << p.nome << " (" << p.genero << ") [ID: " << p.id << "]";
    if (p.id_conjuge > 0 && pessoaExiste(arvore, p.id_conjuge)) {
      const Pessoa& conjuge = arvore.at(p.id_conjuge);
      cout << " 💑 " << conjuge.nome;
    }
    cout << endl;

    // Adiciona filhos à fila
    for (int filho_id : p.filhos) {
      fila.push({ filho_id, nivel + 1 });
    }
  }
}

void listarArvoreDesdeAncestral(map<int, Pessoa>& arvore) {
  int pessoa_id = buscarPessoaInterativo(arvore);
  if (pessoa_id == -1) return;

  const Pessoa& ancestral = arvore.at(pessoa_id);

  cout << "\n=== ÁRVORE COMPLETA DESDE " << ancestral.nome << " ===" << endl;
  cout << "Ancestral: " << ancestral.nome << " (" << ancestral.genero << ") [ID: " << ancestral.id << "]" << endl;

  if (ancestral.id_conjuge > 0 && pessoaExiste(arvore, ancestral.id_conjuge)) {
    const Pessoa& conjuge = arvore.at(ancestral.id_conjuge);
    cout << "Cônjuge: " << conjuge.nome << " (" << conjuge.genero << ") [ID: " << conjuge.id << "]" << endl;
  }

  cout << "=====================================" << endl;

  vector<bool> ultimos;
  imprimirArvore(arvore, pessoa_id, 0, ultimos);

  // Estatísticas
  int total_descendentes = contarDescendentes(arvore, pessoa_id);
  cout << "\n--- ESTATÍSTICAS DA ÁRVORE ---" << endl;
  cout << "Ancestral principal: " << ancestral.nome << endl;
  cout << "Total de descendentes: " << (total_descendentes - 1) << endl;
  cout << "Filhos diretos: " << ancestral.filhos.size() << endl;
}

void exibirAscendentesEDescendentes(map<int, Pessoa>& arvore) {
  int pessoa_id = buscarPessoaInterativo(arvore);
  if (pessoa_id == -1) return;

  const Pessoa& pessoa = arvore.at(pessoa_id);

  cout << "\n=== LINHAGEM COMPLETA DE " << pessoa.nome << " ===" << endl;

  // Exibir ascendentes
  cout << "\n--- ASCENDENTES (da raiz até " << pessoa.nome << ") ---" << endl;

  // Encontrar a raiz da árvore
  int raiz_id;
  encontrarRaiz(arvore, raiz_id);

  if (raiz_id != -1) {
    cout << "Raiz: ";
    exibirLinhaAscendencia(arvore, pessoa_id);
    cout << endl;
  }
  else {
    cout << "Não foi possível encontrar a raiz da árvore." << endl;
  }

  // Exibir descendentes
  cout << "\n--- DESCENDENTES (de " << pessoa.nome << " até os últimos) ---" << endl;
  vector<bool> ultimos;
  imprimirArvore(arvore, pessoa_id, 0, ultimos);

  // Estatísticas
  cout << "\n--- ESTATÍSTICAS ---" << endl;
  cout << "Pessoa: " << pessoa.nome << " (" << pessoa.genero << ") [ID: " << pessoa.id << "]" << endl;
  cout << "Número de descendentes diretos: " << pessoa.filhos.size() << endl;
}

void exibirNivelParentesco(map<int, Pessoa>& arvore) {
  cout << "\n=== NÍVEL DE PARENTESCO ENTRE DUAS PESSOAS ===" << endl;

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
  cout << "Pessoa 1: " << p1.nome << " (ID: " << p1.id << ")" << endl;
  cout << "Pessoa 2: " << p2.nome << " (ID: " << p2.id << ")" << endl;

  if (nivel == -1) {
    cout << "❌ Não há parentesco entre as duas pessoas." << endl;
  }
  else if (nivel == 0) {
    cout << "👤 São a mesma pessoa!" << endl;
  }
  else {
    cout << "📏 Nível de parentesco: " << nivel << " grau(s) de separação" << endl;

    // Descrição do parentesco
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
  }
}

void exibirContagemDescendentes(map<int, Pessoa>& arvore) {
  cout << "\n=== CONTAGEM DE DESCENDENTES ===" << endl;

  int pessoa_id = buscarPessoaInterativo(arvore);
  if (pessoa_id == -1) return;

  const Pessoa& pessoa = arvore.at(pessoa_id);
  int total_descendentes = contarDescendentes(arvore, pessoa_id);
  int filhos_diretos = pessoa.filhos.size();
  int filhos_indiretos = total_descendentes - filhos_diretos;

  cout << "\n=== RESULTADO ===" << endl;
  cout << "Pessoa: " << pessoa.nome << " (ID: " << pessoa.id << ")" << endl;
  cout << "📊 ESTATÍSTICAS DE DESCENDENTES:" << endl;
  cout << "   • Filhos diretos: " << filhos_diretos << endl;
  cout << "   • Descendentes indiretos: " << filhos_indiretos << endl;
  cout << "   • TOTAL de descendentes: " << total_descendentes << endl;

  if (filhos_diretos > 0) {
    cout << "\n👶 FILHOS DIRETOS:" << endl;
    for (int filho_id : pessoa.filhos) {
      const Pessoa& filho = arvore.at(filho_id);
      int netos = contarDescendentes(arvore, filho_id);
      cout << "   • " << filho.nome << " (ID: " << filho.id << ")";
      if (netos > 0) {
        cout << " → " << netos << " descendente(s)";
      }
      cout << endl;
    }
  }
}

void exibirGeracoesSeparadas(map<int, Pessoa>& arvore) {
  cout << "\n=== GERAÇÕES SEPARADAS POR NÍVEL ===" << endl;

  int pessoa_id = buscarPessoaInterativo(arvore);
  if (pessoa_id == -1) return;

  const Pessoa& pessoa = arvore.at(pessoa_id);

  cout << "\n=== GERAÇÕES A PARTIR DE " << pessoa.nome << " ===" << endl;
  cout << "Ancestral: " << pessoa.nome << " (" << pessoa.genero << ") [ID: " << pessoa.id << "]" << endl;

  if (pessoa.id_conjuge > 0 && pessoaExiste(arvore, pessoa.id_conjuge)) {
    const Pessoa& conjuge = arvore.at(pessoa.id_conjuge);
    cout << "Cônjuge: " << conjuge.nome << " (" << conjuge.genero << ") [ID: " << conjuge.id << "]" << endl;
  }

  cout << "=====================================" << endl;

  exibirGeracoesPorNivel(arvore, pessoa_id);

  // Estatísticas
  int total_descendentes = contarDescendentes(arvore, pessoa_id);
  cout << "\n--- ESTATÍSTICAS ---" << endl;
  cout << "Total de descendentes: " << total_descendentes << endl;
}