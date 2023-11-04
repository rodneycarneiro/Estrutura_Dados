/* Autor....: Rodney Carneiro
   Data.....: 11/10/2023
   Objetivo.: Cadastrar e consultar cliente
*/

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>
#include <time.h>
#include <conio.h>

// Definição Estruturas de dados
typedef struct
{
    int cd_cliente;
    char nm_cliente[50];
    char ds_endereco[50];
    int nr_numero;
    char nr_documento[20];
    char ds_cidade[50];
    char cd_uf[05];
    char dt_cadastro[19];
    char nr_telefone[15];
} reg_cliente;

typedef struct TipoItem *TipoApontador;

typedef struct TipoItem
{
    reg_cliente conteudo;
    TipoApontador proximo;
} TipoItem;

typedef struct
{
    TipoApontador Primeiro;
    TipoApontador Ultimo;
} TipoLista;

// Funcao para posicionar o cursor em um determinado ponto da Tela
void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = (short)x;
    coord.Y = (short)y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Mostra a Tela Padrao
void tela()
{
    int t;
    system("cls");
    gotoxy(01, 01);
    printf("+-----------------------------------------------------------------------------+");
    gotoxy(01, 02);
    printf("| UNICV");
    gotoxy(60, 02);
    printf("Estrutura de Dados |");
    gotoxy(01, 03);
    printf("|");
    gotoxy(20, 02);
    printf("SISTEMA DE GESTAO DE CLIENTE");
    gotoxy(79, 03);
    printf("|");
    gotoxy(01, 04);
    printf("+-----------------------------------------------------------------------------+");
    for (t = 5; t < 24; t++)
    {
        gotoxy(01, t);
        printf("|");
        gotoxy(79, t);
        printf("|");
    }
    gotoxy(01, 22);
    printf("+-----------------------------------------------------------------------------+");
    gotoxy(02, 23);
    printf("MSG.:");
    gotoxy(01, 24);
    printf("+-----------------------------------------------------------------------------+");
}
// Tela de interacao do cliente
void tela_clie()
{
    tela();
    gotoxy(10, 05);
    printf("Codigo do Cliente.: ");
    gotoxy(10, 07);
    printf("Nome do Cliente...: ");
    gotoxy(10, 9);
    printf("Endereco..........: ");
    gotoxy(10, 11);
    printf("Numero............: ");
    gotoxy(10, 13);
    printf("CPF...............: ");
    gotoxy(10, 15);
    printf("Cidade............: ");
    gotoxy(10, 17);
    printf("Estado............: ");
    gotoxy(10, 19);
    printf("Data cadastro.....: ");
    gotoxy(10, 21);
    printf("Telefone..........: ");
}

// Limpa a Tela
void limpa_tela()
{
    int lin;
    int col;
    for (lin = 5; lin < 22; lin++)
    {
        for (col = 2; col < 79; col++)
        {
            gotoxy(col, lin);
            printf(" ");
        }
    }
}

// Pesquisa se existe o Elementos na Lista
TipoApontador pesquisa(TipoLista *L, int codigo)
{
    TipoApontador aux;
    aux = L->Primeiro;
    while (aux != NULL)
    {
        if (aux->conteudo.cd_cliente == codigo)
        {
            break;
        }
        aux = aux->proximo;
    }
    return aux;
}

// Conta quantos Elementos tem na Lista
int conta_elementos(TipoLista *L)
{
    int cont;
    TipoApontador aux;
    aux = L->Primeiro;
    cont = 0;
    while (aux != NULL)
    {
        cont = cont + 1;
        aux = aux->proximo;
    }
    return cont;
}

// Ordenação na Lista em ordem de Codigo
void ordena_codigo(TipoLista *L)
{
    int i;
    int j;
    int qtde;
    reg_cliente reg;
    TipoApontador aux1;
    TipoApontador aux2;

    qtde = conta_elementos(L);
    aux1 = L->Primeiro;
    aux2 = aux1->proximo;
    for (i = 1; i <= qtde - 1; i++)
    {
        for (j = i + 1; j <= qtde; j++)
        {
            if (aux1->conteudo.cd_cliente > aux2->conteudo.cd_cliente)
            {
                reg = aux1->conteudo;
                aux1->conteudo = aux2->conteudo;
                aux2->conteudo = reg;
            }
            aux2 = aux2->proximo;
        }
        aux1 = aux1->proximo;
        aux2 = aux1->proximo;
    }
}

