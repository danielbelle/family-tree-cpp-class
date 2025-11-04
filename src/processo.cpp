#include "processo.hpp"

// Implementação das funções de processo

string gerarIDPessoa() {
  static int counter = 0;
  return "P_" + to_string(++counter);
}

string gerarIDArvore() {
  static int counter = 0;
  return "A_" + to_string(++counter);
}

Pessoa* criarPessoa(const string& nome, const string& dataNasc, char genero) {
  Pessoa* novaPessoa = new Pessoa();
  novaPessoa->id = gerarIDPessoa();
  novaPessoa->nome = nome;
  novaPessoa->dataNascimento = dataNasc;
  novaPessoa->genero = genero;

  pessoas.push_back(novaPessoa);
  return novaPessoa;
}

Pessoa* buscarPessoa(const string& id) {
  for (auto pessoa : pessoas) {
    if (pessoa->id == id) {
      return pessoa;
    }
  }
  return nullptr;
}

vector<Pessoa*> buscarPessoasPorNome(const string& nome) {
  vector<Pessoa*> resultado;
  for (auto pessoa : pessoas) {
    if (pessoa->nome.find(nome) != string::npos) {
      resultado.push_back(pessoa);
    }
  }
  return resultado;
}

bool definirRelacaoPaiFilho(Pessoa* pai, Pessoa* mae, Pessoa* filho) {
  if (filho == nullptr) {
    return false;
  }

  // Validar gêneros
  if (pai && pai->genero != 'M') {
    cout << "⚠️  AVISO: " << pai->nome << " é do gênero feminino, mas está como pai." << endl;
  }
  if (mae && mae->genero != 'F') {
    cout << "⚠️  AVISO: " << mae->nome << " é do gênero masculino, mas está como mãe." << endl;
  }

  // Definir pais do filho
  filho->pai = pai;
  filho->mae = mae;

  // Adicionar filho aos pais
  if (pai) {
    pai->filhos.push_back(filho);
  }
  if (mae) {
    mae->filhos.push_back(filho);
  }

  return true;
}

ArvoreGenealogica* criarArvoreGenealogica(const string& nome) {
  ArvoreGenealogica* novaArvore = new ArvoreGenealogica();
  novaArvore->id = gerarIDArvore();
  novaArvore->nome = nome;

  arvores.push_back(novaArvore);
  return novaArvore;
}

ArvoreGenealogica* buscarArvoreGenealogica(const string& id) {
  for (auto arvore : arvores) {
    if (arvore->id == id) {
      return arvore;
    }
  }
  return nullptr;
}

bool adicionarPessoaArvore(ArvoreGenealogica* arvore, Pessoa* pessoa) {
  if (arvore == nullptr || pessoa == nullptr) {
    return false;
  }

  // Verificar se já está na árvore
  for (auto p : arvore->pessoas) {
    if (p->id == pessoa->id) {
      return true; // Já está na árvore
    }
  }

  arvore->pessoas.push_back(pessoa);

  // Se é a primeira pessoa ou não tem ancestral principal, definir como ancestral principal
  if (arvore->ancestralPrincipal == nullptr) {
    arvore->ancestralPrincipal = pessoa;
  }

  return true;
}

vector<Pessoa*> buscarAscendentes(Pessoa* pessoa) {
  vector<Pessoa*> ascendentes;
  if (pessoa == nullptr) return ascendentes;

  // Buscar recursivamente pais, avós, etc.
  queue<Pessoa*> fila;
  if (pessoa->pai) fila.push(pessoa->pai);
  if (pessoa->mae) fila.push(pessoa->mae);

  while (!fila.empty()) {
    Pessoa* atual = fila.front();
    fila.pop();

    ascendentes.push_back(atual);

    // Adicionar pais do atual à fila
    if (atual->pai) fila.push(atual->pai);
    if (atual->mae) fila.push(atual->mae);
  }

  return ascendentes;
}

vector<Pessoa*> buscarDescendentes(Pessoa* pessoa) {
  vector<Pessoa*> descendentes;
  if (pessoa == nullptr) return descendentes;

  // Buscar recursivamente filhos, netos, etc.
  queue<Pessoa*> fila;
  for (auto filho : pessoa->filhos) {
    fila.push(filho);
  }

  while (!fila.empty()) {
    Pessoa* atual = fila.front();
    fila.pop();

    descendentes.push_back(atual);

    // Adicionar filhos do atual à fila
    for (auto filho : atual->filhos) {
      fila.push(filho);
    }
  }

  return descendentes;
}

