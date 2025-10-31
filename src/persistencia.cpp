#include "pch/pch.hpp"

using namespace std;
using namespace arvore;

namespace persistencia {

  bool salvarBancoDeDados(const vector<ArvoreGenealogica*>& arvores,
    const unordered_map<string, Pessoa*>& pessoasGlobal) {
    try {
      json j;
      j["dataUltimaModificacao"] = "2025"; // time(nullptr)
      j["versao"] = "1.0";

      // Salvar árvores
      json arvoresJson = json::array();
      for (const auto& arvore : arvores) {
        if (arvore) {
          arvoresJson.push_back(arvoreParaJson(arvore));
        }
      }
      j["arvores"] = arvoresJson;

      // Salvar pessoas sem árvore
      json pessoasSemArvoreJson = json::array();
      for (const auto& par : pessoasGlobal) {
        Pessoa* pessoa = par.second;
        bool pertenceArvore = false;

        // Verificar se a pessoa pertence a alguma árvore
        for (const auto& arvore : arvores) {
          if (arvore && arvore->indicePessoas.find(pessoa->nome) != arvore->indicePessoas.end()) {
            pertenceArvore = true;
            break;
          }
        }

        if (!pertenceArvore) {
          pessoasSemArvoreJson.push_back(pessoaParaJson(pessoa));
        }
      }
      j["pessoasSemArvore"] = pessoasSemArvoreJson;

      // Criar diretório se não existir
      system("mkdir data 2>nul");

      // Salvar em arquivo único
      ofstream arquivo("data/armazenamento.json");
      if (!arquivo.is_open()) {
        return false;
      }

      arquivo << j.dump(4);
      arquivo.close();

      return true;
    }
    catch (const exception& e) {
      cerr << "❌ Erro ao salvar banco de dados: " << e.what() << endl;
      return false;
    }
  }

  bool carregarBancoDeDados(vector<ArvoreGenealogica*>& arvores,
    unordered_map<string, Pessoa*>& pessoasGlobal) {
    try {
      ifstream arquivo("data/armazenamento.json");
      if (!arquivo.is_open()) {
        cout << "❌ Banco de dados não encontrado. Criando novo..." << endl;
        return false;
      }

      json j;
      arquivo >> j;
      arquivo.close();

      // Limpar estruturas existentes
      for (auto arvore : arvores) {
        delete arvore;
      }
      arvores.clear();
      pessoasGlobal.clear();

      // Carregar árvores
      if (j.contains("arvores")) {
        for (const auto& arvoreJson : j["arvores"]) {
          ArvoreGenealogica* arvore = jsonParaArvore(arvoreJson);
          if (arvore) {
            arvores.push_back(arvore);

            // Adicionar pessoas ao índice global
            for (const auto& par : arvore->indicePessoas) {
              pessoasGlobal[par.first] = par.second;
            }
          }
        }
        }

      // Carregar pessoas sem árvore
      if (j.contains("pessoasSemArvore")) {
        for (const auto& pessoaJson : j["pessoasSemArvore"]) {
          Pessoa* pessoa = jsonParaPessoa(pessoaJson);
          if (pessoa) {
            pessoasGlobal[pessoa->nome] = pessoa;
          }
        }
      }

      cout << "✅ Banco de dados carregado com sucesso!" << endl;
      cout << "   Árvores: " << arvores.size() << endl;
      cout << "   Pessoas: " << pessoasGlobal.size() << endl;

      return true;
      }
    catch (const exception& e) {
      cerr << "❌ Erro ao carregar banco de dados: " << e.what() << endl;
      return false;
    }
  }

  bool salvarArvore(const ArvoreGenealogica* arvore, const string& nomeArquivo) {
    // Para compatibilidade, mas agora salva no banco unificado
    vector<ArvoreGenealogica*> arvoresTemp;
    if (arvore) {
      // Clonar a árvore (simplificado - em produção seria mais complexo)
      ArvoreGenealogica* novaArvore = criarArvore();
      novaArvore->raizFamilia = arvore->raizFamilia;
      novaArvore->indicePessoas = arvore->indicePessoas;
      arvoresTemp.push_back(novaArvore);
    }

    // Usar o mapa global de pessoas
    unordered_map<string, Pessoa*> pessoasTemp;
    for (const auto& par : arvore->indicePessoas) {
      pessoasTemp[par.first] = par.second;
    }

    return salvarBancoDeDados(arvoresTemp, pessoasTemp);
  }

  ArvoreGenealogica* carregarArvore(const string& nomeArquivo) {
    // Para compatibilidade, carrega a primeira árvore do banco
    vector<ArvoreGenealogica*> arvores;
    unordered_map<string, Pessoa*> pessoasTemp;

    if (carregarBancoDeDados(arvores, pessoasTemp) && !arvores.empty()) {
      return arvores[0];
    }
    return nullptr;
  }

  vector<string> listarArvoresSalvas() {
    vector<string> arvores;
    vector<ArvoreGenealogica*> arvoresTemp;
    unordered_map<string, Pessoa*> pessoasTemp;

    if (carregarBancoDeDados(arvoresTemp, pessoasTemp)) {
      for (size_t i = 0; i < arvoresTemp.size(); i++) {
        arvores.push_back("Arvore_" + to_string(i + 1));
      }
    }

    return arvores;
  }

  json pessoaParaJson(const Pessoa* pessoa) {
    json j;
    j["nome"] = pessoa->nome;
    j["dataNascimento"] = pessoa->dataNascimento;
    j["genero"] = string(1, pessoa->genero);
    return j;
  }

  json arvoreParaJson(const ArvoreGenealogica* arvore) {
    json j;
    j["totalPessoas"] = arvore->indicePessoas.size();

    // Salvar pessoas da árvore
    json pessoasJson = json::array();
    for (const auto& par : arvore->indicePessoas) {
      pessoasJson.push_back(pessoaParaJson(par.second));
    }
    j["pessoas"] = pessoasJson;

    return j;
  }

  Pessoa* jsonParaPessoa(const json& j) {
    try {
      string nome = j["nome"];
      string dataNascimento = j["dataNascimento"];
      char genero = j["genero"].get<string>()[0];
      return criarPessoa(nome, dataNascimento, genero);
    }
    catch (const exception& e) {
      cerr << "❌ Erro ao converter JSON para Pessoa: " << e.what() << endl;
      return nullptr;
    }
  }

  ArvoreGenealogica* jsonParaArvore(const json& j) {
    try {
      ArvoreGenealogica* arvore = criarArvore();

      if (j.contains("pessoas")) {
        for (const auto& pessoaJson : j["pessoas"]) {
          Pessoa* pessoa = jsonParaPessoa(pessoaJson);
          if (pessoa) {
            arvore->indicePessoas[pessoa->nome] = pessoa;
          }
        }
      }

      return arvore;
    }
    catch (const exception& e) {
      cerr << "❌ Erro ao converter JSON para Árvore: " << e.what() << endl;
      return nullptr;
    }
  }

  // TODO: Implementar famílias quando a estrutura estiver madura
  json familiaParaJson(const Familia* familia) {
    json j;
    return j;
  }

  Familia* jsonParaFamilia(const json& j) {
    return nullptr;
  }

}