// Ordenação na Lista em ordem de Nome
void ordena_nome(TipoLista *L)
{
    int i;
    int j;
    int qtde;
    int result;
    reg_cliente reg;
    TipoApontador aux1;
    TipoApontador aux2;

    qtde = conta_elementos(L);
    aux1 = L->Primeiro;
    aux2 = aux1->proximo;
    for (i = 1; i <= qtde - 1; i++)
    {
        for (j = i + 1; j <= qtde; j++)
        {
            result = strcmp(aux1->conteudo.nm_cliente, aux2->conteudo.nm_cliente);
            if (result > 0)
            {

                reg = aux1->conteudo;
                aux1->conteudo = aux2->conteudo;
                aux2->conteudo = reg;
            }

            aux2 = aux2->proximo;
        }
        aux1 = aux1->proximo;
        aux2 = aux1->proximo;
    }
}

// Cadastrar Cliente na Lista
void cadastrar(TipoLista *L)
{
    TipoApontador p;
    TipoApontador aux1;
    int resp;
    reg_cliente reg_clie;
    tela_clie();
    gotoxy(35, 03);
    printf("CADASTRAR CLIENTE");
    do
    {
        gotoxy(30, 05);
        scanf("%d", &reg_clie.cd_cliente);
        getchar();
        aux1 = pesquisa(L, reg_clie.cd_cliente);
        if (aux1 != NULL)
        {
            gotoxy(07, 23);
            printf("                                            ");
            gotoxy(07, 23);
            printf("Codigo Ja Cadastrado..");
            getch();
            gotoxy(07, 23);
            printf("                                            ");
        }
    } while (aux1 != NULL);
    gotoxy(30, 07);
    fgets(reg_clie.nm_cliente, 50, stdin);
    gotoxy(30, 9);
    fgets(reg_clie.ds_endereco, 50, stdin);
    gotoxy(30, 11);
    scanf("%d", &reg_clie.nr_numero);
    getchar();
    gotoxy(30, 13);
    fgets(reg_clie.nr_documento, 20, stdin);
    gotoxy(30, 15);
    fgets(reg_clie.ds_cidade, 50, stdin);
    gotoxy(30, 17);
    fgets(reg_clie.cd_uf, 05, stdin);
    gotoxy(30, 19);
    fflush(stdin);
    fgets(reg_clie.dt_cadastro, 19, stdin);
    gotoxy(30, 21);
    fgets(reg_clie.nr_telefone, 15, stdin);
    gotoxy(07, 23);
    printf("Deseja gravar os dados (1-Sim; 2-Nao).:");
    scanf("%d", &resp);
    if (resp == 1)
    {
        p = (TipoApontador)malloc(sizeof(TipoItem));
        // Move os valores lidos para o Ponteiro
        p->conteudo = reg_clie;
        if (L->Primeiro == NULL)
        {
            L->Primeiro = p;
            L->Primeiro->proximo = NULL;
            L->Ultimo = L->Primeiro;
        }
        else
        {
            L->Ultimo->proximo = p;
            L->Ultimo = L->Ultimo->proximo;
            L->Ultimo->proximo = NULL;
        }
    }
}

// Consultar Cliente
void consultar(TipoLista *L)
{
    int resp;
    TipoApontador p;
    p = L->Primeiro;
    if (p == NULL)
    {
        tela();
        gotoxy(8, 23);
        printf("LISTA VAZIA...");
        getch();
    }
    else
    {
        tela();
        while (p != NULL)
        {
            tela_clie();
            gotoxy(35, 03);
            printf("CONSULTAR CLIENTE");
            gotoxy(30, 05);
            printf("%d", p->conteudo.cd_cliente);
            gotoxy(30, 07);
            printf("%s", p->conteudo.nm_cliente);
            gotoxy(30, 9);
            printf("%s", p->conteudo.ds_endereco);
            gotoxy(30, 11);
            printf("%d", p->conteudo.nr_numero);
            gotoxy(30, 13);
            printf("%s", p->conteudo.nr_documento);
            gotoxy(30, 15);
            printf("%s", p->conteudo.ds_cidade);
            gotoxy(30, 17);
            printf("%s", p->conteudo.cd_uf);
            gotoxy(30, 19);
            printf("%s", p->conteudo.dt_cadastro);
            gotoxy(30, 21);
            printf("%s", p->conteudo.nr_telefone);
            gotoxy(10, 23);
            system("pause");
            p = p->proximo;
        }
    }
}

