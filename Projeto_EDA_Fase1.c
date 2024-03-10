#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct elementos{
    int valor;
    int linha;
    int coluna;
} Elemento;

typedef struct matrizes{
    int num_linhas;
    int num_colunas;
    Elemento elementos;
    struct matrizes* seguinte;
} Matriz;

Matriz* criar_matriz() {
    Matriz* matriz = (Matriz*) malloc(sizeof(Matriz));
    matriz->num_linhas = 0;
    matriz->num_colunas = 0;
    return matriz;
}

Matriz* popular_matriz(Matriz* matriz) {
    Matriz* inicio = NULL; 
    Matriz* atual = NULL; 

    for (int i = 1; i <= matriz->num_linhas; i++) {
        for (int j = 1; j <= matriz->num_colunas; j++) {
            Matriz* novo_elemento = (Matriz*)malloc(sizeof(Matriz));
            if (novo_elemento != NULL) {
                novo_elemento->elementos.valor = rand() % 1000;
                novo_elemento->elementos.linha = i;
                novo_elemento->elementos.coluna = j;
                novo_elemento->seguinte = NULL; 

                if (inicio == NULL) {
                    inicio = novo_elemento; 
                    atual = novo_elemento; 
                } else {
                    atual->seguinte = novo_elemento; 
                    atual = novo_elemento; 
                }
            }
        }
    }
    return inicio; 
}

void listar_matriz(Matriz* matriz) {
    Matriz* aux = matriz;
    int flag_linha = 0;
    while(aux!=NULL){
        flag_linha = aux->elementos.linha;

        printf("%d\t", aux->elementos.valor);

        // printf("\n\nLinha: %d | Coluna: %d | Valor: %d\n",aux->elementos.linha, aux->elementos.coluna, aux->elementos.valor);

        aux = aux->seguinte;

        if (aux != NULL && aux->elementos.linha != flag_linha) {
            printf("\n");
        }
        
    }
}

void listar_elemento_matriz(Matriz* matriz, int linha, int coluna) {
    Matriz* aux = matriz;

    int encontrado = 0;
    while(aux!=NULL){
        if(aux->elementos.linha == linha && aux->elementos.coluna == coluna){
            encontrado = 1;
            printf("\n\nElemento (%d, %d): %d\n", linha, coluna, aux->elementos.valor);
            // printf("\n\nLinha: %d | Coluna: %d | Valor: %d\n",linha, coluna, aux->elementos.valor);
            exit(0);
        }
        
        aux = aux->seguinte;
    }

    if(encontrado == 0){
        printf("\n\nElemento (%d, %d) nao encontrado na matriz.\n", linha, coluna);
        exit;
    }
}

Matriz* alterar_elemento_matriz(Matriz* matriz, int linha, int coluna, int valor) {
    Matriz* aux = matriz;

    int valor_antigo = 0;
    
    while (aux != NULL) {
        if (aux->elementos.linha == linha && aux->elementos.coluna == coluna) {
            valor_antigo = aux->elementos.valor;
            aux->elementos.valor = valor;
            printf("\n\nElemento (%d, %d) alterado de %d para %d\n", linha, coluna, valor_antigo, aux->elementos.valor);
            return matriz;
        }
        aux = aux->seguinte;
    }
    
    printf("\n\nElemento (%d, %d) nao encontrado na matriz.\n", linha, coluna);
    return matriz;
}

int contar(Matriz* matriz){
    Matriz* aux = matriz;
    int count = 0;
    while(aux!=NULL){
        count++;
        aux = aux->seguinte;
    }
    return count;
}

