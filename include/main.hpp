#pragma once

#include "core/arvore.hpp"
#include "io/csv_handler.hpp"
#include "io/utf8_config.hpp"
#include "ui/menu.hpp"
#include "ui/impressao.hpp"
#include "utils/validacao.hpp"
#include <iostream>
#include <limits>

using namespace std;

int main();
map<int, Pessoa> configurarArvore();
void mostrarCabecalho();
void mostrarErro(const string& mensagem);