#include <iostream>
#include <vector>
#include "pessoa.h"
#include "csv_reader.h"
#include "familia.h"

using namespace std;

// Configurar UTF-8 para suporte a caracteres especiais
void configurarUTF8() {
  setlocale(LC_ALL, "en_US.UTF-8");
}

int main() {
  configurarUTF8();

  cout << "=== SISTEMA DE GENEALOGIA ===" << endl;

  // Carregar dados do CSV
  vector<Pessoa> pessoas = lerCSV("dados/dados.csv");

  if (pessoas.empty()) {
    cout << "Nenhum dado carregado. Verifique o arquivo CSV." << endl;
    return 1;
  }

  // Mostrar floresta de árvores genealógicas
  mostrarFlorestaGenealogica(pessoas);

  return 0;
}