Matriz* popular_matriz_txt(Matriz* matriz) {
    FILE *fptr;
    fptr = fopen("matriz2.txt", "r");

    char txtLinha[100];

    Matriz* inicio = NULL; 
    Matriz* atual = NULL; 

    int linhaCounter = 0;
    int colunaCounter = 0;
    int numElementosPorLinha = 0;

    if(fptr != NULL) {
        while (fgets(txtLinha, sizeof(txtLinha), fptr)) {
            // pointer para a guardar ultima substring encontrada
            char *valor_string = NULL;

            // token a linha inteira
            char *substring_atual = strtok(txtLinha, ";");

            linhaCounter++;
            colunaCounter = 0;

            while (substring_atual != NULL) {
                valor_string = substring_atual;
                int valor = atoi(valor_string);

                colunaCounter++;

                // printf("Valor: %d | Linha: %d | Coluna: %d\n", valor,linhaCounter,colunaCounter);

                Matriz* novo_elemento = (Matriz*)malloc(sizeof(Matriz));
                if (novo_elemento != NULL) {
                    novo_elemento->elementos.valor = valor;
                    novo_elemento->elementos.linha = linhaCounter;
                    novo_elemento->elementos.coluna = colunaCounter;
                    novo_elemento->seguinte = NULL; 

                    if (inicio == NULL) {
                        inicio = novo_elemento; 
                        atual = novo_elemento; 
                    } else {
                        atual->seguinte = novo_elemento; 
                        atual = novo_elemento; 
                    }
                }
                
                // da token a próxima substring
                substring_atual = strtok(NULL, ";");
            }

            if(linhaCounter == 1) {
                numElementosPorLinha = colunaCounter;
            }
            // printf("numElementosPorLinha: %d | colunaCounter: %d | linhaCounter: %d\n", numElementosPorLinha,colunaCounter,linhaCounter);
            if(linhaCounter >= 2 && numElementosPorLinha != colunaCounter){
                printf("Matriz invalida: numero de elementos por linha deve manter-se constante.\n");
                exit(0);
            }

            // printf("numElementosPorLinha: %d | linhaCounter: %d\n", numElementosPorLinha,linhaCounter);
        }
    } else {
        printf("Nao foi possivel abrir ficheiro.");
    }

    // Close the file
    fclose(fptr);

    // printf("Linha: %d | Coluna: %d\n",linhaCounter,colunaCounter);

    inicio->num_linhas = linhaCounter;
    inicio->num_colunas = colunaCounter;

    return inicio; 
}

Matriz* add_linha_coluna(Matriz* matriz) {
    Matriz* aux = matriz;

    printf("Adicionar linha (1) ou coluna (2):\n");
    int tipo_add;
    scanf("%d", &tipo_add);

    switch (tipo_add) {
        case 1: // Add Linha
            int nova_linha = -1;
            printf("Adicionar uma linha apos a linha... (insira um numero entre 1 e %d.)\n", matriz->num_linhas);
            scanf("%d", &nova_linha);

            if (nova_linha < 1 || nova_linha > matriz->num_linhas) {
                printf("Numero de linha selecionado invalido. Por favor selecione um numero entre 1 e %d.", matriz->num_linhas);
                exit(0);
            }

            int *nums_add_linha = (int *)malloc(matriz->num_colunas * sizeof(int));

            for (int i = 0; i < matriz->num_colunas; i++) {
                int num = 0;
                printf("Elemento %d:\n", i+1);
                scanf("%d", &num);
                nums_add_linha[i] = num;
            }

            int added_linha = 0;

            while (aux != NULL) {
                if (aux->elementos.linha == nova_linha && aux->elementos.coluna == matriz->num_colunas) {
                    for (int i = 0; i < matriz->num_colunas; i++) {
                        Matriz* novo_elemento = (Matriz*)malloc(sizeof(Matriz));
                        if (novo_elemento != NULL) {
                            novo_elemento->elementos.valor = nums_add_linha[i];
                            novo_elemento->elementos.linha = nova_linha+1;
                            novo_elemento->elementos.coluna = i+1;
                            novo_elemento->seguinte = aux->seguinte;
                            aux->seguinte = novo_elemento;
                            aux = novo_elemento;
                        }
                    }
                    matriz->num_linhas++;
                    added_linha = 1;
                }

                aux = aux->seguinte;
                if(aux != NULL && added_linha == 1){
                    aux->elementos.linha++;
                }
            }

            free(nums_add_linha);
            break;
        case 2: // Add Coluna
            int nova_coluna = -1;
            printf("Adicionar uma coluna apos a coluna... (insira um numero entre 1 e %d.)\n", matriz->num_colunas);
            scanf("%d", &nova_coluna);

            if (nova_coluna < 1 || nova_coluna > matriz->num_colunas) {
                printf("Numero de coluna selecionado invalido. Por favor selecione um numero entre 1 e %d.", matriz->num_colunas);
                exit(0);
            }

            int *nums_add_coluna = (int *)malloc(matriz->num_linhas * sizeof(int));

            for (int i = 0; i < matriz->num_linhas; i++) {
                int num = 0;
                printf("Elemento %d:\n", i+1);
                scanf("%d", &num);
                nums_add_coluna[i] = num;
            }

            while (aux != NULL) {
                if (aux->elementos.coluna == nova_coluna) {
                    Matriz* novo_elemento = (Matriz*)malloc(sizeof(Matriz));
                    if (novo_elemento != NULL) {
                        novo_elemento->elementos.valor = nums_add_coluna[aux->elementos.linha-1];
                        novo_elemento->elementos.linha = aux->elementos.linha;
                        novo_elemento->elementos.coluna = nova_coluna+1;
                        novo_elemento->seguinte = aux->seguinte;
                        aux->seguinte = novo_elemento;
                        aux = novo_elemento;
                    }
                }

                aux = aux->seguinte;
            }
            matriz->num_colunas++;

            free(nums_add_coluna);
            break;
        default:
            printf("Tipo de alteracao invalido. Selecione linha (1) ou coluna (2)");
            exit(0);
    }
    
    return matriz;
}