// Cadastrar Elemento no Inicio da Lista
void cad_inicio(TipoLista *L)
{
    int resp;
    TipoApontador p;
    TipoApontador aux1;
    reg_cliente reg_clie;
    tela_clie();
    gotoxy(25, 03);
    printf("CADASTRAR CLIENTE NO INICIO");

    do
    {
        gotoxy(30, 05);
        scanf("%d", &reg_clie.cd_cliente);
        getchar();
        aux1 = pesquisa(L, reg_clie.cd_cliente);
        if (aux1 != NULL)
        {
            gotoxy(07, 23);
            printf("                                            ");
            gotoxy(07, 23);
            printf("Codigo Ja Cadastrado..");
            getch();
            gotoxy(07, 23);
            printf("                                            ");
        }
    } while (aux1 != NULL);
    gotoxy(30, 07);
    fgets(reg_clie.nm_cliente, 50, stdin);
    gotoxy(30, 9);
    fgets(reg_clie.ds_endereco, 50, stdin);
    gotoxy(30, 11);
    scanf("%d", &reg_clie.nr_numero);
    getchar();
    gotoxy(30, 13);
    fgets(reg_clie.nr_documento, 20, stdin);
    gotoxy(30, 15);
    fgets(reg_clie.ds_cidade, 50, stdin);
    gotoxy(30, 17);
    fgets(reg_clie.cd_uf, 05, stdin);
    gotoxy(30, 19);
    fflush(stdin);
    fgets(reg_clie.dt_cadastro, 19, stdin);
    gotoxy(30, 21);
    fgets(reg_clie.nr_telefone, 15, stdin);

    gotoxy(07, 23);
    printf("Deseja gravar os dados (1-Sim; 2-Nao).:");
    scanf("%d", &resp);
    if (resp == 1)
    {
        p = (TipoApontador)malloc(sizeof(TipoItem));
        p->proximo = L->Primeiro;
        L->Primeiro = p;
        if (L->Ultimo == NULL)
        {
            L->Ultimo = L->Primeiro;
        }
        // Move os valores lidos para o Ponteiro
        L->Primeiro->conteudo = reg_clie;
    }
}

