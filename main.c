#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include <float.h>
#include <stdbool.h>
#include <windows.h>

// DECLARAÇÕES DAS FUNÇÕES (ASSOCIA NOME ÀS FUNÇÕES PARA CHAMÁ-LAS MAIS TARDE)
int header(int errorType);
int loginScreen();
int caixaScreen();
int vendasScreen();
bool validarInputInt(int* input, const char* prompt);
bool validarInputFloat(float* input, const char* prompt);

// DECLARANDO A ESTRUTURA DE UM OBJETO ITEM A GRANEL (DEFINE OS ATRIBUTOS DOS ITENS A GRANEL)
typedef struct {
    // NOME DO ITEM
    char* nome;  
    // PREÇO DO ITEM
    float preco; 
} granelItem;

typedef struct {
    // NOME DO ITEM
    char nome[50]; 
    // PREÇO DO ITEM
    float preco;   
    // PESO DO ITEM
    float peso;    
} historicoVenda;

// DECLARANDO AS VARIÁVEIS (INICIALIZA VARIÁVEIS USADAS AO LONGO DO PROGRAMA)

// VARIÁVEL QUE ARMAZENA O ESTADO DO LOGIN
int loginCache = 0; 

// VARIÁVEL PARA GUARDAR A ESCOLHA DO CAIXA
int escolhaCaixa; 

// ARMAZENA O LOGIN DO USUÁRIO
char login[15]; 

// ARMAZENA A SENHA DO USUÁRIO
char senha[15]; 

// NOME DO USUÁRIO DO CAIXA
char userCaixa[15] = "Caixa"; 

// NOME DO USUÁRIO DE VENDAS
char userVendas[15] = "Vendas"; 

// SENHA DO USUÁRIO DO CAIXA
char senhaCaixa[] = "senha123caixa"; 

// SENHA DO USUÁRIO DE VENDAS
char senhaVendas[] = "senha123vendas"; 

// DECLARANDO UM ARRAY DINÂMICO DE OBJETOS ITEM A GRANEL (LISTA DINÂMICA PARA GUARDAR OS ITENS A GRANEL)
granelItem* granelList = NULL; // PONTEIRO PARA A LISTA DE ITENS A GRANEL
size_t num_granelList = 0; // CONTADOR DE QUANTOS ITENS HÁ NA LISTA

historicoVenda* historicoVendas = NULL; // PONTEIRO PARA O HISTÓRICO DE VENDAS
size_t numHistoricoVendas = 0; // CONTADOR DE QUANTAS VENDAS ESTÃO NO HISTÓRICO

// FUNÇÃO PARA INICIALIZAR A LISTA DE ITENS A GRANEL (POPULA A LISTA COM ITENS E SEUS PREÇOS)
void inicializaGranelList() {
    // ALLOCA MEMÓRIA PARA 6 ITENS
    granelList = malloc(6 * sizeof(granelItem)); 
    // ADICIONA ITEM MACA COM PREÇO
    granelList[0] = (granelItem){"Maca", 15.75}; 
    // ADICIONA ITEM TOMATE COM PREÇO
    granelList[1] = (granelItem){"Tomate", 8.10}; 
    // ADICIONA ITEM CENOURA COM PREÇO
    granelList[2] = (granelItem){"Cenoura", 5.29}; 
    // ADICIONA ITEM BANANA COM PREÇO
    granelList[3] = (granelItem){"Banana", 11.98}; 
    // ADICIONA ITEM PIMENTÃO COM PREÇO
    granelList[4] = (granelItem){"Pimentao", 13.55}; 
    // ADICIONA ITEM BATATA COM PREÇO
    granelList[5] = (granelItem){"Batata", 8.99}; 
    // INFORMA QUE EXISTEM 6 ITENS NA LISTA
    num_granelList = 6; 
}