void listarArvoreCompleta(Pessoa* pessoa) {
  if (pessoa == nullptr) return;
  mostrarArvoreHierarquica(pessoa);
}

void mostrarArvoreHierarquica(Pessoa* pessoa, int nivel, vector<bool> ultimos) {
  if (pessoa == nullptr) return;

  // Imprimir indentação
  for (int i = 0; i < nivel; i++) {
    if (i == nivel - 1) {
      cout << (ultimos[i] ? "└── " : "├── ");
    }
    else {
      cout << (ultimos[i] ? "    " : "│   ");
    }
  }

  // Imprimir informações da pessoa
  cout << pessoa->nome << " (" << pessoa->id << ")";
  if (!pessoa->dataNascimento.empty()) {
    cout << " - 📅 Nasc: " << pessoa->dataNascimento;
  }
  cout << " - ⚧️ " << (pessoa->genero == 'M' ? "Masculino" : "Feminino");
  cout << endl;

  // Processar filhos
  size_t numFilhos = pessoa->filhos.size();
  for (size_t i = 0; i < numFilhos; i++) {
    vector<bool> novosUltimos = ultimos;
    novosUltimos.push_back(i == numFilhos - 1);
    mostrarArvoreHierarquica(pessoa->filhos[i], nivel + 1, novosUltimos);
  }
}

void limparMemoria() {
  for (auto p : pessoas) {
    delete p;
  }
  for (auto a : arvores) {
    delete a;
  }
  pessoas.clear();
  arvores.clear();
}

// NOVAS FUNCIONALIDADES

int calcularParentesco(Pessoa* p1, Pessoa* p2) {
  if (p1 == nullptr || p2 == nullptr) return -1;
  if (p1 == p2) return 0; // Mesma pessoa

  // Buscar ancestral comum mais próximo usando BFS em ambas as direções
  map<Pessoa*, int> distanciaDeP1;
  queue<pair<Pessoa*, int>> fila;

  // Marcar todos os ascendentes de p1 com sua distância
  fila.push({ p1, 0 });
  while (!fila.empty()) {
    auto [atual, dist] = fila.front();
    fila.pop();

    if (distanciaDeP1.find(atual) != distanciaDeP1.end()) continue;
    distanciaDeP1[atual] = dist;

    if (atual->pai) fila.push({ atual->pai, dist + 1 });
    if (atual->mae) fila.push({ atual->mae, dist + 1 });
  }

  // Buscar em p2 e seus ascendentes
  set<Pessoa*> visitados;
  fila.push({ p2, 0 });
  int menorDistancia = -1;

  while (!fila.empty()) {
    auto [atual, dist] = fila.front();
    fila.pop();

    if (visitados.find(atual) != visitados.end()) continue;
    visitados.insert(atual);

    // Se encontrou um ancestral comum
    if (distanciaDeP1.find(atual) != distanciaDeP1.end()) {
      int distanciaTotal = distanciaDeP1[atual] + dist;
      if (menorDistancia == -1 || distanciaTotal < menorDistancia) {
        menorDistancia = distanciaTotal;
      }
    }

    // Continuar busca pelos pais
    if (atual->pai) fila.push({ atual->pai, dist + 1 });
    if (atual->mae) fila.push({ atual->mae, dist + 1 });
  }

  return menorDistancia;
}

int contarDescendentes(Pessoa* pessoa) {
  if (pessoa == nullptr) return 0;

  int count = 0;
  queue<Pessoa*> fila;
  for (auto filho : pessoa->filhos) {
    fila.push(filho);
    count++;
  }

  while (!fila.empty()) {
    Pessoa* atual = fila.front();
    fila.pop();

    for (auto filho : atual->filhos) {
      fila.push(filho);
      count++;
    }
  }

  return count;
}

