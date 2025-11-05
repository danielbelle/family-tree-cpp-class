#include "../include/main.hpp"

int main() {
  // Configurar UTF-8 no console
  configurarUTF8();

  map<int, Pessoa> arvore = configurarArvore();

  // falha ao configurar, sair com código de erro
  if (arvore.empty()) {
    mostrarErro("Configure o arquivo dados/dados.csv que sua árvore carregará automaticamente.\nO cabeçalho deve ser:\nid,nome,genero,ano_nascimento,id_pai,id_mae,id_conjuge\n");
  }

  // Menu interativo para adicionar pessoas e relações
  menuInterativo(arvore);

  return 0;
}

map<int, Pessoa> configurarArvore() {
  mostrarCabecalho();

  // Ler dados do CSV
  vector<Pessoa> pessoas = lerCSV("dados/dados.csv");

  if (pessoas.empty()) {
    mostrarErro("Nenhum dado encontrado ou arquivo vazio.");
    return {};
  }

  cout << "Pessoas carregadas: " << pessoas.size() << endl;

  // Construir árvore genealógica
  map<int, Pessoa> arvore = construirArvore(pessoas);

  // Encontrar a raiz da árvore
  int raiz_id = -1;
  encontrarRaiz(arvore, raiz_id);

  if (raiz_id == -1) {
    mostrarErro("Não foi possível encontrar a raiz da árvore.");
    return {};
  }

  cout << "\nRaiz da árvore: " << arvore.at(raiz_id).nome << " (ID: " << raiz_id << ")" << endl;

  // Validar árvore
  if (!validarArvore(arvore)) {
    mostrarErro("Árvore genealógica inválida.");
    return {};
  }

  // Imprimir árvore
  cout << "\n=== ÁRVORE GENEALÓGICA ===" << endl;
  vector<bool> ultimos;
  imprimirArvore(arvore, raiz_id, 0, ultimos);

  return arvore;
}

void mostrarCabecalho() {
  cout << "=== SISTEMA DE ÁRVORE GENEALÓGICA ===" << endl;
}

void mostrarErro(const string& msg) {
  cout << "Erro: " << msg << endl;
}
