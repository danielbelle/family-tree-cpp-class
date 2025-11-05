#pragma once

#include "../core/pessoa.hpp"
#include "../include/core/arvore.hpp"
#include "../include/utils/busca.hpp"
#include "../include/utils/validacao.hpp"
#include <iostream>
#include <queue>
#include <functional>
#include <map>
#include <vector>
#include <stack>

using namespace std;

// Funções de impressão da árvore
void imprimirArvore(const map<int, Pessoa>& arvore, int pessoa_id, int nivel, vector<bool>& ultimos);
void imprimirArvoreIterativa(const map<int, Pessoa>& arvore, int raiz_id);
void exibirLinhaAscendencia(const map<int, Pessoa>& arvore, int pessoa_id);
void exibirGeracoesPorNivel(const map<int, Pessoa>& arvore, int pessoa_id);

// Funções de exibição unificadas
void listarArvoreDesdeAncestral(map<int, Pessoa>& arvore);
void exibirAscendentesEDescendentes(map<int, Pessoa>& arvore);
void exibirNivelParentesco(map<int, Pessoa>& arvore);
void exibirContagemDescendentes(map<int, Pessoa>& arvore);
void exibirGeracoesSeparadas(map<int, Pessoa>& arvore);
void exibirEstatisticasAvancadas(map<int, Pessoa>& arvore);