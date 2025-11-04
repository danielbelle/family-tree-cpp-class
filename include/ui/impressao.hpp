#ifndef IMPRESSAO_HPP
#define IMPRESSAO_HPP

#include "../core/pessoa.hpp"
#include <map>
#include <vector>

using namespace std;

// Funções unificadas de impressão da árvore
void imprimirArvore(const map<int, Pessoa>& arvore, int pessoa_id, int nivel, vector<bool>& ultimos);
void exibirLinhaAscendencia(const map<int, Pessoa>& arvore, int pessoa_id);
void exibirGeracoesPorNivel(const map<int, Pessoa>& arvore, int pessoa_id);

// Funções de exibição específicas
void listarArvoreDesdeAncestral(map<int, Pessoa>& arvore);
void exibirAscendentesEDescendentes(map<int, Pessoa>& arvore);
void exibirNivelParentesco(map<int, Pessoa>& arvore);
void exibirContagemDescendentes(map<int, Pessoa>& arvore);
void exibirGeracoesSeparadas(map<int, Pessoa>& arvore);

#endif