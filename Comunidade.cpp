#include <iostream>
#include <fstream>
#include <string>
#include "utilities.h"

using namespace std;

typedef struct pessoa{
    int id;
    string nome;
    string curso;
    int semestre;
    int ano_ingresso;
} ALUNO;

struct Node {
    ALUNO aluno;
    Node *proximo;
};

struct TurmaCafe {
    Node *inicio;
    int tamanho;
};

void abrir_garrafa(TurmaCafe *);
ALUNO novo_participante();
void adicionar_participante(TurmaCafe *, ALUNO);
void mostrar_participantes(TurmaCafe *);
void localizar_editar_participantes(TurmaCafe *, int);
void editar_participante(ALUNO *);
void fechar_garrafa(TurmaCafe *);

int main()
{   // curso (DSM ou SI ou GE).
    TurmaCafe turma_cafe;
    ALUNO aluno;
    abrir_garrafa(&turma_cafe);
    int id_aluno, opcao = 0;
    do {
        cout << endl << "Menu Principal\n";
        cout << "1. Cadastrar Aluno\n";
        cout << "2. Editar Aluno\n";
        cout << "3. Mostrar Turma do Café\n";
        cout << "4. Cadastrar contribuição\n";
        cout << "5. Mostrar contribuintes\n";
        cout << "6. Relatório de Contribuintes por curso\n";
        cout << "0. Sair\n";
        cout << "Escolha uma opção: ";
        cin >> opcao;

        switch (opcao) {
            case 1:
                /* Adicionar participantes */ 
                aluno = novo_participante();
                /* Adicionar particimante (Teste Rápido) */
                // aluno = {1, "João", "DSM", 1, 2024};
                adicionar_participante(&turma_cafe, aluno);
                break;
            case 2:
                cout << "Digite o ID do aluno: ";
                cin >> id_aluno;
                localizar_editar_participantes(&turma_cafe, id_aluno);
                break;
            case 3:
                mostrar_participantes(&turma_cafe);
                break;
            case 4:
            case 5:
            case 6:
                main_contribuintes(opcao);
                break;
            case 0:
                cout << "Saindo...\n";
                break;
            default:
                cout << "Opção inválida!\n";
        }
    } while (opcao != 0);

    fechar_garrafa(&turma_cafe);
    return 0;
}

// Função para abrir o arquivo "participantes.txt" e carregar os participantes para a lista
void abrir_garrafa(TurmaCafe* turma){
    turma->tamanho = 0;
    turma->inicio = NULL;

    ifstream arquivo_entrada("participantes.txt");
    if (arquivo_entrada.is_open()) {
        ALUNO aluno;
        while (arquivo_entrada >> aluno.id >> aluno.nome >> aluno.curso >> aluno.semestre >> aluno.ano_ingresso) {
            adicionar_participante(turma, aluno);
        }
        arquivo_entrada.close();
    }
}

// Função para criar um novo participante com dados inseridos pelo usuário
ALUNO novo_participante(){
    ALUNO novoAluno;
    cout << "Nome do aluno: ";
    cin >> novoAluno.nome;
    cout << "Curso do aluno: ";
    cin >> novoAluno.curso;
    while (novoAluno.curso != "DSM" && novoAluno.curso != "SI" &&  novoAluno.curso != "GE") {
        cout << "Curso inválido. Por favor, digite os cursos disponiveis [DSM, SI ou GE]: ";
        cin >> novoAluno.curso;
    }
    cout << "Semestre do aluno: ";
    cin >> novoAluno.semestre;
    cout << "Ano de ingresso do aluno: ";
    cin >> novoAluno.ano_ingresso;

    return novoAluno;
}

