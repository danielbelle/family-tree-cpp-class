#ifndef CSV_HANDLER_HPP
#define CSV_HANDLER_HPP

#include "../core/pessoa.hpp"
#include <vector>
#include <string>
#include <map>

using namespace std;

// Funções de leitura e escrita de arquivos CSV
vector<Pessoa> lerCSV(const string& filename);
void salvarCSV(const map<int, Pessoa>& arvore, const string& filename);

#endif