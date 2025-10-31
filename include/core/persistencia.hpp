#pragma once

#include "estruturas.hpp"

namespace persistencia {
  // Funções vazias para compatibilidade
  bool salvarBancoDeDados(const vector<ArvoreGenealogica*>& arvores,
    const unordered_map<string, Pessoa*>& pessoasGlobal);
  bool carregarBancoDeDados(vector<ArvoreGenealogica*>& arvores,
    unordered_map<string, Pessoa*>& pessoasGlobal);
  vector<string> listarArvoresSalvas();
}