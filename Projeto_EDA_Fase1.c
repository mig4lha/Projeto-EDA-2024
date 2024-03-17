#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

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

void limpar_terminal() {
    #ifdef _WIN32 
        //Windows
        system("cls");
    #else
        //Linux
        system("clear"); 
    #endif
}

void limpar_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

Matriz* criar_matriz() {
    Matriz* matriz = (Matriz*) malloc(sizeof(Matriz));
    matriz->num_linhas = 0;
    matriz->num_colunas = 0;
    return matriz;
}

void apagar_matriz(Matriz* matriz) {
    free(matriz);
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

        // printf("\n\nLinha: %d | Coluna: %d | Valor: %d\n",aux->elementos.linha, aux->elementos.coluna, aux->elementos.valor);

        printf("%d\t", aux->elementos.valor);

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

void guardar_matriz_txt(Matriz* matriz) {
    FILE *f = fopen("matriz_modificada.txt", "w");
    if (f == NULL)
    {
        printf("Nao foi possivel abrir ficheiro.\n");
        exit(0);
    }

    Matriz* aux = matriz;
    int flag_linha = 0;

    while(aux!=NULL){
        flag_linha = aux->elementos.linha;
        // printf("\n\nLinha: %d | Coluna: %d | Valor: %d\n",aux->elementos.linha, aux->elementos.coluna, aux->elementos.valor);
        if(flag_linha == 1 && aux->elementos.coluna == matriz->num_colunas) {
            fprintf(f, "%d\n", aux->elementos.valor);
        } else if(aux->elementos.coluna == matriz->num_colunas) {
            fprintf(f, "%d\n", aux->elementos.valor);
        } else{
            fprintf(f, "%d;", aux->elementos.valor);
        }

        aux = aux->seguinte;        
    }

    fclose(f);
}

Matriz* alterar_elemento_matriz(Matriz* matriz) {
    Matriz* aux = matriz;

    int linha = 0;
    int coluna = 0;
    int valor = 0;

    printf("Selecione uma coordenada linha para alterar:\n");
    scanf("%d",&linha);
    printf("\nSelecione uma coordenada coluna para alterar:\n");
    scanf("%d",&coluna);
    printf("\nSelecione um novo valor para o elemento:\n");
    scanf("%d",&valor);

    int valor_antigo = 0;
    int encontrado = 0;
    
    while (aux != NULL) {
        if (aux->elementos.linha == linha && aux->elementos.coluna == coluna) {
            valor_antigo = aux->elementos.valor;
            aux->elementos.valor = valor;
            encontrado = 1;
            limpar_terminal();
            printf("\nElemento (%d, %d) alterado de %d para %d\n", linha, coluna, valor_antigo, aux->elementos.valor);
            getchar();
        }
        aux = aux->seguinte;
    }
    
    if(encontrado == 0){
        limpar_terminal();
        printf("\nElemento (%d, %d) nao encontrado na matriz.\n", linha, coluna);
        getchar();
    }

    // guardar_matriz_txt(matriz);

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
        printf("Nao foi possivel abrir ficheiro. Por favor crie um ficheiro 'matriz.txt' no diretorio do projeto para comecar.\nPrima ENTER para terminar o processo.");
        getchar();
        exit(0);
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

    int num_linhas = matriz->num_linhas;
    int num_colunas = matriz->num_colunas;

    printf("Adicionar linha (1) ou coluna (2):\n");
    int tipo_add;
    scanf("%d", &tipo_add);

    switch (tipo_add) {
        case 1: // Add Linha
            int nova_linha = -1;
            printf("Adicionar uma linha apos a linha... (insira um numero entre 0 e %d.)\n", matriz->num_linhas);
            scanf("%d", &nova_linha);

            if (nova_linha < 0 || nova_linha > matriz->num_linhas) {
                printf("Numero de linha selecionado invalido. Por favor selecione um numero entre 0 e %d.", matriz->num_linhas);
                exit(0);
            }

            int *nums_add_linha = (int *)malloc(matriz->num_colunas * sizeof(int));

            for (int i = 0; i < matriz->num_colunas; i++) {
                int num = 0;
                printf("Elemento %d:\n", i+1);
                scanf("%d", &num);
                nums_add_linha[i] = num;
            }

            limpar_input_buffer();

            int added_linha = 0;

            if (nova_linha == 0) {
                for (int i = matriz->num_colunas; i > 0 ; i--) {
                    Matriz* novo_elemento = (Matriz*)malloc(sizeof(Matriz));
                    if (novo_elemento != NULL) {
                        novo_elemento->elementos.valor = nums_add_linha[i-1];
                        novo_elemento->elementos.linha = 1;
                        novo_elemento->elementos.coluna = i;
                        novo_elemento->seguinte = aux;
                        aux = novo_elemento;
                    }
                }

                Matriz* linhas_seguintes = aux;
                
                int skip_counter = 0;
                while (linhas_seguintes != NULL) {
                    if(skip_counter <= num_colunas){
                        skip_counter++;
                    }
                    if(skip_counter > num_colunas){
                        linhas_seguintes->elementos.linha++;
                    }
                    linhas_seguintes = linhas_seguintes->seguinte;
                }

                matriz = aux;

                matriz->num_linhas = num_linhas+1;
                matriz->num_colunas = num_colunas;

            } else {
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

    // guardar_matriz_txt(matriz);
    
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

            matriz->num_linhas = num_linhas-1;
            matriz->num_colunas = num_colunas;

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

            matriz->num_linhas = num_linhas;
            matriz->num_colunas = num_colunas-1;

            break;
        default:
            printf("Tipo de alteracao invalido. Selecione linha (1) ou coluna (2)");
            exit(0);
    }

    // guardar_matriz_txt(matriz);

    return matriz;
}

int encontrar_menor_valor_linha_matriz(int *elementos_linha, int counter_linha, int num_colunas) {
    int menor_elemento = elementos_linha[1];
    int coluna = 1;
    int i = 1;

    while(i<=num_colunas){
        if(menor_elemento > elementos_linha[i]){
            menor_elemento = elementos_linha[i];
            coluna = i;
        }
        i++;
    }

    printf("Menor elemento: %d | Linha: %d | Coluna: %d\n", menor_elemento,counter_linha,coluna);

    return coluna;
}

int valor_elemento_matriz(Matriz* matriz, int linha, int coluna){
    Matriz* aux = matriz;
    while (aux != NULL) {
        if (aux->elementos.linha == linha && aux->elementos.coluna == coluna) {
            return aux->elementos.valor;
        }
        aux = aux->seguinte;
    }
}

int calcular_soma_maxima_possivel(Matriz* matriz) {
    Matriz* matriz_calculo = criar_matriz();
    matriz_calculo = popular_matriz_txt(matriz);

    Matriz* aux = matriz_calculo;
    Matriz* aux2 = matriz_calculo;

    int somatorio = 0;
    int *menor_elementos_linhas = (int *)malloc(matriz->num_linhas * sizeof(int));
    int counter_linha = 1;

    while (aux != NULL)
    {
        int *elementos_linha = (int *)malloc(matriz->num_colunas * sizeof(int));

        for (int i = 1; i <= matriz->num_colunas; i++) {
            elementos_linha[i] = aux->elementos.valor;
            aux = aux->seguinte;
        }

        for (int i = 1; i <= matriz->num_colunas; i++) {
            printf("Elemento %d: %d\n", i, elementos_linha[i]);
        }

        // O menor elemento da linha está a ser guardado no index counter_linha 
        // e está posicionado na coluna retornada pela função
        // menor_elementos_linhas[linha] = coluna
        menor_elementos_linhas[counter_linha] = encontrar_menor_valor_linha_matriz(elementos_linha, counter_linha, matriz->num_colunas);
        counter_linha++;
    }

    printf("\nMenores elementos:\n");
    for (int h = 1; h <= matriz->num_linhas; h++)
    {
        printf("Linha: %d | Coluna: %d\n", h,menor_elementos_linhas[h]);
    }
    printf("\n");

    int menor_elemento_da_linha = 0;
    int linha_anterior = 1;
    while (aux2 != NULL)
    {
        printf("Linha: %d | Linha anterior: %d | Coluna: %d | Elemento: %d\n",aux2->elementos.linha,linha_anterior,aux2->elementos.coluna,aux2->elementos.valor);
        if(menor_elemento_da_linha == 0 || linha_anterior != aux2->elementos.linha){
            menor_elemento_da_linha = valor_elemento_matriz(aux2,aux2->elementos.linha,menor_elementos_linhas[aux2->elementos.linha]);
            // printf("\n%d\n", valor_elemento_matriz(aux2,aux2->elementos.linha,menor_elementos_linhas[aux2->elementos.linha]));
        }
        if(menor_elementos_linhas[aux2->elementos.linha] != aux2->elementos.coluna){
            aux2->elementos.valor = aux2->elementos.valor - menor_elemento_da_linha;
        } else {
            aux2->elementos.valor = 0;
        }
        if(aux2 != NULL && aux2->elementos.linha != linha_anterior){
            linha_anterior = aux2->elementos.linha;
        }
        aux2 = aux2->seguinte;
    }

    printf("\n");
    listar_matriz(matriz_calculo);
    printf("\n");
    
    // apagar_matriz(matriz_calculo);

    return(somatorio);
}

void menu(Matriz* matriz) {
    limpar_terminal();
    printf("Selecione uma opcao:\n\n");
    printf("1. Listar matriz\n");
    printf("2. Alterar elemento da matriz\n");
    printf("3. Adicionar linha/coluna da matriz\n");
    printf("4. Remover linha/coluna da matriz\n");
    printf("5. Calcular somatorio maximo possível\n");
    printf("6. Sair\n\n");

    int escolha = 0;
    int count = 0;

    printf("Escolha: ");
    scanf("%d", &escolha);
    limpar_input_buffer();

    limpar_terminal();

    switch (escolha)
    {
    case 1:        
        printf("\nNum Linhas: %d | Num Colunas: %d",matriz->num_linhas,matriz->num_colunas);
        count = contar(matriz);
        printf(" | Num Elementos: %d\n\n",count);
        listar_matriz(matriz);
        printf("\n\nPressione ENTER para continuar.");
        getchar();
        menu(matriz);
        break;
    case 2:
        printf("\nNum Linhas: %d | Num Colunas: %d",matriz->num_linhas,matriz->num_colunas);
        count = contar(matriz);
        printf(" | Num Elementos: %d\n\n",count);
        listar_matriz(matriz);
        printf("\n\n");
        matriz = alterar_elemento_matriz(matriz);
        printf("\nNum Linhas: %d | Num Colunas: %d",matriz->num_linhas,matriz->num_colunas);
        count = contar(matriz);
        printf(" | Num Elementos: %d\n\n",count);
        listar_matriz(matriz);
        printf("\n\nPressione ENTER para continuar.");
        getchar();
        menu(matriz);
        break;
    case 3:
        printf("\nNum Linhas: %d | Num Colunas: %d",matriz->num_linhas,matriz->num_colunas);
        count = contar(matriz);
        printf(" | Num Elementos: %d\n\n",count);
        listar_matriz(matriz);
        printf("\n\n");
        matriz = add_linha_coluna(matriz);
        printf("\nNum Linhas: %d | Num Colunas: %d",matriz->num_linhas,matriz->num_colunas);
        count = contar(matriz);
        printf(" | Num Elementos: %d\n\n",count);
        listar_matriz(matriz);
        printf("\n\nPressione ENTER para continuar.");
        getchar();
        menu(matriz);
        break;
    case 4:
        printf("\nNum Linhas: %d | Num Colunas: %d",matriz->num_linhas,matriz->num_colunas);
        count = contar(matriz);
        printf(" | Num Elementos: %d\n\n",count);
        listar_matriz(matriz);
        printf("\n\n");
        matriz = remove_linha_coluna(matriz);
        printf("\nNum Linhas: %d | Num Colunas: %d",matriz->num_linhas,matriz->num_colunas);
        count = contar(matriz);
        printf(" | Num Elementos: %d\n\n",count);
        listar_matriz(matriz);
        printf("\n\nPressione ENTER para continuar.");
        getchar();
        menu(matriz);
    case 5:
        printf("\nNum Linhas: %d | Num Colunas: %d",matriz->num_linhas,matriz->num_colunas);
        count = contar(matriz);
        printf(" | Num Elementos: %d\n\n",count);
        listar_matriz(matriz);
        printf("\n\n");
        int somatorio = calcular_soma_maxima_possivel(matriz);
        printf("\nSoma maxima possivel dos inteiros: %d",somatorio);
        printf("\n\nPressione ENTER para continuar.");
        getchar();
        menu(matriz);
        break;
    case 6:
        exit(0);
        break;
    default:
        printf("Escolha invalida. Pressione ENTER para recomecar.");
        getchar();
        menu(matriz);
        break;
    }

}

void info () {
    limpar_terminal();
    printf("Projeto de Avaliação - Estrutura de Dados Avançadas\n");
    printf("Fase 1: Linked Lists\n\n");

    printf("Importante: O programa ira ler um ficheiro de texto de nome 'matriz.txt' presente no diretorio do projeto!\n\n\n");
    
    printf("1. Continuar\n");
    printf("2. Sair\n\n");

    int escolha = 0;

    printf("Escolha: ");
    scanf("%d", &escolha);
    limpar_input_buffer();

    limpar_terminal();

    switch (escolha)
    {
    case 1:
        Matriz* matriz = criar_matriz();
        matriz = popular_matriz_txt(matriz);
        menu(matriz);
        break;
    case 2:
        exit(0);
        break;
    default:
        printf("Escolha invalida. Pressione ENTER para recomecar.");
        getchar();
        info();
        break;
    }
}

int main() {
    srand(time(NULL));

    info();

    return(0);
}