#ifndef BUSCA_HPP
#define BUSCA_HPP

#include "../core/pessoa.hpp"
#include <map>
#include <string>

using namespace std;

// Funções de busca de pessoas
int buscarPessoaPorNome(const map<int, Pessoa>& arvore, const string& nome);
int buscarPessoaInterativo(const map<int, Pessoa>& arvore);

#endif