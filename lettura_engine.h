#ifndef LETTURA_ENGINE_H_INCLUDED
#define LETTURA_ENGINE_H_INCLUDED
#include "variabili.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

// --------------------LETTURA engine-----------------------//
// il codice inserisce i dati del motore Lycoming O-320-H2AD//

void lettura_engine()
{
    FILE *fp;
    FILE *fp2;
    int i=0, n=60, j=0;
    char parola[n], *endptr;
    double dati[10];

    fp=fopen("engine.txt", "r");
    if ((fopen("engine.txt", "r"))==NULL){
        printf("ERRORE nell'apertura del file");
        exit(2);
    }
    while (fgets(parola,n,fp)!=NULL){ // lettura riga per riga
        if (parola[0]=='*'){ // le righe che inzizano con '*' non vengon lette perche' non contengon dati utili
            continue;
        }
        else{
            // printf("%s",parola);
            dati[i]=strtof(parola, &endptr); // copia i valori della stringa nel vettore dati
            if(dati[i]!=0){ // controllo per togliere gli zeri che venivano salvati nel vettore dati[i]
                //printf("%g\n",dati[i]);
                dati_engine[i]=dati[i];
                //printf("%g\n",dati_engine[i]);
                i++;
            }
        }
    }
    fclose(fp);


    fp2=fopen("engine.verifica.txt","w");

    if (fp2==NULL)
        {
        printf("Errore nell'apertura del file engine.verifica");
        return 2;
    }


    fprintf(fp2,"Potenza massima a quota 0:\t\t   %g\n",dati_engine[0]);
    fprintf(fp2,"Esponente variazione potenza con la quota: %g\n",dati_engine[1]);
    fprintf(fp2,"rpm minimo:\t\t\t\t   %g\n",dati_engine[2]);
    fprintf(fp2,"rpm massimo:\t\t\t\t   %g\n",dati_engine[3]);
    fprintf(fp2,"Rmeccanico della trasmissione:\t\t   %g\n",dati_engine[4]);
    fprintf(fp2,"Consumo specifico:\t\t\t   %g\n",dati_engine[5]);


    fclose(fp2);

    return 0;
}


#endif // LETTURA_ENGINE_H_INCLUDED
