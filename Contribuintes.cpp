#include <iostream>
#include <fstream>
#include <string>
#include "utilities.h"

using namespace std;

typedef struct pessoa{
    int id;
    int mes;
    int ano;
    float valor;
} ALUNO;

struct Node {
    ALUNO aluno;
    Node *proximo;
};

struct Contribuintes {
    Node *inicio;
    int tamanho;
};

void iniciar_contribuicao(Contribuintes*);
ALUNO nova_contribuicao();
void cadastrar_contribuicao(Contribuintes*, ALUNO);
bool verificar_TurmaCafe(int);
void mostrar_contribuintes(Contribuintes*);
void relatorio_curso(Contribuintes*);
void finalizar_contribuicao(Contribuintes*);

void main_contribuintes(int opcao)
{
    Contribuintes pagamentos;
    ALUNO aluno;

    iniciar_contribuicao(&pagamentos);

    do {
        switch (opcao) {
            case 4:
                cout << endl;
                /* Adicionar participantes */ 
                aluno = nova_contribuicao();
                /* Adicionar particimante (Teste Rápido) */
                // aluno = {12, 5, 2024, 7.50};
                cadastrar_contribuicao(&pagamentos, aluno);
                break;
            case 5:
                mostrar_contribuintes(&pagamentos);
                break;
            case 6:
                relatorio_curso(&pagamentos);
                break;
        }
        opcao = 0;
    } while (opcao != 0);

    finalizar_contribuicao(&pagamentos);
}

// Função para iniciar a estrutura de contribuições, carregando dados do arquivo se disponível
void iniciar_contribuicao(Contribuintes* payments){
    payments->inicio = NULL;
    payments->tamanho = 0;
    ifstream arquivo_entrada("contribuintes.txt");
    if (arquivo_entrada.is_open()) {
        ALUNO aluno;
        while (arquivo_entrada >> aluno.id >> aluno.mes >> aluno.ano >> aluno.valor) {
            cadastrar_contribuicao(payments, aluno);
        }
        arquivo_entrada.close();
    }
}

// Função para registrar uma nova contribuição inserida pelo usuário
ALUNO nova_contribuicao() {
    ALUNO aluno;

    cout << "Digite o ID: ";
    cin >> aluno.id;

    if (!verificar_TurmaCafe(aluno.id)) {
        cout << endl << "ID não foi encontrado" << endl << endl;
        aluno.id = -1;
        return aluno;
    }

    cout << "Digite o mês: ";
    cin >> aluno.mes;

    // Verifica se o mês está entre 1 e 12
    while (aluno.mes < 1 || aluno.mes > 12) {
        cout << "Mês inválido. Por favor, digite um valor entre 1 e 12: ";
        cin >> aluno.mes;
    }

    cout << "Digite o ano: ";
    cin >> aluno.ano;

    // Verifica se o ano é igual ou maior que 2024
    while (aluno.ano < 2024) {
        cout << "Ano inválido. Por favor, digite um valor igual ou maior que 2024: ";
        cin >> aluno.ano;
    }

    cout << "Digite o valor: ";
    cin >> aluno.valor;

    return aluno;
}

// Função para cadastrar uma nova contribuição na lista de pagamentos
void cadastrar_contribuicao(Contribuintes* payments, ALUNO aluno){
    if (aluno.id != -1){
        if (!verificar_TurmaCafe(aluno.id)){
            cout << endl << "ID não foi encontrado" << endl << endl;
        } else {
            Node *node = new Node;

            if (node == NULL){
                cout << "Acabou a memória" << endl;
                exit(1);
            }

            node->aluno = aluno;
            node->proximo = NULL;

            if (payments->inicio == NULL){
                payments->inicio = node;
            } else {
                Node *atual = payments->inicio;
                while (atual->proximo != NULL){
                    atual = atual->proximo;
                }
                atual->proximo = node;
            }
            payments->tamanho++;
        }
    }
}

