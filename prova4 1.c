#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARQUIVO_LIVROS "livros.txt"
#define MAX_LIVROS 1000
#define MAX_LINHA 256

typedef struct {
    int id;
    char titulo[100];
    char genero[50];
    char autor[100];
    char editora[100];
} Livro;

void adicionarLivro();
void listarLivros();
void buscarLivro();
void atualizarLivro();
void removerLivro();
void carregarLivros(Livro livros[], int *total);
void salvarLivros(Livro livros[], int total);
void mostrarLivro(Livro livro);

int main() {
    int opcao;

    do {
        printf("\nSistema de Gerenciamento de Livros\n");
        printf("1 - Adicionar um novo registro\n");
        printf("2 - Listar registros\n");
        printf("3 - Buscar um registro\n");
        printf("4 - Atualizar um registro\n");
        printf("5 - Remover um registro\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // Limpar buffer do enter

        switch (opcao) {
            case 1:
                adicionarLivro();
                break;
            case 2:
                listarLivros();
                break;
            case 3:
                buscarLivro();
                break;
            case 4:
                atualizarLivro();
                break;
            case 5:
                removerLivro();
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}

void adicionarLivro() {
    FILE *arquivo = fopen(ARQUIVO_LIVROS, "a+");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    Livro novoLivro;
    printf("Informe o ID do livro: ");
    scanf("%d", &novoLivro.id);
    getchar(); // Limpar buffer do enter
    printf("Informe o titulo: ");
    fgets(novoLivro.titulo, 100, stdin);
    strtok(novoLivro.titulo, "\n"); // Remover newline
    printf("Informe o genero: ");
    fgets(novoLivro.genero, 50, stdin);
    strtok(novoLivro.genero, "\n"); // Remover newline
    printf("Informe o autor: ");
    fgets(novoLivro.autor, 100, stdin);
    strtok(novoLivro.autor, "\n"); // Remover newline
    printf("Informe a editora: ");
    fgets(novoLivro.editora, 100, stdin);
    strtok(novoLivro.editora, "\n"); // Remover newline

    int opcao;
    printf("Deseja adicionar o livro no inicio ou no fim do arquivo?\n");
    printf("1 - Inicio\n");
    printf("2 - Fim\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opcao);

    fseek(arquivo, 0, SEEK_END); // Mover para o final do arquivo

    if (opcao == 1) {
        fseek(arquivo, 0, SEEK_SET); // Mover para o início do arquivo
    }

    fprintf(arquivo, "%d|%s|%s|%s|%s\n", novoLivro.id, novoLivro.titulo, novoLivro.genero, novoLivro.autor, novoLivro.editora);
    fclose(arquivo);

    printf("Livro adicionado com sucesso!\n");
}


void listarLivros() {
    FILE *arquivo = fopen(ARQUIVO_LIVROS, "r");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    Livro livros[MAX_LIVROS];
    int totalLivros = 0;
    char linha[MAX_LINHA];

    while (fgets(linha, sizeof(linha), arquivo) && totalLivros < MAX_LIVROS) {
        sscanf(linha, "%d|%99[^|]|%49[^|]|%99[^|]|%99[^\n]", &livros[totalLivros].id, livros[totalLivros].titulo, livros[totalLivros].genero, livros[totalLivros].autor, livros[totalLivros].editora);
        totalLivros++;
    }
    fclose(arquivo);

    int opcao;
    printf("Escolha o tipo de visualizacao:\n");
    printf("1 - Os 5 primeiros registros\n");
    printf("2 - Os 5 ultimos registros\n");
    printf("3 - Todos os registros\n");
    scanf("%d", &opcao);

    int i;
    switch (opcao) {
        case 1:
            for (i = 0; i < 5 && i < totalLivros; i++) {
                mostrarLivro(livros[i]);
            }
            break;
        case 2:
            for (i = (totalLivros > 5 ? totalLivros - 5 : 0); i < totalLivros; i++) {
                mostrarLivro(livros[i]);
            }
            break;
        case 3:
            for (i = 0; i < totalLivros; i++) {
                mostrarLivro(livros[i]);
            }
            break;
        default:
            printf("Opcao invalida!\n");
    }
}

void buscarLivro() {
    FILE *arquivo = fopen(ARQUIVO_LIVROS, "r");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    int id;
    printf("Informe o ID do livro a ser buscado: ");
    scanf("%d", &id);

    Livro livro;
    char linha[MAX_LINHA];
    int encontrado = 0;

    while (fgets(linha, sizeof(linha), arquivo)) {
        sscanf(linha, "%d|%99[^|]|%49[^|]|%99[^|]|%99[^\n]", &livro.id, livro.titulo, livro.genero, livro.autor, livro.editora);
        if (livro.id == id) {
            mostrarLivro(livro);
            encontrado = 1;
            break;
        }
    }
    fclose(arquivo);

    if (!encontrado) {
        printf("Livro com ID %d nao encontrado!\n", id);
    }
}

void atualizarLivro() {
    FILE *arquivo = fopen(ARQUIVO_LIVROS, "r+");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    Livro livros[MAX_LIVROS];
    int totalLivros = 0;
    char linha[MAX_LINHA];

    while (fgets(linha, sizeof(linha), arquivo) && totalLivros < MAX_LIVROS) {
        sscanf(linha, "%d|%99[^|]|%49[^|]|%99[^|]|%99[^\n]", &livros[totalLivros].id, livros[totalLivros].titulo, livros[totalLivros].genero, livros[totalLivros].autor, livros[totalLivros].editora);
        totalLivros++;
    }

    int id, encontrado = 0;
    printf("Informe o ID do livro a ser atualizado: ");
    scanf("%d", &id);
    getchar(); // Limpar buffer do enter

    for (int i = 0; i < totalLivros; i++) {
        if (livros[i].id == id) {
            printf("Informe o novo titulo: ");
            fgets(livros[i].titulo, 100, stdin);
            strtok(livros[i].titulo, "\n");
            printf("Informe o novo genero: ");
            fgets(livros[i].genero, 50, stdin);
            strtok(livros[i].genero, "\n");
            printf("Informe o novo autor: ");
            fgets(livros[i].autor, 100, stdin);
            strtok(livros[i].autor, "\n");
            printf("Informe a nova editora: ");
            fgets(livros[i].editora, 100, stdin);
            strtok(livros[i].editora, "\n");
            encontrado = 1;
            break;
        }
    }

    if (encontrado) {
        freopen(ARQUIVO_LIVROS, "w", arquivo);
        for (int i = 0; i < totalLivros; i++) {
            fprintf(arquivo, "%d|%s|%s|%s|%s\n", livros[i].id, livros[i].titulo, livros[i].genero, livros[i].autor, livros[i].editora);
        }
        printf("Livro atualizado com sucesso!\n");
    } else {
        printf("Livro com ID %d nao encontrado!\n", id);
    }

    fclose(arquivo);
}

void removerLivro() {
    FILE *arquivo = fopen(ARQUIVO_LIVROS, "r+");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    Livro livros[MAX_LIVROS];
    int totalLivros = 0;
    char linha[MAX_LINHA];

    while (fgets(linha, sizeof(linha), arquivo) && totalLivros < MAX_LIVROS) {
        sscanf(linha, "%d|%99[^|]|%49[^|]|%99[^|]|%99[^\n]", &livros[totalLivros].id, livros[totalLivros].titulo, livros[totalLivros].genero, livros[totalLivros].autor, livros[totalLivros].editora);
        totalLivros++;
    }

    int id, encontrado = 0;
    printf("Informe o ID do livro a ser removido: ");
    scanf("%d", &id);

    FILE *tempArquivo = fopen("temp.txt", "w");
    if (!tempArquivo) {
        perror("Erro ao abrir o arquivo temporario");
        fclose(arquivo);
        return;
    }

    for (int i = 0; i < totalLivros; i++) {
        if (livros[i].id != id) {
            fprintf(tempArquivo, "%d|%s|%s|%s|%s\n", livros[i].id, livros[i].titulo, livros[i].genero, livros[i].autor, livros[i].editora);
        } else {
            encontrado = 1;
        }
    }

    fclose(arquivo);
    fclose(tempArquivo);

    remove(ARQUIVO_LIVROS);
    rename("temp.txt", ARQUIVO_LIVROS);

    if (encontrado) {
        printf("Livro removido com sucesso!\n");
    } else {
        printf("Livro com ID %d nao encontrado!\n", id);
    }
}

void mostrarLivro(Livro livro) {
    printf("ID: %d\n", livro.id);
    printf("Titulo: %s\n", livro.titulo);
    printf("Genero: %s\n", livro.genero);
    printf("Autor: %s\n", livro.autor);
    printf("Editora: %s\n", livro.editora);
}
