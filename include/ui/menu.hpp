#ifndef MENU_HPP
#define MENU_HPP

#include "../core/pessoa.hpp"
#include <map>

using namespace std;

// Sistema de menu interativo
void menuInterativo(map<int, Pessoa>& arvore);
void adicionarPessoaInterativo(map<int, Pessoa>& arvore);

#endif