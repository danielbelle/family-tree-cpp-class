#include "../../include/utils/validacao.hpp"

bool validarGenero(char genero) {
  return genero == 'M' || genero == 'F';
}

char solicitarGeneroValido() {
  char genero;
  do {
    cout << "Gênero (M/F): ";
    cin >> genero;
    genero = toupper(genero);
    if (!validarGenero(genero)) {
      cout << "Gênero inválido! Digite M ou F: ";
    }
  } while (!validarGenero(genero));
  return genero;
}

void removerDuplicatas(vector<int>& vetor) {
  sort(vetor.begin(), vetor.end());
  vetor.erase(unique(vetor.begin(), vetor.end()), vetor.end());
}

bool pessoaExiste(const map<int, Pessoa>& arvore, int id) {
  return arvore.find(id) != arvore.end();
}

/**
 * Valida inconsistências na árvore genealógica
 */
bool validarInconsistencias(const map<int, Pessoa>& arvore) {
  bool consistente = true;

  for (const auto& par : arvore) {
    const Pessoa& p = par.second;

    // Valida que pais existem se especificados
    if (p.id_pai > 0 && !pessoaExiste(arvore, p.id_pai)) {
      cout << "❌ ERRO: Pai ID " << p.id_pai << " não existe para " << p.nome << endl;
      consistente = false;
    }

    if (p.id_mae > 0 && !pessoaExiste(arvore, p.id_mae)) {
      cout << "❌ ERRO: Mãe ID " << p.id_mae << " não existe para " << p.nome << endl;
      consistente = false;
    }

    // Valida que cônjuge existe se especificado
    if (p.id_conjuge > 0 && !pessoaExiste(arvore, p.id_conjuge)) {
      cout << "❌ ERRO: Cônjuge ID " << p.id_conjuge << " não existe para " << p.nome << endl;
      consistente = false;
    }

    // Valida que pessoa não é pai/mãe de si mesma
    if (p.id_pai == p.id || p.id_mae == p.id) {
      cout << "❌ ERRO: " << p.nome << " é pai/mãe de si mesma!" << endl;
      consistente = false;
    }
  }

  if (consistente) {
    cout << "✅ Árvore validada com sucesso - sem inconsistências encontradas!" << endl;
  }

  return consistente;
}