#pragma once

#include "../core/pessoa.hpp"
#include "../io/utf8_config.hpp"
#include "validacao.hpp"
#include <algorithm>
#include <iostream>
#include <map>
#include <string>

using namespace std;

// Funções de busca de pessoas
int buscarPessoaPorNome(const map<int, Pessoa>& arvore, const string& nome);
int buscarPessoaInterativo(const map<int, Pessoa>& arvore);