Matriz* remove_linha_coluna(Matriz* matriz) {
    Matriz* aux = matriz;

    int num_linhas = matriz->num_linhas;
    int num_colunas = matriz->num_colunas;

    printf("Remover linha (1) ou coluna (2):\n");
    int tipo_add;
    scanf("%d", &tipo_add);

    switch (tipo_add) {
        case 1: // Remove Linha
            int linha = -1;
            printf("Remover linha... (insira um numero entre 1 e %d.)\n", matriz->num_linhas);
            scanf("%d", &linha);

            if (linha < 1 || linha > matriz->num_linhas) {
                printf("Numero de linha selecionado invalido. Por favor selecione um numero entre 1 e %d.", matriz->num_linhas);
                exit(0);
            }

            Matriz* anterior = NULL;
            while (aux != NULL) {
                if (aux->elementos.linha == linha) {
                    if (anterior == NULL) {
                        matriz = aux->seguinte;
                    } else {
                        anterior->seguinte = aux->seguinte;
                    }

                    Matriz* temp = aux;
                    aux = aux->seguinte;
                    temp->seguinte = NULL;
                    free(temp);
                } else {
                    if(aux->elementos.linha > linha){
                        aux->elementos.linha--;
                    }
                    anterior = aux;
                    aux = aux->seguinte;
                }
            }
            break;
        case 2: // Remove Coluna
            int coluna = -1;
            printf("Remover coluna... (insira um numero entre 1 e %d.)\n", matriz->num_colunas);
            scanf("%d", &coluna);

            if (coluna < 1 || coluna > matriz->num_colunas) {
                printf("Numero de coluna selecionado invalido. Por favor selecione um numero entre 1 e %d.", matriz->num_linhas);
                exit(0);
            }

            Matriz* anterior_coluna = NULL;
            while (aux != NULL) {
                if (aux->elementos.coluna == coluna) {
                    if (anterior_coluna == NULL) {
                        matriz = aux->seguinte;
                    } else {
                        anterior_coluna->seguinte = aux->seguinte;
                    }

                    Matriz* temp = aux;
                    aux = aux->seguinte;
                    temp->seguinte = NULL;
                    free(temp);
                } else {
                    if(aux->elementos.coluna > coluna){
                        aux->elementos.coluna--;
                    }
                    anterior_coluna = aux;
                    aux = aux->seguinte;
                }
            }
            break;
        default:
            printf("Tipo de alteracao invalido. Selecione linha (1) ou coluna (2)");
            exit(0);
    }
    
    matriz->num_linhas = num_linhas;
    matriz->num_colunas = num_colunas-1;

    return matriz;
}

void apagar_matriz(Matriz* matriz) {
    free(matriz);
}

int main() {
    srand(time(NULL));
    Matriz* matriz = criar_matriz();
    matriz = popular_matriz_txt(matriz);
    printf("\nNum Linhas: %d | Num Colunas: %d",matriz->num_linhas,matriz->num_colunas);
    // matriz = popular_matriz(matriz);
    int count = contar(matriz);
    printf(" | Num Elementos: %d\n\n",count);
    listar_matriz(matriz);
    printf("\n\n");
    matriz = remove_linha_coluna(matriz);
    printf("\nNum Linhas: %d | Num Colunas: %d",matriz->num_linhas,matriz->num_colunas);
    // matriz = popular_matriz(matriz);
    count = contar(matriz);
    printf(" | Num Elementos: %d\n\n",count);
    listar_matriz(matriz);
    // matriz = alterar_elemento_matriz(matriz,1,2,502);
    // printf("\n");
    // listar_matriz(matriz);
    // printf("\n\n");
    // printf("\nTeste");
    // listar_elemento_matriz(matriz,4,4);

    return(0);
}