#ifndef FAMILIA_H
#define FAMILIA_H

#include <string>
#include <vector>
#include <unordered_map>
#include "pessoa.h"

using namespace std;

struct Familia {
  string idFamilia;
  string nomeFamilia;
  vector<string> membros; // IDs dos membros
};

// Funções para gerenciamento de famílias
unordered_map<string, Familia> agruparPorFamilia(const vector<Pessoa>& pessoas);
const Pessoa* encontrarPessoaPorId(const string& id, const vector<Pessoa>& pessoas);
void mostrarFamilia(const Familia& familia, const vector<Pessoa>& todasPessoas);
void mostrarFlorestaGenealogica(const vector<Pessoa>& pessoas);

#endif