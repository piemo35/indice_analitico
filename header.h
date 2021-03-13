//
// Created by Ahmed & Pietro on 27/11/2019.
//

#ifndef INDICEANALITICO_HEADER_H
#define INDICEANALITICO_HEADER_H

#endif //INDICEANALITICO_HEADER_H
//**********************************************************
/** start programming */
#include <stdio.h>
#include <stdlib.h>
//#include <malloc.h>
#include <string.h>
#include <ctype.h>

#define  MAXSIZE 20

struct nodo {
    char parola[MAXSIZE];
    int pagina;
    struct nodo * next;
};

typedef struct nodo * NODO;

/** Restituisce la posizione dell'array in cui si trova l'iniziale della parola  **/
int h(int parola){ return parola-65; }

/** Inizializza tutte le teste a NULL **/
void inizializzaTeste(NODO * arr){
	int i;
    for (i=0; i<26; i++)  *(arr+i) = NULL;
}

/** Inserimento ordinato del nodo nelle liste **/
void ordina(NODO * teste , NODO nuovo){
    NODO app = *( teste ); //puntatore di appoggio per le teste
    NODO scorri; // puntatore di scorrimento

    //Inserimento in testa
    if(!app){ //lista vuota
        *(teste) = nuovo;
    }

	//un solo elemento in lista
	else if (!app->next){
		//prima parola < nuova parola
        if(strcmp(app->parola, nuovo->parola) < 0) app->next = nuovo;

        //prima parola > nuova parola
		if(strcmp(app->parola, nuovo->parola) > 0){
			nuovo->next = app;
        	*(teste) = nuovo;
		}

        //prima parola = nuova parola
        if(strcmp(app->parola, nuovo->parola) == 0){
            free(nuovo);
        }

    }

	//piu elementi in lista
	else{
	 	//parola nell'indice > nuova parola
		if ((strcmp(app->parola, nuovo->parola) > 0) ){
    	    nuovo->next = app;
    	    *(teste) = nuovo;
    	}

		//parola nell'indice < nuova parola (bisogna scorrere la lista)
		else if((strcmp(app->parola, nuovo->parola) < 0) ){
        	scorri = *teste;

        	// Inserimento in mezzo
        	while (scorri->next){
            	if(strcmp(scorri->parola, nuovo->parola) > 0){ // posizione trovata
                	nuovo->next = scorri;
                	scorri = nuovo;
            	}
            	scorri = scorri->next;
        	}

        	// Inserimento in coda
        	if(!nuovo->next){
        	    scorri->next = nuovo;
        	}
    	}

        //parola nell'indice = nuova parola;
        else{
            free(nuovo);
        }

    }
}

/** Crea un nuovo nodo e chiama la funzione per inserirlo in modo ordinato nella lista **/
void creaNodo(NODO * testa , char parola [], int pagina ){
    NODO nuovo;
    nuovo = (NODO)malloc(sizeof(struct nodo));

    strcpy(nuovo->parola , parola );
    nuovo->pagina = pagina;
    nuovo->next = NULL;

    ordina(testa,nuovo);
}

/** Legge da file e chiama la funzione per creare il nodo **/
void leggiFile(NODO *testa){
    FILE * fp;
    char parola[MAXSIZE];
    int pagina;// , pos = 0;
    fp = fopen("data.txt","r");

    if(!fp){ /// check file
        printf("Errore nell'apertura del file'");
        exit(1);
    }


    do{
    	fscanf(fp,"%s",parola);
		if(feof(fp)) break;

        for(int i=0;i<sizeof(parola);i++) parola[i] = toupper(parola[i]);

		//strupr(parola);
        //pos = h(parola[0]);
        creaNodo((testa + h(parola[0])), parola, pagina);

		pagina++;
	}while(1);

	fclose(fp);
}

/** Visualizza l'indice completo **/
void visualizza (NODO * teste){
	int i;
    for (i = 0; i < 26 ; ++i) {
        NODO app = *(teste + i);
        printf("\n%c) ",i+65);
        while (app != NULL){
            printf(" %s [%d] |",app->parola,app->pagina);
            app = app->next;
            if(!app)
                printf("\n");
        }
            if(!teste[i])
                printf("\n");
    }
    //system("pause");
}

