#include "main.hpp"


int main() {

#ifdef _WIN32
  SetConsoleOutputCP(CP_UTF8);
#endif
#include "main.hpp"

  cout << "=== SISTEMA DE ÁRVORE GENEALÓGICA ===" << endl;

  // Ler dados do CSV
  vector<Pessoa> pessoas = lerCSV("dados/dados.csv");

  if (pessoas.empty()) {
    cout << "Erro: Nenhum dado encontrado ou arquivo vazio." << endl;
    return 1;
  }

  cout << "Pessoas carregadas: " << pessoas.size() << endl;

  // Construir árvore genealógica
  map<int, Pessoa> arvore = construirArvore(pessoas);

  // Encontrar a raiz da árvore
  int raiz_id = -1;
  encontrarRaiz(arvore, raiz_id);

  if (raiz_id == -1) {
    cout << "Erro: Não foi possível encontrar a raiz da árvore." << endl;
    return 1;
  }

  cout << "\nRaiz da árvore: " << arvore.at(raiz_id).nome << " (ID: " << raiz_id << ")" << endl;

  // Validar árvore
  if (!validarArvore(arvore)) {
    cout << "Erro: Árvore genealógica inválida." << endl;
    return 1;
  }

  // Imprimir árvore
  cout << "\n=== ÁRVORE GENEALÓGICA ===" << endl;
  vector<bool> ultimos;
  imprimirArvore(arvore, raiz_id, 0, ultimos);

  return 0;
}

vector<Pessoa> lerCSV(const string& filename) {
  vector<Pessoa> pessoas;
  ifstream arquivo(filename);

  if (!arquivo.is_open()) {
    cout << "Erro ao abrir arquivo: " << filename << endl;
    return pessoas;
  }

  string linha;
  bool cabecalho = true;

  while (getline(arquivo, linha)) {
    if (cabecalho) {
      cabecalho = false;
      continue;
    }

    if (linha.empty()) continue;

    stringstream ss(linha);
    string token;
    Pessoa p;
    vector<string> dados;

    while (getline(ss, token, ',')) {
      dados.push_back(token);
    }

    if (dados.size() >= 6) {
      p.id = stoi(dados[0]);
      p.nome = dados[1];
      p.genero = dados[2][0];
      p.id_pai = stoi(dados[3]);
      p.id_mae = stoi(dados[4]);
      p.id_conjuge = stoi(dados[5]);

      pessoas.push_back(p);
    }
  }

  arquivo.close();
  return pessoas;
}

map<int, Pessoa> construirArvore(vector<Pessoa>& pessoas) {
  map<int, Pessoa> arvore;

  // Primeiro, adiciona todas as pessoas ao mapa
  for (auto& p : pessoas) {
    arvore[p.id] = p;
  }

  // Agora, constrói as relações de filhos
  for (auto& par : arvore) {
    Pessoa& p = par.second;

    // Se tem pai, adiciona esta pessoa como filho do pai
    if (p.id_pai > 0 && arvore.find(p.id_pai) != arvore.end()) {
      arvore[p.id_pai].filhos.push_back(p.id);
    }

    // Se tem mãe, adiciona esta pessoa como filho da mãe
    if (p.id_mae > 0 && arvore.find(p.id_mae) != arvore.end()) {
      arvore[p.id_mae].filhos.push_back(p.id);
    }
  }

  // Remove duplicatas nos vetores de filhos
  for (auto& par : arvore) {
    Pessoa& p = par.second;
    sort(p.filhos.begin(), p.filhos.end());
    p.filhos.erase(unique(p.filhos.begin(), p.filhos.end()), p.filhos.end());
  }

  return arvore;
}

void encontrarRaiz(map<int, Pessoa>& arvore, int& raiz_id) {
  // A raiz é alguém que não tem pais definidos (id_pai = 0 e id_mae = 0)
  // e tem pelo menos um filho
  for (const auto& par : arvore) {
    const Pessoa& p = par.second;
    if (p.id_pai == 0 && p.id_mae == 0 && !p.filhos.empty()) {
      raiz_id = p.id;
      return;
    }
  }

  // Se não encontrou, procura por alguém sem pais
  for (const auto& par : arvore) {
    const Pessoa& p = par.second;
    if (p.id_pai == 0 && p.id_mae == 0) {
      raiz_id = p.id;
      return;
    }
  }
}

void imprimirArvore(const map<int, Pessoa>& arvore, int pessoa_id, int nivel, vector<bool>& ultimos) {
  if (arvore.find(pessoa_id) == arvore.end()) return;

  const Pessoa& p = arvore.at(pessoa_id);

  // Imprime a estrutura visual
  for (int i = 0; i < nivel; i++) {
    if (i == nivel - 1) {
      // Último nível: usa os caracteres de árvore
      cout << (ultimos[i] ? "   └── " : "   ├── ");
    }
    else {
      // Níveis anteriores: usa espaçamento ou linha vertical
      cout << (ultimos[i] ? "    " : "   │");
    }
  }

  // Imprime a pessoa
  cout << p.nome << " (" << p.genero << ") [ID: " << p.id << "]";

  // Se tem conjuge, imprime também
  if (p.id_conjuge > 0 && arvore.find(p.id_conjuge) != arvore.end()) {
    const Pessoa& conjuge = arvore.at(p.id_conjuge);
    cout << " 💑 " << conjuge.nome << " (" << conjuge.genero << ")";
  }
  cout << endl;

  // Imprime os filhos
  if (!p.filhos.empty()) {
    ultimos.push_back(false);

    for (size_t i = 0; i < p.filhos.size(); i++) {
      if (i == p.filhos.size() - 1) {
        ultimos[nivel] = true;
      }
      imprimirArvore(arvore, p.filhos[i], nivel + 1, ultimos);
    }

    ultimos.pop_back();
  }
}

bool validarArvore(const map<int, Pessoa>& arvore) {
  // Verifica se não há pessoas que são pais de si mesmas
  for (const auto& par : arvore) {
    const Pessoa& p = par.second;

    // Uma pessoa não pode ser pai/mãe de si mesma
    if (p.id_pai == p.id || p.id_mae == p.id) {
      cout << "Erro: Pessoa " << p.nome << " é pai/mãe de si mesma!" << endl;
      return false;
    }

    // Verifica relações de casamento
    if (p.id_conjuge > 0) {
      if (arvore.find(p.id_conjuge) == arvore.end()) {
        cout << "Erro: Conjuge ID " << p.id_conjuge << " não encontrado para " << p.nome << endl;
        return false;
      }

      const Pessoa& conjuge = arvore.at(p.id_conjuge);

      // Verifica se o casamento é mútuo
      if (conjuge.id_conjuge != p.id) {
        cout << "Erro: Casamento não mútuo entre " << p.nome << " e " << conjuge.nome << endl;
        return false;
      }
    }
  }

  cout << "Árvore validada com sucesso!" << endl;
  return true;
}