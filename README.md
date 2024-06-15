# Turma do Café

Este é o projeto "Turma do Café" da Fatec Araras. O programa gerencia uma comunidade de entusiastas de café, controlando os participantes e suas contribuições financeiras.

## Funcionalidades

1. **Gerenciamento de Participantes:**
   - **Inserir novo participante:** Adicione novos membros à comunidade.
   - **Editar participante existente:** Modifique os dados dos membros (exceto o ID).
   - **Carregar participantes de arquivo:** Importe uma lista de participantes de um arquivo-texto.
   - **Salvar participantes em arquivo:** Exporte a lista de participantes para um arquivo-texto.

2. **Gerenciamento de Contribuições:**
   - **Cadastrar contribuição:** Registre contribuições financeiras dos membros.
   - **Salvar contribuições em arquivo:** Exporte a lista de contribuintes para um arquivo-texto.
   - **Salvar contribuições por curso em arquivos separados:** Exporte as contribuições separadas por curso para arquivos-texto distintos.

## Estrutura de Dados

### Participantes
- **ID:** Número inteiro
- **Nome:** Primeiro nome (string)
- **Semestre:** Semestre de ingresso
- **Ano de Ingresso:** Ano de ingresso na Fatec Araras
- **Curso:** DSM, SI, ou GE

### Contribuições
- **ID do Participante:** Número inteiro
- **Mês:** Número inteiro (1 a 12)
- **Ano:** Número inteiro (2024 ou posterior)
- **Valor da Contribuição:** Valor financeiro

## Menu Principal

1. Inserir novo participante
2. Editar participante existente
3. Carregar participantes de arquivo
4. Salvar participantes em arquivo
5. Cadastrar contribuição
6. Salvar contribuições em arquivo
7. Salvar contribuições por curso em arquivos separados

## Como Usar

1. Clone o repositório:
    ```sh
    git clone https://github.com/PedNeto/turma-do-cafe.git

    cd turma-do-cafe

2. Executando o programa (Linux):
    ```sh
    g++ Comunidade.cpp Contribuintes.cpp -o ProjCafe

    ./ProjCafe

## Agradecimentos

Este projeto foi desenvolvido sob a orientação do professor [Orlando Saraiva Jr.](https://github.com/orlandosaraivajr), responsável pela disciplina de Estrutura de Dados na Fatec Araras, como parte do programa acadêmico para a turma do 2º semestre.