// FUNÇÃO DE BUSCA LINEAR (PROCURA UM ITEM PELO NOME NA LISTA)
granelItem* busca_linear(granelItem* granelList, size_t size, const char* nome) {
    // LOOP QUE PASSEA POR TODOS OS ITENS E COMPARA O NOME
    for (size_t i = 0; i < size; i++) {
        // SE O NOME DO ITEM CORRESPONDER
        if (strcmp(granelList[i].nome, nome) == 0) { 
            // RETORNA O PONTEIRO PARA O ITEM ENCONTRADO
            return &granelList[i]; 
        }
    }
    // SE NÃO ENCONTRAR O ITEM, RETORNA NULL
    return NULL; 
}

// FUNÇÃO PARA ADICIONAR UMA VENDA NO HISTÓRICO (ARMAZENA OS DADOS DE UMA VENDA)
void adicionarHistoricoVenda(const char* nome, float preco, float peso) {
    // REALOCA O ARRAY PARA GUARDAR UMA NOVA VENDA
    historicoVendas = realloc(historicoVendas, (numHistoricoVendas + 1) * sizeof(historicoVenda));
    // COPIA O NOME DA VENDA PARA O HISTÓRICO
    strcpy(historicoVendas[numHistoricoVendas].nome, nome);
    // ATRIBUI O PREÇO E O PESO DA VENDA AO HISTÓRICO
    historicoVendas[numHistoricoVendas].preco = preco;
    historicoVendas[numHistoricoVendas].peso = peso;
    // INCREMENTA O NÚMERO DE VENDAS NO HISTÓRICO
    numHistoricoVendas++; 
}

// FUNÇÃO PRINCIPAL DO PROGRAMA
int main() {
    // INICIALIZA A LISTA DE ITENS A GRANEL
    inicializaGranelList(); 
    
    // RÓTULO PARA VOLTAR AO INÍCIO
    comeco: 
    // CHAMA A FUNÇÃO PARA EXIBIR O CABEÇALHO DE ACORDO COM O LOGIN
    header(loginCache); 
    // CHAMA A FUNÇÃO DE TELA DE LOGIN E ARMAZENA O RESULTADO
    loginCache = loginScreen(); 

    // SE O LOGIN FOR DO CAIXA
    if(loginCache == 1) { 
        // CHAMA A TELA DO CAIXA
        caixaScreen(); 
        // VOLTA PARA O INÍCIO
        goto comeco; 
    }
    // SE O LOGIN FOR DE VENDAS
    if(loginCache == 2) { 
        // CHAMA A TELA DE VENDAS
        vendasScreen(); 
        // VOLTA PARA O INÍCIO
        goto comeco; 
    }
    // SE O LOGIN FOR INVÁLIDO, VOLTA AO INÍCIO
    goto comeco; 

    // FINALIZA O PROGRAMA
    return 0; 
}


// FUNÇÃO PARA TELA DE LOGIN (VERIFICA O LOGIN E A SENHA DO USUÁRIO)
int loginScreen() {
    // SOLICITA O LOGIN DO USUÁRIO
    printf("Digite seu Login: ");
    fgets(login, sizeof(login), stdin);
    login[strcspn(login, "\n")] = '\0';

    // VERIFICA SE O USUÁRIO É O CAIXA
    if(strcmp(login, userCaixa) == 0) {
        // SOLICITA A SENHA DO CAIXA
        printf("\nDigite sua Senha: ");
        fgets(senha, sizeof(senha), stdin);
        senha[strcspn(senha, "\n")] = '\0';

        // VERIFICA SE A SENHA DO CAIXA ESTÁ CORRETA
        if(strcmp(senha, senhaCaixa) == 0) {
            printf("Caixa LOGADO\n");
            return 1; // RETORNA 1 SE O LOGIN FOI BEM-SUCEDIDO
        }
        return 403; // RETORNA 403 SE A SENHA ESTIVER ERRADA
    }

    // VERIFICA SE O USUÁRIO É DE VENDAS
    if(strcmp(login, userVendas) == 0) {
        // SOLICITA A SENHA DO USUÁRIO DE VENDAS
        printf("\nDigite sua Senha: ");
        fgets(senha, sizeof(senha), stdin);
        senha[strcspn(senha, "\n")] = '\0';

        // VERIFICA SE A SENHA DE VENDAS ESTÁ CORRETA
        if(strcmp(senha, senhaVendas) == 0) {
            printf("Vendas LOGADO\n");
            return 2; // RETORNA 2 SE O LOGIN FOI BEM-SUCEDIDO
        }
        return 403; // RETORNA 403 SE A SENHA ESTIVER ERRADA
    }
    return 404; // RETORNA 404 SE O USUÁRIO NÃO FOR ENCONTRADO
}

