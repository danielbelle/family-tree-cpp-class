#ifndef VALIDACAO_HPP
#define VALIDACAO_HPP

#include "../core/pessoa.hpp"
#include <map>
#include <vector>

// Funções de validação e utilitárias
bool validarGenero(char genero);
char solicitarGeneroValido();
void removerDuplicatas(vector<int>& vetor);
bool pessoaExiste(const map<int, Pessoa>& arvore, int id);

#endif