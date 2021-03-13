#include "header.h"
int main() {
    int scelta;
    NODO  teste[26] ; /**  Array di teste, ogni testa corrisponde ad una lettera dell'alfabeto **/

    inizializzaTeste(teste); /** Assegna NULL a tutte le teste**/
    leggiFile(teste); /** Legge da file e chiama le funzioni per allocare le parole lette  **/

    /** Start Menu **/
    while (1){

        printf("\t\t Menu \n1) Visualizza indice completo \n2) Ricerca parola \n3) Cancella parola \n4) Inserisci parola \n0) Esci \n ");
        scanf("%d",&scelta);
        fflush(stdin);

        switch(scelta){
            case 1:
                visualizza(teste);
                break;
            case 2:
                ricerca(teste);
                break;
            case 3:
				cancella(teste) ? printf("\tParola cancellata correttamente \n\n") : printf("\tLa parola cercata non e' presente nell'indice \n\n");
				//system("pause");
				break;
			case 4:
				inserisciParola(teste);
				break;
            case 0:
                printf("\n\t\t\t Alla prossima! :) \n\n");
                exit(0);
            default:
                printf("\n Qualcosa e' andato storto, riprova! \n");
                break;
        }
    }
    return 0;
}