// Função para adicionar um novo participante à lista da turma de café
void adicionar_participante(TurmaCafe* turma, ALUNO aluno){
    Node *node = new Node;
    if (node == NULL){
        cout << "Acabou a memória" << endl;
        exit(1);
    }
    node->aluno = aluno;
    node->aluno.id = turma->tamanho + 1;
    node->proximo = NULL;

    if (turma->inicio == NULL) {
        turma->inicio = node;
    } else {
        Node *atual = turma->inicio;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        atual->proximo = node;
    }
    turma->tamanho++;
}

// Função para mostrar todos os participantes da turma de café
void mostrar_participantes(TurmaCafe* turma){
    if (turma->inicio != NULL){
        cout << endl << "Quantidade de Participantes: " << turma->tamanho << endl;
        Node* node = turma->inicio;
        while (node != NULL){
            cout << "["<< node->aluno.nome <<"]";
            node = node->proximo;
        }
        cout << endl << endl;
    } else {
        cout << "Sem participantes no momento :(";
    }
}

// Função para editar informações de um participante
void editar_participante(ALUNO* aluno){
    string nome, curso, semestre, ano_ingresso;
    char alterar;

    cout << "Deseja alterar o nome (s/n)? ";
    cin >> alterar;
    if (alterar == 's' || alterar == 'S') {
        cout << "Digite o nome[" << aluno->nome << "]: ";
        cin >> nome;
        aluno->nome = (nome.empty()) ? aluno->nome : nome;
    }

    cout << "Deseja alterar o curso (s/n)? ";
    cin >> alterar;
    if (alterar == 's' || alterar == 'S') {
        cout << "Digite o curso[" << aluno->curso << "]: ";
        cin >> curso;
        while (curso != "DSM" && curso != "SI" &&  curso != "GE") {
            cout << "Curso inválido. Por favor, digite os cursos disponiveis [DSM, SI ou GE]: ";
            cin >> curso;
        }
        aluno->curso = (curso.empty()) ? aluno->curso : curso;
    }

    cout << "Deseja alterar o semestre (s/n)? ";
    cin >> alterar;
    if (alterar == 's' || alterar == 'S') {
        cout << "Digite o semestre[" << aluno->semestre << "]: ";
        cin >> semestre;
        aluno->semestre = (semestre.empty()) ? aluno->semestre : stoi(semestre);
    }

    cout << "Deseja alterar o Ano de Ingressão (s/n)? ";
    cin >> alterar;
    if (alterar == 's' || alterar == 'S') {
        cout << "Digite o Ano de Ingressão[" << aluno->ano_ingresso << "]: ";
        cin >> ano_ingresso;
        aluno->ano_ingresso = (ano_ingresso.empty()) ? aluno->ano_ingresso : stoi(ano_ingresso);
    }
}

// Função para localizar e editar informações de um participante pelo ID
void localizar_editar_participantes(TurmaCafe* turma, int id_aluno){
    if (turma->inicio != NULL){
        Node *node = turma->inicio;

        while (node != NULL){
            if (node->aluno.id == id_aluno){
                editar_participante(&node->aluno);
            }
            node = node->proximo;
        }
    } else {
        cout << "Sem participantes no momento :(";
    }
}

// Função para fechar a "garrafa", ou seja, salvar os participantes de volta no arquivo e liberar memória
void fechar_garrafa(TurmaCafe* turma) {
    ofstream arquivo_saida("participantes.txt");
    if (arquivo_saida.is_open()) {
        Node* atual = turma->inicio;
        while (atual) {
            arquivo_saida << atual->aluno.id << " " << atual->aluno.nome << " " << atual->aluno.curso << " " << atual->aluno.semestre << " " << atual->aluno.ano_ingresso << endl;
            atual = atual->proximo;
        }
        arquivo_saida.close();
    } else {
        cout << "Erro ao abrir arquivo de saída." << endl;
    }

    Node* atual = turma->inicio;
    while (atual) {
        Node* proximo = atual->proximo;
        delete atual;
        atual = proximo;
    }
    turma->inicio = nullptr;
    turma->tamanho = 0;
}
