#include <stdio.h>
#include <stdlib.h>

#define MAX_ITENS 50  // Define o número máximo de itens na lista e no carrinho
#define MAX_NOME 50   // Define o tamanho máximo da descrição de um item

// Struct pra sinalizar um item na lista de itens
typedef struct {
    int id;                // Identificador do item
    char descricao[MAX_NOME]; // Nome ou descrição do item
    float preco;           // Preço do item
} Item;

// Struct pra sinalizar um item no carrinho junto com a quantidade.
typedef struct {
    Item produto; // O produto que estiver na lista
    int qtd;      // Quantidade do produto no carrinho
} CarrinhoCompras;

// Função para exibir o cabeçalho bonitinho
void exibirBanner() {
    printf("\n---------------------------\n");
    printf("-| SUPERMERCADO VIDA BOA |- \n");
    printf("---------------------------\n");
}

// Função pra cadastrar um novo item pra lista
void adicionarProduto(Item catalogo[MAX_ITENS], int *totalItens) {
    char continuarCadastro = 's';  // Variável de controle para continuar o cadastro de itens

    // For para cadastrar múltiplos itens até o usuário decidir parar ou atingir o limite de itens
    for (; continuarCadastro == 's' && *totalItens < MAX_ITENS; (*totalItens)++) {
        printf("\n-----------------------\n");
        printf("-| Cadastro de Itens |-\n");
        printf("-----------------------\n");

        Item novoProduto;
        novoProduto.id = *totalItens + 1;  // Define o ID automaticamente com base no total de itens cadastrados

        printf("Informe o nome do item: \n");
        getchar();  //getchar para o usuário informar o nome do item
        fgets(novoProduto.descricao, MAX_NOME, stdin);  //o usuário insere o nome

        printf("Informe o valor do item: \n");
        scanf("%f", &novoProduto.preco);  //o usuário insere o valor do item

        catalogo[*totalItens] = novoProduto;  // Adiciona o item à lista

        if (*totalItens < MAX_ITENS - 1) {
            printf("Deseja cadastrar mais itens? (s/n): ");
            getchar();  //getchar para o usuário escolher se quer ou não cadastrar mais itens
            scanf("%c", &continuarCadastro);  //o usuário insere a opção
        } else {
            printf("Limite de itens cadastrados atingido!\n");
        }
    }
}

// Função para exibir os produtos cadastrados na lista de itens
void mostrarProdutos(Item catalogo[MAX_ITENS], int totalItens) {
    if (totalItens == 0) {
        printf("\nNão há itens cadastrados.\n");
    } else {
        printf("\nLista de itens disponíveis:\n");
        for (int i = 0; i < totalItens; i++) {
            printf("Código: %d\nItem: %sPreço: R$ %.2f\n", catalogo[i].id, catalogo[i].descricao, catalogo[i].preco);
        }
    }
}

// Função para adicionar itens ao carrinho
void adicionarAoCarrinho(Item catalogo[MAX_ITENS], int totalItens, CarrinhoCompras carrinho[MAX_ITENS], int *totalCarrinho) {
    if (totalItens == 0) {
        printf("\nNão há itens disponíveis!\n");
        return;
    }

    char continuarAdicionando = 's';  // Variável de controle para continuar adicionando ao carrinho
    printf("\n-|     Carrinho INSANO    |- \n");

    //For para adicionar vários itens ao carrinho
    for (; continuarAdicionando == 's';) {
        int codigoProduto;
        printf("\nInforme o código do item que deseja adicionar: \n");
        scanf("%d", &codigoProduto);

        int produtoEncontrado = 0;  // Variável de controle para verificar se o item foi encontrado
        for (int i = 0; i < totalItens; i++) {
            if (catalogo[i].id == codigoProduto) {
                produtoEncontrado = 1;  // Marca que o item foi encontrado
                int jaTem = 0;

                // Verifica se o item já está no carrinho
                for (int j = 0; j < *totalCarrinho; j++) {
                    if (carrinho[j].produto.id == codigoProduto) {
                        carrinho[j].qtd++;  // Aumenta a quantidade do item no carrinho
                        printf("\nA quantidade de itens foi aumentada!\n");
                        jaTem = 1;
                        break;
                    }
                }

                // Se o item ainda não estiver no carrinho, o adiciona
                if (!jaTem) {
                    carrinho[*totalCarrinho].produto = catalogo[i];
                    carrinho[*totalCarrinho].qtd = 1;
                    (*totalCarrinho)++;
                    printf("O item %s foi adicionado ao carrinho\n", catalogo[i].descricao);
                }
                break;
            }
        }

        // Caso o produto não seja encontrado na lista de itens
        if (!produtoEncontrado) {
            printf("\nO item com o código %d não foi encontrado!\n", codigoProduto);
        }

        // Pergunta ao usuário se deseja adicionar mais itens
        printf("\nDeseja adicionar mais algum item ao carrinho? (s/n): ");
        getchar();  // Limpa o buffer
        scanf("%c", &continuarAdicionando);
    }
}

// Função para visualizar os itens do carrinho
void visualizarCarrinho(CarrinhoCompras carrinho[MAX_ITENS], int totalCarrinho) {
    if (totalCarrinho == 0) {
        printf("O carrinho está vazio!\n");
        return;
    }

    printf("\nCarrinho INSANO:\n");
    for (int i = 0; i < totalCarrinho; i++) {
        printf("Item: %sQuantidade: %d\n", carrinho[i].produto.descricao, carrinho[i].qtd);
    }
}

