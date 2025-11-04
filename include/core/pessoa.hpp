#ifndef PESSOA_HPP
#define PESSOA_HPP

#include <vector>
#include <string>

using namespace std;

// Estrutura que representa uma pessoa na árvore genealógica
struct Pessoa {
  int id;
  string nome;
  char genero;
  int id_pai;
  int id_mae;
  int id_conjuge;
  vector<int> filhos;
};

#endif