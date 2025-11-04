#include "menu_criar.hpp"

void exibirMenuCriar() {
  cout << "\n📝 === MENU CRIAR ===" << endl;
  cout << "1. 👤 Criar Pessoa" << endl;
  cout << "2. 🌳 Criar Árvore Genealógica" << endl;
  cout << "3. 👨‍👩‍👧‍👦 Definir Relação Pai/Mãe-Filho" << endl;
  cout << "0. ↩️  Voltar ao Menu Principal" << endl;
}

void processarOpcaoCriar(const string& opcao) {
  if (opcao == "0") return;

  switch (stoi(opcao)) {
  case 1:
    menuCriarPessoa();
    break;
  case 2:
    menuCriarArvoreGenealogica();
    break;
  case 3:
    menuDefinirRelacao();
    break;
  default:
    cout << "❌ Opção inválida!" << endl;
    break;
  }
}

void menuCriar() {
  string opcao;

  do {
    exibirMenuCriar();
    cout << "🎯 Escolha uma opção: ";
    getline(cin, opcao);
    processarOpcaoCriar(opcao);

  } while (opcao != "0");
}

// Implementações das funções do menu criar
void menuCriarPessoa() {
  string nome, dataNasc;
  char genero;

  cout << "\n👤 --- Criar Nova Pessoa ---" << endl;
  cout << "📝 Nome: ";
  getline(cin, nome);
  cout << "📅 Data de Nascimento (DD/MM/AAAA): ";
  getline(cin, dataNasc);
  cout << "⚧️  Gênero (M/F): ";
  cin >> genero;
  cin.ignore();

  genero = toupper(genero);
  if (genero != 'M' && genero != 'F') {
    cout << "❌ Gênero inválido! Use M ou F." << endl;
    return;
  }

  Pessoa* novaPessoa = criarPessoa(nome, dataNasc, genero);
  cout << "✅ Pessoa criada com ID: " << novaPessoa->id << endl;

  // CHAMA MENU PÓS-CRIAÇÃO
  menuPosCriacaoPessoa(novaPessoa);
}

void menuCriarArvoreGenealogica() {
  string nome;

  cout << "\n🌳 --- Criar Nova Árvore Genealógica ---" << endl;
  cout << "📝 Nome da árvore genealógica: ";
  getline(cin, nome);

  ArvoreGenealogica* novaArvore = criarArvoreGenealogica(nome);
  cout << "✅ Árvore Genealógica criada com ID: " << novaArvore->id << endl;
}

void menuDefinirRelacao() {
  string idPai, idMae, idFilho;

  cout << "\n👨‍👩‍👧‍👦 --- Definir Relação Pai/Mãe-Filho ---" << endl;
  cout << "🆔 ID do Pai (deixe vazio se não existir): ";
  getline(cin, idPai);
  cout << "🆔 ID da Mãe (deixe vazio se não existir): ";
  getline(cin, idMae);
  cout << "🆔 ID do Filho: ";
  getline(cin, idFilho);

  Pessoa* pai = idPai.empty() ? nullptr : buscarPessoa(idPai);
  Pessoa* mae = idMae.empty() ? nullptr : buscarPessoa(idMae);
  Pessoa* filho = buscarPessoa(idFilho);

  if (filho == nullptr) {
    cout << "❌ Filho não encontrado!" << endl;
    return;
  }

  if (pai == nullptr && mae == nullptr) {
    cout << "❌ Erro: Pelo menos um progenitor deve existir!" << endl;
    return;
  }

  if (definirRelacaoPaiFilho(pai, mae, filho)) {
    cout << "✅ Relação definida com sucesso!" << endl;
  }
  else {
    cout << "❌ Erro ao definir relação!" << endl;
  }
}

// Funções do menu pós-criação
void menuPosCriacaoPessoa(Pessoa* novaPessoa) {
  string opcao;

  do {
    cout << "\n🎯 MENU PÓS-CRIAÇÃO: " << novaPessoa->nome << " (" << novaPessoa->id << ")" << endl;
    cout << "1. 🔗 Associar à Árvore Genealógica" << endl;
    cout << "2. 👨‍👩‍👧‍👦 Definir Pais desta Pessoa" << endl;
    cout << "3. ❤️  Definir Cônjuge" << endl;
    cout << "4. 👶 Adicionar Filhos" << endl;
    cout << "5. 🌳 Mostrar Árvore desta Pessoa" << endl;
    cout << "0. ✅ Finalizar e Voltar ao Menu Principal" << endl;
    cout << "🎯 Escolha uma opção: ";
    getline(cin, opcao);

    switch (stoi(opcao)) {
    case 1:
      associarPessoaArvoreExistente(novaPessoa);
      break;
    case 2:
      definirPaisParaPessoa(novaPessoa);
      break;
    case 3:
      definirConjugeParaPessoa(novaPessoa);
      break;
    case 4:
      adicionarFilhosParaPessoa(novaPessoa);
      break;
    case 5:
      mostrarArvoreIndividual(novaPessoa);
      break;
    case 0:
      cout << "✅ Pessoa " << novaPessoa->nome << " finalizada!" << endl;
      break;
    default:
      cout << "❌ Opção inválida!" << endl;
      break;
    }
  } while (opcao != "0");
}

