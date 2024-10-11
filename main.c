#include <string.h> 
#include <stdio.h>
#define clrscr() printf("\e[1;1H\e[2J")
#include <windows.h>

int header();
int loginScreen();
int caixaScreen();
int vendasScreen(){return 0;};
void setConsoleColor();

char login[15];
char senha[15];
char userCaixa[15] = "Caixa";
char userVendas[15] = "Vendas";
char senhaCaixa[] = "senha123caixa";
char senhaVendas[] = "senha123vendas";
int loginCache = 0;

int main(){

    comeco:

    header(loginCache);

    loginCache = loginScreen();
    if(loginCache == 1){
        caixaScreen();
        return 0;
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
    setConsoleColor(3);
    printf("   ___   _   _____  __   _   \n");
    printf("  / __| /_\\ |_ _\\ \\/ /  /_\\  \n");
    printf(" | (__ / _ \\ | | >  <  / _ \\ \n");
    printf("  \\___/_/ \\_\\___/_/\\_\\/_/ \\_\\\n");
    printf("                             \n");
    setConsoleColor(7);

    

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
    printf(" | | | | \\| |_ _| _ \\    | _ \\_ _|  \\/  |      /_\\ |   \\/ __|  \n");
    printf(" | |_| | .` || ||  _/    |  _/| || |\\/| |     / _ \\| |) \\__ \\  \n");
    printf("  \\___/|_|\\_|___|_|      |_| |___|_|  |_|    /_/ \\_\\___/|___/  \n");
    printf("                                                               \n\n");
    
    setConsoleColor(2);
    printf(" ___                             ___        .-.                                   ___      \n");
    printf("(   )                           (   )      /    \\                           .-.  (   )     \n");
    printf(" | | .-.     .--.    ___ .-.     | |_      | .`. ;   ___ .-.     ___  ___  ( __)  | |_     \n");
    printf(" | |/   \\   /    \\  (   )   \\   (   __)    | |(___) (   )   \\   (   )(   ) (''\") (   __)   \n");
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
