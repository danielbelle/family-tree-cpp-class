#pragma once
#include "includes.hpp"

// Declarações das variáveis globais
extern vector<Pessoa*> pessoas;
extern vector<ArvoreGenealogica*> arvores;

// Declarações das funções de processo
void criarPessoa();
void listarPessoas();
void limparMemoria();

// Gestão de pessoas
Pessoa* criarPessoa(const string& nome, const string& dataNasc, char genero);
Pessoa* buscarPessoa(const string& id);
vector<Pessoa*> buscarPessoasPorNome(const string& nome);
bool definirRelacaoPaiFilho(Pessoa* pai, Pessoa* mae, Pessoa* filho);

// Gestão de árvores genealógicas
ArvoreGenealogica* criarArvoreGenealogica(const string& nome);
bool adicionarPessoaArvore(ArvoreGenealogica* arvore, Pessoa* pessoa);
ArvoreGenealogica* buscarArvoreGenealogica(const string& id);

// Navegação e busca
vector<Pessoa*> buscarAscendentes(Pessoa* pessoa);
vector<Pessoa*> buscarDescendentes(Pessoa* pessoa);
void listarArvoreCompleta(Pessoa* ancestral);

// Utilitários
string gerarIDPessoa();
string gerarIDArvore();
void mostrarArvoreHierarquica(Pessoa* pessoa, int nivel = 0, vector<bool> ultimos = vector<bool>());
void mostrarTodasArvores();

// Novas funcionalidades
int calcularParentesco(Pessoa* p1, Pessoa* p2);
int contarDescendentes(Pessoa* pessoa);
void mostrarGeracoes(Pessoa* ancestral);
bool gravarArvoreCSV(ArvoreGenealogica* arvore);
bool carregarArvoreCSV();

// NOVAS FUNÇÕES ADICIONADAS
void listarPessoasComIDs();
void listarArvoresComIDs();
bool gravarArvoreCSVComplementar(ArvoreGenealogica* arvore);