# 🌳 Sistema de Árvore Genealógica

Um sistema completo em C++ para gerenciamento e análise de árvores genealógicas,
com interface interativa e suporte a múltiplas funcionalidades de parentesco.

## 📋 Pré-requisitos

### Para Windows:

- **MinGW-w64** (compilador GCC para Windows)
- **CMake** (versão 3.10 ou superior)
- **Git Bash** (recomendado) ou PowerShell

### Para Linux/macOS:

- **GCC** ou **Clang** (com suporte C++17)
- **CMake** (versão 3.10 ou superior)
- **Make**

### Verificação dos pré-requisitos:

```bash
# Verificar compilador
g++ --version

# Verificar CMake
cmake --version

# Verificar Make (Linux/macOS) ou MinGW (Windows)
make --version
# ou
mingw32-make --version
```

## 🚀 Compilação e Execução

### Método Automático (Recomendado):

```bash
# No Linux/macOS/Git Bash
chmod +x run
./run

# No Windows (PowerShell ou Git Bash)
.\run
```

### Método Manual:

```bash
# Criar pasta de build
mkdir build
cd build

# Configurar com CMake
cmake ..

# Compilar
make  # Linux/macOS
# ou
mingw32-make  # Windows

# Executar
./family-tree  # Linux/macOS
# ou
.\family-tree.exe  # Windows
```

## 🏗️ Estrutura do Projeto

```
family_tree/
├── CMakeLists.txt
├── dados/
│   └── dados.csv
├── include/
│   ├── core/
│   │   ├── arvore.hpp
│   │   └── pessoa.hpp
│   ├── io/
│   │   ├── csv_handler.hpp
│   │   └── utf8_config.hpp
│   ├── ui/
│   │   ├── impressao.hpp
│   │   └── menu.hpp
│   ├── utils/
│   │   ├── busca.hpp
│   │   └── validacao.hpp
│   └── main.hpp
└── src/
    ├── core/
    │   └── arvore.cpp
    ├── io/
    │   ├── csv_handler.cpp
    │   └── utf8_config.cpp
    ├── ui/
    │   ├── impressao.cpp
    │   └── menu.cpp
    ├── utils/
    │   ├── busca.cpp
    │   └── validacao.cpp
    └── main.cpp
```

## 📊 Estruturas de Dados e STL Utilizadas

### Estruturas Principais:

1. **`struct Pessoa`**:

   - Representa um indivíduo na árvore
   - Campos: id, nome, gênero, ano_nascimento, relações familiares

2. **`struct EstatisticasArvore`**:

   - Métricas da árvore (total de pessoas, gerações)

3. **`struct OpcaoMenu` e `TopicoMenu`**:
   - Sistema de menu modular e extensível

### Containers STL Utilizados:

- **`std::map<int, Pessoa>`**: Árvore genealógica principal (acesso O(log n) por
  ID)
- **`std::vector<Pessoa>`**: Lista de pessoas para carregamento inicial
- **`std::vector<int>`**: Lista de filhos para cada pessoa
- **`std::queue<int>`**: BFS para cálculo de parentesco e estatísticas
- **`std::stack<int>`**: DFS para contagem de descendentes
- **`std::set<int>`**: Controle de visitados em algoritmos de busca
- **`std::function<void()>`**: Sistema de callbacks para menu

## ⚙️ Funcionamento do Sistema

### 1. **Carregamento de Dados**

- Leitura de arquivo CSV com dados das pessoas
- Construção automática da árvore genealógica
- Validação de consistência dos dados

### 2. **Algoritmos Implementados**

- **BFS Bidirecional**: Cálculo de graus de parentesco
- **DFS Iterativo**: Contagem de descendentes
- **Busca em Largura**: Análise de gerações
- **Validação de Ciclos**: Detecção de inconsistências

### 3. **Sistema de Menu**

- Interface modular por tópicos
- Operações interativas para gestão
- Visualizações diversas da árvore

## ✨ Funcionalidades

### 👥 Gestão de Pessoas

- Adicionar novas pessoas
- Definir relações parentais
- Busca por nome ou ID
- Listagem completa

### 🌳 Visualização

- Árvore hierárquica completa
- Visualização a partir de qualquer ancestral
- Linha de ascendência
- Gerações por nível

### 📊 Análise

- Cálculo de parentesco entre duas pessoas
- Contagem de descendentes
- Estatísticas avançadas
- Validação de inconsistências

### 💾 Armazenamento

- Salvamento automático em CSV
- Persistência das alterações

## ✅ Vantagens

### 🎯 Arquitetura

- **Código Modular**: Separação clara de responsabilidades
- **Headers Organizados**: Estrutura por funcionalidade
- **CMake Configurável**: Suporte multi-plataforma

### 🔧 Tecnologia

- **C++17**: Recursos modernos da linguagem
- **UTF-8 Nativo**: Suporte a caracteres especiais
- **STL Robustez**: Containers e algoritmos otimizados

### 🎮 Usabilidade

- **Menu Intuitivo**: Navegação fácil e lógica
- **Feedback Visual**: Emojis e formatação clara
- **Validação Rigorosa**: Prevenção de dados inconsistentes

## ⚠️ Limitações e Considerações

### 🚧 Limitações Atuais

- **Performance**: BFS bidirecional pode ser custoso para árvores muito grandes
- **Memória**: Uso de múltiplas estruturas para diferentes visualizações
- **Complexidade**: Alguns algoritmos O(n²) em worst-case

### 🔄 Possíveis Melhorias

- **Indexação por Nome**: Hash map para buscas mais rápidas
- **Cache de Resultados**: Otimização para consultas repetidas
- **Serialização Binária**: Carregamento mais rápido que CSV
- **Interface Gráfica**: Visualização gráfica da árvore

## 🛠️ Resolução de Problemas

### Erro de Compilação:

```bash
# Limpar build e recriar
rm -rf build
mkdir build
cd build
cmake ..
make
```

### Problemas de UTF-8:

- Verificar locale do sistema
- Usar terminal com suporte UTF-8
- No Windows, usar Git Bash ou PowerShell moderno

### Arquivo CSV Corrompido:

- Manter cabeçalho: `id,nome,genero,ano_nascimento,id_pai,id_mae,id_conjuge`
- IDs devem ser numéricos e únicos
- Relações devem referenciar IDs existentes

## 📝 Exemplo de Uso

1. **Carregar dados** do `dados/dados.csv`
2. **Navegar pelo menu** para explorar funcionalidades
3. **Adicionar pessoas** através da interface interativa
4. **Definir relações** parentais existentes
5. **Salvar alterações** para persistir os dados

## 🎯 Casos de Uso Típicos

- **Pesquisa Genealógica**: Construir e analisar linhagens familiares
- **Estudos Acadêmicos**: Análise de padrões familiares e hereditaridade
- **Preservação Histórica**: Documentação de árvores familiares complexas

---

**Desenvolvido com C++17 | Suporte Multi-plataforma | Licença MIT**
