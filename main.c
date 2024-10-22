#include <string.h>
#include <stdio.h>
#define clrscr() printf("\e[1;1H\e[2J")
#include <windows.h>

// DECLARANDO AS FUNÇÕES
int header();
int loginScreen();
int caixaScreen();
int vendasScreen();
void setConsoleColor();

// DECLARANDO A ESTRUTURA DE UM OBJETO ITEM A GRANEL
typedef struct {
    char* nome;
    float preco;
} granelItem;


// DECLARANDO AS VARIAVEIS
int loginCache = 0;
int escolhaCaixa;

char login[15];
char senha[15];
char userCaixa[15] = "Caixa";
char userVendas[15] = "Vendas";
char senhaCaixa[] = "senha123caixa";
char senhaVendas[] = "senha123vendas";

// DECLARANDO UM ARRAY DE OBJETOS ITEM A GRANEL
granelItem granelList[] = {
    {"Maca", 15.75},
    {"Tomate", 8.10},
    {"Cenoura", 5.29},
    {"Banana", 11.98},
    {"Pimentao", 13.55},
    {"Batata", 8.99}
};
size_t num_granelList = sizeof(granelList) / sizeof(granelItem);

// FUNÇÃO DE BUSCA DOS ITENS A GRANEL
granelItem* busca_linear(granelItem* granelList, size_t size, const char* nome) {
    for (size_t i=0; i<size; i++) {
        if (strcmp(granelList[i].nome, nome) == 0) {
            return &granelList[i];
        }
    }
    return NULL;
}

int main(){

    // GOTO MARCANDO O COMEÇO DO CODIGO E A FUNÇÃO CLRSCR QUE LIMPA O TERMINAL
    comeco:
    clrscr();
    // PASSANDO A VARIAVEL LOGIN CACHE PARA CASO HAJA UM ERRO O HEADER EXIBIR O ERRO.
    header(loginCache);

    // ARMAZENANDO O VALOR DE LOGIN SCREEN QUE RETORNARÁ CASO HAJA ALGUM ERRO OU OPÇÃO CORRETAMENTE SELECIONADA
    loginCache = loginScreen();

    // CASO O USUARIO LOGAR CORRETAMENTE NO USUARIO DO CAIXA A FUNÇÃO TERÁ RETORNADO 1 E EXECUTARA A FUNÇÃO DO CAIXA
    if(loginCache == 1){
        caixaScreen();
        goto comeco;
    }

    // CASO O USUARIO LOGAR CORRETAMENTE NO USUARIO DE VENDAS A FUNÇÃO TERÁ RETORNADO 2 E EXECUTARA A FUNÇÃO DE VENDAS
    if(loginCache == 2){
        vendasScreen();
        goto comeco;
    }
    // SE NÃO ELE LIMPARÁ O TERMINAL E IRÁ PRO COMEÇO
    clrscr();
    goto comeco;

    return 0;
}

int loginScreen(){

    // PEGANDO O LOGIN DO USUARIO 
    printf("Digite seu Login: ");
    fgets(login, sizeof(login), stdin);
    // E REMOVENDO O CHARACTER FINAL DA STRING (ISSO OCORRERA PARA TODA A VEZ QUE FORMOS RECEBER UMA STRING)
    login[strcspn(login, "\n")] = '\0';

    // CASO O LOGIN DO USUARIO FOR IGUAL O USUARIO DO CAIXA ELE PROSSEGUIRÁ PARA DIGITAR A SENHA
    if(strcmp(login, userCaixa) == 0){
        printf("\nDigite sua Senha: ");
        fgets(senha, sizeof(senha), stdin);
        senha[strcspn(senha, "\n")] = '\0';
        // ESSE GETCHAR É POR QUE ESTAVA DANDO UM ERRO DE STDIN BUFFER E FOI O UNICO JEITO QUE EU CONSEGUI ARRUMAR
        getchar();

        // CASO A SENHA TAMBÉM FOR IGUAL ELE LOGARA E RETORNARA QUE FOI LOGADO COM SUCESSO PARA A FUNÇÃO MAIN
        if(strcmp(senha, senhaCaixa) == 0){
            printf("Caixa LOGADO\n");
            return 1;
        }
        // CASO A SENHA ESTEJA ERRADA ELE RETORNARA O ERRO 403 QUE SIGNIFICA ACESSO NÃO CONCEDIDO
        return 403;
    }

    if(strcmp(login, userVendas) == 0){
        printf("\nDigite sua Senha: ");
        fgets(senha, sizeof(senha), stdin);
        senha[strcspn(senha, "\n")] = '\0';
        getchar();

        // CASO A SENHA TAMBÉM FOR IGUAL ELE LOGARA E RETORNARA QUE FOI LOGADO COM SUCESSO PARA A FUNÇÃO MAIN
        if(strcmp(senha, senhaVendas) == 0){
            printf("Vendas LOGADO\n");
            return 2;
        }
         // CASO A SENHA ESTEJA ERRADA ELE RETORNARA O ERRO 403 QUE SIGNIFICA ACESSO NÃO CONCEDIDO
        return 403;
    }

    // CASO NENHUM LOGIN BATA ELE RETORNARA O ERRO 404 QUE SIGNIFICA NÃO ENCONTRADO
    return 404;
}

