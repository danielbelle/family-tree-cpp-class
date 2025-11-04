#include "csv_reader.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

vector<Pessoa> lerCSV(const string& filename, char delimiter) {
  vector<Pessoa> pessoas;
  ifstream arquivo(filename);

  if (!arquivo.is_open()) {
    cerr << "Erro: Não foi possível abrir o arquivo " << filename << endl;
    return pessoas;
  }

  string linha;
  bool primeiraLinha = true;

  while (getline(arquivo, linha)) {
    // Pular linha de cabeçalho
    if (primeiraLinha) {
      primeiraLinha = false;
      continue;
    }

    // Processar linha
    Pessoa pessoa = parseLinhaCSV(linha, delimiter);
    if (validarPessoa(pessoa)) {
      pessoas.push_back(pessoa);
    }
    else {
      cerr << "Aviso: Linha inválida ignorada: " << linha << endl;
    }
  }

  arquivo.close();
  cout << "Carregadas " << pessoas.size() << " pessoas do CSV." << endl;
  return pessoas;
}

Pessoa parseLinhaCSV(const string& linha, char delimiter) {
  vector<string> campos = splitString(linha, delimiter);

  if (!validarLinhaCSV(campos)) {
    return criarPessoa("", "", "", "", ""); // Retorna pessoa inválida
  }

  Pessoa pessoa = criarPessoa(campos[0], campos[1], campos[2], campos[3], campos[4]);

  // Campos opcionais
  if (campos.size() > 5) pessoa.conjuge = campos[5];
  if (campos.size() > 6) pessoa.idConjuge = campos[6];
  if (campos.size() > 7) pessoa.pai = campos[7];
  if (campos.size() > 8) pessoa.idPai = campos[8];
  if (campos.size() > 9) pessoa.mae = campos[9];
  if (campos.size() > 10) pessoa.idMae = campos[10];

  return pessoa;
}

vector<string> splitString(const string& str, char delimiter) {
  vector<string> tokens;
  stringstream ss(str);
  string token;

  while (getline(ss, token, delimiter)) {
    tokens.push_back(token);
  }

  return tokens;
}

bool validarLinhaCSV(const vector<string>& campos) {
  // Mínimo: idPessoa, nome, genero, familia, idFamilia
  if (campos.size() < 5) {
    return false;
  }

  // Validar gênero
  if (!validarGenero(campos[2])) {
    return false;
  }

  return true;
}