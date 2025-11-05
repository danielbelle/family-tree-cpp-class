#pragma once

#include "../core/pessoa.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
#include <string>

using namespace std;

// Funções de leitura e escrita de arquivos CSV
vector<Pessoa> lerCSV(const string& filename);
void salvarCSV(const map<int, Pessoa>& arvore, const string& filename);
