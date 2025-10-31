#pragma once

using namespace std;
using namespace arvore;

// Criar pessoa
Pessoa* criarPessoa(const string& nome, const string& data, char genero);


// Ler pessoa
// Update pessoa
// Delete pessoa

// Criar familia
Familia* criarFamilia(Pessoa* pai, Pessoa* mae);
// Ler familia
// Update familia
// Delete familia


// Criar arvore
ArvoreGenealogica* criarArvore();
// Ler arvore
// Update arvore
// Delete arvore