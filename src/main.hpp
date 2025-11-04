#ifndef MAIN_HPP
#define MAIN_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

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

// Protótipos das funções
vector<Pessoa> lerCSV(const string& filename);
map<int, Pessoa> construirArvore(vector<Pessoa>& pessoas);
void encontrarRaiz(map<int, Pessoa>& arvore, int& raiz_id);
void imprimirArvore(const map<int, Pessoa>& arvore, int pessoa_id, int nivel, vector<bool>& ultimos);
bool validarArvore(const map<int, Pessoa>& arvore);

#endif