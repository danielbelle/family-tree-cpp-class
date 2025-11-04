#ifndef PESSOA_H
#define PESSOA_H

#include <string>
#include <vector>

using namespace std;

struct Pessoa {
  string idPessoa;
  string nome;
  string genero;  // "M" ou "F"
  string familia;
  string idFamilia;

  // Relacionamentos (podem ser vazios)
  string conjuge;
  string idConjuge;
  string pai;
  string idPai;
  string mae;
  string idMae;
};

// Funções utilitárias para pessoas
bool validarGenero(const string& genero);
bool validarPessoa(const Pessoa& pessoa);
void mostrarPessoa(const Pessoa& pessoa);
string gerarIdAutomatico(const vector<Pessoa>& pessoas);
Pessoa criarPessoa(const string& id, const string& nome, const string& genero,
  const string& familia, const string& idFamilia);

#endif