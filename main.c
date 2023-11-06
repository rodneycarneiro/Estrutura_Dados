/* Autor....: Rodney Carneiro
   Data.....: 11/10/2023
   Objetivo.: Cadastrar e consultar cliente
*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <locale.h>

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
    gotoxy(07, 05);
    printf("   Codigo do Cliente.: ");
    gotoxy(07, 07);
    printf("1- Nome do Cliente...: ");
    gotoxy(07, 9);
    printf("2- Endereco..........: ");
    gotoxy(07, 11);
    printf("3- Numero............: ");
    gotoxy(07, 13);
    printf("4- CPF...............: ");
    gotoxy(07, 15);
    printf("5- Cidade............: ");
    gotoxy(07, 17);
    printf("6- Estado............: ");
    gotoxy(07, 19);
    printf("7- Data cadastro.....: ");
    gotoxy(07, 21);
    printf("8- Telefone..........: ");
}

// Limpa a Tela
void limpa_tela()
{
    int lin;
    int col;
    for (lin = 7; lin < 22; lin++)
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

// Le o nome do Cliente
char *le_nm_nome()
{
    char *nm_cliente;
    nm_cliente = malloc(sizeof(char) * 50);
    do
    {
        gotoxy(30, 07);
        printf("                                               ");
        gotoxy(30, 07);
        fgets(nm_cliente, 50, stdin);

        if ((strlen(nm_cliente) == 1) && (strcmp(nm_cliente, "0") == -1))
        {
            gotoxy(07, 23);
            printf("Nome do cliente e Obrigatorio");
            getch();
            gotoxy(07, 23);
            printf("                              ");
        }
    } while ((strlen(nm_cliente) == 1) && (strcmp(nm_cliente, "0") == -1));
    return nm_cliente;
}

// Le o Endereco do Cliente
char *le_ds_endereco()
{
    char *ds_endereco;
    ds_endereco = malloc(sizeof(char) * 50);
    do
    {
        gotoxy(30, 9);
        printf("                                               ");
        gotoxy(30, 9);
        fgets(ds_endereco, 50, stdin);

        if ((strlen(ds_endereco) == 1) && (strcmp(ds_endereco, "0") == -1))
        {
            gotoxy(07, 23);
            printf("Endereco do cliente e Obrigatorio");
            getch();
            gotoxy(07, 23);
            printf("                                    ");
        }
    } while ((strlen(ds_endereco) == 1) && (strcmp(ds_endereco, "0") == -1));
    return ds_endereco;
}
// Le o Numero do Endereco do Cliente
int le_nr_numero()
{
    int nr_numero;
    do
    {
        gotoxy(30, 11);
        printf("                                               ");
        gotoxy(30, 11);
        scanf("%d", &nr_numero);
        getchar();
        if (nr_numero == 0)
        {
            gotoxy(07, 23);
            printf("Numero do Endereco do cliente e Obrigatorio");
            getch();
            gotoxy(07, 23);
            printf("                                             ");
        }
    } while (nr_numero <= 0);
    return nr_numero;
}

// Le o CPF do Cliente
char *le_nr_documento()
{
    char *nr_documento;
    nr_documento = malloc(sizeof(char) * 20);
    do
    {
        gotoxy(30, 13);
        printf("                                               ");
        gotoxy(30, 13);
        fgets(nr_documento, 20, stdin);

        if ((strlen(nr_documento) == 1) && (strcmp(nr_documento, "0") == -1))
        {
            gotoxy(07, 23);
            printf("O CPF do cliente e Obrigatorio");
            getch();
            gotoxy(07, 23);
            printf("                                    ");
        }
    } while ((strlen(nr_documento) == 1) && (strcmp(nr_documento, "0") == -1));
    return nr_documento;
}

// Le a Cidade do Cliente
char *le_ds_cidade()
{
    char *ds_cidade;
    ds_cidade = malloc(sizeof(char) * 50);
    do
    {
        gotoxy(30, 15);
        printf("                                               ");
        gotoxy(30, 15);
        fgets(ds_cidade, 50, stdin);

        if ((strlen(ds_cidade) == 1) && (strcmp(ds_cidade, "0") == -1))
        {
            gotoxy(07, 23);
            printf("Cidade do cliente e Obrigatorio");
            getch();
            gotoxy(07, 23);
            printf("                                    ");
        }
    } while ((strlen(ds_cidade) == 1) && (strcmp(ds_cidade, "0") == -1));
    return ds_cidade;
}

// Le o Estado do Cliente
char *le_cd_uf()
{
    char *cd_uf;
    cd_uf = malloc(sizeof(char) * 5);
    do
    {
        gotoxy(30, 17);
        printf("                                               ");
        gotoxy(30, 17);
        fgets(cd_uf, 5, stdin);

        if ((strlen(cd_uf) == 1) && (strcmp(cd_uf, "0") == -1))
        {
            gotoxy(07, 23);
            printf("Estado do cliente e Obrigatorio");
            getch();
            gotoxy(07, 23);
            printf("                                    ");
        }
    } while ((strlen(cd_uf) == 1) && (strcmp(cd_uf, "0") == -1));
    return cd_uf;
}
// Le Data do Cadastro do Cliente
char *le_dt_cadastro()
{
    char *dt_cadastro;
    dt_cadastro = malloc(sizeof(char) * 19);
    do
    {
        gotoxy(30, 19);
        printf("                                               ");
        gotoxy(30, 19);
        fgets(dt_cadastro, 19, stdin);

        if ((strlen(dt_cadastro) == 1) && (strcmp(dt_cadastro, "0") == -1))
        {
            gotoxy(07, 23);
            printf("Data do Cadastro do cliente e Obrigatorio");
            getch();
            gotoxy(07, 23);
            printf("                                            ");
        }
    } while ((strlen(dt_cadastro) == 1) && (strcmp(dt_cadastro, "0") == -1));
    return dt_cadastro;
}

// Le Numero do Telefone do Cliente
char *le_nr_telefone()
{
    char *nr_telefone;
    nr_telefone = malloc(sizeof(char) * 15);
    do
    {
        gotoxy(30, 21);
        printf("                                               ");
        gotoxy(30, 21);
        fgets(nr_telefone, 15, stdin);

        if ((strlen(nr_telefone) == 1) && (strcmp(nr_telefone, "0") == -1))
        {
            gotoxy(07, 23);
            printf("Numero do Telefone do cliente e Obrigatorio");
            getch();
            gotoxy(07, 23);
            printf("                                            ");
        }
    } while ((strlen(nr_telefone) == 1) && (strcmp(nr_telefone, "0") == -1));
    return nr_telefone;
}

// Le as informações do Cliente
void leitura(reg_cliente *reg_clie)
{
    strcpy(reg_clie->nm_cliente, le_nm_nome());
    strcpy(reg_clie->ds_endereco, le_ds_endereco());
    reg_clie->nr_numero = le_nr_numero();
    strcpy(reg_clie->nr_documento, le_nr_documento());
    strcpy(reg_clie->ds_cidade, le_ds_cidade());
    strcpy(reg_clie->cd_uf, le_cd_uf());
    strcpy(reg_clie->dt_cadastro, le_dt_cadastro());
    strcpy(reg_clie->nr_telefone, le_nr_telefone());
}

// Mostra Registro do Cliente
void mostra_cliente(reg_cliente reg_clie)
{
    gotoxy(30, 05);
    printf("%d", reg_clie.cd_cliente);
    gotoxy(30, 07);
    printf("%s", reg_clie.nm_cliente);
    gotoxy(30, 9);
    printf("%s", reg_clie.ds_endereco);
    gotoxy(30, 11);
    printf("%d", reg_clie.nr_numero);
    gotoxy(30, 13);
    printf("%s", reg_clie.nr_documento);
    gotoxy(30, 15);
    printf("%s", reg_clie.ds_cidade);
    gotoxy(30, 17);
    printf("%s", reg_clie.cd_uf);
    gotoxy(30, 19);
    printf("%s", reg_clie.dt_cadastro);
    gotoxy(30, 21);
    printf("%s", reg_clie.nr_telefone);
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
        printf("           ");
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
    // Le os dados do Cliente
    leitura(&reg_clie);

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

// Consultar Cliente Especifico
void consultar_cliente(TipoLista *L)
{
    TipoApontador p;
    int codigo;
    int qtde;
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
        do
        {
            tela();
            tela_clie();
            gotoxy(25, 03);
            printf("CONSULTAR CLIENTE ESPECIFICO");
            gotoxy(60, 03);
            qtde = conta_elementos(L);
            printf("Total Clientes.: %d", qtde);
            gotoxy(30, 05);
            scanf("%d", &codigo);
            p = pesquisa(L, codigo);
            if (p == NULL)
            {
                gotoxy(07, 23);
                printf("Cliente Nao Cadastrado..");
                getch();
            }
        } while (p == NULL);

        // Mostra registro do Cliente
        mostra_cliente(p->conteudo);

        gotoxy(10, 23);
        system("pause");
    }
}

// Consultar Todos Clientes como Fichario
void consultar(TipoLista *L)
{
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
            // Mostra registro do Cliente
            mostra_cliente(p->conteudo);

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
        printf("           ");
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
    // Le os dados do Cliente
    leitura(&reg_clie);

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
            printf("Posicao Maior que Qtde Elementos..");
            getch();
        }
    } while (Posicao != 0 && Posicao > qtde);

    if (Posicao > 0)
    {
        do
        {
            gotoxy(30, 05);
            printf("           ");
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
        // Le os dados do Cliente
        leitura(&reg_clie);

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

        // Mostra registro do Cliente
        mostra_cliente(p->conteudo);

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

        // Mostra registro do Cliente
        mostra_cliente(p->conteudo);

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

        // Mostra registro do Cliente
        mostra_cliente(p->conteudo);

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
void consulta_todos(TipoLista *L, char msg[40])
{
    TipoApontador p;
    int lin;
    tela();
    gotoxy(22, 03);
    printf("%s", msg);
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
            if (lin > 21)
            {
                gotoxy(07, 23);
                system("pause");
                limpa_tela();
                lin = 7;
            }
            p = p->proximo;
        }
        gotoxy(07, 23);
        system("pause");
    }
}
// Altera dados de um cliente Especifico
void altera_cliente(TipoLista *L)
{
    TipoApontador p;
    reg_cliente reg_clie;
    int codigo;
    int qtde;
    int campo;
    int resp;
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
        do
        {
            tela();
            tela_clie();
            gotoxy(25, 03);
            printf("ALTERACAO DADOS DO CLIENTE");
            gotoxy(60, 03);
            qtde = conta_elementos(L);
            printf("Total Clientes.: %d", qtde);
            gotoxy(30, 05);
            scanf("%d", &codigo);
            p = pesquisa(L, codigo);
            if (p == NULL)
            {
                gotoxy(07, 23);
                printf("Cliente Nao Cadastrado..");
                getch();
            }
        } while (p == NULL);

        // Mostra registro do Cliente
        mostra_cliente(p->conteudo);
        reg_clie = p->conteudo;
        do
        {
            gotoxy(07, 23);
            printf("                                               ");
            gotoxy(07, 23);
            printf("Digite o Campo a ser Alterado (0=Sair).: ");
            scanf("%d", &campo);
            getchar();
            if (campo > 8)
            {
                gotoxy(07, 23);
                printf("                                           ");
                gotoxy(07, 23);
                printf("Campo invalido..");
                getch();
            }
            switch (campo)
            {
            case 1:
                strcpy(reg_clie.nm_cliente, le_nm_nome());
                break;
            case 2:
                strcpy(reg_clie.ds_endereco, le_ds_endereco());
                break;
            case 3:
                reg_clie.nr_numero = le_nr_numero();
                break;
            case 4:
                strcpy(reg_clie.nr_documento, le_nr_documento());
                break;
            case 5:
                strcpy(reg_clie.ds_cidade, le_ds_cidade());
                break;
            case 6:
                strcpy(reg_clie.cd_uf, le_cd_uf());
                break;
            case 7:
                strcpy(reg_clie.dt_cadastro, le_dt_cadastro());
                break;
            case 8:
                strcpy(reg_clie.nr_telefone, le_nr_telefone());
                break;
            default:
                break;
            }
        } while ((campo != 0));
        gotoxy(07, 23);
        printf("                                             ");
        gotoxy(07, 23);
        printf("Confirma a Alteracao dos Dados (1-Sim;2-Nao).: ");
        scanf("%d", &resp);
        if (resp == 1)
        {
            p->conteudo = reg_clie;
        }
    }
}

// Le as Informações do Arquivo em DISCO e Grava na Lista Simplesmente Encadeada
void le_arquivo(TipoLista *L)
{
    FILE *ptr;
    char *filename = "Clientes.dat";
    char *modo_gravacao = "rb";
    reg_cliente reg_clie;
    TipoApontador p;
    L->Primeiro = NULL;
    L->Ultimo = NULL;
    tela();
    gotoxy(25, 03);
    printf("CARREGA DADOS DO ARQUIVO PARA A LISTA");

    // Abre o arquivo para Gravacao; Se ocorrer erro o Programa Aborta
    ptr = fopen(filename, modo_gravacao);
    if (ptr == NULL)
    {
        gotoxy(07, 23);
        printf("Erro ao Abrir o Arquivo");
        getch();
    }
    else
    {
        gotoxy(01, 05);
        while (!feof(ptr))
        {
            if (fread(&reg_clie, sizeof(reg_clie), 1, ptr) != 0)
            {
                if (L->Primeiro == NULL)
                {
                    p = (TipoApontador)malloc(sizeof(TipoItem));
                    p->conteudo = reg_clie;
                    p->proximo = NULL;
                    L->Primeiro = p;
                    L->Ultimo = p;
                }
                else
                {
                    p->proximo = (TipoApontador)malloc(sizeof(TipoItem));
                    p = p->proximo;
                    p->conteudo = reg_clie;
                    p->proximo = NULL;
                    L->Ultimo = p;
                }
            }
        }
        fclose(ptr);
        gotoxy(07, 23);
        printf("Dados lidos com Sucesso");
        getch();
    }
}

// Grava Informações da Lista Simplesmente Encadeada em um Arquivo em DISCO
void gravar(TipoLista *L)
{
    FILE *ptr;
    char *filename = "Clientes.dat";
    char *modo_gravacao = "wb";
    reg_cliente reg_clie;
    TipoApontador p;
    p = L->Primeiro;
    tela();
    gotoxy(25, 03);
    printf("GRAVA DADOS DA LISTA NO ARQUIVO EM DISCO");
    if (p == NULL)
    {
        gotoxy(07, 23);
        printf("LISTA VAZIA..");
        getch();
    }
    else
    {
        // Abre o arquivo para Gravacao; Se ocorrer erro o Programa Aborta
        if ((ptr = fopen(filename, modo_gravacao)) == NULL)
        {
            gotoxy(07, 23);
            printf("Erro ao Abrir o Arquivo");
            getch();
        }
        else
        {
            while (p != NULL)
            {
                reg_clie = p->conteudo;
                fwrite(&reg_clie, sizeof(reg_clie), 1, ptr);
                p = p->proximo;
            }
            fclose(ptr);
            gotoxy(07, 23);
            printf("Dados Gravados com Sucesso");
            getch();
        }
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
        gotoxy(25, 8);
        printf("1 - Consultar Fichario do Cliente Geral");
        gotoxy(25, 10);
        printf("2 - Consultar em Ordem de Codigo");
        gotoxy(25, 12);
        printf("3 - Consultar em Order Alfabetica");
        gotoxy(25, 14);
        printf("4 - Consultar o Codigo Especifico");
        gotoxy(25, 16);
        printf("5 - Retornar Menu Principal");
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
            consulta_todos(L, "CONSULTA LISTA CLIENTES - ORDEM DE CODIGO");
            break;
        case 3:
            ordena_nome(L);
            consulta_todos(L, "CONSULTA LISTA CLIENTES - ORDEM ALFABETICA");
            break;
        case 4:
            consultar_cliente(L);
            break;
        default:
            break;
        }

    } while (opc != 5);
}

// Programa principal
int main()
{
    TipoLista L;
    L.Primeiro = NULL;
    L.Ultimo = NULL;
    int opc;
    system("color 1F");
    setlocale(LC_ALL, "portuguese-brazilian");
    le_arquivo(&L);
    do
    {
        tela();
        gotoxy(30, 03);
        printf("MENU PRINCIPAL");
        gotoxy(20, 8);
        printf("1 - Cadatrar Cliente no Final da Lista");
        gotoxy(20, 9);
        printf("2 - Cadastrar Cliente no Inicio da Lista");
        gotoxy(20, 10);
        printf("3 - Cadastrar Cliente em uma Posicao da Lista");
        gotoxy(20, 11);
        printf("4 - Remover Cliente no Final da Lista");
        gotoxy(20, 12);
        printf("5 - Remover Cliente na Posicao da Lista");
        gotoxy(20, 13);
        printf("6 - Remover Cliente no Inicio da Lista");
        gotoxy(20, 14);
        printf("7 - Consultar Todos Clientes");
        gotoxy(20, 15);
        printf("8 - Altera dados do Cliente");
        gotoxy(20, 16);
        printf("9 - Finalizar Programa");
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
            cad_inicio(&L);
            break;
        }
        case 3:
        {
            cad_posicao(&L);
            break;
        }
        case 4:
        {
            remove_final(&L);
            break;
        }
        case 5:
        {
            remove_posicao(&L);
            break;
        }
        case 6:
        {
            remove_inicio(&L);
            break;
        }
        case 7:
        {
            menu_consultar(&L);
            break;
        }
        case 8:
        {
            altera_cliente(&L);
            break;
        }
        }
    } while (opc < 9);
    gravar(&L);
    return 0;
}