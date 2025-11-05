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