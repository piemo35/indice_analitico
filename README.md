# indice_analitico

Progetto "Indice Analitico" sviluppato da Ahmed Mera & Pietro Piemontese. 2019

Programma C che simula un indice analitico utilizzando liste e operazioni CRUD

SCOPO DEL PROGRAMMA: 

- Creare un indice analitico con un array di teste di liste;
	(Ogni testa sara' l'inizio di una lista contenente tutte le parole del file che iniziano con quella lettera)

- Leggere le parole scritte all'interno di un file di testo;

C - Creare il nodo contenente PAROLA e PAGINA e inserirlo in modo ordinato nella lista corretta;
R - Visualizzare tutto l'indice;
U - Inserire una nuova parola;
D - Cancellare parola;


STRUTTURA DEL NODO:

struct nodo {
    char parola[MAXSIZE];   //parola letta dal file
    int pagina;		//pagina in cui si trova la parola
    struct nodo * next;		//puntatore al nodo successivo
};

