#pragma once

#include "estruturas.hpp"

using json = nlohmann::json;

namespace persistencia {

  // Estrutura para o banco de dados unificado
  struct BancoDeDados {
    vector<ArvoreGenealogica*> arvores;
    vector<Pessoa*> pessoasSemArvore;
    vector<Familia*> familiasSemArvore;
    string dataUltimaModificacao;
  };

  // Salvar TODO o banco de dados
  bool salvarBancoDeDados(const vector<ArvoreGenealogica*>& arvores,
                         const unordered_map<string, Pessoa*>& pessoasGlobal);

  // Carregar TODO o banco de dados
  bool carregarBancoDeDados(vector<ArvoreGenealogica*>& arvores,
                           unordered_map<string, Pessoa*>& pessoasGlobal);

  // Salvar árvore específica no banco (para compatibilidade)
  bool salvarArvore(const ArvoreGenealogica* arvore, const string& nomeArquivo);

  // Carregar árvore específica do banco
  ArvoreGenealogica* carregarArvore(const string& nomeArquivo);

  // Listar árvores salvas
  vector<string> listarArvoresSalvas();

  // Conversões JSON
  json pessoaParaJson(const Pessoa* pessoa);
  json familiaParaJson(const Familia* familia);
  json arvoreParaJson(const ArvoreGenealogica* arvore);

  Pessoa* jsonParaPessoa(const json& j);
  Familia* jsonParaFamilia(const json& j);
  ArvoreGenealogica* jsonParaArvore(const json& j);

} 