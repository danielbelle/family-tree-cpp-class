#include "familia.h"
#include <iostream>

using namespace std;

unordered_map<string, Familia> agruparPorFamilia(const vector<Pessoa>& pessoas) {
  unordered_map<string, Familia> familias;

  for (const auto& pessoa : pessoas) {
    // Se a família não existe, criar
    if (familias.find(pessoa.idFamilia) == familias.end()) {
      Familia novaFamilia;
      novaFamilia.idFamilia = pessoa.idFamilia;
      novaFamilia.nomeFamilia = pessoa.familia;
      familias[pessoa.idFamilia] = novaFamilia;
    }

    // Adicionar pessoa à família
    familias[pessoa.idFamilia].membros.push_back(pessoa.idPessoa);
  }

  return familias;
}

const Pessoa* encontrarPessoaPorId(const string& id, const vector<Pessoa>& pessoas) {
  for (const auto& pessoa : pessoas) {
    if (pessoa.idPessoa == id) {
      return &pessoa;
    }
  }
  return nullptr;
}

void mostrarFamilia(const Familia& familia, const vector<Pessoa>& todasPessoas) {
  cout << "\n=== FAMÍLIA: " << familia.nomeFamilia << " (ID: " << familia.idFamilia << ") ===" << endl;
  cout << "Membros (" << familia.membros.size() << "):" << endl;

  for (const auto& membroId : familia.membros) {
    const Pessoa* pessoa = encontrarPessoaPorId(membroId, todasPessoas);
    if (pessoa) {
      cout << "  - ";
      mostrarPessoa(*pessoa);
    }
  }
}

void mostrarFlorestaGenealogica(const vector<Pessoa>& pessoas) {
  auto familias = agruparPorFamilia(pessoas);

  cout << "\n=== FLORESTA GENEALÓGICA ===" << endl;
  cout << "Total de famílias encontradas: " << familias.size() << endl;

  for (const auto& par : familias) {
    mostrarFamilia(par.second, pessoas);
  }

  // Estatísticas
  cout << "\n=== ESTATÍSTICAS ===" << endl;
  cout << "Total de pessoas: " << pessoas.size() << endl;
  cout << "Total de famílias: " << familias.size() << endl;
}