// Cadastrar Elemento em Uma Posicao da Lista
void cad_posicao(TipoLista *L)
{
    TipoApontador p;
    TipoApontador r;
    TipoApontador aux1;
    reg_cliente reg_clie;
    int resp;
    int Posicao;
    int cont;
    int qtde;
    do
    {
        tela_clie();
        gotoxy(20, 03);
        printf("CADASTRAR CLIENTE EM UMA POSICAO");
        gotoxy(60, 03);
        qtde = conta_elementos(L);
        printf("Total Clientes.: %d", qtde);

        gotoxy(8, 23);
        printf("Deseja cadastrar em qual Posicao.: ");
        scanf("%d", &Posicao);
        if (Posicao > qtde)
        {
            gotoxy(07, 23);
            printf("                                                    ");
            gotoxy(8, 23);
            printf("Posicão Maior que Qtde Elementos..");
            getch();
        }
    } while (Posicao != 0 && Posicao > qtde);

    if (Posicao > 0)
    {
        do
        {
            gotoxy(30, 05);
            scanf("%d", &reg_clie.cd_cliente);
            getchar();
            aux1 = pesquisa(L, reg_clie.cd_cliente);
            if (aux1 != NULL)
            {
                gotoxy(07, 23);
                printf("                                            ");
                gotoxy(07, 23);
                printf("Codigo Ja Cadastrado..");
                getch();
                gotoxy(07, 23);
                printf("                                            ");
            }
        } while (aux1 != NULL);
        gotoxy(30, 07);
        fgets(reg_clie.nm_cliente, 50, stdin);
        gotoxy(30, 9);
        fgets(reg_clie.ds_endereco, 50, stdin);
        gotoxy(30, 11);
        scanf("%d", &reg_clie.nr_numero);
        getchar();
        gotoxy(30, 13);
        fgets(reg_clie.nr_documento, 20, stdin);
        gotoxy(30, 15);
        fgets(reg_clie.ds_cidade, 50, stdin);
        gotoxy(30, 17);
        fgets(reg_clie.cd_uf, 05, stdin);
        gotoxy(30, 19);
        fgets(reg_clie.dt_cadastro, 19, stdin);
        gotoxy(30, 21);
        fgets(reg_clie.nr_telefone, 15, stdin);

        gotoxy(07, 23);
        printf("Deseja gravar os dados (1-Sim; 2-Nao).:");
        scanf("%d", &resp);
        if (resp == 1)
        {
            r = (TipoApontador)malloc(sizeof(TipoItem));

            // Move os valores lidos para o Ponteiro
            r->conteudo = reg_clie;

            // Insere o Registro na Lista
            p = L->Primeiro;
            for (cont = 1; cont <= Posicao - 2; cont++)
            {
                p = p->proximo;
            }
            if (Posicao == 1)
            {
                r->proximo = L->Primeiro;
                L->Primeiro = r;
            }
            else
            {
                r->proximo = p->proximo;
                p->proximo = r;
            }
        }
    }
}

// Remover Cliente no Final da Lista
void remove_final(TipoLista *L)
{
    TipoApontador p;
    TipoApontador r;
    p = L->Ultimo;
    int resp;

    if (p == NULL)
    {
        tela();
        gotoxy(8, 23);
        printf("LISTA VAZIA..");
        getch();
    }
    else
    {
        tela_clie();
        gotoxy(30, 03);
        printf("REMOVER CLIENTE FINAL");
        gotoxy(30, 05);
        printf("%d", p->conteudo.cd_cliente);
        gotoxy(30, 07);
        printf("%s", p->conteudo.nm_cliente);
        gotoxy(30, 9);
        printf("%s", p->conteudo.ds_endereco);
        gotoxy(30, 11);
        printf("%d", p->conteudo.nr_numero);
        gotoxy(30, 13);
        printf("%s", p->conteudo.nr_documento);
        gotoxy(30, 15);
        printf("%s", p->conteudo.ds_cidade);
        gotoxy(30, 17);
        printf("%s", p->conteudo.cd_uf);
        gotoxy(30, 19);
        printf("%s", p->conteudo.dt_cadastro);
        gotoxy(30, 21);
        printf("%s", p->conteudo.nr_telefone);
        gotoxy(07, 23);
        printf("Deseja Remover o Cliente no Inicio (1=Sim; 2-Nao).:");
        scanf("%d", &resp);
        if (resp == 1)
        {
            if (L->Primeiro->proximo == NULL)
            {
                free(p);
                L->Primeiro = NULL;
                L->Ultimo = NULL;
            }
            else
            {
                // Localiza o Penultimo Elemento
                r = L->Primeiro;
                p = r->proximo;
                while (p->proximo != NULL)
                {
                    r = r->proximo;
                    p = p->proximo;
                }
                r->proximo = NULL;
                L->Ultimo = r;
                free(p);
            }
            gotoxy(07, 23);
            printf("                                                       ");
            gotoxy(07, 23);
            printf("Registro Removido com Sucesso.");
            getch();
        }
    }
}