// FUNÇÃO PARA A TELA DE CAIXA (MENU DO CAIXA)
int caixaScreen() {

    // MENU DE OPÇÕES DO CAIXA
    caixa_menu:
    printf("\n[1] Listar Produtos");
    printf("\n[2] Adicionar Produto");
    printf("\n[3] Remover Produto");
    printf("\n[4] Mostrar Historico de Vendas");
    printf("\n[5] Sair");

    // SOLICITA A ESCOLHA DO CAIXA
    if (!validarInputInt(&escolhaCaixa, "\nSua escolha: ")) {
        goto caixa_menu; // RETORNA AO MENU SE A ENTRADA FOR INVÁLIDA
    }

    // OPÇÃO PARA LISTAR OS PRODUTOS
    if (escolhaCaixa == 1) {
        // EXIBE A LISTA DE PRODUTOS A GRANEL
        printf("-----------------------\n");
        printf("| Produto | Preco |\n");
        printf("-----------------------\n");
        for (size_t i = 0; i < num_granelList; i++) {
            printf("| %s | R$ %.2f |\n", granelList[i].nome, granelList[i].preco);
        }
        printf("-----------------------\n");
        goto caixa_menu; // RETORNA AO MENU
    }
    // OPÇÃO PARA ADICIONAR UM PRODUTO
    else if (escolhaCaixa == 2) { // Adicionar Produto
        char novoProduto[50];
        float preco;

        // SOLICITA O NOME DO NOVO PRODUTO
        printf("\nDigite o nome do novo produto: ");
        fgets(novoProduto, sizeof(novoProduto), stdin);
        novoProduto[strcspn(novoProduto, "\n")] = '\0';

        // SOLICITA O PREÇO DO NOVO PRODUTO
        if (!validarInputFloat(&preco, "Digite o preco do produto: ")) {
            goto caixa_menu; // RETORNA AO MENU SE A ENTRADA FOR INVÁLIDA
        }

        // REALOCA O ARRAY PARA ADICIONAR O NOVO PRODUTO
        granelList = realloc(granelList, (num_granelList + 1) * sizeof(granelItem));
        granelList[num_granelList].nome = strdup(novoProduto);
        granelList[num_granelList].preco = preco;
        num_granelList++;

        // INFORMA QUE O PRODUTO FOI ADICIONADO COM SUCESSO
        printf("\nProduto adicionado com sucesso!\n");
        goto caixa_menu; // RETORNA AO MENU
    }
    // OPÇÃO PARA REMOVER UM PRODUTO
    else if (escolhaCaixa == 3) { // Remover Produto
        char produtoRemover[50];

        // SOLICITA O NOME DO PRODUTO A SER REMOVIDO
        printf("\nDigite o nome do produto a ser removido: ");
        fgets(produtoRemover, sizeof(produtoRemover), stdin);
        produtoRemover[strcspn(produtoRemover, "\n")] = '\0';

        // PROCURA O PRODUTO NA LISTA E O REMOVE
        for (size_t i = 0; i < num_granelList; i++) {
            if (strcmp(granelList[i].nome, produtoRemover) == 0) {
                free(granelList[i].nome); // LIBERA A MEMÓRIA DO NOME DO PRODUTO
                for (size_t j = i; j < num_granelList - 1; j++) {
                    granelList[j] = granelList[j + 1]; // REALOCA O RESTANTE DA LISTA
                }
                num_granelList--; // ATUALIZA O NÚMERO DE PRODUTOS
                granelList = realloc(granelList, num_granelList * sizeof(granelItem)); // REDUZ O TAMANHO DO ARRAY
                printf("\nProduto removido com sucesso!\n");
                goto caixa_menu; // RETORNA AO MENU
            }
        }
        printf("\nProduto nao encontrado.\n"); // INFORMA SE O PRODUTO NÃO FOI ENCONTRADO
        goto caixa_menu; // RETORNA AO MENU
    }
    // OPÇÃO PARA EXIBIR O HISTÓRICO DE VENDAS
    else if (escolhaCaixa == 4) { // Exibir histórico de vendas
        printf("\nHistorico de Vendas:\n");
        if (numHistoricoVendas == 0) {
            printf("Nenhuma venda realizada ainda.\n"); // INFORMA SE NÃO HÁ VENDAS REGISTRADAS
        } else {
            // EXIBE AS VENDAS REALIZADAS
            float total = 0;
            for (size_t i = 0; i < numHistoricoVendas; i++) {
                total += historicoVendas[i].preco;
                printf("Produto: %s | Valor Total: R$ %.2f | Peso: %.2f kg\n",
                       historicoVendas[i].nome, historicoVendas[i].preco, historicoVendas[i].peso);
            }
            printf("\nTOTAL: R$ %.2f\n", total);
        }
        goto caixa_menu; // RETORNA AO MENU
    }
    // OPÇÃO PARA SAIR
    else if (escolhaCaixa == 5) {
        return 0; // FINALIZA O PROGRAMA
    }
    // CASO A OPÇÃO SEJA INVÁLIDA
    else {
        printf("\nOpcao invalida! Tente novamente.\n"); // INFORMA QUE A OPÇÃO É INVÁLIDA
        goto caixa_menu; // RETORNA AO MENU
    }

    return 0;
}

