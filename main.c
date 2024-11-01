#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
//#include "Funzioni.h"

//gestire una rubrica
//contatto{numero, nome, cognome}
//rucbrica = contatto[]
//stampa in file

//METODO
//1# dichiara la struttura dell'info;
typedef struct contatto
{
    long int num;
    char *nome;
    char *cogn;
} t_contatto;
//2#nodo
struct nodo
{
    t_contatto info;
    struct nodo* next;
};


// Funzione per attendere che l'utente prema un tasto per continuare
void premiPerContinuare()
{
    printf("\n\nPremi un tasto per continuare...\n");
    fflush(stdin);
    getchar(); // Attende l'input dell'utente
}
void stampaRubrica(struct nodo *rub)
{
    struct nodo * aus=rub;
//    aus=(struct nodo*)malloc(sizeof(struct nodo));
//    aus->info.cogn=(char*)malloc(sizeof(char)*10);
//    aus->info.nome=(char*)malloc(sizeof(char)*10);
//    aus->info.cogn="Cognome\0";
//    aus->info.nome="Nome\0";
//    aus->info.num=10;
//    aus->next=NULL;
    int i=0;
    while(aus!=NULL)
    {
        //in teoria (*p).etc == p->etc
        printf("\n[%d] %s %s numero: %d",i++,(*aus).info.cogn,aus->info.nome,(*aus).info.num);
        aus=aus->next;
    };
    if(aus==NULL&&i==0)  printf("\nRubrica vuota");
}
void menu(struct nodo* rub)
{
    system("cls");
    printf("1.Aggiungi contatto");
    printf("\n2.Elimina contatto");
    printf("\n3.Carica su FILE");
    printf("\n4.Scarica da FILE");

    //STAMPA DELLA RUBRICA SOTTO IL MENU
    stampaRubrica(rub);
}
t_contatto creaContatto()
{
    //contatto da returnare
    t_contatto p;
    //virtual buffer per l'input. Il fine è di
    //allocare dinamicamente la memoria a cogn e nome
    char aus[50];

    printf("\n\nCREAZIONE DI UN CONTATTO");
    //perciò in ogni richiesta di input la gets va  a
    //aus (virtual buffer)
    printf("\nInserire cognome: ");
    fflush(stdin);
    gets(aus);

    //con strlen si va ad allocare la memoria per cogn
    //poi si copia la stringa
    p.cogn=(char*)malloc(sizeof(char)*(strlen(aus)+1));
    strcpy(p.cogn,aus);

    //controllo di giusto input
//    printf("Ciao %s",p.cogn);

    //STESSA cosa per gli altri campi di input
    fflush(stdin);
    printf("Inserire il nome: ");
    gets(aus);

    p.nome=(char*)malloc(sizeof(char)*(strlen(aus)+1));
    strcpy(p.nome,aus);
//    printf("Salve %s %s",p.cogn,p.nome);

    fflush(stdin);
    printf("Ora inserire il numero di telefono: ");
    scanf("%d",&(p.num));
    printf("\nSalve %s %s di numero %d",p.cogn,p.nome,p.num);

    return  p;
}
struct node *aggiungiContatto(struct nodo *head,t_contatto _info)
{
    printf("\n\nAGGIUNTA DI UN NUOVO CONTATTO");
    struct nodo *p;
    p=(struct nodo*)malloc(sizeof(struct nodo));
//    printf("\nInfo del contato da aggiungere:\nNome: %s\nCognome: %s\nNumero: %d",_info.cogn,_info.nome,_info.num);
//    premiPerContinuare();
    p->info=_info;
//    printf("\nInfo del contato aggiunta:\nNome: %s\nCognome: %s\nNumero: %d",p->info.cogn,(*p).info.nome,(*p).info.num);
//    premiPerContinuare();

    (*p).next= NULL;

    if(head!=NULL)
    {
        struct nodo *aus=head;
        while((*aus).next!=NULL) aus=(*aus).next;
        aus->next=p;

    }
    else head=p;

    return head;
}

int SceltaContatto(struct nodo *head,int lun)
{
    int pos;
    do
    {
        stampaRubrica(head);
        printf("\nScrivi l'indice del contatto da eliminare: ");
        fflush(stdin);
        scanf("%d",&pos);
    }
    while(pos>=lun||pos<0);
    return pos;
}
struct node *EliminaContatto(struct nodo *head,int index)
{
    if(head!=NULL)
    {
        if(index==0)    head=head->next;
        else
        {
            struct nodo* p=head;
            struct nodo* prec=head;
            int i=0;
            while(i<index)
            {
                prec=p;
                i++;
                p=p->next;
            }
            prec->next=p->next;
        }
    }
    return head;
};

void caricaSuFile(struct nodo *head,char *file)
{
    FILE *fp;
    if((fp=fopen(file,"w"))!=NULL)
    {
        while(head!=NULL)
        {
            fprintf(fp,"%s;%s;%d\n",head->info.cogn,head->info.nome,head->info.num);
            head=head->next;
        };

    }
    else printf("Errore nell'apertura del file");
    fclose(fp);
}
struct nodo *scaricaDaFile(char *file,int *lenght){
    struct nodo *head=NULL;
    FILE *fp;
    fp=fopen(file,"r");
    char line[100];
            fgets(line,100,fp);
    while(!feof(fp)){
            t_contatto info;
            char aus[50];
            strcpy(aus,strtok(line,";"));
            info.cogn=(char*)malloc(sizeof(char)*(strlen(aus)+1));
            strcpy(info.cogn,aus);


            strcpy(aus,strtok(NULL,";"));
            info.nome=(char*)malloc(sizeof(char)*(strlen(aus)+1));
            strcpy(info.nome,aus);

            info.num=numeroDaCaratteri(strtok(NULL,";"));

            head=aggiungiContatto(head,info);
            (*lenght)++;

            printf("%s",line);
            fgets(line,100,fp);
    };
    fclose(fp);
    return head;
};
int numeroDaCaratteri(char s[50]){
    int n=0;
    int len=strlen(s)-1;
    printf("\n%s di len %d",s,len);
    for(int i=0;i<len;i++){
        printf("\n(%d)*(%d)",s[i]-48,(int)pow(10, len-i-1));
        n+=(s[i]-48)*(int)pow(10, len-i-1);
    }
    printf("\nnum:%d",n);
    return n;
}

int main()
{
    system("COLOR 0a");
    struct node *rubrica=NULL;
    char file[]="rubrica.txt\0";

    int lenght=0;

    int scelta=0;
    do
    {
        menu(rubrica);
        printf("\n\nScrivere l'azione da eseguire: ");
        fflush(stdin);
        scanf("%d",&scelta);
        switch(scelta)
        {
        case 1:
            rubrica=aggiungiContatto(rubrica,creaContatto());
            lenght++;
            break;

        case 2:
            if(lenght>0)
            {
                rubrica=EliminaContatto(rubrica,SceltaContatto(rubrica,lenght));
                lenght--;
            }
            else printf("\n\nNon ci sono contatti da eliminare");
            break;
        case 3:
            caricaSuFile(rubrica,file);
            break;
        case 4:
            rubrica=scaricaDaFile(file,&lenght);
            break;
        default:
            break;
        }
        premiPerContinuare();
    }
    while(scelta!=0);
    return 0;
}
