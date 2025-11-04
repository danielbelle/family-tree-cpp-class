#include "../../include/io/csv_handler.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>

using namespace std;

vector<Pessoa> lerCSV(const string& filename) {
  vector<Pessoa> pessoas;
  ifstream arquivo(filename);

  if (!arquivo.is_open()) {
    cout << "Erro ao abrir arquivo: " << filename << endl;
    return pessoas;
  }

  string linha;
  bool cabecalho = true;

  while (getline(arquivo, linha)) {
    if (cabecalho) {
      cabecalho = false;
      continue;
    }

    if (linha.empty()) continue;

    stringstream ss(linha);
    string token;
    Pessoa p;
    vector<string> dados;

    while (getline(ss, token, ',')) {
      dados.push_back(token);
    }

    if (dados.size() >= 6) {
      p.id = stoi(dados[0]);
      p.nome = dados[1];
      p.genero = dados[2][0];
      p.id_pai = stoi(dados[3]);
      p.id_mae = stoi(dados[4]);
      p.id_conjuge = stoi(dados[5]);

      pessoas.push_back(p);
    }
  }

  arquivo.close();
  return pessoas;
}

void salvarCSV(const map<int, Pessoa>& arvore, const string& filename) {
  ofstream arquivo(filename);

  if (!arquivo.is_open()) {
    cout << "Erro ao abrir arquivo para salvar: " << filename << endl;
    return;
  }

  // Escrever cabeçalho
  arquivo << "id,nome,genero,id_pai,id_mae,id_conjuge" << endl;

  // Escrever dados
  for (const auto& par : arvore) {
    const Pessoa& p = par.second;
    arquivo << p.id << "," << p.nome << "," << p.genero << ","
      << p.id_pai << "," << p.id_mae << "," << p.id_conjuge << endl;
  }

  arquivo.close();
  cout << "Dados salvos em " << filename << " com sucesso!" << endl;
}