// INICIA A TELA DE VENDAS
int vendasScreen() {
    // DECLARAÇÃO DAS VARIÁVEIS
    char produtoSelecionado[50];
    float peso, total = 0.0;
    int numProdutos = 0;
    int escolha;

    // ESTRUTURA PARA ARMAZENAR INFORMAÇÕES SOBRE OS PRODUTOS
    struct {
        char nome[50];
        float preco;
        float peso;
    } listaProdutos[100];

    // INÍCIO DO LAÇO PRINCIPAL DO SISTEMA DE VENDAS
    while (1) {
        // INFORMA QUE O CAIXA DE VENDAS FOI INICIADO
        printf("Caixa de Vendas iniciado\n");

        // REINICIA O VALOR TOTAL E O NÚMERO DE PRODUTOS A CADA NOVA VENDA
        total = 0.0;
        numProdutos = 0;

        // LAÇO PARA SELEÇÃO DE PRODUTOS
        while (1) {
            // EXIBE A LISTA DE PRODUTOS DISPONÍVEIS
            printf("\nProdutos Disponiveis:\n");
            for (size_t i = 0; i < num_granelList; i++) {
                // EXIBE O NOME E PREÇO DOS PRODUTOS DISPONÍVEIS
                printf("%s - R$ %.2f/kg\n", granelList[i].nome, granelList[i].preco);
            }
            fflush(stdin);  // LIMPA O BUFFER DE ENTRADA

            // SOLICITA AO USUÁRIO O NOME DO PRODUTO A SER SELECIONADO
            printf("Digite o nome do produto (ou '0' para encerrar): ");
            fgets(produtoSelecionado, sizeof(produtoSelecionado), stdin);
            produtoSelecionado[strcspn(produtoSelecionado, "\n")] = '\0'; // REMOVE A QUEBRA DE LINHA

            // SE O USUÁRIO DIGITAR '0', ENCERRA A VENDA
            if (strcmp(produtoSelecionado, "0") == 0) {
                break;
            }

            // BUSCA O PRODUTO SELECIONADO NA LISTA DE PRODUTOS DISPONÍVEIS
            granelItem* item = busca_linear(granelList, num_granelList, produtoSelecionado);
            if (item == NULL) {
                // CASO O PRODUTO NÃO SEJA ENCONTRADO, INFORMA O ERRO E VOLTA A PEDIR O NOME
                printf("Produto nao encontrado. Tente novamente.\n");
                continue;
            }

            // VALIDA O PESO INFORMADO PELO USUÁRIO
            if (!validarInputFloat(&peso, "Digite o peso em quilos: ")) {
                continue;
            }

            // CALCULA O VALOR FINAL BASEADO NO PESO E PREÇO DO PRODUTO
            float valorFinal = peso * item->preco;
            total += valorFinal; // ADICIONA O VALOR AO TOTAL

            // REGISTRA AS INFORMAÇÕES DO PRODUTO NA LISTA DE VENDAS
            strcpy(listaProdutos[numProdutos].nome, item->nome);
            listaProdutos[numProdutos].preco = valorFinal;
            listaProdutos[numProdutos].peso = peso;
            numProdutos++;

            // ADICIONA A VENDA AO HISTÓRICO
            adicionarHistoricoVenda(item->nome, valorFinal, peso);
        }

        // EXIBE O RESUMO DA COMPRA PARA O USUÁRIO
        printf("\nResumo da compra:\n");
        for (int i = 0; i < numProdutos; i++) {
            // EXIBE NOME, PREÇO E PESO DE CADA PRODUTO VENDIDO
            printf("Produto: %s | Preco: R$ %.2f | Peso: %.2f kg\n",
                   listaProdutos[i].nome, listaProdutos[i].preco, listaProdutos[i].peso);
        }
        printf("\nValor total da compra: R$ %.2f\n", total);

        // LAÇO PARA VALIDAR A ESCOLHA DO USUÁRIO SE DESEJA CONTINUAR OU SAIR
        while (1) {
            // SOLICITA A ESCOLHA DO USUÁRIO PARA CONTINUAR OU VOLTAR AO LOGIN
            if (!validarInputInt(&escolha, "\n[1] Outra venda\n[2] Voltar para a tela de login\nEscolha: ")) {
                continue;
            }
            if (escolha == 1) {
                // SE ESCOLHER 1, INICIA NOVA VENDA
                break;
            } else if (escolha == 2) {
                // SE ESCOLHER 2, RETORNA PARA A TELA DE LOGIN
                return 0; // Retorna para a tela de login
            } else {
                // SE A OPÇÃO FOR INVÁLIDA, INFORMA O ERRO E REPETE A OPÇÃO
                printf("Opção Inválida, Tente novamente.\n");
            }
        }
    }
}