// Função para verificar se um aluno está registrado na turma de café
bool verificar_TurmaCafe(int id_aluno){
    ifstream arquivo_entrada("participantes.txt");
    if (arquivo_entrada.is_open()){
        string line;
        ALUNO aluno;
        while (arquivo_entrada >> aluno.id)
        {
            // Ignorar o restante da linha
            std::getline(arquivo_entrada, line);
            // Verifica se o id inserido está no arquivo participantes.txt
            if (id_aluno == aluno.id){
                arquivo_entrada.close();
                return true;
            }
        }
        arquivo_entrada.close();
    }
    return false;
}

// Função para mostrar todos os contribuintes registrados
void mostrar_contribuintes(Contribuintes* payments){
    if (payments->inicio != NULL){
        cout << endl << "Quantidade de Contribuintes: " << payments->tamanho << endl;
        Node* node = payments->inicio;
        while (node != NULL){
            cout << "["<< node->aluno.id <<"]";
            node = node->proximo;
        }
        cout << endl << endl;
    } else {
        cout << "Sem Contribuintes no momento :(";
    }
}

// Função para gerar relatórios separados por curso dos contribuintes
void relatorio_curso(Contribuintes* payments) {
    if (payments->inicio != NULL) {
        Node* node = payments->inicio;
        string cursos[10];
        int qtd = 0;

        ifstream arquivo_entrada("participantes.txt");
        if (!arquivo_entrada.is_open()) {
            cout << "Erro ao abrir arquivo de entrada." << endl;
            return;
        }

        struct Participante {
            int id;
            string curso;
        };

        Participante participantes[100];
        int num_participantes = 0;

        string line, curso;
        ALUNO aluno;
        while (arquivo_entrada >> aluno.id >> line >> curso) {
            getline(arquivo_entrada, line); // Ignorar o restante da linha
            participantes[num_participantes++] = {aluno.id, curso};
        }
        arquivo_entrada.close();
        
        while (node != NULL) {
            for (int i = 0; i < num_participantes; ++i) {
                if (node->aluno.id == participantes[i].id) {
                    curso = participantes[i].curso;
                    
                    bool encontrado = false;
                    for (int j = 0; j < qtd; ++j) {
                        if (cursos[j] == curso) {
                            encontrado = true;
                            break;
                        }
                    }
                    
                    if (!encontrado) {
                        cursos[qtd++] = curso;
                        ofstream arqv("contribuintes_" + curso + ".txt", ios::trunc);
                        arqv.close();
                    }
                    
                    ofstream arquivo_saida("contribuintes_" + curso + ".txt", ios::app);
                    if (arquivo_saida.is_open()) {
                        arquivo_saida << node->aluno.id << " " << node->aluno.mes << " " << node->aluno.ano << " " << node->aluno.valor << endl;
                        arquivo_saida.close();
                    } else {
                        cout << "Erro ao abrir arquivo de saída." << endl;
                    }
                }
            }
            node = node->proximo;
        }
        cout << endl << "Relatorios gerados com sucesso!" << endl;
    } else {
        cout << "Sem Contribuintes no momento :(" << endl;
    }
}

// Função para finalizar e salvar os dados dos contribuintes em arquivo
void finalizar_contribuicao(Contribuintes* payments){
    ofstream arquivo_saida("contribuintes.txt");
    if (arquivo_saida.is_open()) {
        Node* atual = payments->inicio;
        while (atual) {
            arquivo_saida << atual->aluno.id << " " << atual->aluno.mes << " " << atual->aluno.ano << " " << atual->aluno.valor << endl;
            atual = atual->proximo;
        }
        arquivo_saida.close();
    } else {
        cout << "Erro ao abrir arquivo de saída." << endl;
    }

    Node* atual = payments->inicio;
    while (atual)
    {
        Node* proximo = atual->proximo;
        delete atual;
        atual = proximo;
    }
    payments->inicio = NULL;
    payments->tamanho = 0;
}
