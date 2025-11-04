#include "pessoa.h"
#include <iostream>

using namespace std;

Pessoa criarPessoa(const string& id, const string& nome, const string& genero,
  const string& familia, const string& idFamilia) {
  Pessoa pessoa;
  pessoa.idPessoa = id;
  pessoa.nome = nome;
  pessoa.genero = genero;
  pessoa.familia = familia;
  pessoa.idFamilia = idFamilia;
  pessoa.conjuge = "";
  pessoa.idConjuge = "";
  pessoa.pai = "";
  pessoa.idPai = "";
  pessoa.mae = "";
  pessoa.idMae = "";
  return pessoa;
}

bool validarGenero(const string& genero) {
  return genero == "M" || genero == "F";
}

bool validarPessoa(const Pessoa& pessoa) {
  return !pessoa.idPessoa.empty() &&
    !pessoa.nome.empty() &&
    validarGenero(pessoa.genero) &&
    !pessoa.familia.empty() &&
    !pessoa.idFamilia.empty();
}

void mostrarPessoa(const Pessoa& pessoa) {
  cout << "ID: " << pessoa.idPessoa << " | Nome: " << pessoa.nome
    << " | Gênero: " << pessoa.genero << " | Família: " << pessoa.familia
    << " | ID Família: " << pessoa.idFamilia << endl;

  if (!pessoa.conjuge.empty()) {
    cout << "  Cônjuge: " << pessoa.conjuge << " (ID: " << pessoa.idConjuge << ")" << endl;
  }
  if (!pessoa.pai.empty()) {
    cout << "  Pai: " << pessoa.pai << " (ID: " << pessoa.idPai << ")" << endl;
  }
  if (!pessoa.mae.empty()) {
    cout << "  Mãe: " << pessoa.mae << " (ID: " << pessoa.idMae << ")" << endl;
  }
}

string gerarIdAutomatico(const vector<Pessoa>& pessoas) {
  int maxId = 0;
  for (const auto& pessoa : pessoas) {
    if (pessoa.idPessoa.size() > 1 && pessoa.idPessoa[0] == 'p') {
      try {
        int idNum = stoi(pessoa.idPessoa.substr(1));
        if (idNum > maxId) maxId = idNum;
      }
      catch (...) {
        continue;
      }
    }
  }
  return "p" + to_string(maxId + 1);
}