// FUNÇÃO DE HEADER QUE EXIBE MENSAGENS DE ERRO E TÍTULO
int header(int errorType) {
    // VERIFICA O TIPO DE ERRO E EXIBE A MENSAGEM CORRESPONDENTE
    if (errorType == 403) {
        printf("\n\033[1mSENHA INCORRETA!\033[0m\n\n");
    }
    if (errorType == 404) {
        printf("\n\033[1mUSUARIO NAO ENCONTRADO!\033[0m\n\n");
    }

    // EXIBE O CABEÇALHO COM O NOME DO SISTEMA
    printf("  _   _ _  _ ___ ___      ___ ___ __  __        _   ___  ___   \n");
    printf(" | | | | \\| |_ _| _ \\    | _ \\_ _|  \\/  |      /_\\ |   \\/ __|  \n");
    printf(" | |_| | .` || ||  _/    |  _/| || |\\/| |     / _ \\| |) \\__ \\  \n");
    printf("  \\___/|_|\\_|___|_|      |_| |___|_|  |_|    /_/ \\_\\___/|___/  \n");
    printf("                                                               \n\n");

    // EXIBE O LOGO DO SISTEMA
    printf(" ___                             ___        .-.                                   ___      \n");
    printf("(   )                           (   )      /    \\                           .-.  (   )     \n");
    printf(" | | .-.     .--.    ___ .-.     | |_      | .`. ;   ___ .-.     ___  ___  ( __)  | |_     \n");
    printf(" | |/   \\   /    \\  (   )   \\   (   __)    | |(___) (   )   \\   (   )(   ) (''') (   __)   \n");
    printf(" |  .-. .  |  .-. ;  | ' .-. ;   | |       | |_      | ' .-. ;   | |  | |   | |   | |      \n");
    printf(" | |  | |  | |  | |  |  / (___)  | | ___  (   __)    |  / (___)  | |  | |   | |   | | ___  \n");
    printf(" | |  | |  | |  | |  | |         | |(   )  | |       | |         | |  | |   | |   | |(   ) \n");
    printf(" | |  | |  | |  | |  | |         | | | |   | |       | |         | |  | |   | |   | | | |  \n");
    printf(" | |  | |  | '  | |  | |         | ' | |   | |       | |         | |  ; '   | |   | ' | |  \n");
    printf(" | |  | |  '  `-' /  | |         ' `-' ;   | |       | |         ' `-'  /   | |   ' `-' ;  \n");
    printf("(___)(___)  `.__.'  (___)         `.__.   (___)     (___)         '.__.'   (___)   `.__.   \n");
    printf("                                                                                           \n");
    printf("                                                                                           \n");
    printf("\n");

    return 0;
}