void associarPessoaArvoreExistente(Pessoa* pessoa) {
  if (arvores.empty()) {
    cout << "ℹ️  Nenhuma árvore cadastrada. Deseja criar uma? (S/N): ";
    string resposta;
    getline(cin, resposta);

    if (resposta == "S" || resposta == "s") {
      string nomeArvore;
      cout << "📝 Nome da nova árvore genealógica: ";
      getline(cin, nomeArvore);

      ArvoreGenealogica* novaArvore = criarArvoreGenealogica(nomeArvore);
      adicionarPessoaArvore(novaArvore, pessoa);
      cout << "✅ " << pessoa->nome << " associado à árvore " << novaArvore->nome << endl;
    }
    return;
  }

  cout << "\n🌳 Árvores Disponíveis:" << endl;
  for (size_t i = 0; i < arvores.size(); i++) {
    cout << i + 1 << ". " << arvores[i]->nome << " (" << arvores[i]->id << ")" << endl;
  }

  cout << "🎯 Escolha o número da árvore (0 para criar nova): ";
  string escolha;
  getline(cin, escolha);

  try {
    int index = stoi(escolha);
    if (index == 0) {
      string nomeArvore;
      cout << "📝 Nome da nova árvore genealógica: ";
      getline(cin, nomeArvore);

      ArvoreGenealogica* novaArvore = criarArvoreGenealogica(nomeArvore);
      adicionarPessoaArvore(novaArvore, pessoa);
      cout << "✅ " << pessoa->nome << " associado à árvore " << novaArvore->nome << endl;
    }
    else if (index > 0 && static_cast<size_t>(index) <= arvores.size()) {
      adicionarPessoaArvore(arvores[index - 1], pessoa);
      cout << "✅ " << pessoa->nome << " associado à árvore " << arvores[index - 1]->nome << endl;
    }
    else {
      cout << "❌ Número inválido!" << endl;
    }
  }
  catch (...) {
    cout << "❌ Opção inválida!" << endl;
  }

  cout << "\n↩️  Voltando ao menu de " << pessoa->nome << "..." << endl;
}

Pessoa* criarProgenitorComGenero(const string& tipo, Pessoa* filho) {
  cout << "\n--- Criar " << tipo << " de " << filho->nome << " ---" << endl;

  string nome, dataNasc;
  char genero = (tipo == "Pai") ? 'M' : 'F'; // Gênero automático

  cout << "📝 Nome do " << tipo << ": ";
  getline(cin, nome);
  cout << "📅 Data de Nascimento (DD/MM/AAAA): ";
  getline(cin, dataNasc);

  // Já define o gênero automaticamente
  cout << "⚧️  Gênero: " << (genero == 'M' ? "Masculino (automático)" : "Feminino (automático)") << endl;

  Pessoa* progenitor = criarPessoa(nome, dataNasc, genero);
  cout << "✅ " << tipo << " criado: " << progenitor->nome << " (" << progenitor->id << ")" << endl;

  return progenitor;
}

