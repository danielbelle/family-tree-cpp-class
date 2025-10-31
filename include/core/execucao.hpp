#pragma once

#include "estruturas.hpp"

namespace execucao {

  // Variáveis globais
  extern ArvoreGenealogica* arvoreGlobal;
  extern unordered_map<string, Pessoa*> pessoasGlobal;

  // Operações
  Pessoa* criarPessoaInterface();
  Familia* criarFamiliaInterface();
  void criarArvoreInterface();
  void listarPessoas();
  void limparTela();
  void pausar();

} // namespace execucao