/** Scrive su file la parola inserita dall'utente **/
void inserisciParola(NODO * testa){
	FILE* fp;
	fp = fopen("data.txt","a");
	int controllo = 1;
    int pagina;
	char parola[MAXSIZE];

	do{
		printf("\nParola da aggiungere: ");
		scanf("%s",parola);
		fflush(stdin);
        printf("\nPagina: ");
        scanf("%d",&pagina);
        fflush(stdin);

        for(int i=0;i<sizeof(parola);i++) parola[i] = (char) toupper(parola[i]);

        creaNodo((testa + h(parola[0])), parola, pagina);

		fprintf(fp," %s ",parola);

		printf("\nParola aggiunta correttamente\nPremi 1 per inserire un'altra parola\nPremi 0 per uscire");

		scanf("%d",&controllo);
		//fflush(stdin);
	}while(controllo == 1);

	fclose(fp);
}

/** Cancella la parola inserita dall'utente anche dal file di testo **/
void cancellaDaFile(char parola[]){
    char parola_file[MAXSIZE];
    int righe = 0;
    FILE *fp,*app;
    fp = fopen("data.txt","r"); //file originale
    app = fopen("copia.txt","w"); //file di appoggio
        do{
            fscanf(fp,"%s",parola_file);
            if(feof(fp)) break;

            for(int i=0;i<sizeof(*parola);i++) parola[i] = (char) toupper(parola[i]);
            for(int i=0;i<sizeof(parola_file);i++) parola_file[i] = (char) toupper(parola_file[i]);

            if(strcmp(parola,parola_file) == 0){ //se la parola letta e' uguale a quella da eliminare
                continue;
            }else{ //se la parola letta e' diversa da quella da eliminare
                if(righe>14){ //se ha gia scritto piu di 14 parole sulla stessa riga va a capo
                    printf("\n");
                    righe = 0; 
                }
                fprintf(app," %s ",parola_file); //scrive la parola letta da "data.txt" sul file "copia.txt"
                righe++;
            }
        }while(1);
    fclose(app);
    fclose(fp);

    remove("data.txt"); //elimino il vecchio file
    rename("copia.txt","data.txt"); //rinomino il file "copia.txt" in "data.txt"
}

/** Restituisce 1 se la parola e' stata cancellata, 0 se non e' stata trovata  **/
int cancella(NODO * teste){
    char parola [MAXSIZE];
    int controllo = 0;
    printf("Parola da cancellare: ");
    scanf("%s",parola);
    fflush(stdin);

    cancellaDaFile(parola);

    for(int i=0;i<sizeof(parola);i++) parola[i] = (char) toupper(parola[i]);

    NODO app = *(teste + h(parola[0]));
    NODO prev;

    for(int i=0;i<sizeof(app->parola);i++) app->parola[i] = (char) toupper(app->parola[i]);


    // Un solo elemento in lista e prima parola = a quella cercata
    if((app->next == NULL) && (strcmp(app->parola, parola ) == 0)){
        *(teste + h(parola[0])) = NULL;
        return 1;
    }


    // Piu elementi in lista (bisogna scorrere la lista)
    while (app->next != NULL){

        for(int i=0;i<sizeof(app->next->parola);i++) app->next->parola[i] = (char) toupper(app->next->parola[i]);

        //parola corrente == a quella cercata
        if((strcmp(app->parola, parola ) == 0)){
            *(teste + h(parola[0])) = app->next;
            return 1;
        }

        //prossima parola == a quella cercata
        if(strcmp(app->next->parola, parola) == 0){
            prev = app->next;
            app->next = app->next->next;
            free(prev);
            return 1;
        }

        app = app->next;
    }

    return 0;
}

/** Ricerca la parola inserita dall'utente **/
void ricerca(NODO * teste){
    char parola [MAXSIZE];
    int controllo = 0;

    printf("Parola da cercare: ");
    scanf("%s",parola);
    fflush(stdin);

    for(int i=0;i<sizeof(parola);i++) parola[i] = (char) toupper(parola[i]);
    NODO app = *(teste + h(parola[0]));

    for(int i=0;i<sizeof(app->parola);i++) app->parola[i] = (char) toupper(app->parola[i]);

    while (app){
        if(strcmp(app->parola, parola ) == 0){ // Parola trovata
            printf("La parola cercata e' presente nell'indice! \n%s [%d]\n",app->parola,app->pagina);
            controllo = 1;
        }
        app = app->next;
    }
    if(controllo == 0) printf("Parola non trovata\n");
    //system("pause");
}