// Remover Elemento em Uma Posicao da Lista
void remove_posicao(TipoLista *L)
{
    TipoApontador p;
    TipoApontador r;
    int resp;
    int Posicao;
    int cont;
    int qtde;
    do
    {
        tela_clie();
        gotoxy(20, 03);
        printf("CADASTRAR CLIENTE EM UMA POSICAO");
        gotoxy(60, 03);
        qtde = conta_elementos(L);
        printf("Total Clientes.: %d", qtde);

        gotoxy(8, 23);
        printf("Deseja cadastrar em qual Posicao.: ");
        scanf("%d", &Posicao);
        if (Posicao > qtde)
        {
            gotoxy(07, 23);
            printf("                                                    ");
            gotoxy(8, 23);
            printf("Posicão Maior que Qtde Elementos..");
            getch();
        }
    } while (Posicao != 0 && Posicao > qtde);

    if (Posicao > 0)
    {
        // Encontra o Elemento a ser removido e o Anterior a Ele
        if (Posicao == 1)
        {
            r = L->Primeiro;
            p = r;
        }
        else
        {
            r = L->Primeiro;
            p = r->proximo;
            cont = 1;
            while (cont < Posicao - 1)
            {
                cont = cont + 1;
                p = p->proximo;
                r = r->proximo;
            }
        }
        // mostra o Elemento a ser removido na Tela
        tela_clie();
        gotoxy(30, 03);
        printf("REMOVER CLIENTE INICIO");
        gotoxy(30, 05);
        printf("%d", p->conteudo.cd_cliente);
        gotoxy(30, 07);
        printf("%s", p->conteudo.nm_cliente);
        gotoxy(30, 9);
        printf("%s", p->conteudo.ds_endereco);
        gotoxy(30, 11);
        printf("%d", p->conteudo.nr_numero);
        gotoxy(30, 13);
        printf("%s", p->conteudo.nr_documento);
        gotoxy(30, 15);
        printf("%s", p->conteudo.ds_cidade);
        gotoxy(30, 17);
        printf("%s", p->conteudo.cd_uf);
        gotoxy(30, 19);
        printf("%s", p->conteudo.dt_cadastro);
        gotoxy(30, 21);
        printf("%s", p->conteudo.nr_telefone);
        gotoxy(07, 23);
        printf("Deseja Remover o Cliente no Inicio (1=Sim; 2-Nao).:");
        scanf("%d", &resp);
        if (resp == 1)
        {
            if (Posicao == 1)
            {
                L->Primeiro = p->proximo;
                free(p);
            }
            else
            {
                r->proximo = p->proximo;
                free(p);
            }
        }
    }
}

// Remover Cliente no Inicio
void remove_inicio(TipoLista *L)
{
    TipoApontador p;
    p = L->Primeiro;
    int resp;

    if (p == NULL)
    {
        tela();
        gotoxy(8, 23);
        printf("LISTA VAZIA..");
        getch();
    }
    else
    {
        tela_clie();
        gotoxy(30, 03);
        printf("REMOVER CLIENTE INICIO");
        gotoxy(30, 05);
        printf("%d", p->conteudo.cd_cliente);
        gotoxy(30, 07);
        printf("%s", p->conteudo.nm_cliente);
        gotoxy(30, 9);
        printf("%s", p->conteudo.ds_endereco);
        gotoxy(30, 11);
        printf("%d", p->conteudo.nr_numero);
        gotoxy(30, 13);
        printf("%s", p->conteudo.nr_documento);
        gotoxy(30, 15);
        printf("%s", p->conteudo.ds_cidade);
        gotoxy(30, 17);
        printf("%s", p->conteudo.cd_uf);
        gotoxy(30, 19);
        printf("%s", p->conteudo.dt_cadastro);
        gotoxy(30, 21);
        printf("%s", p->conteudo.nr_telefone);
        gotoxy(07, 23);
        printf("Deseja Remover o Cliente no Inicio (1=Sim; 2-Nao).:");
        scanf("%d", &resp);
        if (resp == 1)
        {
            // Verifica se tem um segundo elemento. Se nao tiver o p->proximo sera NULL
            if (p->proximo == NULL)
            {
                free(p);
                L->Primeiro = NULL;
                L->Ultimo = NULL;
            }
            else
            {
                L->Primeiro = p->proximo;
                free(p);
            }
            gotoxy(07, 23);
            printf("                                                       ");
            gotoxy(07, 23);
            printf("Registro Removido com Sucesso.");
            getch();
        }
    }
}