int caixaScreen(){

    // LIMPA A TELA
    clrscr();

    // SETTA O GOTO DE INICIO
    caixa_menu:
    printf("\n[1] Listar Produtos");
    printf("\n[2] Selecionar Produto");
    printf("\n[3] Sair");
    printf("\nSua escolha: ");
    scanf("%d", &escolhaCaixa);
    getchar(); // PARA LIMPAR O BUFFER DE ENTRADA
    
    if(escolhaCaixa == 1){
        printf("-----------------------\n");
        printf("| Produto | Preco |\n");
        printf("-----------------------\n");
        // LOOP PELO ARRAY DE OBJETOS A GRANEL PRINTANDO CADA UM COM O ITERADOR CHAMADO "I"
        for (size_t i = 0; i < num_granelList; i++) {
            printf("| %s | R$ %.2f |\n", granelList[i].nome, granelList[i].preco);
        }
        printf("-----------------------\n");

        // VOLTA PARA O INICIO DA FUNÇÃO
        goto caixa_menu;
    }
    else if(escolhaCaixa == 2){

        // VARIAVEIS QUE CONTEM O NOME DO PRODUTO SELECIONADO E SUA QUANTIDADE (QUE O USUARIO VAI SETTAR)
        char produtoSelecionado[50];
        float quantidade;

        printf("\nDigite o nome do produto: ");
        fgets(produtoSelecionado, sizeof(produtoSelecionado), stdin);
        produtoSelecionado[strcspn(produtoSelecionado, "\n")] = '\0';

        // PROCURA NO ARRAY O NOME DO ITEM QUE O USUARIO DIGITOU E CASO TENHA ENCONTRADO GUARDA ELE NUMA VARIAVEL
        granelItem* item = busca_linear(granelList, num_granelList, produtoSelecionado);
        // CASO A BUSCA NÃO TENHA RETORNADO EM NULO ELE SEGUE
        if (item != NULL) {
            printf("Digite a quantidade em gramas: ");
            scanf("%f", &quantidade);
            getchar(); // PARA LIMPAR O BUFFER DE ENTRADA

            // FAZ O CALCULO DO PREÇO A GRANEL A CADA 100 GRAMAS
            float valorFinal = (quantidade / 100) * item->preco;

            // EXIBE O VALOR FINAL QUE FOI CALCULADO ANTERIORMENTE E O NOME DO RESULTADO DA BUSCA
            printf("\nProduto: %s\nValor Final: R$ %.2f\n", item->nome, valorFinal);
        } else {
            printf("\nProduto nao encontrado.\n");
        }
        goto caixa_menu;
    }
    else if(escolhaCaixa == 3){
        return 0;
    }
    else {
        printf("\nOpção inválida! Tente novamente.\n");
        goto caixa_menu;
    }

    return 0;
}

