#include "../include/core/arvore.hpp"
#include "../include/io/csv_handler.hpp"
#include "../include/io/utf8_config.hpp"
#include "../include/ui/menu.hpp"
#include "../include/ui/impressao.hpp"
#include "../include/utils/validacao.hpp"
#include <iostream>
#include <limits>

using namespace std;

int main() {
  // Configurar UTF-8 no console
  configurarUTF8();

  cout << "=== SISTEMA DE ÁRVORE GENEALÓGICA ===" << endl;

  // Ler dados do CSV
  vector<Pessoa> pessoas = lerCSV("dados/dados.csv");

  if (pessoas.empty()) {
    cout << "Erro: Nenhum dado encontrado ou arquivo vazio." << endl;
    return 1;
  }

  cout << "Pessoas carregadas: " << pessoas.size() << endl;

  // Construir árvore genealógica
  map<int, Pessoa> arvore = construirArvore(pessoas);

  // Encontrar a raiz da árvore
  int raiz_id = -1;
  encontrarRaiz(arvore, raiz_id);

  if (raiz_id == -1) {
    cout << "Erro: Não foi possível encontrar a raiz da árvore." << endl;
    return 1;
  }

  cout << "\nRaiz da árvore: " << arvore.at(raiz_id).nome << " (ID: " << raiz_id << ")" << endl;

  // Validar árvore
  if (!validarArvore(arvore)) {
    cout << "Erro: Árvore genealógica inválida." << endl;
    return 1;
  }

  // Imprimir árvore
  cout << "\n=== ÁRVORE GENEALÓGICA ===" << endl;
  vector<bool> ultimos;
  imprimirArvore(arvore, raiz_id, 0, ultimos);

  // Menu interativo para adicionar pessoas e relações
  cout << "\n=== MODO INTERATIVO ===" << endl;
  menuInterativo(arvore);

  return 0;
}