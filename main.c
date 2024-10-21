#include <string.h> 
#include <stdio.h>
#define clrscr() printf("\e[1;1H\e[2J")
#include <windows.h>


int header();
int loginScreen();
int caixaScreen();
int vendasScreen(){return 0;};
void setConsoleColor();

typedef struct {
    char* nome;
    float preco;
} granelItem;

int loginCache = 0;
int escolhaCaixa;

char login[15];
char senha[15];
char userCaixa[15] = "Caixa";
char userVendas[15] = "Vendas";
char senhaCaixa[] = "senha123caixa";
char senhaVendas[] = "senha123vendas";


granelItem granelList[] = {
    {"Maca", 5.50},
    {"Tomate", 8.75},
    {"Cenoura", 4.20},
    {"Banana", 3.15},
    {"Pimentao", 2.30},
    {"Batata", 6.80}
};
size_t num_granelList = sizeof(granelList) / sizeof(granelItem);

granelItem* linear_search(granelItem* granelList, size_t size, const char* nome) {
    for (size_t i=0; i<size; i++) {
        if (strcmp(granelList[i].nome, nome) == 0) {
            return &granelList[i];
        }
    }
    return NULL;
}
int main(){

    comeco:

    header(loginCache);

    loginCache = loginScreen();
    if(loginCache == 1){
        caixaScreen();
        goto comeco;
    }

    if(loginCache == 2){
        vendasScreen();
        return 0;
    }

    clrscr();
    goto comeco;

    return 0;
}

int loginScreen(){

    printf("Digite seu Login: ");
    fgets(login, sizeof(login), stdin);
    login[strcspn(login, "\n")] = '\0';

    if(strcmp(login, userCaixa) == 0){
        printf("\nDigite sua Senha: ");
        fgets(senha, sizeof(senha), stdin);
        senha[strcspn(senha, "\n")] = '\0';

        if(strcmp(senha, senhaCaixa) == 0){
            printf("Caixa LOGADO\n");
            return 1;
        }
        return 403;
    }

    if(strcmp(login, userVendas) == 0){
        printf("\nDigite sua Senha: ");
        fgets(senha, sizeof(senha), stdin);
        senha[strcspn(senha, "\n")] = '\0';

        if(strcmp(senha, senhaVendas) == 0){
            printf("Vendas LOGADO\n");
            return 2;
        }
        return 403;
    }

    return 404;
}

int caixaScreen(){
    clrscr();

    caixa_menu:
    printf("\n[1] Listar Produtos");
    printf("\n[2] Selecionar Produto");
    printf("\n[3] Sair");
    printf("\nSua escolha: ");
    scanf("%d", &escolhaCaixa);
    getchar(); // Para limpar o buffer do teclado
    
    if(escolhaCaixa == 1){
        printf("-----------------------\n");
        printf("| Produto | Preco |\n");
        printf("-----------------------\n");
        for (size_t i = 0; i < num_granelList; i++) {
            printf("| %s | R$ %.2f |\n", granelList[i].nome, granelList[i].preco);
        }
        printf("-----------------------\n");
        goto caixa_menu;
    }
    else if(escolhaCaixa == 2){
        char produtoSelecionado[50];
        float quantidade;

        printf("\nDigite o nome do produto: ");
        fgets(produtoSelecionado, sizeof(produtoSelecionado), stdin);
        produtoSelecionado[strcspn(produtoSelecionado, "\n")] = '\0';

        granelItem* item = linear_search(granelList, num_granelList, produtoSelecionado);
        if (item != NULL) {
            printf("Digite a quantidade em gramas: ");
            scanf("%f", &quantidade);
            getchar(); // Para limpar o buffer do teclado

            float valorFinal = (quantidade / 100) * item->preco;
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

int header(int errorType){

    if(errorType == 403){
        setConsoleColor(4);
        printf("\n\033[1mSENHA INCORRETA!\033[0m\n\n");
        setConsoleColor(7);
    }
    if(errorType == 404){
        setConsoleColor(4);
        printf("\n\033[1mUSUARIO NAO ENCONTRADO!\033[0m\n\n");
        setConsoleColor(7);
    }

    setConsoleColor(1);
    printf("  _   _ _  _ ___ ___      ___ ___ __  __        _   ___  ___   \n");
    printf(" | | | | \| |_ _| _ \    | _ \_ _|  \/  |      /_\ |   \/ __|  \n");
    printf(" | |_| | .` || ||  _/    |  _/| || |\/| |     / _ \| |) \__ \  \n");
    printf("  \___/|_|\_|___|_|      |_| |___|_|  |_|    /_/ \_\___/|___/  \n");
    printf("                                                               \n\n");
    
    setConsoleColor(2);
    printf(" ___                             ___        .-.                                   ___      \n");
    printf("(   )                           (   )      /    \                           .-.  (   )     \n");
    printf(" | | .-.     .--.    ___ .-.     | |_      | .`. ;   ___ .-.     ___  ___  ( __)  | |_     \n");
    printf(" | |/   \   /    \  (   )   \   (   __)    | |(___) (   )   \   (   )(   ) (''') (   __)   \n");
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

    setConsoleColor(7);

    return 0;
}

void setConsoleColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}
