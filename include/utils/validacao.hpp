#pragma once

#include "../core/pessoa.hpp"
#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

// Funções de validação e utilitárias
bool validarGenero(char genero);
char solicitarGeneroValido();
void removerDuplicatas(vector<int>& vetor);
bool pessoaExiste(const map<int, Pessoa>& arvore, int id);

// Validação de inconsistências
bool validarInconsistencias(const map<int, Pessoa>& arvore);