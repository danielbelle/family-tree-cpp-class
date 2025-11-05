#pragma once

#include "../utils/validacao.hpp"
#include "pessoa.hpp"
#include <iostream>
#include <queue>
#include <set>
#include <functional>
#include <map>
#include <vector>
#include <stack>

using namespace std;

// Estrutura para estatísticas avançadas
struct EstatisticasArvore {
  int total_pessoas;
  int geracoes;
};

// Funções principais de construção e manipulação da árvore
map<int, Pessoa> construirArvore(vector<Pessoa>& pessoas);
void encontrarRaiz(const map<int, Pessoa>& arvore, int& raiz_id);
bool validarArvore(const map<int, Pessoa>& arvore);

// Funções de manipulação de pessoas
int obterProximoId(const map<int, Pessoa>& arvore);
void adicionarPessoa(map<int, Pessoa>& arvore, const Pessoa& nova_pessoa);
void definirPais(map<int, Pessoa>& arvore, int id_filho);

// Funções de cálculo de parentesco
int calcularParentesco(const map<int, Pessoa>& arvore, int pessoa1_id, int pessoa2_id);
int contarDescendentes(const map<int, Pessoa>& arvore, int pessoa_id);

// Funções de análise avançada
EstatisticasArvore calcularEstatisticas(const map<int, Pessoa>& arvore);