void definirPaisParaPessoa(Pessoa* pessoa) {
  cout << "\n👨‍👩‍👧‍👦 Definir Pais para " << pessoa->nome << endl;

  string opcao;
  cout << "1. 🆔 Usar IDs de pais existentes" << endl;
  cout << "2. 👥 Criar novos pais" << endl;
  cout << "3. ↩️  Voltar ao menu anterior" << endl;
  cout << "🎯 Escolha uma opção: ";
  getline(cin, opcao);

  if (opcao == "3") {
    return; // Volta para o menu pós-criação da pessoa original
  }

  Pessoa* pai = nullptr;
  Pessoa* mae = nullptr;

  if (opcao == "1") {
    // Opção 1: Usar IDs existentes
    string idPai, idMae;
    cout << "🆔 ID do Pai (deixe vazio se não existir): ";
    getline(cin, idPai);
    cout << "🆔 ID da Mãe (deixe vazio se não existir): ";
    getline(cin, idMae);

    pai = idPai.empty() ? nullptr : buscarPessoa(idPai);
    mae = idMae.empty() ? nullptr : buscarPessoa(idMae);

    if (pai && pai->genero != 'M') {
      cout << "⚠️  Aviso: " << pai->nome << " é do gênero feminino, mas está como pai." << endl;
    }
    if (mae && mae->genero != 'F') {
      cout << "⚠️  Aviso: " << mae->nome << " é do gênero masculino, mas está como mãe." << endl;
    }
  }
  else if (opcao == "2") {
    // Opção 2: Criar novos pais - MANTÉM FOCO NA PESSOA ORIGINAL
    cout << "\n--- Criar Pais para " << pessoa->nome << " ---" << endl;

    string criarPai;
    cout << "❓ Deseja criar o PAI? (S/N): ";
    getline(cin, criarPai);

    if (criarPai == "S" || criarPai == "s") {
      pai = criarProgenitorComGenero("Pai", pessoa);
    }

    string criarMae;
    cout << "❓ Deseja criar a MÃE? (S/N): ";
    getline(cin, criarMae);

    if (criarMae == "S" || criarMae == "s") {
      mae = criarProgenitorComGenero("Mãe", pessoa);
    }
  }
  else {
    cout << "❌ Opção inválida!" << endl;
    return;
  }

  if (pai == nullptr && mae == nullptr) {
    cout << "⚠️  Nenhum pai definido." << endl;
    return;
  }

  // Define a relação pai/filho - FOCO PERMANECE NA PESSOA ORIGINAL
  if (definirRelacaoPaiFilho(pai, mae, pessoa)) {
    cout << "✅ Pais definidos com sucesso para " << pessoa->nome << "!" << endl;

    // LÓGICA PARA DEFINIR PAIS COMO RAÍZES DA ÁRVORE
    definirPaisComoRaizDaArvore(pessoa, pai, mae);

  }
  else {
    cout << "❌ Erro ao definir pais!" << endl;
  }

  cout << "\n↩️  Voltando ao menu de " << pessoa->nome << "..." << endl;
}

void definirPaisComoRaizDaArvore(Pessoa* pessoa, Pessoa* pai, Pessoa* mae) {
  // Verificar se a pessoa já está em alguma árvore
  ArvoreGenealogica* arvoreExistente = nullptr;

  for (auto arvore : arvores) {
    for (auto p : arvore->pessoas) {
      if (p->id == pessoa->id) {
        arvoreExistente = arvore;
        break;
      }
    }
    if (arvoreExistente) break;
  }

  if (arvoreExistente) {
    // Pessoa já está em uma árvore - redefinir ancestral principal
    Pessoa* novoAncestral = nullptr;

    if (pai) {
      novoAncestral = pai;
      cout << "👑 " << pai->nome << " definido como novo ancestral principal da árvore!" << endl;
    }
    else if (mae) {
      novoAncestral = mae;
      cout << "👑 " << mae->nome << " definido como novo ancestral principal da árvore!" << endl;
    }

    if (novoAncestral) {
      arvoreExistente->ancestralPrincipal = novoAncestral;
      // Garantir que os pais estão na árvore
      if (pai) adicionarPessoaArvore(arvoreExistente, pai);
      if (mae) adicionarPessoaArvore(arvoreExistente, mae);
    }
  }
  else {
    // Pessoa não está em nenhuma árvore - criar nova ou associar pais
    if (!arvores.empty()) {
      cout << "❓ Deseja criar uma NOVA árvore genealógica com os pais como raiz? (S/N): ";
      string resposta;
      getline(cin, resposta);

      if (resposta == "S" || resposta == "s") {
        string nomeArvore;
        cout << "📝 Nome da nova árvore genealógica: ";
        getline(cin, nomeArvore);

        ArvoreGenealogica* novaArvore = criarArvoreGenealogica(nomeArvore);

        // Definir pai ou mãe como ancestral principal
        if (pai) {
          novaArvore->ancestralPrincipal = pai;
          cout << "🌳 " << pai->nome << " definido como ancestral principal da nova árvore!" << endl;
        }
        else if (mae) {
          novaArvore->ancestralPrincipal = mae;
          cout << "🌳 " << mae->nome << " definido como ancestral principal da nova árvore!" << endl;
        }

        // Adicionar todos à árvore
        if (pai) adicionarPessoaArvore(novaArvore, pai);
        if (mae) adicionarPessoaArvore(novaArvore, mae);
        adicionarPessoaArvore(novaArvore, pessoa);
      }
    }
    else {
      // Criar árvore automaticamente se não existir nenhuma
      string nomeArvore = "Árvore da Família " + pessoa->nome;
      ArvoreGenealogica* novaArvore = criarArvoreGenealogica(nomeArvore);

      // Definir pai ou mãe como ancestral principal
      if (pai) {
        novaArvore->ancestralPrincipal = pai;
        cout << "🌳 " << pai->nome << " definido como ancestral principal da árvore!" << endl;
      }
      else if (mae) {
        novaArvore->ancestralPrincipal = mae;
        cout << "🌳 " << mae->nome << " definido como ancestral principal da árvore!" << endl;
      }
      else {
        // Se não tem pais, a própria pessoa é a raiz
        novaArvore->ancestralPrincipal = pessoa;
        cout << "🌳 " << pessoa->nome << " definido como ancestral principal da árvore!" << endl;
      }

      // Adicionar todos à árvore
      if (pai) adicionarPessoaArvore(novaArvore, pai);
      if (mae) adicionarPessoaArvore(novaArvore, mae);
      adicionarPessoaArvore(novaArvore, pessoa);
    }
  }
}

