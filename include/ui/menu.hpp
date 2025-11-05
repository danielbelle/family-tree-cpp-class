#pragma once

#include "../core/pessoa.hpp"
#include "../include/core/arvore.hpp"
#include "../include/io/csv_handler.hpp"
#include "../include/ui/impressao.hpp"
#include "../include/utils/busca.hpp"
#include "../include/utils/validacao.hpp"
#include "../include/io/utf8_config.hpp"
#include <iostream>
#include <map>
#include <functional>
#include <vector>

using namespace std;

// Structure para representar uma opção de menu
struct OpcaoMenu {
  string descricao;
  function<void(map<int, Pessoa>&)> acao;
};

// Structure para representar um tópico do menu
struct TopicoMenu {
  string nome;
  vector<OpcaoMenu> opcoes;
};

// Sistema de menu interativo
void menuInterativo(map<int, Pessoa>& arvore);
void adicionarPessoaInterativo(map<int, Pessoa>& arvore);
void definirPaisParaPessoaCriada(map<int, Pessoa>& arvore);
void verArvoreCompleta(map<int, Pessoa>& arvore);
void listarTodasPessoas(map<int, Pessoa>& arvore);
void localizarPessoaPorNome(map<int, Pessoa>& arvore);