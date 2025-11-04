#pragma once
#include "includes.hpp"

void exibirMenuExibir();
void processarOpcaoExibir(const string& opcao);
void menuExibir();

// APENAS AS FUNÇÕES ESPECÍFICAS DO MENU
void listarPessoasComIDs();
void listarArvoresComIDs();
void mostrarArvoreComRelacoesCompletas(Pessoa* pessoa);