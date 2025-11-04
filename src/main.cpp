#include "main.hpp"
#include <limits>

void configurarUTF8() {
#ifdef _WIN32
  // Configurar console Windows para UTF-8
  SetConsoleOutputCP(CP_UTF8);
  SetConsoleCP(CP_UTF8);

  // Buffer para evitar problemas com acentos
  setvbuf(stdout, nullptr, _IOFBF, 1000);
#else
  // Linux/macOS já suportam UTF-8 nativamente
  setlocale(LC_ALL, "en_US.UTF-8");
#endif
}

// Função para ler string com suporte a UTF-8
string lerStringUTF8() {
  string texto;

  // Limpar buffer do cin
  cin.ignore(numeric_limits<streamsize>::max(), '\n');

  // Ler linha com suporte a caracteres especiais
  getline(cin, texto);

  return texto;
}

int main() {
  // Configurar UTF-8 no console
  configurarUTF8();

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

  // Menu interativo para adicionar pessoas e relações
  cout << "\n=== MODO INTERATIVO ===" << endl;
  menuInterativo(arvore);

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
    removerDuplicatas(p.filhos);
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
    cout << " 💑 " << conjuge.nome << " (" << conjuge.genero << ") [ID: " << conjuge.id << "]";
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

int obterProximoId(const map<int, Pessoa>& arvore) {
  if (arvore.empty()) {
    return 1; // Primeiro ID se a árvore estiver vazia
  }

  // Encontrar o maior ID atual
  int maior_id = 0;
  for (const auto& par : arvore) {
    if (par.first > maior_id) {
      maior_id = par.first;
    }
  }

  return maior_id + 1; // Próximo ID disponível
}

void removerDuplicatas(vector<int>& vetor) {
  sort(vetor.begin(), vetor.end());
  vetor.erase(unique(vetor.begin(), vetor.end()), vetor.end());
}

bool validarGenero(char genero) {
  return genero == 'M' || genero == 'F';
}

char solicitarGeneroValido() {
  char genero;
  do {
    cout << "Gênero (M/F): ";
    cin >> genero;
    genero = toupper(genero);
    if (!validarGenero(genero)) {
      cout << "Gênero inválido! Digite M ou F: ";
    }
  } while (!validarGenero(genero));
  return genero;
}

Pessoa criarNovaPessoa(const map<int, Pessoa>& arvore, const string& nome, char genero, int id_conjuge) {
  Pessoa nova;
  nova.id = obterProximoId(arvore);
  nova.nome = nome;
  nova.genero = genero;
  nova.id_pai = 0;
  nova.id_mae = 0;
  nova.id_conjuge = id_conjuge;
  return nova;
}

void adicionarPessoa(map<int, Pessoa>& arvore, const Pessoa& nova_pessoa) {
  // Criar uma cópia da pessoa com ID gerado automaticamente
  Pessoa pessoa_com_id = nova_pessoa;
  pessoa_com_id.id = obterProximoId(arvore);

  // Adicionar nova pessoa
  arvore[pessoa_com_id.id] = pessoa_com_id;

  // Atualizar relações com pais se especificados
  if (pessoa_com_id.id_pai > 0 && arvore.find(pessoa_com_id.id_pai) != arvore.end()) {
    arvore[pessoa_com_id.id_pai].filhos.push_back(pessoa_com_id.id);
    removerDuplicatas(arvore[pessoa_com_id.id_pai].filhos);
  }

  if (pessoa_com_id.id_mae > 0 && arvore.find(pessoa_com_id.id_mae) != arvore.end()) {
    arvore[pessoa_com_id.id_mae].filhos.push_back(pessoa_com_id.id);
    removerDuplicatas(arvore[pessoa_com_id.id_mae].filhos);
  }

  cout << "Pessoa " << pessoa_com_id.nome << " adicionada com sucesso! (ID: " << pessoa_com_id.id << ")" << endl;
}

void definirParenteComoPai(map<int, Pessoa>& arvore, Pessoa& filho, int id_parente) {
  filho.id_pai = id_parente;
  arvore[id_parente].filhos.push_back(filho.id);
  removerDuplicatas(arvore[id_parente].filhos);
}

void definirParenteComoMae(map<int, Pessoa>& arvore, Pessoa& filho, int id_parente) {
  filho.id_mae = id_parente;
  arvore[id_parente].filhos.push_back(filho.id);
  removerDuplicatas(arvore[id_parente].filhos);
}

void criarConjugeAutomatico(map<int, Pessoa>& arvore, Pessoa& parente, Pessoa& filho, char genero_conjuge) {
  cout << "Criando nova pessoa como " << (genero_conjuge == 'M' ? "pai" : "mãe") << " de " << filho.nome << endl;
  cout << "Nome: ";

  string nome_conjuge = lerStringUTF8();

  Pessoa novo_conjuge = criarNovaPessoa(arvore, nome_conjuge, genero_conjuge, parente.id);
  arvore[novo_conjuge.id] = novo_conjuge;

  parente.id_conjuge = novo_conjuge.id;

  if (genero_conjuge == 'M') {
    filho.id_pai = novo_conjuge.id;
  }
  else {
    filho.id_mae = novo_conjuge.id;
  }

  novo_conjuge.filhos.push_back(filho.id);

  cout << novo_conjuge.nome << " criado(a) como " << (genero_conjuge == 'M' ? "pai" : "mãe")
    << " de " << filho.nome << " e cônjuge de " << parente.nome
    << " (ID: " << novo_conjuge.id << ")" << endl;
}

void processarDefinicaoMae(map<int, Pessoa>& arvore, Pessoa& pai, Pessoa& filho) {
  if (pai.id_conjuge > 0) {
    filho.id_mae = pai.id_conjuge;
    arvore[pai.id_conjuge].filhos.push_back(filho.id);
    removerDuplicatas(arvore[pai.id_conjuge].filhos);
    cout << arvore[pai.id_conjuge].nome << " definida automaticamente como mãe (cônjuge do pai)" << endl;
  }
  else {
    char resposta;
    cout << pai.nome << " não tem cônjuge. Deseja definir uma mãe para " << filho.nome << "? (s/n): ";
    cin >> resposta;
    if (resposta == 's' || resposta == 'S') {
      criarConjugeAutomatico(arvore, pai, filho, 'F');
    }
  }
}

void processarDefinicaoPai(map<int, Pessoa>& arvore, Pessoa& mae, Pessoa& filho) {
  if (mae.id_conjuge > 0) {
    filho.id_pai = mae.id_conjuge;
    arvore[mae.id_conjuge].filhos.push_back(filho.id);
    removerDuplicatas(arvore[mae.id_conjuge].filhos);
    cout << arvore[mae.id_conjuge].nome << " definido automaticamente como pai (cônjuge da mãe)" << endl;
  }
  else {
    char resposta;
    cout << mae.nome << " não tem cônjuge. Deseja definir um pai para " << filho.nome << "? (s/n): ";
    cin >> resposta;
    if (resposta == 's' || resposta == 'S') {
      criarConjugeAutomatico(arvore, mae, filho, 'M');
    }
  }
}

void definirPais(map<int, Pessoa>& arvore, int id_filho) {
  if (arvore.find(id_filho) == arvore.end()) {
    cout << "Erro: Pessoa com ID " << id_filho << " não encontrada!" << endl;
    return;
  }

  Pessoa& filho = arvore[id_filho];
  cout << "\nDefinindo pais para: " << filho.nome << " (ID: " << id_filho << ")" << endl;

  if (filho.id_pai > 0 && filho.id_mae > 0) {
    cout << "Esta pessoa já tem ambos os pais definidos!" << endl;
    cout << "Pai: " << arvore[filho.id_pai].nome << " (ID: " << filho.id_pai << ")" << endl;
    cout << "Mãe: " << arvore[filho.id_mae].nome << " (ID: " << filho.id_mae << ")" << endl;
    return;
  }

  int id_parente;
  cout << "Digite o ID do pai ou mãe existente: ";
  cin >> id_parente;

  if (arvore.find(id_parente) == arvore.end()) {
    cout << "Erro: Pessoa com ID " << id_parente << " não encontrada!" << endl;
    return;
  }

  Pessoa& parente = arvore[id_parente];
  cout << "Parente selecionado: " << parente.nome << " (" << parente.genero << ") [ID: " << id_parente << "]";

  if (parente.id_conjuge > 0) {
    Pessoa& conjuge = arvore[parente.id_conjuge];
    cout << " 💑 " << conjuge.nome << " (" << conjuge.genero << ")" << endl;
  }
  else {
    cout << " (sem cônjuge)" << endl;
  }

  // Lógica unificada para ambos os gêneros
  if (parente.genero == 'M') {
    definirParenteComoPai(arvore, filho, id_parente);
    cout << parente.nome << " definido como pai de " << filho.nome << endl;

    if (filho.id_mae == 0) {
      processarDefinicaoMae(arvore, parente, filho);
    }
  }
  else if (parente.genero == 'F') {
    definirParenteComoMae(arvore, filho, id_parente);
    cout << parente.nome << " definida como mãe de " << filho.nome << endl;

    if (filho.id_pai == 0) {
      processarDefinicaoPai(arvore, parente, filho);
    }
  }

  cout << "Relações de parentesco definidas com sucesso!" << endl;
}

void salvarCSV(const map<int, Pessoa>& arvore, const string& filename) {
  ofstream arquivo(filename);

  if (!arquivo.is_open()) {
    cout << "Erro ao abrir arquivo para salvar: " << filename << endl;
    return;
  }

  // Escrever cabeçalho
  arquivo << "id,nome,genero,id_pai,id_mae,id_conjuge" << endl;

  // Escrever dados
  for (const auto& par : arvore) {
    const Pessoa& p = par.second;
    arquivo << p.id << "," << p.nome << "," << p.genero << ","
      << p.id_pai << "," << p.id_mae << "," << p.id_conjuge << endl;
  }

  arquivo.close();
  cout << "Dados salvos em " << filename << " com sucesso!" << endl;
}

void adicionarPessoaInterativo(map<int, Pessoa>& arvore) {
  Pessoa nova;
  nova.id = 0;

  cout << "Nome: ";
  nova.nome = lerStringUTF8();

  nova.genero = solicitarGeneroValido();
  nova.id_pai = 0;
  nova.id_mae = 0;
  nova.id_conjuge = 0;

  adicionarPessoa(arvore, nova);
}

// Função para buscar pessoa por nome (retorna ID ou -1 se não encontrou)
int buscarPessoaPorNome(const map<int, Pessoa>& arvore, const string& nome) {
  // Converter nome para minúsculas para busca case-insensitive
  string nomeLower = nome;
  transform(nomeLower.begin(), nomeLower.end(), nomeLower.begin(), ::tolower);

  for (const auto& par : arvore) {
    const Pessoa& p = par.second;

    // Converter nome da pessoa para minúsculas
    string pessoaNomeLower = p.nome;
    transform(pessoaNomeLower.begin(), pessoaNomeLower.end(), pessoaNomeLower.begin(), ::tolower);

    if (pessoaNomeLower == nomeLower) {
      return p.id;
    }
  }
  return -1; // Não encontrado
}

// Função para exibir a linha de ascendência (da raiz até a pessoa)
void exibirLinhaAscendencia(const map<int, Pessoa>& arvore, int pessoa_id) {
  if (arvore.find(pessoa_id) == arvore.end()) return;

  const Pessoa& p = arvore.at(pessoa_id);

  // Primeiro exibe os ascendentes recursivamente
  if (p.id_pai > 0) {
    exibirLinhaAscendencia(arvore, p.id_pai);
  }
  else if (p.id_mae > 0) {
    exibirLinhaAscendencia(arvore, p.id_mae);
  }

  // Depois exibe a pessoa atual
  if (p.id_pai > 0 || p.id_mae > 0) {
    cout << " -> ";
  }

  cout << p.nome << " (" << p.genero << ")";
}

// Função para exibir a linha de descendência (da pessoa até os últimos descendentes)
void exibirLinhaDescendencia(const map<int, Pessoa>& arvore, int pessoa_id, int nivel, vector<bool>& ultimos) {
  if (arvore.find(pessoa_id) == arvore.end()) return;

  const Pessoa& p = arvore.at(pessoa_id);

  // Imprime a estrutura visual
  for (int i = 0; i < nivel; i++) {
    if (i == nivel - 1) {
      cout << (ultimos[i] ? "   └── " : "   ├── ");
    }
    else {
      cout << (ultimos[i] ? "    " : "   │");
    }
  }

  // Imprime a pessoa
  cout << p.nome << " (" << p.genero << ") [ID: " << p.id << "]";

  // Se tem conjuge, imprime também
  if (p.id_conjuge > 0 && arvore.find(p.id_conjuge) != arvore.end()) {
    const Pessoa& conjuge = arvore.at(p.id_conjuge);
    cout << " 💑 " << conjuge.nome;
  }
  cout << endl;

  // Imprime os filhos recursivamente
  if (!p.filhos.empty()) {
    ultimos.push_back(false);

    for (size_t i = 0; i < p.filhos.size(); i++) {
      if (i == p.filhos.size() - 1) {
        ultimos[nivel] = true;
      }
      exibirLinhaDescendencia(arvore, p.filhos[i], nivel + 1, ultimos);
    }

    ultimos.pop_back();
  }
}

// Função auxiliar para buscar pessoa de forma interativa
int buscarPessoaInterativo(const map<int, Pessoa>& arvore) {
  int opcao_busca;
  cout << "\n=== BUSCAR PESSOA ===" << endl;
  cout << "1. Buscar por ID" << endl;
  cout << "2. Buscar por nome" << endl;
  cout << "Escolha: ";
  cin >> opcao_busca;

  int pessoa_id = -1;

  if (opcao_busca == 1) {
    cout << "Digite o ID: ";
    cin >> pessoa_id;

    if (arvore.find(pessoa_id) == arvore.end()) {
      cout << "Erro: Pessoa com ID " << pessoa_id << " não encontrada!" << endl;
      return -1;
    }
  }
  else if (opcao_busca == 2) {
    string nome;
    cout << "Digite o nome: ";
    nome = lerStringUTF8();

    pessoa_id = buscarPessoaPorNome(arvore, nome);

    if (pessoa_id == -1) {
      cout << "Erro: Pessoa com nome '" << nome << "' não encontrada!" << endl;
      return -1;
    }
  }
  else {
    cout << "Opção inválida!" << endl;
    return -1;
  }

  return pessoa_id;
}

// Função específica para listar árvore completa a partir de um ancestral
void listarArvoreDesdeAncestral(map<int, Pessoa>& arvore) {
  int pessoa_id = buscarPessoaInterativo(arvore);
  if (pessoa_id == -1) return;

  const Pessoa& ancestral = arvore.at(pessoa_id);

  cout << "\n=== ÁRVORE COMPLETA DESDE " << ancestral.nome << " ===" << endl;
  cout << "Ancestral: " << ancestral.nome << " (" << ancestral.genero << ") [ID: " << ancestral.id << "]" << endl;

  if (ancestral.id_conjuge > 0 && arvore.find(ancestral.id_conjuge) != arvore.end()) {
    const Pessoa& conjuge = arvore.at(ancestral.id_conjuge);
    cout << "Cônjuge: " << conjuge.nome << " (" << conjuge.genero << ") [ID: " << conjuge.id << "]" << endl;
  }

  cout << "=====================================" << endl;

  vector<bool> ultimos;
  exibirLinhaDescendencia(arvore, pessoa_id, 0, ultimos);

  // Estatísticas adicionais
  int total_descendentes = 0;
  function<void(int)> contarDescendentes = [&](int id) {
    const Pessoa& p = arvore.at(id);
    total_descendentes++;
    for (int filho_id : p.filhos) {
      contarDescendentes(filho_id);
    }
    };
  contarDescendentes(pessoa_id);

  cout << "\n--- ESTATÍSTICAS DA ÁRVORE ---" << endl;
  cout << "Ancestral principal: " << ancestral.nome << endl;
  cout << "Total de descendentes: " << (total_descendentes - 1) << endl; // -1 para excluir o próprio ancestral
  cout << "Filhos diretos: " << ancestral.filhos.size() << endl;
}

// Função principal que exibe ascendentes e descendentes (OTIMIZADA)
void exibirAscendentesEDescendentes(map<int, Pessoa>& arvore) {
  int pessoa_id = buscarPessoaInterativo(arvore);
  if (pessoa_id == -1) return;

  const Pessoa& pessoa = arvore.at(pessoa_id);

  cout << "\n=== LINHAGEM COMPLETA DE " << pessoa.nome << " ===" << endl;

  // Exibir ascendentes
  cout << "\n--- ASCENDENTES (da raiz até " << pessoa.nome << ") ---" << endl;

  // Encontrar a raiz da árvore
  int raiz_id;
  encontrarRaiz(arvore, raiz_id);

  if (raiz_id != -1) {
    cout << "Raiz: ";
    exibirLinhaAscendencia(arvore, pessoa_id);
    cout << endl;
  }
  else {
    cout << "Não foi possível encontrar a raiz da árvore." << endl;
  }

  // Exibir descendentes (REUTILIZANDO a função listarArvoreDesdeAncestral)
  cout << "\n--- DESCENDENTES (de " << pessoa.nome << " até os últimos) ---" << endl;

  // Reutiliza a lógica de exibição de descendentes
  vector<bool> ultimos;
  exibirLinhaDescendencia(arvore, pessoa_id, 0, ultimos);

  // Estatísticas
  cout << "\n--- ESTATÍSTICAS ---" << endl;
  cout << "Pessoa: " << pessoa.nome << " (" << pessoa.genero << ") [ID: " << pessoa.id << "]" << endl;
  cout << "Número de descendentes diretos: " << pessoa.filhos.size() << endl;
}

// Função para calcular o nível de parentesco entre duas pessoas (distância em nós)
int calcularParentesco(const map<int, Pessoa>& arvore, int pessoa1_id, int pessoa2_id) {
  if (arvore.find(pessoa1_id) == arvore.end() || arvore.find(pessoa2_id) == arvore.end()) {
    return -1; // Pessoa não encontrada
  }

  if (pessoa1_id == pessoa2_id) {
    return 0; // Mesma pessoa
  }

  // Usar BFS para encontrar o caminho mais curto
  queue<pair<int, int>> fila; // (pessoa_id, distancia)
  set<int> visitados;

  fila.push({ pessoa1_id, 0 });
  visitados.insert(pessoa1_id);

  while (!fila.empty()) {
    auto [atual, distancia] = fila.front();
    fila.pop();

    const Pessoa& p = arvore.at(atual);

    // Verificar pais
    vector<int> parentes;
    if (p.id_pai > 0) parentes.push_back(p.id_pai);
    if (p.id_mae > 0) parentes.push_back(p.id_mae);
    if (p.id_conjuge > 0) parentes.push_back(p.id_conjuge);

    // Adicionar filhos
    for (int filho_id : p.filhos) {
      parentes.push_back(filho_id);
    }

    for (int parente_id : parentes) {
      if (parente_id == pessoa2_id) {
        return distancia + 1; // Encontrou!
      }

      if (visitados.find(parente_id) == visitados.end() && arvore.find(parente_id) != arvore.end()) {
        visitados.insert(parente_id);
        fila.push({ parente_id, distancia + 1 });
      }
    }
  }

  return -1; // Não há parentesco
}

// Função para contar o número de descendentes diretos e indiretos
int contarDescendentes(const map<int, Pessoa>& arvore, int pessoa_id) {
  if (arvore.find(pessoa_id) == arvore.end()) {
    return 0;
  }

  int total = 0;
  function<void(int)> contar = [&](int id) {
    const Pessoa& p = arvore.at(id);
    for (int filho_id : p.filhos) {
      total++;
      contar(filho_id);
    }
    };

  contar(pessoa_id);
  return total;
}

// Função para mostrar gerações separadas por nível
void exibirGeracoesPorNivel(const map<int, Pessoa>& arvore, int pessoa_id) {
  if (arvore.find(pessoa_id) == arvore.end()) return;

  queue<pair<int, int>> fila; // (pessoa_id, nivel)
  fila.push({ pessoa_id, 0 });

  int nivel_atual = 0;

  while (!fila.empty()) {
    auto [atual, nivel] = fila.front();
    fila.pop();

    const Pessoa& p = arvore.at(atual);

    // Se mudou de nível, imprime cabeçalho
    if (nivel > nivel_atual) {
      nivel_atual = nivel;
      cout << "\n--- GERAÇÃO " << nivel << " ---" << endl;
    }

    // Imprime a pessoa
    cout << "  " << p.nome << " (" << p.genero << ") [ID: " << p.id << "]";
    if (p.id_conjuge > 0 && arvore.find(p.id_conjuge) != arvore.end()) {
      const Pessoa& conjuge = arvore.at(p.id_conjuge);
      cout << " 💑 " << conjuge.nome;
    }
    cout << endl;

    // Adiciona filhos à fila
    for (int filho_id : p.filhos) {
      fila.push({ filho_id, nivel + 1 });
    }
  }
}

// Função interativa para exibir nível de parentesco
void exibirNivelParentesco(map<int, Pessoa>& arvore) {
  cout << "\n=== NÍVEL DE PARENTESCO ENTRE DUAS PESSOAS ===" << endl;

  cout << "Primeira pessoa:" << endl;
  int pessoa1_id = buscarPessoaInterativo(arvore);
  if (pessoa1_id == -1) return;

  cout << "\nSegunda pessoa:" << endl;
  int pessoa2_id = buscarPessoaInterativo(arvore);
  if (pessoa2_id == -1) return;

  const Pessoa& p1 = arvore.at(pessoa1_id);
  const Pessoa& p2 = arvore.at(pessoa2_id);

  int nivel = calcularParentesco(arvore, pessoa1_id, pessoa2_id);

  cout << "\n=== RESULTADO ===" << endl;
  cout << "Pessoa 1: " << p1.nome << " (ID: " << p1.id << ")" << endl;
  cout << "Pessoa 2: " << p2.nome << " (ID: " << p2.id << ")" << endl;

  if (nivel == -1) {
    cout << "❌ Não há parentesco entre as duas pessoas." << endl;
  }
  else if (nivel == 0) {
    cout << "👤 São a mesma pessoa!" << endl;
  }
  else {
    cout << "📏 Nível de parentesco: " << nivel << " grau(s) de separação" << endl;

    // Descrição do parentesco
    if (nivel == 1) {
      // Verificar relação direta
      const Pessoa& p1 = arvore.at(pessoa1_id);
      const Pessoa& p2 = arvore.at(pessoa2_id);

      if (p1.id_pai == pessoa2_id || p1.id_mae == pessoa2_id) {
        cout << "   👶 " << p1.nome << " é filho(a) de " << p2.nome << endl;
      }
      else if (p2.id_pai == pessoa1_id || p2.id_mae == pessoa1_id) {
        cout << "   👨‍👧 " << p1.nome << " é pai/mãe de " << p2.nome << endl;
      }
      else if (p1.id_conjuge == pessoa2_id) {
        cout << "   💑 " << p1.nome << " é cônjuge de " << p2.nome << endl;
      }
      else {
        bool encontrou = false;
        for (int filho_id : p1.filhos) {
          if (filho_id == pessoa2_id) {
            cout << "   👨‍👧 " << p1.nome << " é pai/mãe de " << p2.nome << endl;
            encontrou = true;
            break;
          }
        }
        if (!encontrou) {
          cout << "   🔗 Parentesco direto" << endl;
        }
      }
    }
    else if (nivel == 2) {
      cout << "   👥 Parentesco de segundo grau (avós/netos, tios/sobrinhos)" << endl;
    }
    else if (nivel == 3) {
      cout << "   👥 Parentesco de terceiro grau (bisavós/bisnetos, primos)" << endl;
    }
    else {
      cout << "   👥 Parentesco distante" << endl;
    }
  }
}

// Função interativa para exibir contagem de descendentes
void exibirContagemDescendentes(map<int, Pessoa>& arvore) {
  cout << "\n=== CONTAGEM DE DESCENDENTES ===" << endl;

  int pessoa_id = buscarPessoaInterativo(arvore);
  if (pessoa_id == -1) return;

  const Pessoa& pessoa = arvore.at(pessoa_id);
  int total_descendentes = contarDescendentes(arvore, pessoa_id);
  int filhos_diretos = pessoa.filhos.size();
  int filhos_indiretos = total_descendentes - filhos_diretos;

  cout << "\n=== RESULTADO ===" << endl;
  cout << "Pessoa: " << pessoa.nome << " (ID: " << pessoa.id << ")" << endl;
  cout << "📊 ESTATÍSTICAS DE DESCENDENTES:" << endl;
  cout << "   • Filhos diretos: " << filhos_diretos << endl;
  cout << "   • Descendentes indiretos: " << filhos_indiretos << endl;
  cout << "   • TOTAL de descendentes: " << total_descendentes << endl;

  if (filhos_diretos > 0) {
    cout << "\n👶 FILHOS DIRETOS:" << endl;
    for (int filho_id : pessoa.filhos) {
      const Pessoa& filho = arvore.at(filho_id);
      int netos = contarDescendentes(arvore, filho_id);
      cout << "   • " << filho.nome << " (ID: " << filho.id << ")";
      if (netos > 0) {
        cout << " → " << netos << " descendente(s)";
      }
      cout << endl;
    }
  }
}

// Função interativa para exibir gerações separadas por nível
void exibirGeracoesSeparadas(map<int, Pessoa>& arvore) {
  cout << "\n=== GERAÇÕES SEPARADAS POR NÍVEL ===" << endl;

  int pessoa_id = buscarPessoaInterativo(arvore);
  if (pessoa_id == -1) return;

  const Pessoa& pessoa = arvore.at(pessoa_id);

  cout << "\n=== GERAÇÕES A PARTIR DE " << pessoa.nome << " ===" << endl;
  cout << "Ancestral: " << pessoa.nome << " (" << pessoa.genero << ") [ID: " << pessoa.id << "]" << endl;

  if (pessoa.id_conjuge > 0 && arvore.find(pessoa.id_conjuge) != arvore.end()) {
    const Pessoa& conjuge = arvore.at(pessoa.id_conjuge);
    cout << "Cônjuge: " << conjuge.nome << " (" << conjuge.genero << ") [ID: " << conjuge.id << "]" << endl;
  }

  cout << "=====================================" << endl;

  exibirGeracoesPorNivel(arvore, pessoa_id);

  // Estatísticas
  int total_descendentes = contarDescendentes(arvore, pessoa_id);
  cout << "\n--- ESTATÍSTICAS ---" << endl;
  cout << "Total de descendentes: " << total_descendentes << endl;
}

// Atualização do menuInterativo para incluir as novas funções
void menuInterativo(map<int, Pessoa>& arvore) {
  int opcao;

  do {
    cout << "\n=== MENU INTERATIVO ===" << endl;
    cout << "1. Adicionar nova pessoa" << endl;
    cout << "2. Definir pais para uma pessoa" << endl;
    cout << "3. Salvar alterações no CSV" << endl;
    cout << "4. Visualizar árvore atual" << endl;
    cout << "5. Listar todas as pessoas" << endl;
    cout << "6. Exibir ascendentes e descendentes" << endl;
    cout << "7. Buscar pessoa por nome" << endl;
    cout << "8. Listar árvore desde ancestral" << endl;
    cout << "9. Nível de parentesco entre duas pessoas" << endl;      // NOVA
    cout << "10. Contar descendentes de uma pessoa" << endl;          // NOVA
    cout << "11. Exibir gerações por nível" << endl;                  // NOVA
    cout << "0. Sair" << endl;
    cout << "Escolha: ";
    cin >> opcao;

    switch (opcao) {
    case 1:
      adicionarPessoaInterativo(arvore);
      break;
    case 2: {
      int id_filho;
      cout << "Digite o ID da pessoa que deseja definir os pais: ";
      cin >> id_filho;
      definirPais(arvore, id_filho);
      break;
    }
    case 3:
      salvarCSV(arvore, "dados/dados.csv");
      break;
    case 4: {
      int raiz_id;
      encontrarRaiz(arvore, raiz_id);
      vector<bool> ultimos;
      cout << "\n=== ÁRVORE ATUAL ===" << endl;
      imprimirArvore(arvore, raiz_id, 0, ultimos);
      break;
    }
    case 5: {
      cout << "\n=== LISTA DE PESSOAS ===" << endl;
      for (const auto& par : arvore) {
        const Pessoa& p = par.second;
        cout << "ID: " << p.id << " | " << p.nome << " (" << p.genero << ")";
        if (p.id_pai > 0) cout << " | Pai: " << p.id_pai;
        if (p.id_mae > 0) cout << " | Mãe: " << p.id_mae;
        if (p.id_conjuge > 0) cout << " | Cônjuge: " << p.id_conjuge;
        cout << " | Filhos: " << p.filhos.size();
        cout << endl;
      }
      break;
    }
    case 6:
      exibirAscendentesEDescendentes(arvore);
      break;
    case 7: {
      string nomeBusca = "";
      cout << "Digite o nome: ";
      nomeBusca = lerStringUTF8();

      int pessoa_id = buscarPessoaPorNome(arvore, nomeBusca);

      if (pessoa_id == -1) {
        cout << "Erro: Pessoa com nome '" << nomeBusca << "' não encontrada!" << endl;
      }
      else {
        const Pessoa& p = arvore.at(pessoa_id);
        cout << "Pessoa encontrada: " << p.nome << " (ID: " << pessoa_id << ") Gênero: " << p.genero << endl;
        cout << "Pai: " << (p.id_pai > 0 ? arvore.at(p.id_pai).nome : "Não definido") << endl;
        cout << "Mãe: " << (p.id_mae > 0 ? arvore.at(p.id_mae).nome : "Não definido") << endl;
        cout << "Cônjuge: " << (p.id_conjuge > 0 ? arvore.at(p.id_conjuge).nome : "Não definido") << endl;
        cout << "Filhos: " << p.filhos.size() << endl;
      }
      break;
    }
    case 8:
      listarArvoreDesdeAncestral(arvore);
      break;
    case 9:  // NOVO
      exibirNivelParentesco(arvore);
      break;
    case 10: // NOVO
      exibirContagemDescendentes(arvore);
      break;
    case 11: // NOVO
      exibirGeracoesSeparadas(arvore);
      break;
    case 0:
      cout << "Saindo do menu interativo..." << endl;
      break;
    default:
      cout << "Opção inválida!" << endl;
    }
  } while (opcao != 0);
}