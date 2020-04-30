#ifndef LETTURA_PROPELLER_H_INCLUDED
#define LETTURA_PROPELLER_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "variabili.h"

//***********************   LETTURA PROPELLER.TXT   ***********************//

void lettura_propeller()
{
//definizione delle variabili
char stringa [80]; //prendo una stringa di 80 elementi per scorrere le righe del file
double datipropeller[11];
int i,j,k; //variabili per i cicli
//
//***apertura file propeller.txt***
//
FILE *fp;
FILE *fpout;

//controllo sull'apertura
if ((fp=fopen("propeller.txt","r"))==NULL){
        printf("errore apertura file propeller\n");
        exit (1);
   }

i=0;j=0;
//faccio un while per scorrere il file fino all'ultima riga
while(fgets(stringa,80,fp)!=NULL){

    switch(stringa[0]){
		case'*'://se il primo elemennto della nuova riga è un '*' allora esco
            break;
        case' '://se il primo elemennto della nuova riga è uno spazio allora esco
            break;
        default://in caso non abbiamo nè '*' nè ' ' allora comincio a leggere le righe
            if (i<11){
                sscanf(stringa,"%lf",&datipropeller[i]); //per i primi 11 dati prendo le caratteristiche
                i++;
            }
            else if(isdigit(stringa[0])&& j<60){ //con isdigit mi chiedo se il primo elemento della stringa sia una cifra o un meno
                sscanf(stringa,"%lf %lf %lf %lf ",&csi[j], &rd[j], &chad[j],&ba[j]);
                j++;
            }
            break;
        }
}

fclose(fp);//chiusura file

//leggiamo il file propeller_verificalettura.txt per vedere se i dati sono stati salvati
if ((fpout=fopen("propeller_verificalettura.txt","w"))==NULL){
    printf("errore verifica lettura file propeller\n");
    exit (2);
   }
//riscrivo i valori del vettore caratteristiche non i loro veri nomi
diametro=datipropeller[0];
diametro_ogiva=datipropeller[1];
num_pale=datipropeller[2];
inerzia=datipropeller[3];
stazioni=datipropeller[4];
Clalfa=datipropeller[5];
Cl0=datipropeller[6];
a0=datipropeller[7];
Cdalfa2=datipropeller[8];
Cdalfa=datipropeller[9];
Cd0=datipropeller[10];
//scriviamo sul file propeller_verificalettura.txt
fprintf(fpout,"**************************************\nverifica di lettura file propeller.txt\n**************************************\n");
fprintf(fpout,"%.0lf \t\tdiametro [m]\n%3.1lf \t\tdiametro ogiva [m]\n%.0lf \t\tnumero di pale\n%5.3lf \t\tinerzia[kgm^2]\n%.0lf\t\tnumero di stazioni\n",diametro,diametro_ogiva,num_pale,inerzia,stazioni);
fprintf(fpout,"**************************************\nProfilo\n**************************************\n");
fprintf(fpout,"%8.6lf \tClalfa[rad^-1]\n%6.4lf \t\tCl0\n%11.8lf \ta0 [rad]\n%6.4lf \t\tCdalfa2 [rad^-2]\n%5.3lf \t\tCdalfa[rad^-1]\n%6.4lf \t\tCd0",Clalfa,Cl0,a0,Cdalfa2,Cdalfa,Cd0);
fprintf(fpout,"\n\n**************************************\nCaratteristiche dell'elica\n**************************************\n\n");
fprintf(fpout,"CSI   RD[m] CH AD  BA[deg]\n");

for(k=0;k<j;k++)
    fprintf(fpout,"%4.2lf  %4.2lf  %5.3lf  %6.3lf\n",csi[k],rd[k],chad[k],ba[k]);
    fprintf(fpout,"**************************************\n");

fclose(fpout);

    return 0;
}


#endif // LETTURA_PROPELLER_H_INCLUDED