Pessoa* criarConjugeComGenero(Pessoa* pessoa) {
  cout << "\n--- Criar Cônjuge para " << pessoa->nome << " ---" << endl;

  string nomeConjuge, dataNasc;
  char generoConjuge = (pessoa->genero == 'M') ? 'F' : 'M'; // Gênero oposto automático

  cout << "📝 Nome do Cônjuge: ";
  getline(cin, nomeConjuge);
  cout << "📅 Data de Nascimento (DD/MM/AAAA): ";
  getline(cin, dataNasc);

  // Gênero automático baseado na pessoa original
  cout << "⚧️  Gênero: " << (generoConjuge == 'M' ? "Masculino" : "Feminino") << " (automático - oposto de " << pessoa->nome << ")" << endl;

  Pessoa* conjuge = criarPessoa(nomeConjuge, dataNasc, generoConjuge);
  cout << "✅ Cônjuge criado: " << conjuge->nome << " (" << conjuge->id << ")" << endl;

  return conjuge;
}

void definirConjugeParaPessoa(Pessoa* pessoa) {
  cout << "\n❤️  Definir Cônjuge para " << pessoa->nome << endl;

  string opcao;
  cout << "1. 🔍 Buscar cônjuge existente" << endl;
  cout << "2. 👤 Criar novo cônjuge" << endl;
  cout << "3. ↩️  Voltar ao menu anterior" << endl;
  cout << "🎯 Escolha uma opção: ";
  getline(cin, opcao);

  if (opcao == "3") {
    return; // Volta para o menu pós-criação da pessoa original
  }

  Pessoa* conjuge = nullptr;

  if (opcao == "1") {
    // Buscar pessoas do gênero oposto
    vector<Pessoa*> possiveisConjuges;
    char generoOposto = (pessoa->genero == 'M') ? 'F' : 'M';

    for (auto p : pessoas) {
      if (p->genero == generoOposto && p->id != pessoa->id) {
        possiveisConjuges.push_back(p);
      }
    }

    if (possiveisConjuges.empty()) {
      cout << "ℹ️  Nenhum cônjuge potencial encontrado." << endl;
      cout << "❓ Deseja criar um novo cônjuge? (S/N): ";
      string resposta;
      getline(cin, resposta);

      if (resposta == "S" || resposta == "s") {
        conjuge = criarConjugeComGenero(pessoa);
        if (conjuge) {
          cout << "✅ Casamento definido entre " << pessoa->nome << " e " << conjuge->nome << endl;
          associarMesmaArvore(pessoa, conjuge);
        }
      }
      return;
    }

    cout << "👥 Possíveis cônjuges:" << endl;
    for (size_t i = 0; i < possiveisConjuges.size(); i++) {
      cout << i + 1 << ". " << possiveisConjuges[i]->nome << " (" << possiveisConjuges[i]->id << ")" << endl;
    }

    cout << "🎯 Escolha o número do cônjuge (0 para criar novo): ";
    string escolha;
    getline(cin, escolha);

    try {
      int index = stoi(escolha);
      if (index == 0) {
        conjuge = criarConjugeComGenero(pessoa);
        if (conjuge) {
          cout << "✅ Casamento definido entre " << pessoa->nome << " e " << conjuge->nome << endl;
          associarMesmaArvore(pessoa, conjuge);
        }
      }
      else if (index > 0 && static_cast<size_t>(index) <= possiveisConjuges.size()) {
        conjuge = possiveisConjuges[index - 1];
        cout << "✅ Casamento definido entre " << pessoa->nome << " e " << conjuge->nome << endl;
        associarMesmaArvore(pessoa, conjuge);
      }
    }
    catch (...) {
      cout << "❌ Opção inválida!" << endl;
    }
  }
  else if (opcao == "2") {
    conjuge = criarConjugeComGenero(pessoa);
    if (conjuge) {
      cout << "✅ Casamento definido entre " << pessoa->nome << " e " << conjuge->nome << endl;
      associarMesmaArvore(pessoa, conjuge);
    }
  }
  else {
    cout << "❌ Opção inválida!" << endl;
    return;
  }

  cout << "\n↩️  Voltando ao menu de " << pessoa->nome << "..." << endl;
}

