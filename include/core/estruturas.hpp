#pragma once

using namespace std;

namespace arvore {

  struct Pessoa {
    string nome;              // Nome completo da pessoa
    string dataNascimento;    // Data no formato "DD/MM/AAAA"
    char genero;              // 'M' ou 'F'
    struct Familia* familiaOrigem;  // Ponteiro para a família dos pais
  };

  struct Familia {
    Pessoa* pai;                      // Ponteiro para o pai
    Pessoa* mae;                      // Ponteiro para a mãe
    vector<Pessoa*> filhos;           // Lista de filhos deste casal
    Familia* familiaAncestral;        // Família dos pais (avós)
    vector<Familia*> familiasFilhas;  // Famílias dos filhos
  };

  struct ArvoreGenealogica {
    Familia* raizFamilia;                        // Família mais antiga
    unordered_map<string, Pessoa*> indicePessoas; // Índice nome → pessoa
  };

}