// Consultar em Lista
void consulta_todos(TipoLista *L,char msg[40])
{
    TipoApontador p;
    int lin;
    tela();
    gotoxy(22, 03);
    printf("%s",msg);
    lin = 7;
    gotoxy(02, 05);
    printf("Cd Nome                       CPF            Cidade          UF Telefone   ");
    gotoxy(02, 06);
    printf("-- -------------------------- -------------- --------------- -- -------------");
    p = L->Primeiro;
    if (p == NULL)
    {
        gotoxy(07, 23);
        printf("LISTA VAZIA..");
        getch();
    }
    else
    {
        while (p != NULL)
        {
            gotoxy(02, lin);
            printf("%d", p->conteudo.cd_cliente);
            gotoxy(05, lin);
            printf("%s", p->conteudo.nm_cliente);
            gotoxy(32, lin);
            printf("%s", p->conteudo.nr_documento);
            gotoxy(47, lin);
            printf("%s", p->conteudo.ds_cidade);
            gotoxy(63, lin);
            printf("%s", p->conteudo.cd_uf);
            gotoxy(66, lin);
            printf("%s", p->conteudo.nr_telefone);
            lin++;
            if (lin == 23)
            {
                gotoxy(07, 23);
                system("pause");
                limpa_tela();
            }
            p = p->proximo;
        }
        gotoxy(07, 23);
        system("pause");
    }
}

// Menu Consultar
void menu_consultar(TipoLista *L)
{
    int opc;
    do
    {
        tela();
        gotoxy(30, 03);
        printf("SUBMENU CONSULTA");
        gotoxy(25, 10);
        printf("1 - Consultar Fichario do Cliente");
        gotoxy(25, 12);
        printf("2 - Consultar em Ordem de Codigo");
        gotoxy(25, 14);
        printf("3 - Consultar em Order Alfabetica");
        gotoxy(25, 16);
        printf("4 - Retornar Menu Principal");
        gotoxy(8, 23);
        printf("Digite sua opcao.: ");
        gotoxy(28, 23);
        scanf("%d", &opc);
        switch (opc)
        {
        case 1:
            consultar(L);
            break;
        case 2:
            ordena_codigo(L);
            consulta_todos(L,"CONSULTA LISTA CLIENTES - ORDEM DE CODIGO");
            break;
        case 3:
            ordena_nome(L);
            consulta_todos(L,"CONSULTA LISTA CLIENTES - ORDEM ALFABETICA");
            break;
        default:
            break;
        }

    } while (opc != 4);
}

// Programa principal
int main()
{
    TipoLista L;
    L.Primeiro = NULL;
    L.Ultimo = NULL;
    int opc;
    system("color 1F");
    do
    {
        tela();
        gotoxy(30, 03);
        printf("MENU PRINCIPAL");
        gotoxy(20, 06);
        printf("1 - Cadatrar Cliente no Final da Lista");
        gotoxy(20, 8);
        printf("2 - Consultar Todos Clientes");
        gotoxy(20, 10);
        printf("3 - Cadastrar Cliente no Inicio da Lista");
        gotoxy(20, 12);
        printf("4 - Cadastrar Cliente em uma Posicao da Lista");
        gotoxy(20, 14);
        printf("5 - Remover Cliente no Final da Lista");
        gotoxy(20, 16);
        printf("6 - Remover Cliente na Posicao da Lista");
        gotoxy(20, 18);
        printf("7 - Remover Cliente no Inicio da Lista");
        gotoxy(20, 20);
        printf("8 - Finalizar Programa");
        gotoxy(8, 23);
        printf("Digite sua opcao.: ");
        gotoxy(28, 23);
        scanf("%d", &opc);
        switch (opc)
        {
        case 1:
        {
            cadastrar(&L);
            break;
        }
        case 2:
        {
            menu_consultar(&L);
            break;
        }
        case 3:
        {
            cad_inicio(&L);
            break;
        }
        case 4:
        {
            cad_posicao(&L);
            break;
        }
        case 5:
        {
            remove_final(&L);
            break;
        }
        case 6:
        {
            remove_posicao(&L);
            break;
        }
        case 7:
        {
            remove_inicio(&L);
            break;
        }
        }
    } while (opc < 8);
    return 0;
}