#pragma once

#include "includes.hpp"

// Declarações das funções principais
void configurarUTF8();

// Declarações das funções dos menus
void menuCriarPessoa();
void menuCriarArvoreGenealogica();
void menuDefinirRelacao();
void menuExibirAscendentes();
void menuExibirDescendentes();
void menuListarArvoreCompleta();
void menuBuscarPessoaPorNome();
void menuListarPessoas();
void menuListarArvores();
void menuGravarArvore();
void menuCarregarArvore();
void menuParentesco();
void menuContarDescendentes();
void menuMostrarGeracoes();

// Funções do menu pós-criação
void menuPosCriacaoPessoa(Pessoa* pessoa);
void associarPessoaArvoreExistente(Pessoa* pessoa);
void definirPaisParaPessoa(Pessoa* pessoa);
void definirConjugeParaPessoa(Pessoa* pessoa);
void adicionarFilhosParaPessoa(Pessoa* pessoa);
void mostrarArvoreIndividual(Pessoa* pessoa);
Pessoa* criarProgenitorComGenero(const string& tipo, Pessoa* filho);
Pessoa* criarConjugeComGenero(Pessoa* pessoa);
void definirPaisComoRaizDaArvore(Pessoa* pessoa, Pessoa* pai, Pessoa* mae);
void associarMesmaArvore(Pessoa* pessoa, Pessoa* conjuge);