void associarMesmaArvore(Pessoa* pessoa, Pessoa* conjuge) {
  for (auto arvore : arvores) {
    for (auto p : arvore->pessoas) {
      if (p->id == conjuge->id) {
        cout << "❓ Deseja associar " << pessoa->nome << " à mesma árvore do cônjuge? (S/N): ";
        string resp;
        getline(cin, resp);
        if (resp == "S" || resp == "s") {
          adicionarPessoaArvore(arvore, pessoa);
        }
        return;
      }
    }
  }
}

void adicionarFilhosParaPessoa(Pessoa* pessoa) {
  cout << "\n👶 Adicionar Filhos para " << pessoa->nome << endl;

  string opcao;
  cout << "1. 🆔 Usar ID de filho existente" << endl;
  cout << "2. 👶 Criar novo filho" << endl;
  cout << "3. ↩️  Voltar ao menu anterior" << endl;
  cout << "🎯 Escolha uma opção: ";
  getline(cin, opcao);

  if (opcao == "3") {
    return; // Volta para o menu pós-criação da pessoa original
  }

  Pessoa* filho = nullptr;

  if (opcao == "1") {
    cout << "🆔 ID do Filho: ";
    string idFilho;
    getline(cin, idFilho);

    filho = buscarPessoa(idFilho);
    if (!filho) {
      cout << "❌ Filho não encontrado!" << endl;
      return;
    }
  }
  else if (opcao == "2") {
    // Criar filho SEM sair da pessoa original
    cout << "\n--- Criar Filho para " << pessoa->nome << " ---" << endl;

    string nomeFilho, dataNasc;
    char generoFilho;

    cout << "📝 Nome do Filho: ";
    getline(cin, nomeFilho);
    cout << "📅 Data de Nascimento (DD/MM/AAAA): ";
    getline(cin, dataNasc);
    cout << "⚧️  Gênero (M/F): ";
    cin >> generoFilho;
    cin.ignore();

    generoFilho = toupper(generoFilho);
    if (generoFilho != 'M' && generoFilho != 'F') {
      cout << "❌ Gênero inválido!" << endl;
      return;
    }

    filho = criarPessoa(nomeFilho, dataNasc, generoFilho);
    cout << "✅ Filho criado: " << filho->nome << endl;
  }
  else {
    cout << "❌ Opção inválida!" << endl;
    return;
  }

  // Encontrar cônjuge se existir (para lógica de gênero)
  Pessoa* conjuge = nullptr;

  // Definir relação pai-filho
  if (pessoa->genero == 'M') {
    definirRelacaoPaiFilho(pessoa, conjuge, filho);
  }
  else {
    definirRelacaoPaiFilho(conjuge, pessoa, filho);
  }

  cout << "✅ " << filho->nome << " adicionado como filho de " << pessoa->nome << "!" << endl;

  // Associar automaticamente à mesma árvore
  for (auto arvore : arvores) {
    for (auto p : arvore->pessoas) {
      if (p->id == pessoa->id) {
        adicionarPessoaArvore(arvore, filho);
        cout << "✅ " << filho->nome << " associado à árvore " << arvore->nome << endl;
        break;
      }
    }
  }

  cout << "\n↩️  Voltando ao menu de " << pessoa->nome << "..." << endl;
}

void mostrarArvoreIndividual(Pessoa* pessoa) {
  cout << "\n🌳 Árvore de " << pessoa->nome << endl;
  mostrarArvoreHierarquica(pessoa);
}