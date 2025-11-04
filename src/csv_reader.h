#ifndef CSV_READER_H
#define CSV_READER_H

#include <string>
#include <vector>
#include "pessoa.h"

using namespace std;

// Funções para leitura de CSV
vector<Pessoa> lerCSV(const string& filename, char delimiter = ',');
Pessoa parseLinhaCSV(const string& linha, char delimiter);
vector<string> splitString(const string& str, char delimiter);
bool validarLinhaCSV(const vector<string>& campos);

#endif