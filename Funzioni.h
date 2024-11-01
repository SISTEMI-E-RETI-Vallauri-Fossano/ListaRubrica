
/*
|===================================================================================================|
|                                       		                                                    |
|                              	     Libreria FUNZIONI                                              |
|                               	                                                                |
|                              		    Ver. 1.3                                                    |
|                                                          		                                    |
|                                 Ult.Agg. 19 Marzo 2012                	                        |
|                                                                               	                |
|  Elenco funzioni:                                                                     	        |
|                                                                                           	    |
|  - clrscr():             	pulisce lo schermo di lavoro;                                           |
|  - gotoxy(x,y):          	posiziona il cursore in una specifica posizione sullo schermo;          |
|  - randomize():          	inizializza la casualità;                                               |
|  - random(numero):       	genera un numero casuale commpreso tra 0 e il numero inserito;          |
|  - textcolor(Colore):    	modifica colore del testo;                                              |
|  - dalay(MilliSecondi):  	crea un attesa in secondi;                                              |
|  - textbackground(Colore):	imposta il colore dello sfondo; 				                    |
|  - bubble(int*,int);     ordina il vettore con il metodo Bubble Sort

   Elenco Funzioni Tabella:
   si richiamano   -->   funzioneTabella(lun,luns/luns+1,tab);
                              |
|  - stampaTabella           stampa un matrice ci caratteri utilizzata come tabella di stringhe          |
|  - stampaTabella           carica per input delle stringhe in celle di un tabella (che in realta'
                              sarebbe una matrice di caratteri)
   - selectionSortTabella    ordinamento di selection sort di una tabella precaricata
|                                                                                         	        |
|===================================================================================================|
*/

#include <time.h>
#include <windows.h>


void controlloFileEsistente(char* file){
    FILE *fp;
     fp=fopen(file,"r");
    if(fp==NULL){
        fclose(fp);
        fp=fopen(file,"w");
        printf("\nFile inessitente ora creato");

    }else{
    printf("\nFile visualizzabile");
    }
    fclose(fp);

}

void caricamentoMatriceCasualeInt(int r,int c,int mat[r][c],int M){
    for(int i=0;i<r;i++)
        for(int j=0;j<c;j++)
        mat[i][j]=random(M)+1;


}
void stampaMatriceInt(int r,int c,int mat[r][c]){
    printf("\n");
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++)
            printf("%3d  ",mat[i][j]);
        printf("\n");
    }
}
void stampaTabella(int lun,int slun,char tab[lun][slun]){

    for(int i=0;i<lun;i++)
        printf("\n%s",tab[i]);

}
void caricaTabellaManuale(int lun,int slun,char tab[lun][slun]){
    for(int i=0;i<lun;i++)
        {
            printf("\nInserire una stringa:");
            fflush(stdin);
            gets(tab[i]);
        }
}
void selectionSortTabella(int lun,int slun,char tab[lun][slun]){
    int posmin;
    char aus[slun];
    for(int i=0;i<lun-1;i++)
    {
        posmin=i;
        for(int j=i;j<lun;j++)
                if(strcmp(tab[posmin],tab[j])>0)
                    posmin=j;
                    if(posmin!=i){
                            strcpy(aus,tab[i]);
                            strcpy(tab[i],tab[posmin]);
                            strcpy(tab[posmin],aus);
                    }
    }

}

void clrscr()
    {
     system("cls");
    }


int gotoxy(short X, short Y)
    {
	 HANDLE hStdout;
	 CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	 hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	 if (! GetConsoleScreenBufferInfo(hStdout, &csbiInfo))
	    {
		 MessageBox(NULL, "GetConsoleScreenBufferInfo", "Console Error", MB_OK);
		 return 1;
	    }
	 csbiInfo.dwCursorPosition.X = X;
	 csbiInfo.dwCursorPosition.Y = Y;
	 if (! SetConsoleCursorPosition(hStdout, csbiInfo.dwCursorPosition))
	    {
		 MessageBox(NULL, "SetConsoleCursorPosition", "Console Error", MB_OK);
		 return 1;
        }
     return 0;
    }


void randomize()
    {
     srand(time(NULL));
    }


int random(int NumMax)
{
    int NumGenerato;

    NumGenerato = rand() % NumMax;
    return NumGenerato;
}


void textcolor(unsigned short color)
    {
     HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
     SetConsoleTextAttribute(hCon,color);
    }


void delay( int MilliSecondi)
    {
     double Secondi = 0;
     if (MilliSecondi > 0)
        Secondi = MilliSecondi / 1000.0;
     clock_t endwait;
     endwait = clock () + Secondi * CLOCKS_PER_SEC;
     while (clock() < endwait)
           {}
    }


void textbackground(unsigned short color)
    {
     WORD wColor = (color & 0x0F) << 4;
     HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
     SetConsoleTextAttribute(hCon,wColor);
    }

void bubble(int*vect,int lunghezza)
  {
    int n;
    int scambio;
    int i;
    int aus;

    n = lunghezza-1;

    do
      {
       scambio = 0;
       for (i=0;i<n;i++)
           {
            if (vect[i]>vect[i+1])
               {
                aus = vect[i];
                vect[i] = vect[i+1];
                vect[i+1] = aus;
                scambio = 1;
               }
           }
       n--;
      }
    while(scambio == 1);

  }