// IMPLEMENTAÇÃO DAS FUNÇÕES DE VALIDAÇÃO

// FUNÇÃO PARA VALIDAR A ENTRADA DE NÚMEROS INTEIROS
bool validarInputInt(int* input, const char* prompt) {
    char buffer[100];

    // EXIBE O PROMPT PARA O USUÁRIO
    printf("%s", prompt);
    fgets(buffer, sizeof(buffer), stdin);  // LÊ A ENTRADA DO USUÁRIO

    // VERIFICA CADA CARACTERE DA ENTRADA PARA GARANTIR QUE SEJA UM DÍGITO OU NEWLINE
    for (int i = 0; buffer[i] != '\0'; i++) {
        if (!isdigit(buffer[i]) && buffer[i] != '\n') {
            // SE HOUVER CARACTERE NÃO NÚMERO, INFORMA O ERRO
            printf("Entrada inválida! Por favor, insira um número positivo.\n");
            return false;  // RETORNA FALSE SE HOUVER CARACTERE NÃO NÚMERO
        }
    }

    // CONVERTE A ENTRADA PARA INTEIRO
    *input = atoi(buffer);

    // VERIFICA SE O VALOR ESTÁ DENTRO DO INTERVALO VÁLIDO PARA INTEIROS
    if (*input < 0 || *input > INT_MAX) {
        // SE O VALOR ESTIVER FORA DO INTERVALO, INFORMA O ERRO
        printf("Entrada fora do intervalo permitido!\n");
        return false;
    }
    return true;  // RETORNA TRUE SE A ENTRADA FOR VÁLIDA
}

// FUNÇÃO PARA VALIDAR A ENTRADA DE NÚMEROS FLOAT
bool validarInputFloat(float* input, const char* prompt) {
    char buffer[100];
    
    // SOLICITA AO USUÁRIO QUE INSIRA O VALOR COM A MENSAGEM DEFINIDA EM 'PROMPT'
    printf("%s", prompt);
    fgets(buffer, sizeof(buffer), stdin);  // LÊ A ENTRADA DO USUÁRIO

    char* endPtr;
    *input = strtof(buffer, &endPtr);  // TENTA CONVERTER O VALOR PARA FLOAT

    // VERIFICA SE A CONVERSÃO FOI BEM-SUCEDIDA E SE O VALOR ESTÁ DENTRO DO INTERVALO PERMITIDO
    if (endPtr == buffer || *endPtr != '\n' || *input < 0 || *input > FLT_MAX) {
        // SE A ENTRADA NÃO FOR VÁLIDA, INFORMA O ERRO
        printf("Entrada invalida! Por favor, insira um valor positivo.\n");
        return false;  // RETORNA FALSE SE A ENTRADA NÃO FOR VÁLIDA
    }
    return true;  // RETORNA TRUE SE A ENTRADA FOR VÁLIDA
}