void mostrarGeracoes(Pessoa* ancestral) {
  if (ancestral == nullptr) return;

  queue<pair<Pessoa*, int>> fila;
  fila.push({ ancestral, 0 });

  int nivelAtual = -1;

  while (!fila.empty()) {
    auto [atual, nivel] = fila.front();
    fila.pop();

    if (nivel != nivelAtual) {
      nivelAtual = nivel;
      cout << "\n📅 Geração " << nivel + 1 << ":" << endl;
    }

    cout << "   👤 " << atual->nome << " (" << atual->id << ")";
    if (!atual->dataNascimento.empty()) {
      cout << " - 📅 " << atual->dataNascimento;
    }
    cout << endl;

    // Adicionar filhos à fila
    for (auto filho : atual->filhos) {
      fila.push({ filho, nivel + 1 });
    }
  }
}

bool gravarArvoreCSV(ArvoreGenealogica* arvore) {
  if (!arvore) {
    cout << "❌ Árvore inválida para gravação!" << endl;
    return false;
  }

  string pasta_dados = "../dados/";
  string caminho_completo = pasta_dados + "dados.csv";

#ifdef _WIN32
  system(("mkdir \"" + pasta_dados + "\" 2>nul").c_str());
#else
  system(("mkdir -p \"" + pasta_dados + "\" 2>/dev/null").c_str());
#endif

  ofstream file(caminho_completo);
  if (!file.is_open()) {
    cout << "❌ Erro: Não foi possível criar o arquivo: " << caminho_completo << endl;
    cout << "💡 Verifique as permissões do diretório." << endl;
    return false;
  }

  // Cabeçalho
  file << "ID,Nome,DataNascimento,Genero,Pai,Mae" << endl;

  // Dados
  int pessoasSalvas = 0;
  for (auto pessoa : arvore->pessoas) {
    file << pessoa->id << ","
      << pessoa->nome << ","
      << pessoa->dataNascimento << ","
      << pessoa->genero << ","
      << (pessoa->pai ? pessoa->pai->id : "") << ","
      << (pessoa->mae ? pessoa->mae->id : "") << endl;
    pessoasSalvas++;
  }

  file.close();

  if (pessoasSalvas > 0) {
    cout << "✅ " << pessoasSalvas << " pessoas salvas em: " << caminho_completo << endl;
    return true;
  }
  else {
    cout << "⚠️  Nenhuma pessoa foi salva!" << endl;
    return false;
  }
}

// Gravação complementar
bool gravarArvoreCSVComplementar(ArvoreGenealogica* arvore) {
  if (!arvore) return false;

  string pasta_dados = "../dados/";
  string caminho_completo = pasta_dados + "dados.csv";

  // Criar pasta se não existir
#ifdef _WIN32
  system(("mkdir \"" + pasta_dados + "\" 2>nul").c_str());
#else
  system(("mkdir -p \"" + pasta_dados + "\" 2>/dev/null").c_str());
#endif

  // Verificar se arquivo já existe
  map<string, bool> pessoasExistentes;
  ifstream arquivoExistente(caminho_completo);

  if (arquivoExistente.is_open()) {
    string linha;
    getline(arquivoExistente, linha); // Pular cabeçalho

    while (getline(arquivoExistente, linha)) {
      if (!linha.empty()) {
        stringstream ss(linha);
        string id;
        getline(ss, id, ',');
        pessoasExistentes[id] = true;
        cout << "📋 Pessoa existente encontrada: " << id << endl;
      }
    }
    arquivoExistente.close();
  }

  // Abrir arquivo
  ofstream file;
  if (pessoasExistentes.empty()) {
    // Arquivo não existe ou está vazio - criar novo
    file.open(caminho_completo);
    if (!file.is_open()) {
      cout << "❌ Erro ao criar arquivo: " << caminho_completo << endl;
      return false;
    }
    file << "ID,Nome,DataNascimento,Genero,Pai,Mae" << endl;
    cout << "📄 Criando novo arquivo CSV..." << endl;
  }
  else {
    // Arquivo existe - abrir em modo append
    file.open(caminho_completo, ios::app);
    if (!file.is_open()) {
      cout << "❌ Erro ao abrir arquivo para complementação!" << endl;
      return false;
    }
    cout << "📄 Complementando arquivo existente..." << endl;
  }

  // Adicionar pessoas
  int novasPessoas = 0;
  for (auto pessoa : arvore->pessoas) {
    if (!pessoasExistentes[pessoa->id]) {
      file << pessoa->id << ","
        << pessoa->nome << ","
        << pessoa->dataNascimento << ","
        << pessoa->genero << ","
        << (pessoa->pai ? pessoa->pai->id : "") << ","
        << (pessoa->mae ? pessoa->mae->id : "") << endl;
      novasPessoas++;
      cout << "➕ Adicionada: " << pessoa->nome << " (" << pessoa->id << ")" << endl;
    }
    else {
      cout << "⏭️  Já existe: " << pessoa->nome << " (" << pessoa->id << ")" << endl;
    }
  }

  file.close();

  if (novasPessoas > 0) {
    cout << "✅ " << novasPessoas << " novas pessoas adicionadas ao arquivo!" << endl;
    cout << "💾 Arquivo salvo em: " << caminho_completo << endl;
    return true;
  }
  else {
    cout << "ℹ️  Nenhuma nova pessoa para adicionar." << endl;
    return true;
  }
}

