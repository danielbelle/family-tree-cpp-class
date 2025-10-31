#pragma once

#include "estruturas.hpp"

namespace execucao {

  // Declaração das variáveis globais
  extern vector<arvore::ArvoreGenealogica*> arvoresGlobal;
  extern std::unordered_map<std::string, arvore::Pessoa*> pessoasGlobal;

  // Operações
  arvore::Pessoa* criarPessoaInterface();
  arvore::Familia* criarFamiliaInterface();
  void criarArvoreInterface();
  void listarPessoas();
  void limparTela();
  void pausar();
  void salvarArquivoUnico(); // Nova função
  void carregarArquivoUnico(); // Nova função
  void salvarArvoreInterface();
  void carregarArvoreInterface();
  void listarArvoresSalvasInterface();
}