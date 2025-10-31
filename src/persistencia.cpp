#include "pch/pch.hpp"

using namespace std;
using namespace arvore;

namespace persistencia {

  bool salvarBancoDeDados(const vector<ArvoreGenealogica*>& arvores,
    const unordered_map<string, Pessoa*>& pessoasGlobal) {
    cout << "❌ Funcionalidade de salvamento removida" << endl;
    return false;
  }

  bool carregarBancoDeDados(vector<ArvoreGenealogica*>& arvores,
    unordered_map<string, Pessoa*>& pessoasGlobal) {
    cout << "❌ Funcionalidade de carregamento removida" << endl;
    return false;
  }

  vector<string> listarArvoresSalvas() {
    return vector<string>(); // Retorna vetor vazio
  }
}