bool carregarArvoreCSV() {
  // Usar caminho fixo: root/dados/dados.csv
  string pasta_dados = "../dados/";
  string caminho_completo = pasta_dados + "dados.csv"; // SEMPRE o mesmo arquivo

  ifstream file(caminho_completo);
  if (!file.is_open()) {
    cout << "❌ Erro: Arquivo não encontrado: " << caminho_completo << endl;
    cout << "💡 Dica: Crie o arquivo 'dados.csv' na pasta 'dados' ou use a opção de gravar para criá-lo automaticamente." << endl;
    return false;
  }

  string linha;
  getline(file, linha); // Pular cabeçalho

  map<string, Pessoa*> pessoasMap;
  vector<tuple<string, string, string>> relacoes; // (pessoa_id, pai_id, mae_id)

  while (getline(file, linha)) {
    stringstream ss(linha);
    string id, nome, dataNasc, genero, pai_id, mae_id;

    getline(ss, id, ',');
    getline(ss, nome, ',');
    getline(ss, dataNasc, ',');
    getline(ss, genero, ',');
    getline(ss, pai_id, ',');
    getline(ss, mae_id, ',');

    // Verificar se a pessoa já existe (evitar duplicação)
    Pessoa* pessoa = nullptr;
    for (auto p : pessoas) {
      if (p->id == id) {
        pessoa = p;
        break;
      }
    }

    // Se não existe, criar nova
    if (!pessoa) {
      pessoa = new Pessoa();
      pessoa->id = id;
      pessoa->nome = nome;
      pessoa->dataNascimento = dataNasc;
      pessoa->genero = genero[0];
      pessoas.push_back(pessoa);
    }

    pessoasMap[id] = pessoa;
    relacoes.push_back({ id, pai_id, mae_id });
  }

  file.close();

  // Estabelecer relações
  for (auto& [pessoa_id, pai_id, mae_id] : relacoes) {
    Pessoa* pessoa = pessoasMap[pessoa_id];
    Pessoa* pai = pai_id.empty() ? nullptr : pessoasMap[pai_id];
    Pessoa* mae = mae_id.empty() ? nullptr : pessoasMap[mae_id];

    if (pessoa && (pai || mae)) {
      definirRelacaoPaiFilho(pai, mae, pessoa);
    }
  }

  // Criar árvore apenas se carregou pessoas
  if (!pessoasMap.empty()) {
    // Verificar se já existe uma árvore com dados carregados
    ArvoreGenealogica* novaArvore = nullptr;
    for (auto arvore : arvores) {
      if (arvore->nome.find("Árvore Principal") != string::npos) {
        novaArvore = arvore;
        break;
      }
    }

    if (!novaArvore) {
      novaArvore = criarArvoreGenealogica("Árvore Principal");
    }

    // Limpar pessoas existentes na árvore e adicionar as novas
    novaArvore->pessoas.clear();
    for (auto& [id, pessoa] : pessoasMap) {
      adicionarPessoaArvore(novaArvore, pessoa);
    }

    cout << "📂 Dados carregados de: " << caminho_completo << endl;
    cout << "✅ " << pessoasMap.size() << " pessoas carregadas" << endl;
  }
  else {
    cout << "⚠️  Nenhuma pessoa foi carregada do arquivo!" << endl;
    return false;
  }

  return true;
  }