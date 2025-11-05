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

using namespace std;

// Sistema de menu interativo
void menuInterativo(map<int, Pessoa>& arvore);
void adicionarPessoaInterativo(map<int, Pessoa>& arvore);
void definirPaisParaPessoaCriada(map<int, Pessoa>& arvore);
void verArvoreCompleta(map<int, Pessoa>& arvore);
void listarTodasPessoas(map<int, Pessoa>& arvore);
void localizarPessoaPorNome(map<int, Pessoa>& arvore);