// Função para finalizar a compra
void finalizarCompra(CarrinhoCompras carrinho[MAX_ITENS], int *totalCarrinho) {
    float somaTotal = 0.0;
    if (*totalCarrinho == 0) {
        printf("O carrinho está vazio!\n");
        return;
    }

    printf("\nResumo da Compra:\n");

    // Exibe os itens no carrinho e calcula o valor total
    for (int i = 0; i < *totalCarrinho; i++) {
        float subtotal = carrinho[i].produto.preco * carrinho[i].qtd;
        printf("Item: %s| Quantidade: %d| Valor: R$ %.2f\n", carrinho[i].produto.descricao, carrinho[i].qtd, subtotal);
        somaTotal += subtotal;
    }

    // Exibe o valor total da compra
    printf("\nValor total da compra: R$ %.2f\n", somaTotal);

    // Detalha o pagamento via Pix
    printf("\nPagamento via chave Pix: CPF 055.160.251-17\n");
    printf("Você tem 2 minutos para enviar o valor R$ %.2f!\n", somaTotal);

    // Pergunta se o usuário deseja voltar ao menu ou finalizar a compra
    int escolha;
    printf("\nDeseja voltar ao menu para fazer algo? Digite (1). Se já pagou e deseja sair, Digite (2) ");
    scanf("%d", &escolha);

    if (escolha == 1) {
        printf("Voltando ao menu...\n");
    } else if (escolha == 2) {
        printf("Compra finalizada! VOLTE SEMPRE!\n");
        *totalCarrinho = 0;  // Esvazia o carrinho ao finalizar a compra
        exit(0);  // Encerra o programa
    } else {
        printf("Opção inválida! Voltando ao menu...\n");
    }
}

// Função para remover um item do carrinho
void removerDoCarrinho(CarrinhoCompras carrinho[MAX_ITENS], int *totalCarrinho) {
    if (*totalCarrinho == 0) {
        printf("\nO carrinho está vazio!\n");
        return;
    }

    int codigoProduto;
    printf("Informe o código do item que deseja remover do carrinho: ");
    scanf("%d", &codigoProduto);

    int i = 0; 
    int encontrou = 0;

    //While para encontrar e remover o item do carrinho
    while (i < *totalCarrinho && !encontrou) {
        if (carrinho[i].produto.id == codigoProduto) {
            encontrou = 1;
            carrinho[i].qtd--;

            // Se a quantidade do item chegar a 0, remove o item do carrinho
            if (carrinho[i].qtd == 0) {
                for (int j = i; j < *totalCarrinho - 1; j++) {
                    carrinho[j] = carrinho[j + 1];
                }
                (*totalCarrinho)--;
            }
            printf("Item removido com sucesso.\n");
        }
        i++;
    }

    // Se o item não for encontrado no carrinho
    if (!encontrou) {
        printf("O item com código %d não está no carrinho.\n", codigoProduto);
    }
}

// Função principal de exibição do menu e controle das opções
int exibirMenu(Item catalogo[MAX_ITENS], int *totalItens, CarrinhoCompras carrinho[MAX_ITENS], int *totalCarrinho) {
    int opcao;

    do {
        printf("-|     Menu INSANO    |- \n");
        printf("\n(Para escolher uma operação digite o número que ela indica!)\n");
        printf("\n | 1. Cadastrar Item *\n");
        printf(" | 2. Listar Itens *\n");
        printf(" | 3. Adicionar ao Carrinho *\n");
        printf(" | 4. Ver Carrinho *\n");
        printf(" | 5. Finalizar Compra *\n");
        printf(" | 6. Remover Produto do Carrinho *\n");
        printf(" | 7. Sair *\n");

        scanf("%d", &opcao);

        //swith para o usuário escolher a operação que desejar
        switch (opcao) {
            case 1:
                adicionarProduto(catalogo, totalItens);
                break;
            case 2:
                mostrarProdutos(catalogo, *totalItens);
                break;
            case 3:
                adicionarAoCarrinho(catalogo, *totalItens, carrinho, totalCarrinho);
                break;
            case 4:
                visualizarCarrinho(carrinho, *totalCarrinho);
                break;
            case 5:
                finalizarCompra(carrinho, totalCarrinho);
                break;
            case 6:
                removerDoCarrinho(carrinho, totalCarrinho);
                break;
            case 7:
                printf("Obrigado, VOLTE SEMPRE!\n");
                break;
            default:
                printf("Opção inválida! Digite novamente.\n");
        }

    } while (opcao != 7);  // Continua exibindo o menu até que a opção seja "7"

    return opcao;
}

// Função principal do programa
int main() {
    exibirBanner();  // Exibe o cabeçalho inicial

    Item catalogo[MAX_ITENS];  // Cria a lista de itens
    int totalItens = 0;  // Inicializa o total de itens no catálogo
    CarrinhoCompras carrinho[MAX_ITENS];  // Cria o carrinho de compras
    int totalCarrinho = 0;  // Inicializa o total de itens no carrinho

    exibirMenu(catalogo, &totalItens, carrinho, &totalCarrinho);  // Exibe o menu principal

   return 0;
}