int vendasScreen() {
    // VARIAVEIS PARA ARMAZENAR O NOME DO PRODUTO, PREÇO, QUANTIDADE, TOTAL DA COMPRA, NÚMERO DE PRODUTOS E ESCOLHA DO USUÁRIO
    char produto[50];
    float preco, quantidade, total = 0.0;
    int numProdutos = 0;
    int escolha;

    // ESTRUTURA PARA ARMAZENAR PRODUTOS DA LISTA DE VENDAS
    struct {
        char nome[50];
        float preco;
        float quantidade;
    } listaProdutos[100];

    // LOOP PRINCIPAL QUE CONTINUA ATÉ QUE O USUÁRIO DECIDA SAIR
    while (1) {
        clrscr(); // LIMPA A TELA PARA UMA NOVA VENDA
        printf("Caixa de Vendas iniciado\n");

        // ZERA AS VARIAVEIS
        total = 0.0; 
        numProdutos = 0; 

        // LOOP PARA INSERIR PRODUTOS NA LISTA DE VENDAS
        while (1) {
            printf("\nDigite o nome do produto (ou '0' para encerrar): ");
            fgets(produto, sizeof(produto), stdin);
            produto[strcspn(produto, "\n")] = '\0'; 

            // SE O USUÁRIO DIGITAR '0', ENCERRA A INSERÇÃO DE PRODUTOS
            if (strcmp(produto, "0") == 0) {
                break;
            }

            // RECEBE O PREÇO E A QUANTIDADE DO PRODUTO
            printf("Digite o preco do produto: ");
            scanf("%f", &preco);
            printf("Digite a quantidade: ");
            scanf("%f", &quantidade);
            getchar(); // LIMPA O BUFFER DE ENTRADA

            // ARMAZENA OS DADOS DO PRODUTO NA LISTA
            strcpy(listaProdutos[numProdutos].nome, produto);
            listaProdutos[numProdutos].preco = preco;
            listaProdutos[numProdutos].quantidade = quantidade;
            numProdutos++; // AUMENTA O CONTADOR DE PRODUTOS

            // ACUMULA O TOTAL DA COMPRA
            total += preco * quantidade;
        }

        // IMPRIME O RESUMO DA COMPRA
        printf("\nResumo da compra:\n");
        for (int i = 0; i < numProdutos; i++) {
            printf("Produto: %s | Preco: R$ %.2f | Quantidade: %.2f\n",
                   listaProdutos[i].nome, listaProdutos[i].preco, listaProdutos[i].quantidade);
        }
        printf("\nValor total da compra: R$ %.2f\n", total);

        // LOOP PARA PERGUNTAR SE O USUÁRIO DESEJA REALIZAR OUTRA VENDA OU VOLTAR PARA A TELA DE LOGIN
        while (1) {
            printf("\n[1] Outra venda\n[2] Voltar para a tela de login\nEscolha: ");
            scanf("%d", &escolha);
            getchar(); // LIMPA O BUFFER DE ENTRADA

            if (escolha == 1) {
                break; // REINICIA O LOOP PARA UMA NOVA VENDA
            } else if (escolha == 2) {
                return 0; // RETORNA PARA A TELA DE LOGIN
            } else {
                printf("Opcao Invalida, Tente novamente.\n");
            }
        }
    }
}

int header(int errorType) {
    // EXIBE MENSAGENS DE ERRO BASEADO NO TIPO DE ERRO RECEBIDO
    if (errorType == 403) {
        setConsoleColor(4); // MUDA A COR DO CONSOLE PARA VERMELHO
        printf("\n\033[1mSENHA INCORRETA!\033[0m\n\n");
        setConsoleColor(7); // VOLTA A COR PADRÃO
    }
    if (errorType == 404) {
        setConsoleColor(4); // MUDA A COR DO CONSOLE PARA VERMELHO
        printf("\n\033[1mUSUARIO NAO ENCONTRADO!\033[0m\n\n");
        setConsoleColor(7); // VOLTA A COR PADRÃO
    }

    // EXIBE O CABEÇALHO DO SISTEMA
    setConsoleColor(1); // MUDA A COR DO CONSOLE PARA AZUL
    printf("  _   _ _  _ ___ ___      ___ ___ __  __        _   ___  ___   \n");
    printf(" | | | | \\| |_ _| _ \\    | _ \\_ _|  \\/  |      /_\\ |   \\/ __|  \n");
    printf(" | |_| | .` || ||  _/    |  _/| || |\\/| |     / _ \\| |) \\__ \\  \n");
    printf("  \\___/|_|\\_|___|_|      |_| |___|_|  |_|    /_/ \\_\\___/|___/  \n");
    printf("                                                               \n\n");
    
    // EXIBE UMA ARTE DE TEXTO COM O NOME DO SISTEMA
    setConsoleColor(2); // MUDA A COR DO CONSOLE PARA VERDE
    printf(" ... (texto omitido para brevidade) ...\n");

    setConsoleColor(7); // VOLTA A COR PADRÃO
    return 0;
}

void setConsoleColor(int color) {
    // FUNÇÃO PARA MUDAR A COR DO TEXTO NO CONSOLE DO WINDOWS
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}
