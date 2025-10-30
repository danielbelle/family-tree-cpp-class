# Uso de Florestas em vez de Árvores

Resumo objetivo sobre por que optar por uma estrutura em floresta (conjunto de
árvores) em modelos genealógicos, vantagens, desvantagens, complexidade das
operações, benefícios e limitações.

## Por que usar florestas em vez de árvores

- Bases genealógicas frequentemente contêm múltiplas linhagens desconectadas;
  uma floresta permite representar várias árvores independentes sem forçar uma
  raiz artificial única.
- Florestas acomodam dados incompletos ou parciais (linhagens isoladas,
  registros faltantes) sem exigir junções que distorçam relações reais.
- Suporta operações por linhagem: consultas, exportação e sincronização por
  árvore individual sem afetar outras.
- Facilita modelagem incremental: novas raízes podem ser adicionadas sem
  reorganizar toda a estrutura.
- Mantém propriedades de árvore por componente, preservando travessias simples e
  eficiência local.

## Vantagens

- Representação fiel de múltiplas linhagens independentes.
- Flexibilidade para dados incompletos: cada componente tem profundidade e
  cobertura próprias.
- Isolamento lógico: operações em uma árvore não exigem varredura de toda a base
  com índice adequado.
- Escalabilidade horizontal: particionamento e processamento independente de
  árvores.
- Facilita importação/mesclagem de fontes distintas, mantendo componentes
  separadas até confirmação de ligações.
- Travessias (BFS/DFS) continuam aplicáveis por componente com complexidade
  previsível relativa ao tamanho do componente.

## Desvantagens

- Gerenciamento de múltiplas raízes aumenta complexidade operacional (lista de
  raízes, coordenação de buscas).
- Consultas globais podem exigir percorrer todas as árvores da floresta (ou
  depender de índice global).
- Ligações entre componentes (casamentos entre linhagens diferentes) exigem
  reconciliação complexa e podem modificar topologia.
- Overhead adicional para rastrear componentes e índices; maior uso de memória.
- Maior complexidade conceitual para quem espera uma única árvore unificada.

## Complexidade das operações (floresta: soma sobre componentes relevantes)

- Criar pessoa: O(1)
- Criar família: O(1)
- Adicionar filho: O(1)
- Ligar família filha: O(1)
- Buscar por nome (com índice hash global): O(1)
- Buscar sem índice (varredura): O(n \* m) — n = famílias visitadas, m = média
  de filhos
- Listar ascendentes: O(h) — segue componente até raiz conhecida
- Listar descendentes de uma família: O(f) — visita subárvore daquela família
- Contar descendentes: O(f)
- Exibir árvore (BFS) por componente: O(f)
- Exibir floresta inteira: O(total de famílias)
- Destruir componente/árvore: O(f + p) para a componente destruída

## Benefícios específicos de usar florestas

- Modelagem realista de bases genealógicas grandes e heterogêneas.
- Ingestão incremental e paralela: validar/processar cada árvore isoladamente.
- Facilita auditoria e versionamento por componente.
- Melhora performance quando consultas são limitadas a subárvores (economia de
  I/O e CPU).
- Evita introduzir artefatos ao forçar uma única raiz; dados mantêm topologia
  natural.

## Limitações e cuidados

- Índice global (por id/nome) é essencial para consultas eficientes entre
  componentes; sem ele buscas globais são caras.
- Mesclagens entre componentes exigem heurísticas e validação (deduplicação de
  pessoas/famílias).
- Entrelaçamentos reais (casamentos que conectam árvores) podem exigir decisão
  de manter árvore, transformar em DAG ou permitir grafo — cada opção afeta
  algoritmos.
- Gerenciamento de memória e liberação segura de entidades compartilhadas é
  necessário.
- Identidade consistente: nomes não são identificadores únicos — usar ids
  estáveis e políticas de deduplicação.
- Análises que cruzam várias árvores têm complexidade maior e podem exigir
  estratégias específicas (índices, pré-processamento).

## Conclusão

Optar por florestas é recomendado quando a base genealógica é heterogênea,
parcial ou composta por múltiplas linhagens independentes — traz flexibilidade,
isolamento e escalabilidade — mas exige índices, políticas de mesclagem e
cuidados com identidade/consistência para evitar sobrecarga e resultados
incorretos.
