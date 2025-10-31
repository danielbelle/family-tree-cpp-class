#include "pch/pch.hpp"

// Criar pessoa
Pessoa* criarPessoa(const string& nome, const string& data, char genero) {
  Pessoa* nova = new Pessoa;
  nova->nome = nome;
  nova->dataNascimento = data;
  nova->genero = genero;
  nova->familiaOrigem = nullptr;
  return nova;
}

// Ler pessoa
// Update pessoa
// Delete pessoa

// Criar familia
Familia* criarFamilia(Pessoa* pai, Pessoa* mae) {
  Familia* nova = new Familia;
  nova->pai = pai;
  nova->mae = mae;
  nova->familiaAncestral = nullptr;
  return nova;
}

// Ler familia
// Update familia
// Delete familia


// Criar arvore
ArvoreGenealogica* criarArvore() {
  ArvoreGenealogica* arvore = new ArvoreGenealogica;
  arvore->raizFamilia = nullptr;
  return arvore;
}
// Ler arvore
// Update arvore
// Delete arvore