#ifndef MAIN_HPP
#define MAIN_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <functional>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

struct Pessoa {
  int id;
  string nome;
  char genero;
  int id_pai;
  int id_mae;
  int id_conjuge;
  vector<int> filhos;
};

// Funções principais
vector<Pessoa> lerCSV(const string& filename);
map<int, Pessoa> construirArvore(vector<Pessoa>& pessoas);
void encontrarRaiz(map<int, Pessoa>& arvore, int& raiz_id);
void imprimirArvore(const map<int, Pessoa>& arvore, int pessoa_id, int nivel, vector<bool>& ultimos);
bool validarArvore(const map<int, Pessoa>& arvore);

// Funções auxiliares
int obterProximoId(const map<int, Pessoa>& arvore);
void removerDuplicatas(vector<int>& vetor);
bool validarGenero(char genero);
char solicitarGeneroValido();
Pessoa criarNovaPessoa(const map<int, Pessoa>& arvore, const string& nome, char genero, int id_conjuge = 0);

// Funções de manipulação
void adicionarPessoa(map<int, Pessoa>& arvore, const Pessoa& nova_pessoa);
void definirPais(map<int, Pessoa>& arvore, int id_filho);
void definirParenteComoPai(map<int, Pessoa>& arvore, Pessoa& filho, int id_parente);
void definirParenteComoMae(map<int, Pessoa>& arvore, Pessoa& filho, int id_parente);
void processarDefinicaoMae(map<int, Pessoa>& arvore, Pessoa& pai, Pessoa& filho);
void processarDefinicaoPai(map<int, Pessoa>& arvore, Pessoa& mae, Pessoa& filho);
void criarConjugeAutomatico(map<int, Pessoa>& arvore, Pessoa& parente, Pessoa& filho, char genero_conjuge);
void salvarCSV(const map<int, Pessoa>& arvore, const string& filename);

// Interface do usuário
void adicionarPessoaInterativo(map<int, Pessoa>& arvore);
void menuInterativo(map<int, Pessoa>& arvore);

// Funções de busca e linhagem
int buscarPessoaPorNome(const map<int, Pessoa>& arvore, const string& nome);
void exibirLinhaAscendencia(const map<int, Pessoa>& arvore, int pessoa_id);
void exibirLinhaDescendencia(const map<int, Pessoa>& arvore, int pessoa_id, int nivel, vector<bool>& ultimos);
void exibirAscendentesEDescendentes(map<int, Pessoa>& arvore);
void listarArvoreDesdeAncestral(map<int, Pessoa>& arvore);
int buscarPessoaInterativo(const map<int, Pessoa>& arvore);

#endif